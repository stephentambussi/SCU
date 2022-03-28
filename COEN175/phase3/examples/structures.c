/* Example run through of this file */
/* open file scope */
struct node a, *b;		/* Error: 'a' has incomplete type (indirection is 0) */

struct node             /* check if defined */
{                       /* open scope */
    int data;
    struct node *next;
};                      /* close scope + define struct */

struct node x, *y;      /* x is okay because struct has been defined */

struct node node;       /* this is also fine because struct has been defined */

int node;			    /* Error: conflicting types for 'node' (due to same identifier) */

int foo;

struct foo              /* check if defined */
{                       /* open scope */
    struct foo *foo;
    int x, y;
};                      /* close scope + define struct */

struct foo              /* check if defined => Error: redefinition of 'foo' */
{			            /* open scope */
    int x, y;
};                      /* close scope + define struct */

struct foo f();			/* Error: pointer type required for 'f' return type */

struct foo *g(struct foo *p,
	struct foo q) { }	/* Error: pointer type required for 'q' */

struct foo (*p)();		/* Error: pointer type required for 'p' return type */
struct foo *(*q)();
/* close file scope */