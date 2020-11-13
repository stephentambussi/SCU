; vi:ai:lisp:sm

; an empty node is represented as an empty list
; a nonempty node is represented as a list with three elements:
;    - the first element is the integer data
;    - the second element is the left child
;    - the third element is the right child

; Returns true if the integer is found in the tree, false otherwise
(define (member? lst x)
  (cond
    ((null? lst) #f)
    ((< x (car lst)) (member? (cadr lst) x)) ;left subtree
    ((> x (car lst)) (member? (caddr lst) x)) ;right subtree
    (else #t))) ;return true because value found

; Inserts values in a list into a tree
(define (insert lst x)
  (cond
    ((null? lst) (list x '() '()))
    ((= x (car lst)) lst) ;if value is already in tree - don't add
    ((< x (car lst)) (list (car lst) (insert (cadr lst) x) (caddr lst))) ; go down left subtree
    ((> x (car lst)) (list (car lst) (cadr lst) (insert (caddr lst) x))))) ; go down right subtree

(define (fold func val lst)
  (if (null? lst) val (fold func (func val (car lst)) (cdr lst))))

(define (build lst)
  (fold (lambda (t v) (insert t v)) '() lst))

(define (inorder lst)
  (if (null? lst) lst
    (append (inorder (cadr lst)) (cons (car lst) (inorder (caddr lst))))))
