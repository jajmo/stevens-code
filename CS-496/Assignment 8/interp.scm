#lang eopl

  ;; interpreter for the IMPLICIT-REFS language

  (require "lang.scm")
  (require "data-structures.scm")
  (require "environments.scm")
  (require "store.scm")
  
  (provide value-of-program value-of instrument-let instrument-newref)

  ;; show the contents of define-datatype values
  (print-struct #t)

  (require racket/pretty)
  ;(provide (all-from (lib "pretty.ss")))

;;;;;;;;;;;;;;;; switches for instrument-let ;;;;;;;;;;;;;;;;

  (define instrument-let (make-parameter #f))

  ;; say (instrument-let #t) to turn instrumentation on.
  ;;     (instrument-let #f) to turn it off again.

;;;;;;;;;;;;;;;; the interpreter ;;;;;;;;;;;;;;;;

  ;; value-of-program : Program -> ExpVal
  (define value-of-program 
    (lambda (pgm)
      (initialize-store!)
      (cases program pgm
        (a-program (stmt)
          (result-of stmt (init-env))))))

  ;; value-of : Exp * Env -> ExpVal
  ;; Page: 118, 119
  (define value-of
    (lambda (exp env)
      
      (cases expression exp

        (const-exp (num) (num-val num))
        (var-exp (var) (deref (apply-env env var)))
        
        (zero-exp (val)
          (let ((val1 (value-of val env)))
            (let ((num (expval->num val1)))
              (bool-val (zero? num)))))
        
        (not-exp (val)
          (let ((val1 (expval->bool (value-of val env))))
            (bool-val (not val1))))
        
        (prod-exp (exp1 exp2)
           (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (* num1 num2)))))
            

        (diff-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (- num1 num2)))))

        (plus-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (+ num1 num2)))))
        
        (proc-exp (var body)
          (proc-val (procedure var body env)))

        (call-exp (rator rand)
          (let ((proc (expval->proc (value-of rator env)))
                (arg (value-of rand env)))
            (apply-procedure proc arg)))

        (letrec-exp (p-names b-vars p-bodies letrec-body)
          (value-of letrec-body
            (extend-env-rec* p-names b-vars p-bodies env)))

        (begin-exp (exp1 exps)
          (letrec 
            ((value-of-begins
               (lambda (e1 es)
                 (let ((v1 (value-of e1 env)))
                   (if (null? es)
                     v1
                     (value-of-begins (car es) (cdr es)))))))
            (value-of-begins exp1 exps)))

        (assign-exp (var exp1)
          (begin
            (setref!
              (apply-env env var)
              (value-of exp1 env))
            (num-val 27)))

        )))
  
  (define result-of
    (lambda (exp env)
      (cases statement exp
        
        (assign-stmt (ident exp)
           (setref! (apply-env env ident) (value-of exp env)))
        
        (print-stmt (exp)
           (print-help (value-of exp env)))
        
        (list-of-stmt (statements)
           (value-of-stmts statements env))
        
        (if-stmt (cond then else)
           (let ((cond-val (value-of cond env)))
             (if (expval->bool cond-val)
                 (result-of then env)
                 (result-of else env))))
        
        (while-stmt (cond body)
           (execute-while cond body env))
        
        (var-stmt (identList exp)
           (result-of exp (extend-env* identList env))))))

  ;; Helper for the print statement
  ;; print-help : ExpVal -> Void
  (define print-help
    (lambda (val)
      (cases expval val
        (num-val (val) (display val) (newline))
        (bool-val (val) (display val) (newline))
        (proc-val (val) (display val) (newline))
        (ref-val (val) (eopl:error "Attempted to print a reference")))))
  
  ;; Execute multiple statements
  ;; value-of-stmts: : List * Env -> ExpVal
  (define value-of-stmts
    (lambda (statements env)
      (when (not (null? statements))
        (begin
          (result-of (car statements) env)
          (value-of-stmts (cdr statements) env)))))
  
  ;; Bind variables to an unitialized value
  ;; extend-env* : List * Env -> Env
  (define extend-env*
    (lambda (vars env)
      (if (null? vars)
          env
          (extend-env* (cdr vars) (extend-env (car vars) (newref (num-val 1)) env)))))
  
  ;; Execute a while loop
  ;; execute-while : ExpVal * ExpVal * Env -> ExpVal
  (define execute-while
    (lambda (cond body env)
      (let ((val (value-of cond env)))
        (when (expval->bool val)
           (begin
             (result-of body env)
             (execute-while cond body env))))))


  ;; apply-procedure : Proc * ExpVal -> ExpVal
  ;; Page: 119

  ;; uninstrumented version
  ;;  (define apply-procedure
  ;;    (lambda (proc1 val)
  ;;      (cases proc proc1
  ;;        (procedure (var body saved-env)
  ;;          (value-of body
  ;;            (extend-env var (newref val) saved-env))))))
  
  ;; instrumented version
  (define apply-procedure
    (lambda (proc1 arg)
      (cases proc proc1
        (procedure (var body saved-env)
          (let ((r (newref arg)))
            (let ((new-env (extend-env var r saved-env)))
              (when (instrument-let)
                (begin
                  (eopl:printf
                    "entering body of proc ~s with env =~%"
                    var)
                  (pretty-print (env->list new-env)) 
                  (eopl:printf "store =~%")
                  (pretty-print (store->readable (get-store-as-list)))
                  (eopl:printf "~%")))
              (value-of body new-env)))))))  

  ;; store->readable : Listof(List(Ref,Expval)) 
  ;;                    -> Listof(List(Ref,Something-Readable))
  (define store->readable
    (lambda (l)
      (map
        (lambda (p)
          (list
            (car p)
            (expval->printable (cadr p))))
        l)))


  


  
