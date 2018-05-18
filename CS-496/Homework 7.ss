#lang eopl

;; Dave N., Julian S., 3/2015

;; Homework exercise -- see below

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Syntax for a language with control structures similar to
; Java.
;
; <program> ::= <stmt>
; <expr> ::= same as PROC lang
; <stmt> ::= while <expr> do <stmt>
;         |  for <ident> from <num> to <num> do <stmt>
;         |  begin {<stmt>}+ end
;         |  if <expr> then <stmt> else <stmt>
;         |  set <ident> = <expr>
;         |  try <stmt> catch <stmt>
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
      
      (statement ("while" expression "do" statement) while-stmt)
      
      (statement ("for" identifier "from" number "to" number "do" statement) for-stmt)
      
      (statement ("begin" statement (arbno ";" statement) "end") begin-stmt)
      
      (statement ("if" expression "then" statement "else" statement) if-stmt)
      
      (statement ("set" identifier "=" expression) assign-stmt)
      
      (statement ("try" statement "catch" statement) try-stmt)
      

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
       ("proc" "(" identifier ")" expression)
       proc-exp)

      (expression
       ("(" expression expression ")")
       call-exp)


      ))

  ;;;;;;;;;;;;;;;; sllgen boilerplate ;;;;;;;;;;;;;;;;
  
  (sllgen:make-define-datatypes the-lexical-spec the-grammar)
  
  (define show-the-datatypes
    (lambda () (sllgen:list-define-datatypes the-lexical-spec the-grammar)))
  
  (define scan&parse
    (sllgen:make-string-parser the-lexical-spec the-grammar))
  
  (define just-scan
    (sllgen:make-string-scanner the-lexical-spec the-grammar))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Homework exercise
;;
;; Step 0: Skip this step if you're already familiar with the
;; 'apply' function in Scheme.
;; Try these expressions in Racket, to figure out what apply does:
;; (+ '(1 2 3))   (apply + '(1 2 3))
;; (apply cons '(a (b c d)))
;;
;; Step 1: run (show-the-datatypes) to see the three data
;; types for the abstract syntax trees.  Get in the mood to
;; follow the grammar.
;;
;; Step 2: Study the functions below.  The implementation of more-for-stm
;; traverses the abstract syntax tree twice.  Replace it by a new implementation 
;; that only traverses the syntax tree once.
;;
;; Hint: Make a helper that returns  a list (f w) where f is the number of
;; for-loops and w the number of while loops.
;;
;; (If this is easy for you, give yourself the extra challenge of
;; making the helper tail-recursive.)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; more-for-pgm: program? -> boolean?
; (more-for-pgm p) = #t if the p's body has more for-loops than while-loops; otherwise #f
(define more-for-pgm
  (lambda (pgm)
    (cases program pgm
	   (a-program (stm) (more-for-stm stm)))))

; more-for-stm: statement? -> boolean?
; (more-for-stm s) = #t if s has more for-loops than while-loops; otherwise #f
(define more-for-stm
   (lambda (stm) (< 0 (more-for-help stm))))

(define more-for-help
  (lambda (stm)
        (cases statement stm
     (while-stmt (wh-expr wh-body) (- (more-for-help wh-body) 1))
     (for-stmt (for-var for-lower for-upper for-body) (+ 1 (more-for-help for-body)))
     (begin-stmt (begin-first begin-rest)
                 (+ (more-for-help begin-first)
                    (apply + (map more-for-help begin-rest))))
      (if-stmt (if-cond if-then if-else) (+ (more-for-help if-then)
                                            (more-for-help if-else)))
      (assign-stmt (var expr) 0)
      (try-stmt (t-try t-catch) (+ (more-for-help t-try) (more-for-help t-catch))))))

; num-fors: statement? -> boolean?
; (num-fors s) = the number of for-loops in statement s
(define num-fors
  (lambda (stm)
    (cases statement stm
     (while-stmt (wh-expr wh-body) (num-fors wh-body))
     (for-stmt (for-var for-lower for-upper for-body) (+ 1 (num-fors for-body)))
     (begin-stmt (begin-first begin-rest)
                 (+ (num-fors begin-first)
                    (apply + (map num-fors begin-rest))))
      (if-stmt (if-cond if-then if-else) (+ (num-fors if-then)
                                            (num-fors if-else)))
      (assign-stmt (var expr) 0)
      (try-stmt (t-try t-catch) (+ (num-fors t-try) (num-fors t-catch))))))

; num-whiles: statement? -> boolean?
; (num-whiles s) = the number of while loops in statement s
(define num-whiles
  (lambda (stm)
    (cases statement stm
     (while-stmt (wh-expr wh-body) (+ 1 (num-whiles wh-body)))
     (for-stmt (for-var for-lower for-upper for-body) (num-whiles for-body))
     (begin-stmt (begin-first begin-rest)
                 (+ (num-whiles begin-first)
                    (apply + (map num-whiles begin-rest))))
      (if-stmt (if-cond if-then if-else) (+ (num-whiles if-then)
                                            (num-whiles if-else)))
      (assign-stmt (var expr) 0)
      (try-stmt (t-try t-catch) (+ (num-whiles t-try) (num-whiles t-catch))))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TESTS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(require rackunit 
         rackunit/text-ui)

(define test-code-1
  "begin set x = 4; while zero?(x) do set x = -(x,1); for i from 1 to 3 do set x = -(i,-(0,x)) end")

(define test-code-2
   "begin 
    set m = 0; 
    for i from 1 to 10 do 
      for x from 2 to 13 do 
        for y from 9 to 4 do 
           while zero?(-(x,13)) do 
              set x = -(i, -(0,x)) end")

(define test-code-3 "begin set m = 0 end")

(define test-code-4 "begin if zero?(m) then set m = 1 else set m = 2 end")

(define test-code-5
  "begin set m = 0; set x = 0; 
   while zero?(x) do 
     while zero?(m) do 
       while zero?(0) do 
         if zero?(m) 
         then while zero?(4) do set m = -(m, 1) 
         else for y from 0 to 3 do set m = -(m,2) end")

(define more-for-tests  
  (test-suite
   "tests for MORE-FOR function"
   (check-equal? (more-for-pgm (scan&parse test-code-1)) #f "both counts 1")
   (check-equal? (more-for-pgm (scan&parse test-code-2)) #t "more fors than whiles")
   (check-equal? (more-for-pgm (scan&parse test-code-3)) #f "both counts 0")
   (check-equal? (more-for-pgm (scan&parse test-code-4)) #f "both counts 0 with if statement")
   (check-equal? (more-for-pgm (scan&parse test-code-5)) #f "more whiles than fors")))

(run-tests more-for-tests 'verbose)