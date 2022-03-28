/* Taken from https://www.cs.uaf.edu/courses/cs301/2014-fall/notes/methods/ */

int printf();

struct parent_vtable {
    int (*bar)();
};

struct parent {
    struct parent_vtable *vtable;
    int v;
};

int parent_bar(struct parent *this) {
    printf("I'm the parent (v = %d)\n", this->v);
    return 0;
}

int child_bar(struct parent *this) {
    printf("I'm the child (v = %d)\n", this->v);
    return 0;
}

int main(void)
{
    struct parent p, c;
    struct parent_vtable parent_class, child_class;

    parent_class.bar = parent_bar;
    child_class.bar = child_bar;

    p.vtable = &parent_class;
    p.v = 10;
    p.vtable->bar(&p);

    c.vtable = &child_class;
    c.v = 11;
    p.vtable->bar(&c);

    return 0;
}
