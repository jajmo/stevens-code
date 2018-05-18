#lang eopl

;;;;;;;;;;;;;;;;;;;;;;;;;
;      Jason Ajmo       ;
;      Homework 3       ;
;I pledge my honor that ;
; I have abided by the  ;
; Stevens Honor System. ;
;;;;;;;;;;;;;;;;;;;;;;;;;

; 2.4
; top and empty-stack? are observers
; empty-stack, push, and pop are constructors

; Specifications:
; (empty-stack) = [stk]
; (push elem [stk]) = [(cons elem [stk])]
; (pop [stk]) = [(cdr stk)]
; (top [stk]) = [(car stk)]
; (empty-stack? [stk]) = bool?

; 2.5

; Get an empty environment
; empty-env: () -> '()
(define empty-env
  (lambda ()
    '()))

; Add a pair to an environment
; extend-env: symbol? x SchemeVal x list? -> list?
(define extend-env
  (lambda (sym val env)
    (cons (cons sym val) env)))

; Get the value represented by the symbol
; apply-env: env x symbol? -> SchemeVal
(define apply-env
  (lambda (env search)
    (cond
      [(eqv? env (empty-env)) (report-no-binding-found search)]
      [(eqv? (caar env) search) (cdr (car env))]
      [else (apply-env (cdr env) search)])))

; Report that an element doesn't exist
; report-no-binding-found: SchemeVal
(define report-no-binding-found
  (lambda (search)
    (eopl:error "No binding found for" search)))

; 2.8
; Check if an environment is empty
; empty-env?: env -> bool?
(define empty-env?
  (lambda (env)
    (if (eqv? env (empty-env))
        #t
        #f)))

; 2.9
; Check if a variable has a binding
; has-binding? env SchemeVal -> bool?
(define has-binding?
  (lambda (env s)
    (cond [(empty-env? env) #f]
          [(eqv? s (caar env)) #t]
          [else (has-binding? (cdr env) s)])))

; 2.10
; Add a list of variables and values to an environment
; extend-env*: list? x list? x env -> env
(define extend-env*
  (lambda (values vars env)
    (if (null? values)
        env
        (extend-env* (cdr values) (cdr vars) (extend-env (car vars) (car values) env)))))

; 2.12

; Get an empty stack
; empty-stack: () -> '()
(define proc-empty-stack
  (lambda ()
    '()))

; Apply a command to a stack
; apply-cmd: SchemeVal x list? -> list?
(define apply-cmd
  (lambda (cmd stack)
    (cond [(eqv? cmd 'top) (car stack)]
          [(eqv? cmd 'pop) (cdr stack)]
          [else (proc-empty-stack)])))

; Push to the stack
; push: SchemeVal x list? -> list?
(define proc-push
  (lambda (val stack)
    (cons val stack)))

; Pop the top of the stack
; pop: list? -> list?
(define proc-pop
  (lambda (stack)
    (apply-cmd 'pop stack)))

; Get the top of the stack
; top: list? -> SchemeVal
(define proc-top
  (lambda (stack)
    (apply-cmd 'top stack)))

; Check if the stack is empty
; empty-stack?: list? -> bool?
(define proc-empty-stack?
  (lambda (stack)
    (if (eq? stack (proc-empty-stack))
        #t
        #f)))

; 2.24

; Binary tree datatype, copy and pasted from book
(define-datatype bintree bintree?
  (leaf-node
   (num integer?))
  (interior-node
   (key symbol?)
   (left bintree?)
   (right bintree?)))

; Convert a binary tree to a list
; bintree-to-list: bintree? -> list?
(define bintree-to-list
  (lambda (tree)
    (cases bintree tree
      (leaf-node (num)
        (list 'leaf-node num))
      (interior-node (key left right)
        (list 'interior-node key (bintree-to-list left) (bintree-to-list right))))))
    
    
