#include <iostream>
#include <fstream>
#include <iomanip>
#define compEQ(a,b) (a == b)
struct Node {
    int data;// данные, хранящиеся в вершине
    Node* next; // следующая вершина
};

Node** hashTable;
int hashTableSize;
int myhash(int data);
Node* insertNode(int data);
void deleteNode(int data);
Node* findNode(int data);

int main() {
    int i, * a, maxnum;
    printf("Введите количество элементов: \n");
    scanf("%d",&maxnum);
    printf("Введите размерность хэш-таблицы : \n");
    scanf("%d", &hashTableSize);
    a = new int[maxnum];
    hashTable = new Node * [hashTableSize];
    for (i = 0; i < hashTableSize; i++)
        hashTable[i] = NULL;
    // генерация массива
    for (i = 0; i < maxnum; i++)
        a[i] = rand();
    // заполнение хеш-таблицы элементами массива
    for (i = 0; i < maxnum; i++) {
        insertNode(a[i]);
    }
    //печать таблицы
    for (int i = 0; i < hashTableSize; i++) {
        if (hashTable[i] == NULL) {
            printf("\t%i\t---\n", i);
        }
        else {
            printf("\t%i\t%d\n", i, hashTable[i]->data);
        }
    }
    printf("\n");
    int sum=0;
    int count = 0;
    
    for (int i = 0; i < hashTableSize; i++) { //цикл для нахождения суммы всех элементов и счетчик ячеек
        if (hashTable[i] != NULL) {
            sum += hashTable[i]->data;
            count++;
        }
    }
    int srznach = sum / count; //среднее значение
    int newcount = 0; //счетчик новый по заданию
    for (int i = 0; i < hashTableSize; i++) {
        if (hashTable[i] != NULL && hashTable[i]->data < srznach ) {
            newcount++;
        }
    }
    printf("Элементов хеш-таблицы со случайными ключам не превышающие среднее значение от всех ключей - %d\n", newcount);
    for (i = maxnum - 1; i >= 0; i--) {
        deleteNode(a[i]);
    }
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    return 0;

}
// хеш-функция размещения вершины
int myhash(int data) {
    return (data % hashTableSize);
}
// функция поиска местоположения и вставки вершины в таблицу
Node* insertNode(int data) {
    Node* p, * p0;
    int bucket;
    // вставка вершины в начало списка
    bucket = myhash(data);
    if ((p = new Node) == 0) {
        fprintf(stderr, "Нехватка памяти (insertNode)\n");
        exit(1);
    }
    p0 = hashTable[bucket];
    hashTable[bucket] = p;
    p->next = p0;
    p->data = data;
    return p;
}
//функция удаления вершины из таблицы
void deleteNode(int data) {
    Node* p0, * p;
    int bucket;
    p0 = 0;
    bucket = myhash(data);
    p = hashTable[bucket];
    while (p && !compEQ(p->data, data)) {
        p0 = p;
        p = p->next;
    }
    if (!p) return;
    if (p0)
        p0->next = p->next;
    else
        hashTable[bucket] = p->next;
    free(p);
}
// функция поиска вершины со значением data
Node* findNode(int data) {
    Node* p;
    p = hashTable[myhash(data)];
    while (p && !compEQ(p->data, data))
        p = p->next;
    return p;
}
