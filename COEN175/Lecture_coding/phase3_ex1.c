int f(), x;

int f(int x, int y)
{
    int z;
    while(x < y)
    {
        int a, b;
    }

    x + a + b;
}

/*
Order of ops for symbol table construction:
open scope
declare f
declare x
define f
open scope
declare x
declare y
declare z
lookup x
lookup y
open scope
declare a
declare b
close scope
lookup x
lookup a
lookup b
close scope
close scope
*/