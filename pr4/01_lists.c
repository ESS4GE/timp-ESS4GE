#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
struct List
{
    struct List *Next;
    struct List *Prev;
    double Data;
};
struct Node
{
    struct Node *Next;
    struct Node *Prev;
    double Data;
};
void init(struct List **l)//получаем значение, взятое по адресу адреса
{
    *l = (struct List *)malloc(sizeof(struct List));
    (*l)->Next = NULL;
    (*l)->Prev = NULL;
    (*l)->Data = 2147483648;
}
void clean(struct List *l)
{
    struct List *Temp = l;
    free(Temp->Prev);
    do
    {
        Temp = Temp->Next;
        free(l);
        l = Temp;
    } while (l != NULL);
}
bool is_empty(struct List *l)
{
    if (l == NULL)
        return 0;
    else
        return 1;
}
struct Node *find(struct List *l, int value)//найти элемент со значением
{
    struct List *Temp = l;
    while (1)
    {
        if (Temp == NULL)
            return NULL;
        else
        {
            if ((Temp->Data) == value)
                return ((struct Node *)l);
        }
        Temp = Temp->Next;
    }
}
int push_prev(struct List *l, int value)//вставить в конец(0 при успехе)
{
    if (l->Data == 2147483648)
    {
        l->Data = value;
        return 0;
    }
    struct List *Temp = (struct List *)malloc(sizeof(struct List));
    Temp = l;
    while (Temp->Next != NULL)
        Temp = Temp->Next;
    Temp->Next = (struct List *)malloc(sizeof(struct List));
    Temp->Next->Prev = Temp;//отличие с прошлым кодом
    Temp = Temp->Next;
    Temp->Data = value;
    Temp->Next = NULL;
    return 0;
}
int push_next(struct List **l, int value)//вставить в начало(0 при успехе)
{
    struct List *Temp = (struct List *)malloc(sizeof(struct List));//при этом здесь **l--это значение
    Temp->Data = value;//l--конкретно двойной адрес, *l--адрес блока, **l-- блок
    Temp->Next = (*l);//то есть, в следующем элементе записан адрес начального эл-та списка
    Temp->Prev = NULL;
    Temp->Next->Prev = Temp;//указатель от прошлого первого элемента
    (*l) = Temp;//вот у нас есть список, засунутый в Temp(адрес), мы берём присваиваем адресу l адрес Temp
    return 0;
}
int insert_after(struct Node *l, int value)//вставка на нужное место(0--успех)
{
    if (l->Next != NULL)
    {
        struct Node *Temp = (struct Node *)malloc(sizeof(struct Node)),
                *Temp2;
        Temp->Next = l->Next;//делаем привязки от элемента к соседним тут
        Temp->Prev = l;//и тут
        Temp->Data = value;
        l->Next->Prev = Temp;//меняем указатель с последующего элемента на вставляемый
        l->Next = Temp;
    }
    else
    {
        l->Next = (struct Node *)malloc(sizeof(struct Node));
        l->Next->Next = NULL;
        l->Next->Data = value;
        l->Next->Prev = l;
    }
    return 0;
}
int insert_before(struct Node *l, int value)//вставка на нужное место(0--успех)
{
    if (l->Prev != NULL)
    {
        struct Node *Temp = (struct Node *)malloc(sizeof(struct Node)),
                *Temp2;
        Temp->Prev = l->Prev;//делаем привязки от элемента к соседним тут
        Temp->Next = l;//и тут
        Temp->Data = value;
        l->Prev->Next = Temp;//меняем указатель с последующего элемента на вставляемый
        l->Prev = Temp;
    }
    else
    {
        l->Prev = (struct Node *)malloc(sizeof(struct Node));
        l->Prev->Prev = NULL;
        l->Prev->Data = value;
        l->Prev->Next = l;
    }
    return 0;
}
int remove_first(struct List *l, int value)//удаление(надо сделать удаление 1-го)
{
    struct List *Temp = l;
    if (l != NULL)
    {
        while (1)
        {
            if ((Temp->Next) == NULL)
                return 1;//не найдено
            if ((Temp->Next->Data) == value)
            {
                Temp = Temp->Next;
                if (Temp->Next != NULL)
                {
                    Temp->Prev->Next = Temp->Next;
                    Temp->Next->Prev = Temp->Prev;
                    free(Temp);
                }
                else
                {
                    Temp->Prev->Next = NULL;
                    free(Temp);
                }
                return 0;
            }
            Temp = Temp->Next;
        }
    }
    else
        return 1;
}
int remove_last(struct List *l, int value)//удаление(надо сделать удаление 1-го)
{
    struct List *Temp = l, *TempL = NULL;
    if (l != NULL)
    {
        while (Temp->Next != NULL)
        {
            if ((Temp->Next->Data) == value)
                TempL = Temp->Next;
            Temp = Temp->Next;
        }
        if (TempL != NULL)
        {
            if (TempL->Next != NULL)
            {
                TempL->Prev->Next = TempL->Next;
                TempL->Next->Prev = TempL->Prev;
                free(TempL);
            }
            else
            {
                TempL->Prev->Next = NULL;
                free(TempL);
            }
            return 1;//не найдено
        }
        return 0;
    }
    else
        return -1;
}
void print(struct List *l)//вывести всё, что есть
{
    while (l != NULL)
    {
        printf("%.0lf ", l->Data);
        l = l->Next;
    }
    printf("\n");
}
void print_inverse(struct List *l)//вывести всё, что есть
{
    while (l->Next != NULL)
        l = l->Next;
    while (l != NULL)
    {
        printf("%.0lf ", l->Data);
        l = l->Prev;
    }
    printf("\n");
}
int main()
{
    struct List *l, *Temp;
    int N, i;
    double a, b;
    scanf("%d", &N);
    init(&l);//передаём адрес адреса
    for (i = 0; i < N; i++)
    {
        scanf("%lf", &a);
        push_prev(l, a);
    }
    print(l);
    for (i = 0; i < 3; i++)
    {
        scanf("%lf", &a);
        if (find(l, a) == NULL)
            printf("0");
        else
            printf("1");
        if (i != 2)
            printf(" ");
        else
            printf("\n");
    }
    scanf("%lf", &a);
    push_prev(l, a);
    print_inverse(l);
    scanf("%lf", &a);
    push_next(&l, a);
    print(l);
    scanf("%lf", &a);
    scanf("%lf", &b);//b--это x, само значение
    struct Node *el = (struct Node *)l;
    while (a != 1)
    {
        el = el->Next;
        a--;
    }
    insert_after(el, b);
    print_inverse(l);
    scanf("%lf", &a);//a=u
    scanf("%lf", &b);//b=y
    if (a == 1)
    {
        el= (struct Node *)malloc(sizeof(struct Node));
        el->Data = b;
        el->Prev = NULL;
        el->Next = (struct Node *)l;
        l->Prev = (struct List *)el;
        l=l->Prev;
    }
    else
    {
        el = (struct Node *)l;
        while (a != 1)
        {
            el = el->Next;
            a--;
        }
        insert_before(el, b);
    }
    print(l);
    scanf("%lf", &a);
    if (l->Data == a)
    {
        Temp = l->Next;
        free(l);
        l = Temp;
        l->Prev = NULL;
    }
    else
        remove_first(l, a);
    print_inverse(l);
    scanf("%lf", &a);
    if ((remove_last(l, a) == 0) && (l->Data == a))
    {
        Temp = l->Next;
        free(l);
        l = Temp;
    }
    print(l);
    clean(l);
    return 1;
}

