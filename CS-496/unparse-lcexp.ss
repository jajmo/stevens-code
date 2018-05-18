#lang eopl

(define-datatype lcexp lcexp?
  (var-exp 
   (name symbol?))
  (lam-exp 
   (par symbol?) 
   (body lcexp?))
  (app-exp 
   (operator lcexp?) 
   (operand lcexp?)))

(define unparse-lc-exp
  (lambda (exp)
    (cases lcexp exp
      (var-exp (name)
        (cons 'lambda (unparse-lc-exp (cdr exp))))
      (lam-exp (par body)
        (cons '(par) (unparse-lc-exp (cdr body))))
      (app-exp (operator operand)
        (cons '(operator (car operand) (caar operand)))))))