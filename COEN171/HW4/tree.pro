exists(X,node(_,X,_)).
exists(X,node(L,N,_)) :- X<N, exists(X,L).
exists(X,node(_,N,R)) :- X>N, exists(X,R).

insert(X,empty,node(empty,X,empty)).
insert(X,node(L,X,R),node(L,X,R)).
insert(X,node(L,N,R),node(L,N,DR)) :- X>N, insert(X,R,DR).
insert(X,node(L,N,R),node(DL,N,R)) :- X<N, insert(X,L,DL).

mktree(X) :- X = node(node(empty,30,node(empty,40,empty)),50,node(empty,60,node(empty,70,empty))).
