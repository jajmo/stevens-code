#lang eopl

; Create a list
'(a b)
(list 'a 'b)

; Data types
"this is a string"
"this is an escaped \" quote" ; Abstract values
(display "a string with a quote \" in it") ; Note the output difference (display form)

; A procedure
(define silly
  (lambda (x y) (+ x y)))
(silly 2 2) ; 4

; Another procedure
(lambda (x) x)

(eqv? "hi" "hi") ; true

; Pairs
(cons 'a 'b)

; List
(cons 1 (cons 2 (cons 3 '())))

; count-ifs
(define count-ifs
  (lambda (stmt)
    (cond [(eq? (car stmt 'if) (+ 1 (count-ifs (cadddr stmt))))]