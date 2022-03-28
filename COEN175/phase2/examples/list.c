struct node {
    int data;
    struct node *link;
};

struct list {
    int count;
    struct node *head;
};

int *malloc();
struct node *null;

int push(struct list *list, int x)
{
    struct node *node;

    node = (struct node *) malloc(sizeof(node));
    node->link = null;
    (*list).head = node;
    list->head->data = x;

    return 0;
}
