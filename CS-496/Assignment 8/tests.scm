#lang eopl

;; tests for IMPLICIT-REFS

(require rackunit 
         rackunit/text-ui)
(require "environments.scm")
(require "data-structures.scm")  ; for expval constructors
(require "lang.scm")             ; for scan&parse
(require "interp.scm")           ; for value-of-program
(require "store.scm")            ; for value-of-program

;; predicate to test exceptions
;; exn? : any -> bool
(define exn? (lambda (exn) #t))
  
;; run : String -> ExpVal
(define run
  (lambda (string)
    (value-of-program (scan&parse string))))


