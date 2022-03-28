int (*p)();
int (*p)();
int *(*p)();				/* conflicting types for 'p' */

int main(void)
{
    int x, y, z;

    {
	int x, y, z;

	{
	    char *x, *y[10], z;
	}
    }
}
