int a, b, c;

int bar(int a, int b, int c)
{
    int a;				/* redeclaration of 'a' */

    b;

    {
	int b, c;
    }

    a;
    c;
    d();				/* 'd' undeclared */
    e;					/* 'e' undeclared */
}

int c, b, a, bar();

char bar();				/* conflicting types for 'bar' */
