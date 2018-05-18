#lang eopl

(define-datatype lcexp lcexp?
  (var-exp (name symbol?))
  (lam-exp (par symbol?) (body lcexp?))
  (app-exp (operator lcexp?) (operand lcexp?)))

(define (numLam lcx)
  (cases lcexp lcx
    (var-exp (n) 0)
    (lam-exp (p b) (+ 1 (numLam b)))
    (app-exp (r x) (+ (numLam r) (numLam x)))))