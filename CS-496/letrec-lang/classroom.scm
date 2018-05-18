#lang eopl

;; LETREC language classroom examples

(require "environments.scm")
(require "data-structures.scm")  ; for expval constructors
(require "lang.scm")             ; for scan&parse
(require "interp.scm")           ; for value-of-program
 
;; run : string -> val
(define run
  (lambda (string)
    (expval->scheme-val (value-of-program (scan&parse string)))))

;; LET
(define exp1 "-(44,33)" ) 
(define exp2 "-(-(44,33),22)" ) 
(define exp3 "-(55, -(22,11))" )
(define exp4 "-(x,1)" )           ;; why ok?
(define exp5 "-(foo,1)" ) 
(define exp6 "if zero?(0) then 3 else 4" )
(define exp7 "if zero?(1) then 3 else 4" )
(define exp8 "if zero?(-(11, 11)) then 3 else foo" )  ;; not eval untaken branch

(define exp9 "let x = 3 in x" ) 
(define exp10 "let x = 3 in -(x,1)" ) 
(define exp11 "let x = -(4,1) in -(x,1)" )
(define exp12 "let x = 3 in let y = 4 in -(x,y)" )
(define exp13 "let x = 3 in let x = 4 in x" ) 
(define exp14 "let x = 3 in let x = -(x,1) in x" )

;; PROC

(define exp15 "let f = proc (x) -(x,11)
               in (f (f 77))" )

(define exp16 "( proc (f) (f (f 77))
                 proc (x) -(x,11) )" )

(define exp17  
"let x = 200
 in let f = proc (z) -(z,x)
    in let x = 100
       in let g = proc (z) -(z,x)
          in -((f 1), (g 1))" )

;; LETREC 

(define lr1 "letrec f(x) = -(x,1) in (f 33)") 
(define lr2 "letrec f(x) = if zero?(x)  then 0 else -((f -(x,1)), -2) in (f 4)") ;; double

(define lr3 "let m = -5 in letrec f(x) = if zero?(x) then 0 else -((f -(x,1)), m) in (f 4)") 

;; (define fact-of-6  "letrec fact(x) = if zero?(x) then 1 else mult(x, (fact sub1(x)))
;;                     in (fact 6)")

(define lr4      ;; higher order nested letrecs       
        "letrec even(odd) = proc(x) if zero?(x) then 1 else (odd -(x,1))
         in letrec  odd(x)  = if zero?(x) then 0 else ((even odd) -(x,1))
         in (odd 13)")
