#lang eopl

  ;; language for IMPLICIT-REFS

  (provide (all-defined-out))
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
    '((program (statement) a-program)

      (expression (number) const-exp)
      (expression (identifier) var-exp)
      
      (expression
        ("-" "(" expression "," expression ")")
        diff-exp)
      
      (expression
       ("+" "(" expression "," expression ")")
       plus-exp)
      
      (expression
       ("*" "(" expression "," expression ")")
       prod-exp)
      
      (expression
       ("zero?(" expression ")")
       zero-exp)
      
      (expression
       ("not(" expression ")")
       not-exp)
      
      (statement
       (identifier "=" expression)
       assign-stmt) 
      
      (statement
       ("print" expression)
       print-stmt)
      
      (statement
       ("{" (separated-list statement ";") "}")
       list-of-stmt)

      (statement
       ("if" expression statement statement)
       if-stmt)

      (statement
       ("while" expression statement)
       while-stmt)
      
      (statement
       ("var" (separated-list identifier ",") ";" statement)
       var-stmt)
      
      (expression (identifier) var-exp)  

      (expression
       ("proc" "(" identifier ")" expression)
       proc-exp)

      (expression
       ("(" expression expression ")")
       call-exp)

      (expression
        ("letrec"
          (arbno identifier "(" identifier ")" "=" expression)
           "in" expression)
        letrec-exp)
      
      (expression
        ("begin" expression (arbno ";" expression) "end")
        begin-exp)

      ;; new for implicit-refs

      (expression
        ("set" identifier "=" expression)
        assign-exp)

      ))

  ;;;;;;;;;;;;;;;; sllgen boilerplate ;;;;;;;;;;;;;;;;
  
  (sllgen:make-define-datatypes the-lexical-spec the-grammar)
  
  (define show-the-datatypes
    (lambda () (sllgen:list-define-datatypes the-lexical-spec the-grammar)))
  
  (define scan&parse
    (sllgen:make-string-parser the-lexical-spec the-grammar))
  
  (define just-scan
    (sllgen:make-string-scanner the-lexical-spec the-grammar))
  
