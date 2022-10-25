#include <cstdlib>			// for free()

void dispose(double *ptr) {
    free(ptr);
}

int main() {
    double *p = new double[1000];
    dispose(p);
    return 0;
}
