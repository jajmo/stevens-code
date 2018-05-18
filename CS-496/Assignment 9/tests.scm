#lang eopl
  
 ;; CHECKED language tests

 (require rackunit 
			 rackunit/text-ui)
 (require "environments.scm")
 (require "data-structures.scm")  ; for expval constructors
 (require "lang.scm")             ; for scan&parse
 (require "interp.scm")           ; for value-of-program
 (require "checker.scm")          ; for check

 ;; predicate to test exceptions
 ;; exn? : any -> bool
 (define exn? (lambda (exn) #t))

 ;; run : String -> ExpVal
 (define run
	(lambda (string)
	  (expval->scheme-val (value-of-program (scan&parse string)))))

 ;; tcheck : String -> Type     (renamed from EOPL code to avoid conflict with rackunit)
  (define tcheck
    (lambda (string)
      (type-to-external-form
        (type-of-program (scan&parse string)))))

 ;;;;;;;; tests ;;;;;;;;;;

 (define tests-for-tcheck
	(test-suite
	 "tests for CHECKED language, type check"

 ;; simple arithmetic
 (check-equal? (tcheck "11") 'int "positive-const")
 (check-equal? (tcheck "-33") 'int "negative-const")
 (check-equal? (tcheck "-(44,33)") 'int "simple-arith-1")

 ;; nested arithmetic
 (check-equal? (tcheck "-(-(44,33),22)") 'int "nested-arith-left")
 (check-equal? (tcheck "-(55, -(22,11))") 'int "nested-arith-right")

 ;; simple variables
 (check-equal? (tcheck "x") 'int "test-var-1")
 (check-equal? (tcheck "-(x,1)") 'int "test-var-2")
 (check-equal? (tcheck "-(1,x)") 'int "test-var-3")

 (check-equal? (tcheck "zero?(-(3,2))") 'bool "zero-test-1")

 (check-exn exn? (lambda () 
    (tcheck "-(2,zero?(0))")) "zero-test-2")

 ;; simple unbound variables
 (check-exn exn? (lambda () 
   (tcheck "foo")) "test-unbound-var-1")

 (check-exn exn? (lambda () 
   (tcheck "-(x,foo)")) "test-unbound-var-2")

 ;; simple conditionals
 (check-equal? (tcheck "if zero?(1) then 3 else 4") 'int "if-true")
 (check-equal? (tcheck "if zero?(0) then 3 else 4") 'int "if-false")

 ;; make sure that the test and both arms get evaluated properly. 
 (check-equal? (tcheck "if zero?(-(11,12)) then 3 else 4") 'int "if-eval-test-true")
 (check-equal? (tcheck "if zero?(-(11, 11)) then 3 else 4") 'int "if-eval-test-false")
 (check-equal? (tcheck "if zero?(1) then -(22,1) else -(22,2)") 'int "if-eval-then")
 (check-equal? (tcheck "if zero?(0) then -(22,1) else -(22,2)") 'int "if-eval-else")

 ;; make sure types of arms agree (new for lang5-1)
 (check-exn exn? (lambda () 
   (tcheck "if zero?(0) then 1 else zero?(1)")) "if-compare-arms")

 (check-exn exn? (lambda () 
   (tcheck "if 1 then 11 else 12"))  "if-check-test-is-boolean")

 ;; simple let
 (check-equal? (tcheck "let x = 3 in x") 'int "simple-let-1")

 ;; make sure the body and rhs get evaluated
 (check-equal? (tcheck "let x = 3 in -(x,1)") 'int "eval-let-body")
 (check-equal? (tcheck "let x = -(4,1) in -(x,1)") 'int "eval-let-rhs")

 ;; check nested let and shadowing
 (check-equal? (tcheck "let x = 3 in let y = 4 in -(x,y)") 'int "simple-nested-let")
 (check-equal? (tcheck "let x = 3 in let x = 4 in x") 'int "check-shadowing-in-body")
 (check-equal? (tcheck "let x = 3 in let x = -(x,1) in x") 'int "check-shadowing-in-rhs")

 ;; simple applications
 (check-equal? (tcheck "(proc(x : int) -(x,1)  30)") 'int "apply-proc-in-rator-pos")

 (check-exn exn? (lambda () 
    (tcheck "(proc(x : (int -> int)) -(x,1)  30)"))
  "checker-doesnt-ignore-type-info-in-proc")

 (check-equal? (tcheck "let f = proc (x : int) -(x,1) in (f 30)") 'int "apply-simple-proc")
 (check-equal? (tcheck "(proc(f : (int -> int))(f 30)  proc(x : int)-(x,1))") 'int "let-to-proc-1")
 (check-equal? (tcheck "((proc (x : int) proc (y : int) -(x,y)  5) 6)") 'int "nested-procs")
 (check-equal?
  (tcheck "let f = proc (x : int) proc (y : int) -(x,y) in ((f -(10,5)) 3)")
  'int "nested-procs2")

 ;; simple letrecs
 (check-equal? (tcheck "letrec int f(x : int) = -(x,1) in (f 33)") 'int "simple-letrec-1")

 (check-equal?
  (tcheck "letrec int f(x : int) = if zero?(x) then 0 else -((f -(x,1)), -2) in (f 4)")
  'int "simple-letrec-2")

 (check-equal?
  (tcheck
   "let m = -5 
    in letrec int f(x : int) = if zero?(x) then -((f -(x,1)), m) else 0 in (f 4)")
  'int "simple-letrec-3")

 (check-equal?
  (tcheck
   "letrec int double (n : int) = if zero?(n) then 0 
                                  else -( (double -(n,1)), -2) 
    in (double 3)")
  'int "double-it")

 ;; tests of expressions that produce procedures
 (check-equal? (tcheck "proc (x : int) -(x,1)") '(int -> int) "build-a-proc-typed")

 (check-equal? (tcheck "proc (x : int) zero?(-(x,1))") '(int -> bool) "build-a-proc-typed-2")

 (check-equal? (tcheck "let f = proc (x : int) -(x,1) in (f 4)") 'int "bind-a-proc-typed")

 (check-equal? (tcheck "let f = proc (x : int) -(x,1) in f") '(int -> int) "bind-a-proc-return-proc")

 (check-equal? (tcheck "proc(f : (int -> bool)) (f 3)") '((int -> bool) -> bool) "type-a-ho-proc-1")

  (check-exn exn? (lambda () (tcheck "proc(f : (bool -> bool)) (f 3)") ) "type-a-ho-proc-2")

 (check-equal?
  (tcheck "proc (x : int) proc (f : (int -> bool)) (f x)")
  '(int -> ((int -> bool) -> bool))
  "apply-a-ho-proc")

 (check-equal?
  (tcheck "proc (x : int) proc (f : (int -> (int -> bool))) (f x)")
  '(int -> ((int -> (int -> bool)) -> (int -> bool)))
  "apply-a-ho-proc-2")

  (check-exn exn? (lambda () 
    (tcheck "proc (x : int) proc (f : (int -> (int -> bool))) (f zero?(x))"))
   "apply-a-ho-proc-3")

 (check-equal? (tcheck "((proc(x : int) proc (y : int)-(x,y)  4) 3)") 'int "apply-curried-proc")

 (check-equal? (tcheck "(proc (x : int) -(x,1) 4)") 'int "apply-a-proc-2-typed")

 (check-equal? (tcheck "letrec int f(x : int) = -(x,1)
                        in (f 40)") 'int "apply-a-letrec")

 (check-equal?
  (tcheck 
   "(proc (x : int)
      letrec bool loop(x : bool) =(loop x)
       in x
     1)") 
  'int "letrec-non-shadowing")

 (check-equal?
  (tcheck "
let times = proc (x : int) proc (y : int) -(x,y)    % not really times
in letrec 
     int fact(x : int) = if zero?(x) then 1 else ((times x) (fact -(x,1)))
   in fact")
  '(int -> int) "letrec-return-fact")

 (check-equal?
  (tcheck "
let times = proc (x : int) proc (y : int) -(x,y)    % not really times
in letrec 
     int fact(x : int) = if zero?(x) then 1 else ((times x) (fact -(x,1)))
   in (fact 4)") 
  'int "letrec-apply-fact")

))

(define tests-for-run
	(test-suite
	 "tests for CHECKED language, run"

 (check-equal? (run "11") 11 "positive-const")
 (check-equal? (run "-33") -33 "negative-const")
 (check-equal? (run "-(44,33)") 11 "simple-arith-1")

 ;; nested arithmetic
 (check-equal? (run "-(-(44,33),22)") -11 "nested-arith-left")
 (check-equal? (run "-(55, -(22,11))") 44 "nested-arith-right")

 ;; simple variables
 (check-equal? (run "x") 10 "test-var-1")
 (check-equal? (run "-(x,1)") 9 "test-var-2")
 (check-equal? (run "-(1,x)") -9 "test-var-3")

 ;; simple unbound variables
 (check-exn exn? (lambda () 
   (run "foo"))  "test-unbound-var-1")

 (check-exn exn? (lambda () 
   (run "-(x,foo)")) "test-unbound-var-2")

 ;; simple conditionals
 (check-equal? (run "if zero?(0) then 3 else 4") 3 "if-true")
 (check-equal? (run "if zero?(1) then 3 else 4") 4 "if-false")

 ;; test dynamic typechecking
 (check-exn exn? (lambda () 
  (run "-(zero?(0),1)"))"no-bool-to-diff-1")

 (check-exn exn? (lambda () 
  (run "-(1,zero?(0))")) "no-bool-to-diff-2")
 (check-exn exn? (lambda () 
  (run "if 1 then 2 else 3")) "no-int-to-if")

 ;; make sure that the test and both arms get evaluated properly. 
 (check-equal? (run "if zero?(-(11,11)) then 3 else 4") 3 "if-eval-test-true")
 (check-equal? (run "if zero?(-(11, 12)) then 3 else 4") 4 "if-eval-test-false")

 ;; and make sure the other arm doesn't get evaluated.
 (check-equal? (run "if zero?(-(11, 11)) then 3 else foo") 3 "if-eval-test-true-2")
 (check-equal? (run "if zero?(-(11,12)) then foo else 4") 4 "if-eval-test-false-2")

 ;; simple let
 (check-equal? (run "let x = 3 in x") 3 "simple-let-1")

 ;; make sure the body and rhs get evaluated
 (check-equal? (run "let x = 3 in -(x,1)") 2 "eval-let-body")
 (check-equal? (run "let x = -(4,1) in -(x,1)") 2 "eval-let-rhs")

 ;; check nested let and shadowing
 (check-equal? (run "let x = 3 in let y = 4 in -(x,y)") -1 "simple-nested-let")
 (check-equal? (run "let x = 3 in let x = 4 in x") 4 "check-shadowing-in-body")
 (check-equal? (run "let x = 3 in let x = -(x,1) in x") 2 "check-shadowing-in-rhs")

 ;; simple applications
 (check-equal? (run "(proc(x : int) -(x,1)  30)") 29 "apply-proc-in-rator-pos")
 (check-equal? (run "(proc(x : (int -> int)) -(x,1)  30)") 29 "interp-ignores-type-info-in-proc")
 (check-equal? (run "let f = proc (x : int) -(x,1) in (f 30)") 29 "apply-simple-proc")
 (check-equal? (run "(proc(f : (int -> int))(f 30)  proc(x : int)-(x,1))") 29 "let-to-proc-1")
 (check-equal? (run "((proc (x : int) proc (y : int) -(x,y)  5) 6)") -1 "nested-procs")
 (check-equal?
  (run "let f = proc(x : int) proc (y : int) -(x,y) in ((f -(10,5)) 6)")
  -1
  "nested-procs2")

 (check-equal?
  (run "
let fix =  proc (f : bool)
            let d = proc (x : bool) proc (z : bool) ((f (x x)) z)
            in proc (n : bool) ((f (d d)) n)
in let
    t4m = proc (f : bool) proc(x : bool) if zero?(x) then 0 else -((f -(x,1)),-4)
in let times4 = (fix t4m)
   in (times4 3)") 
  12
  "y-combinator-1")

 ;; simple letrecs
 (check-equal? (run "letrec int f(x : int) = -(x,1) in (f 33)") 32 "simple-letrec-1")

 (check-equal?
  (run "letrec int f(x : int) = if zero?(x)  then 0 else -((f -(x,1)), -2) in (f 4)")
  8
  "simple-letrec-2")

 (check-equal?
  (run "let m = -5 
        in letrec int f(x : int) = if zero?(x) then 0 else -((f -(x,1)), m) in (f 4)")
  20
  "simple-letrec-3")

 (check-equal?
  (run
  "letrec int even(odd : (int -> int))  = proc(x : int) if zero?(x) then 1 else (odd -(x,1))
   in letrec  int odd(x : int)  = if zero?(x) then 0 else ((even odd) -(x,1))
      in (odd 13)")
  1
  "HO-nested-letrecs")

 ))

(run-tests tests-for-tcheck 'verbose)

(run-tests tests-for-run 'verbose)


