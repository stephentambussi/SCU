int a, b(), c();
char b(), d();			/* conflicting types for 'b' */
int c(), d(), e();		/* conflicting types for 'd' */

int y[10];
int y[5];			/* conflicting types for 'y' */
int x;
int x[10];			/* conflicting types for 'x' */

int foo();

int foo(void)
{
    a = z;			/* 'z' undeclared */
}

int foo();
int *e();			/* conflicting types for 'e' */

char foo();			/* conflicting types for 'foo' */

int foo(void) {			/* redefinition of 'foo' */
}
