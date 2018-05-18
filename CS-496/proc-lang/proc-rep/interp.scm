#lang eopl
  
  ;; interpreter for the PROC language, using the procedural
  ;; representation of procedures.

  (require "lang.scm")
  (require "data-structures.scm")
  (require "environments.scm")

  (provide value-of-program value-of)

;;;;;;;;;;;;;;;; the interpreter ;;;;;;;;;;;;;;;;

  ;; value-of-program : Program -> ExpVal
  (define value-of-program 
    (lambda (pgm)
      (cases program pgm
        (a-program (exp1)
          (value-of exp1 (init-env))))))

  ;; value-of : Exp * Env -> ExpVal
  (define value-of
    (lambda (exp env)
      (cases expression exp

        (const-exp (num) (num-val num))

        (var-exp (var) (apply-env env var))

        (diff-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (- num1 num2)))))

        (zero?-exp (exp1)
          (let ((val1 (value-of exp1 env)))
            (let ((num1 (expval->num val1)))
              (if (zero? num1)
                (bool-val #t)
                (bool-val #f)))))
              
        (if-exp (exp1 exp2 exp3)
          (let ((val1 (value-of exp1 env)))
            (if (expval->bool val1)
              (value-of exp2 env)
              (value-of exp3 env))))

        (let-exp (var exp1 body)       
          (let ((val1 (value-of exp1 env)))
            (value-of body
              (extend-env var val1 env))))
        
        (proc-exp (var body)
          (proc-val (procedure var body env #f)))

        (call-exp (rator rand)
          (let ((proc (expval->proc (value-of rator env)))
                (arg (value-of rand env)))
            (apply-procedure proc arg)))
        
        (list-exp (lst)
          (list-val (map (apply-elem env) lst)))
        
        (cond-exp (conds acts)
          (cond-val conds acts env))
        
        (traceproc-exp (var body)
          (proc-val (procedure var body env #t)))
            
        )))
  
  ;; value-of-trace : Exp * Env -> ExpVal
  ;; Prints out trace messages
  (define value-of-trace
    (lambda (exp env)
      (cases expression exp

        (const-exp (num) 
                   (begin
                     (display "Evaluating a constant expression")
                     (newline)
                     (num-val num)))
                      
        (var-exp (var) 
                 (begin
                   (display "Evaluating a var expression")
                   (newline)
                   (apply-env env var)))

        (diff-exp (exp1 exp2)
          (let ((val1 (value-of-trace exp1 env))
                (val2 (value-of-trace exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (begin
                (display "Calculating the difference between ")
                (display num1)
                (display " and ")
                (display num2)
                (newline)
              (let ((result (num-val (- num1 num2))))
                (display "The result is ")
                (display (expval->num result))
                (newline)
                result)))))

        (zero?-exp (exp1)
          (let ((val1 (value-of-trace exp1 env)))
            (let ((num1 (expval->num val1)))
              (begin
                (display "Evaluating if ")
                (display num1)
                (display " is zero")
                (newline)
                (display num1)
                (display " is ")
                (if (zero? num1)
                    (begin
                      (display "zero")
                      (newline)
                      (bool-val #t))
                    (begin
                      (display "not zero")
                      (newline)
                      (bool-val #f)))))))
              
        (if-exp (exp1 exp2 exp3)
          (let ((val1 (value-of-trace exp1 env)))
            (begin
              (display "Evaluating if statement")
              (newline)
              (display "If statement evaluates to ")
              (if (expval->bool val1)
                  (begin
                    (display "true")
                    (newline)
                    (value-of-trace exp2 env))
                  (begin
                    (display "false")
                    (newline)
                    (value-of-trace exp3 env))))))

        (let-exp (var exp1 body)       
          (let ((val1 (value-of-trace exp1 env)))
            (begin
              (display "Setting ")
              (display var)
              (display " equal to ")
              (display val1)
              (newline)
              (value-of-trace body
                 (extend-env var val1 env)))))
        
        (proc-exp (var body)
          (begin
            (display "Evaluating procedure")
            (newline)
            (proc-val (procedure var body env #f))))

        (call-exp (rator rand)
          (begin
            (display "Evaluating call expression")
            (newline)
            (let ((proc (expval->proc (value-of rator env)))
                  (arg (value-of-trace rand env)))
              (apply-procedure proc arg))))
        
        (list-exp (lst)
          (begin
            (display "Evaluating list expression")
            (newline)
            (list-val (map (apply-elem env) lst))))
        
        (cond-exp (conds acts)
          (begin
            (display "Evaluating condition expression")
            (newline)
            (cond-val conds acts env)))
        
        (traceproc-exp (var body)
          (begin
            (display "Evaluating traceproc expression")
            (newline)
            (proc-val (procedure var body env #t))))
            
        )))
  
  ;; helper for list-exp
  ;; apply-elem : Env * ExpVal -> ExpVal
  (define apply-elem
    (lambda(env)
      (lambda(elem)
        (value-of elem env))))
  
  ;; helper for cond-exp
  ;; cond-val : ExpVal * ExpVal * Env -> Bool
  (define cond-val
    (lambda (conds acts env)
      (cond [(null? conds) (eopl:error "No conditions return #t")]
            [(expval->bool (value-of (car conds) env)) (value-of (car acts) env)]
            [else (cond-val (cdr conds) (cdr acts) env)])))


  ;; procedure : Var * Exp * Env -> Proc
  ;; Page: 79
  (define procedure
    (lambda (var body env trace)
      (lambda (val)
        (if trace
        (value-of-trace body (extend-env var val env))
        (value-of body (extend-env var val env))))))
  
  ;; apply-procedure : Proc * ExpVal -> ExpVal
  ;; Page: 79
  (define apply-procedure
    (lambda (proc val)
      (proc val)))


