int x, *y, z;

int foo(void) {
    int **x, y, *z;
}

int foo(void) {			/* redefinition of 'foo' */
    int **x, *y, z;
}
