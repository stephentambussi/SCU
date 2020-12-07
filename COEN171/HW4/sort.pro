partition(_,[],[],[]).
partition(P,[H|T],L,[H|G]) :- H>=P, partition(P,T,L,G).
partition(P,[H|T],[H|L],G) :- H<P, partition(P,T,L,G).

quicksort([],[]).
quicksort([H|T],S) :- partition(H,T,L1,L2), quicksort(L1,S1), quicksort(L2,S2), append(S1,[H|S2],S).
