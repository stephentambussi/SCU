(define (filter f lst)
	(cond
		((null? lst) lst)
		((f (car lst))
			(cons (car lst) (filter f (cdr lst))))
		(else (filter f (cdr lst)))))

(define (quicksort lst)
	(if (null? lst) lst
		(let*
			((h (car lst))
			(t (cdr lst))
			(above (lambda (x) (>= x h )))
			(below (lambda (x) (< x h ))))
		(append (quicksort (filter below t)) (cons h (quicksort(filter above t)))))))
