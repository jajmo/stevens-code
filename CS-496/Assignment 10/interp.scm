#lang eopl
  
  (require "lang.scm")
  (require "data-structures.scm")
  (require "environments.scm")
  (require "store.scm")

  (provide value-of-program value-of)

;;;;;;;;;;;;;;;; the interpreter ;;;;;;;;;;;;;;;;

  ;; value-of-program : Program -> Expval
  (define value-of-program 
    (lambda (pgm)
      (initialize-store!)
      (cases program pgm
        (a-program (body)
          (value-of body (init-env))))))


  ;; value-of : Exp * Env -> ExpVal
  (define value-of
    (lambda (exp env)
      (cases expression exp

        (const-exp (num) (num-val num))

        (var-exp (var) (apply-env env var))

        (diff-exp (exp1 exp2)
          (let ((val1
		  (expval->num
		    (value-of exp1 env)))
                (val2
		  (expval->num
		    (value-of exp2 env))))
            (num-val
	      (- val1 val2))))
        
        (zero?-exp (exp1)
	  (let ((val1 (expval->num (value-of exp1 env))))
	    (if (zero? val1)
	      (bool-val #t)
	      (bool-val #f))))
        
        (newref-exp (exp1)
          (let ((val1 (value-of exp1 env)))
            (ref-val (newref val1))))
          
        (deref-exp (exp)
          (let ((val (value-of exp env)))
           (deref (expval->ref val))))
        
        (setref-exp (exp1 exp2)
          (let ((ref1 (expval->ref (value-of exp1 env)))
                 (val (value-of exp2 env)))
           (begin
             (setref! ref1 val)
             (num-val 1))))
        
        (begin-exp (exp1 exps)
          (letrec 
            ((value-of-begins
               (lambda (e1 es)
                 (let ((v1 (value-of e1 env)))
                   (if (null? es)
                     v1
                     (value-of-begins (car es) (cdr es)))))))
            (value-of-begins exp1 exps)))

        (if-exp (exp0 exp1 exp2) 
          (if (expval->bool (value-of exp0 env))
            (value-of exp1 env)
            (value-of exp2 env)))

        (let-exp (var exp1 body)       
          (let ((val (value-of exp1 env)))
            (value-of body
              (extend-env var val env))))

        (proc-exp (bvar ty body)
	  (proc-val
	    (procedure bvar body env)))

        (call-exp (rator rand)          
          (let ((proc (expval->proc (value-of rator env)))
                (arg  (value-of rand env)))
	    (apply-procedure proc arg)))

        (letrec-exp (ty1 p-name b-var ty2 p-body letrec-body)
          (value-of letrec-body
            (extend-env-rec p-name b-var p-body env)))

	    )))

  ;; apply-procedure : Proc * ExpVal -> ExpVal
  (define apply-procedure
    (lambda (proc1 arg)
      (cases proc proc1
        (procedure (var body saved-env)
          (value-of body (extend-env var arg saved-env))))))



  
