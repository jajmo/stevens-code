#lang eopl

  ;; grammar for the CHECKED language
  
  (provide (all-defined-out)) ; change from all-defined, for Racket 5.3.3

  ;;;;;;;;;;;;;;;; grammatical specification ;;;;;;;;;;;;;;;;
  
  (define the-lexical-spec
    '((whitespace (whitespace) skip)
      (comment ("%" (arbno (not #\newline))) skip)
      (identifier
       (letter (arbno (or letter digit "_" "-" "?")))
       symbol)
      (number (digit (arbno digit)) number)
      (number ("-" digit (arbno digit)) number)
      ))
  
  (define the-grammar
    '((program (expression) a-program)

      (expression (number) const-exp)
      (expression
        ("-" "(" expression "," expression ")")
        diff-exp)
      
      (expression
       ("zero?" "(" expression ")")
       zero?-exp)

      (expression
       ("if" expression "then" expression "else" expression)
       if-exp)

      (expression (identifier) var-exp)

      (expression
       ("let" identifier "=" expression "in" expression)
       let-exp)   

      (expression
       ("proc" "(" identifier ":" type ")" expression)
       proc-exp)
      
      (expression
       ("pair" "(" expression "," expression ")")
       pair-exp)
      
      (expression
       ("unpair" "(" identifier identifier expression expression ")")
       unpair-exp)

      (expression
       ("(" expression expression ")")
       call-exp)

      (expression
        ("letrec"
          type identifier "(" identifier ":" type ")" "=" expression
           "in" expression)
        letrec-exp)

      (type
       ("int")
       int-type)
      
      (type
       ("bool")
       bool-type)
      
      (type
       ("(" type "->" type ")")
       proc-type)
      
      (type
       ("pairof" type type)
       pairof-type)
      
      ))

  ;;;;;;;;;;;;;;;; sllgen boilerplate ;;;;;;;;;;;;;;;;
  
  (sllgen:make-define-datatypes the-lexical-spec the-grammar)
  
  (define show-the-datatypes
    (lambda () (sllgen:list-define-datatypes the-lexical-spec the-grammar)))
  
  (define scan&parse
    (sllgen:make-string-parser the-lexical-spec the-grammar))
  
  (define just-scan
    (sllgen:make-string-scanner the-lexical-spec the-grammar))
  
;;;;;;;;;;;;;;;; type-to-external-form ;;;;;;;;;;;;;;;;

  ;; type-to-external-form : Type -> List
  ;; Page: 243
  (define type-to-external-form
    (lambda (ty)
      (cases type ty
        (int-type () 'int)
        (bool-type () 'bool)
        (proc-type (arg-type result-type)
          (list
            (type-to-external-form arg-type)
            '->
            (type-to-external-form result-type)))
        (pairof-type (t1 t2)
          (list
            (type-to-external-form t1)
            '*
            (type-to-external-form t2))))))


