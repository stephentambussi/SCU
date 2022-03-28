/*
 * tree3.c, or let's do it even better
 */

struct node {
    int data;
    struct node *left, *right;
};

struct tree {
    int (*compare)();
    struct node *root;
};

int printf();
struct node *malloc(), *null;

struct node *node_insert(struct node *root, int data, int (*compare)())
{
    if (!root) {
	root = malloc(sizeof(*root));
	root->data = data;
	root->left = null;
	root->right = null;

    } else {
	if (compare(data, root->data) < 0)
	    root->left = node_insert(root->left, data, compare);
	else if (compare(data, root->data) > 0)
	    root->right = node_insert(root->right, data, compare);
    }

    return root;
}

int node_search(struct node *root, int data, int (*compare)())
{
    if (!root)
	return 0;

    if (compare(data, root->data) < 0)
	return node_search(root->left, data, compare);

    if (compare(data, root->data) > 0)
	return node_search(root->right, data, compare);

    return 1;
}

int node_preorder(struct node *root)
{
    if (root) {
	printf("%d\n", root->data);
	node_preorder(root->left);
	node_preorder(root->right);
    }
}

int node_inorder(struct node *root)
{
    if (root) {
	node_inorder(root->left);
	printf("%d\n", root->data);
	node_inorder(root->right);
    }
}

int compare(int a, int b)
{
    return b - a;
}

int insert(struct tree *tree, int data)
{
    tree->root = node_insert(tree->root, data, tree->compare);
}

int search(struct tree *tree, int data)
{
    return node_search(tree->root, data, tree->compare);
}

int main(void)
{
    struct node *root;
    struct tree tree;

    tree.root = null;
    tree.compare = compare;

    insert(&tree, 7);
    insert(&tree, 4);
    insert(&tree, 1);
    insert(&tree, 0);
    insert(&tree, 5);
    insert(&tree, 2);
    insert(&tree, 3);
    insert(&tree, 6);

    printf("preorder traversal:\n");
    node_preorder(tree.root);
    printf("inorder traversal:\n");
    node_inorder(tree.root);
}
