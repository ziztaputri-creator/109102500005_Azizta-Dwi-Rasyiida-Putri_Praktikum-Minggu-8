
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
    int tail;
    int nomorBerikutnya;
    int totalPergeseran;
};

// Fungsi dasar Queue
Queue createQueue();
bool isEmptyQueue(Queue Q);
int nbQueue(Queue Q);

// Operasi Queue
bool enqueue(Queue &Q, int nilai);
bool dequeue(Queue &Q, Rekaman &hasil);

// Menampilkan dan menghitung data
void printInfo(Queue Q);
void ringkasQueue(Queue Q);
void lihatFisik(Queue Q);

// Mengosongkan Queue
void kosongkanQueue(Queue &Q);

#endif
