
#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
using namespace std;

const int KAPASITAS = 6;

struct Rekaman {
    int nomor;
    int nilai;
};

struct Queue {
    Rekaman data[KAPASITAS];
    int head;
    int count;
    int nomorBerikutnya;
    int totalPergeseran;
};

Queue createQueue();
bool isEmptyQueue(Queue Q);
int nbQueue(Queue Q);

bool enqueue(Queue &Q, int nilai);
bool dequeue(Queue &Q, Rekaman &hasil);

void printInfo(Queue Q);
void ringkasQueue(Queue Q);
void lihatFisik(Queue Q);

void kosongkanQueue(Queue &Q);

#endif
