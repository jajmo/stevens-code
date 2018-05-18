#lang eopl

;;;;;;;;;;;;;;;;;;;;;;;;;
;      Jason Ajmo       ;
;      Homework 1       ;
;I pledge my honor that ;
; I have abided by the  ;
; Stevens Honor System. ;
;;;;;;;;;;;;;;;;;;;;;;;;;

;1.11:
;    The recursion is guarenteed to halt because
; every time the function recurses, it passes in
; the car and cdr to subst-in-s-exp and subst, 
; respectively, having it process a smaller list
; everytime until you have a list with single elements.

; 1.12
(define subst
  (lambda (new old slist)
    (if (null? slist)
        '()
        (cons
           (if (symbol? (car slist))
               (if (eqv? (car slist) old) new (car slist))
               (subst new old (car slist)))
         (subst new old (cdr slist))))))