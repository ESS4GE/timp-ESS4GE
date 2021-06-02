#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct tree {
    struct tree *right;
    struct tree *left;
    int data;
};

int insert(struct tree *t, int value);

void init(struct tree **t, int value);

int print_direct(struct tree *t);

int insert(struct tree *t, int value) {
    if (t->data == value)
        return 1;
    if (value > (t->data)) {
        if ((t->right) != NULL)
            return (insert(t->right, value));
        else {
            t->right = (struct tree *) malloc(sizeof(struct tree));
            t->right->right = NULL;
            t->right->left = NULL;
            t->right->data = value;
            return 0;
        }
    } else {
        if ((t->left) != NULL)
            return (insert(t->left, value));
        else {
            t->left = (struct tree *) malloc(sizeof(struct tree));
            t->left->right = NULL;
            t->left->left = NULL;
            t->left->data = value;
            return 0;
        }
    }
}

void init(struct tree **t, int value) {
    *t = (struct tree *) malloc(sizeof(struct tree));

    (*t)->right = NULL;

    (*t)->left = NULL;

    (*t)->data = value;

}

int print_direct(struct tree *t) {
    if (t == NULL)
        return;
    printf("%d ", t->data);
    print_direct(t->left);
    print_direct(t->right);
}

int main() {
    struct tree *t;
    int i;
    int value;

    scanf("%d", &value);

    init(&t, value);

    for (i = 0; i < 6; i++) {
        scanf("%d", &value);
        insert(t, value);
    }

    print_direct(t);

    return 1;
}