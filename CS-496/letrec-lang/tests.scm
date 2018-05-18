#lang eopl

;; LETREC language 

(require rackunit 
         rackunit/text-ui)
(require "environments.scm")
(require "data-structures.scm")  ; for expval constructors
(require "lang.scm")             ; for scan&parse
(require "interp.scm")           ; for value-of-program

;; predicate to test exceptions
;; exn? : any -> bool
(define exn? (lambda (exn) #t))
  
;; run : String -> ExpVal
(define run
  (lambda (string)
    (expval->scheme-val (value-of-program (scan&parse string)))))

(define letrec-tests  
  (test-suite
   "tests for LETREC language"

       ;; simple letrecs
      (check-equal? (run 
        "letrec f(x) = -(x,1) in (f 33)") 
        32 "simple-letrec-1")
      (check-equal? (run 
        "letrec f(x) = if zero?(x)  then 0 else -((f -(x,1)), -2) in (f 4)")  
         8 "simple-letrec-2")
      (check-equal? (run 
        "let m = -5 in letrec f(x) = if zero?(x) then 0 else -((f -(x,1)), m) in (f 4)") 
        20 "simple-letrec-3")

;; alas, no multiplication in this language.  Exercise: define
;; multiplication as a letrec and then use it to define factorial.
;;      (fact-of-6  "letrec
;;  fact(x) = if zero?(x) then 1 else *(x, (fact sub1(x)))
;;  in (fact 6)" 
;;                  720)

      ;; higher order nested letrecs       
      (check-equal? (run
        "letrec even(odd) = proc(x) if zero?(x) then 1 else (odd -(x,1))
         in letrec  odd(x)  = if zero?(x) then 0 else ((even odd) -(x,1))
         in (odd 13)")
         1
        "HO-nested-letrecs")
))

(define proc-tests     
  (test-suite
   "tests for PROC language"

    (check-equal? (run "(proc(x) -(x,1)  30)") 
                  29 "apply-proc-in-rator-pos")

    (check-equal? (run "let f = proc (x) -(x,1) in (f 30)") 
                  29 "apply-simple-proc")

    (check-equal? (run "(proc(f)(f 30)  proc(x)-(x,1))") 
                  29 "let-to-proc-1")

    (check-equal? (run "((proc (x) proc (y) -(x,y)  5) 6)") 
                  -1 "nested-procs")

    (check-equal? (run "let f = proc(x) proc (y) -(x,y) in ((f -(10,5)) 6)")
                  -1 "nested-procs2")

    (check-equal? (run "
let fix =  proc (f)
            let d = proc (x) proc (z) ((f (x x)) z)
            in proc (n) ((f (d d)) n)
in let
    t4m = proc (f) proc(x) if zero?(x) then 0 else -((f -(x,1)),-4)
in let times4 = (fix t4m)
   in (times4 3)" )
12 "y-combinator-1")

))


(define let-tests
  (test-suite
   "tests for LET Language"
   
   ;; simple arithmetic
   (check-equal? (run "11") 11 "positive const")
   (check-equal? (run "-33") -33 "negative const")
   (check-equal? (run "-(44,33)") 11 "simple arith")
   
   ;; nested arithmetic
   (check-equal? (run "-(-(44,33),22)") -11 "nested arith left")
   (check-equal? (run "-(55, -(22,11))") 44 "nested arith right")
   
   ;; simple variables
   (check-equal? (run "x") 10 "test var 1")
   (check-equal? (run "-(x,1)") 9 "test var 2")
   (check-equal? (run "-(1,x)") -9 "test var 3")
         
   ;; simple unbound variables
   (check-exn exn?
              (lambda () (run "foo"))
              "test-unbound-var-foo")
   (check-exn exn? 
              (lambda () (run "-(x,foo)"))
              "test-unbound-var-foo-subtraction")
     
   ;; simple conditionals
   (check-equal? (run "if zero?(0) then 3 else 4") 3 "if true")
   (check-equal? (run "if zero?(1) then 3 else 4") 4 "if false")
   
   ;; test dynamic typechecking
   ;(no-bool-to-diff-1 "-(zero?(0),1)" error)
   ;(no-bool-to-diff-2 "-(1,zero?(0))" error)
   ;(no-int-to-if "if 1 then 2 else 3" error)
   
   ;; make sure that the test and both arms get evaluated
   ;; properly. 
   (check-equal? 
    (run "if zero?(-(11,11)) then 3 else 4") 
    3 
    "if eval test true")
   (check-equal?
    (run "if zero?(-(11, 12)) then 3 else 4") 
    4 
    "if eval test false")
   
   ;; and make sure the other arm doesn't get evaluated.
   (check-equal?
    (run "if zero?(-(11, 11)) then 3 else foo")
    3
    "if eval test true 2")
   (check-equal?
    (run "if zero?(-(11,12)) then foo else 4")
    4
    "if evalue test false 2")
   
   ;; simple let
   (check-equal? (run "let x = 3 in x") 3 "simple-let-1")
   
   ;; make sure the body and rhs get evaluated
   (check-equal? (run "let x = 3 in -(x,1)") 2 "eval let body")
   (check-equal? (run "let x = -(4,1) in -(x,1)") 2 "eval let rhs")
   
   ;; check nested let and shadowing
   (check-equal? 
    (run "let x = 3 in let y = 4 in -(x,y)")
    -1 
    "simple nested let")
   (check-equal?
    (run "let x = 3 in let x = 4 in x") 
    4
    "check shadowing in body")
   (check-equal?
    (run "let x = 3 in let x = -(x,1) in x")
    2
    "check shadowing in rhs")
   
   ))

(run-tests let-tests 'verbose)

(run-tests proc-tests 'verbose)

(run-tests letrec-tests 'verbose)

;; (run-tests (append let-tests proc-tests letrec-tests) 'verbose