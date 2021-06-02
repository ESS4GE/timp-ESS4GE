#include <stdio.h>
#include <stdlib.h>

// быстрая сортировка
void quickSort(int *arr, int first, int last, FILE* fp, int size) {
    int tmp, i; // переменная для обмена элементов
    int left, right, middle; // переменные для правой и левой границ и центра
    if (first < last) {
        left = first; //левая граница
        right = last; //правая граница
        middle = arr[(left + right) / 2]; // опорный элемент (центр)

        do { // пропускаем уже отсортированные участки
            while (arr[left] < middle) { left++;}
            while (arr[right] > middle) { right--;}

            if (left <= right) {
                tmp = arr[left];
                arr[left] = arr[right];
                arr[right] = tmp;
                left++;
                right--;


                for (i = 0; i < size; i++) {
                    if (i != 0)
                        fprintf(fp, " ");
                    fprintf(fp, "%d", arr[i]);
                }
                fprintf(fp, "\n");

            }
        } while (left <= right);

        quickSort(arr, first, right, fp, size); // сортируем левый подмассив
        quickSort(arr, left, last, fp, size);  // сортируем правый подмассив
    }
}
// "просеивание" через кучу - формирование кучи
void siftDown(int *arr, int root, int bottom, int size, FILE* fp) {
    int j, tmp; // переменная для обмена элементов
    int maxChild; // индекс максимального потомка
    int complete = 0; // флаг того, что куча сформирована
    
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!complete)) {

        if (root * 2 == bottom) { // если мы в последнем ряду,
            maxChild = root * 2;  // запоминаем левый потомок
        // иначе запоминаем больший потомок из двух
        }
        else {
            if (arr[root * 2] > arr[root * 2 + 1])
                maxChild = root * 2;
            else
                maxChild = root * 2 + 1;

        }
        // если элемент вершины меньше максимального потомка
        if (arr[root] < arr[maxChild]) {
            tmp = arr[root];// меняем их местами
            arr[root] = arr[maxChild];
            arr[maxChild] = tmp;
            root = maxChild;

            for (j = 0; j < size; j++) {
                if (j != 0)
                    fprintf(fp, " ");
                fprintf(fp, "%d", arr[j]);
            }
            fprintf(fp, "\n");

        }
        else
            complete = 1; // пирамида сформирована

    }
}

// пирамидальная сортировка
void heapSort(int *arr, int size, FILE* fp) {
    int tmp, j; // переменная для обмена элементов
    // Формируем нижний ряд пирамиды
    for (int i = (size / 2); i >= 0; i--) {
        siftDown(arr, i, size - 1, size, fp);

    }
    // Просеиваем через пирамиду остальные элементы
    for (int i = size - 1; i >= 1; i--) {
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        for (j = 0; j < size; j++) {
            if (j != 0)
                fprintf(fp, " ");
            fprintf(fp, "%d", arr[j]);
        }
        fprintf(fp, "\n");

        siftDown(arr, 0, i - 1, size, fp);
    }
}

int main() {
    int size, i;
    scanf("%d", &size);
    int *a1 = (int*)malloc(sizeof(int) * size);
    int *a2 = (int*)malloc(sizeof(int) * size);
    for (i = 0; i < size; i++) {
        scanf("%d", &a1[i]);
        a2[i] = a1[i];
    }

    char qf [] = "quicksort.log";
    FILE *fp = fopen(qf, "w+");
    for (i = 0; i < size; i++) {
        if (i != 0)
            fprintf(fp, " ");
        fprintf(fp, "%d", a1[i]);
    }
    fprintf(fp, "\n");

    quickSort(a1, 0, size-1, fp, size);
    fclose(fp);

    for(int i = 0; i < size; i++) {
        printf("%d", a1[i]);
        if(i<size-1)
            printf(" ");
    }

    char hf [] = "heapsort.log";
    fp = fopen(hf, "w+");
    for (i = 0; i < size; i++) {
        if (i != 0)
            fprintf(fp, " ");
        fprintf(fp, "%d", a2[i]);
    }
    fprintf(fp, "\n");

    heapSort(a2, size, fp);
    fclose(fp);
    free(a1);
    free(a2);
    printf("\n");
    return 0;
}
