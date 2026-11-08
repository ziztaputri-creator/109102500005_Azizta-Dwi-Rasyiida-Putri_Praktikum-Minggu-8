
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

struct Paket {
    string kode;
    int berat;
    Paket* next;
};

struct Queue {
    Paket* head;
    Paket* tail;
};

// Pembuatan dan pemeriksaan Queue
Queue createQueue();
bool isEmptyQueue(Queue Q);

// Alokasi dan dealokasi node
Paket* alokasi(string kode, int berat);
void dealokasi(Paket* P);

// Operasi Queue
void enqueue(Queue &Q, Paket* P);
Paket* dequeue(Queue &Q);

// Pencarian
Paket* findElm(Queue Q, string kode);
bool fFindElm(Queue Q, Paket* P);

// Fungsi tambahan
int nbList(Queue Q);
void printInfo(Queue Q);
void delAll(Queue &Q);

#endif
