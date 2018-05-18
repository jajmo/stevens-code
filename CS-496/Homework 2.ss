#lang eopl

;;;;;;;;;;;;;;;;;;;;;;;;;
;      Jason Ajmo       ;
;      Homework 2       ;
;I pledge my honor that ;
; I have abided by the  ;
; Stevens Honor System. ;
;;;;;;;;;;;;;;;;;;;;;;;;;

; 1.17
; (down lst) wraps parentheses around the top level elements of lst
; lst: ListOf(SchemeVal) -> ListOf(SchemeVal)
(define down
  (lambda (lst)
    (if (null? lst)
         '()
         (cons (list (car lst)) (down (cdr lst))))))
        
; 1.18
; (swapper s1 s2 slist) replace instances of s1 with s2, and s2 with s1 in slist
; swapper: symbol? * symbol? * ListOf(SchemeVal) -> ListOf(SchemeVal)
(define swapper
  (lambda (s1 s2 slist)
    (cond [(null? slist) '()]
          [(symbol? (car slist))
             (cond [(eqv? (car slist) s1)
                   (cons s2 (swapper s1 s2 (cdr slist)))]
                   [(eqv? (car slist) s2)
                   (cons s1 (swapper s1 s2 (cdr slist)))]
                   [else (cons (car slist) 
                               (swapper s1 s2 (cdr slist)))])]
          [else (cons (swapper s1 s2 (car slist)) 
                      (swapper s1 s2 (cdr slist)))])))

; 1.19
; (list-set lst n x) returns lst, except the n-th element is x
; list-set: ListOf(SchemeVal) * number? * ListOf(SchemeVal) -> ListOf(SchemeVal)
(define list-set
  (lambda (lst n x)
    (cond [(null? lst) '()]
          [(eqv? 0 n) (cons x (cdr lst))]
          [else (cons (car lst) (list-set (cdr lst) (- n 1) x))])))

; 1.24
; (every? pred lst) returns #t if every element of lst satisifies pred, #f otherwise
; ever?: procedure? * ListOf(SchemeVal) -> boolean?
(define every?
  (lambda (pred lst)
    (cond [(null? lst) #t]
          [(not (pred (car lst))) #f]
          [else (every? pred (cdr lst))])))

; 1.27
; (flatten slist) removes all inner parenthes from slist
; flatten: ListOf(SchemeVal) -> ListOf(SchemeVal)
(define flatten
  (lambda (slist)
    (cond [(null? slist) '()]
          [(list? (car slist)) (append (flatten (car slist)) (flatten (cdr slist)))]
          [else (cons (car slist) (flatten (cdr slist)))])))
                 