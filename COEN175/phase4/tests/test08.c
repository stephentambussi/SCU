struct s1 {
    struct s1 x;		/* 'x' has incomplete type */
};

struct s2 {
    struct s1 x;
    struct s2 *y;
};

struct s1 { int x, y; };	/* redefinition of 's1' */

struct s1 f(int x) { }		/* pointer type required for 'f' */

int g(struct s1 y) { }		/* pointer type required for 'y' */

struct s1 *h(struct s2 *y) { }
