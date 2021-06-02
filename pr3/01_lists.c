#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value; // значение, которое хранит узел
    struct node *next; // ссылка на следующий элемент списка
} node;

typedef struct list {
    struct node *head; // начало списка
} list;

// инициализация пустого списка
void init(list *l) {
    l -> head = malloc(sizeof(node));
    l -> head = NULL;
    return;
}

// удалить все элементы из списка
void clean(list *l) {
    if (! l -> head) {
        return;
    }
    node *current = l->head;
    node *temp;
    while (current) {
        temp = current->next;
        free(current);
        current = temp;
    }
    l->head = NULL;
    return;
}

// проверка на пустоту списка
bool is_empty(list *l) {
    if(l -> head == NULL) {
        return true;
    }
    return false;
}

// поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int key) {
    node *current = l -> head;
    if(! l -> head) {
        return NULL;
    }
    while(current -> value != key) {
        current = current -> next;
        if(current == NULL) {
            return NULL;
        }
    }
    return current;
}

node* FindTail(list *l) {
    if(l -> head == NULL) {
        return NULL;
    }
    node *current = l -> head;
    while(current -> next != NULL) {
        current = current -> next;
    }
    return current;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int key) {
    if (! is_empty(l)) {
        node *lastnode = FindTail(l);
        node *current = malloc(sizeof(node));
        lastnode -> next = current;
        current -> next = NULL;
        current -> value = key;
    }
    else {
        node *current = malloc(sizeof(node));
        current -> value = key;
        current -> next = NULL;
        l -> head = current;
    }
    return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int key) {
    node *current;
    current = malloc(sizeof(node));
    current -> value = key;
    current -> next = l -> head;
    l -> head = current;
    return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int key) {
    if(n == NULL) {
        return 1;
    }
    node *current = malloc(sizeof(node));
    current -> value = key;
    current -> next = n -> next;
    n -> next = current;
    return 0;
}

// удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_node(list *l, int key) {
    node *current = l -> head;
    node *previous = NULL;
    if(l -> head == NULL) {
        return 1;
    }
    while(current -> value != key) {
        if(current -> next == NULL) {
            return 1;
        }
        else {
            previous = current;
            current = current -> next;
        }
    }
    if(current == l -> head) {
        l -> head = l -> head -> next;
    }
    else {
        previous -> next = current -> next;
    }
    free(current);
    return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
    node *current = l -> head;
    if (current == NULL) {
        return;
    }
    while(current != NULL) {
        printf("%d ", current-> value);
        current = current -> next;
    }
    printf("\n");
    return;
}
void checkingexist(node *n1, node *n2, node *n3) {
    if(n1 == NULL) {
        printf("0 ");
    }
    else {
        printf("1 ");
    }
    if(n2 == NULL) {
        printf("0 ");
    }
    else {
        printf("1 ");
    }
    if(n3 == NULL) {
        printf("0 ");
    }
    else {
        printf("1 \n");
    }
}
node *findbyindex(list *l, int index) {
    if(l -> head == NULL) {
        return NULL;
    }
    node *current = l -> head;
    int i = 0;
    while(i != index) {
        current = current -> next;
        if(current == NULL) {
            return NULL;
        }
        i++;
    }
    return current;
}

int main() {
    int i, n, k1, k2, k3, m, t, j, x, z, a;
    (void) scanf("%d", &n);
    list *link;
    link = malloc(sizeof(list));
    init(link);
    for(i = 1; i <= n; i++) {
        (void) scanf("%d", &a);
        push_back(link, a);
    }
    print(link);
    (void) scanf("%d %d %d", &k1, &k2, &k3);
    node *finder1 = find(link, k1);
    node *finder2 = find(link, k2);
    node *finder3 = find(link, k3);
    checkingexist(finder1, finder2, finder3);
    (void)scanf("%d", &m);
    push_back(link, m);
    print(link);
    (void)scanf("%d", &t);
    push_front(link, t);
    print(link);
    (void) scanf("%d %d", &j, &x);
    node *FindNode = findbyindex(link, j - 1);
    insert_after(FindNode, x);
    print(link);
    (void) scanf("%d", &z);
    remove_node(link, z);
    print(link);
    clean(link);
    link -> head = NULL;
    return 0;
}
