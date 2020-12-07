solve([]).
solve([R/C | T]) :- solve(T), member(C, [1,2,3,4,5,6,7,8]), cantattack(R/C, T).

cantattack(_,[]).
cantattack(R/C, [R1/C1 | T]) :- C =\= C1, R1-R =\= C1-C, R1-R =\= C-C1, cantattack(R/C, T).

board(8, [8/_]).
board(X, [X/_|T]) :- X =< 8, Y is X+1, board(Y,T).

queens(X) :- board(1, X), solve(X).
