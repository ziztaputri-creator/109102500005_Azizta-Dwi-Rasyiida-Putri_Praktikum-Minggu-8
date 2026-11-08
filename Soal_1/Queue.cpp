
#include "Queue.h"

// Membuat Queue kosong
Queue createQueue() {
    Queue Q;
    Q.head = nullptr;
    Q.tail = nullptr;
    return Q;
}

// Memeriksa apakah Queue kosong
bool isEmptyQueue(Queue Q) {
    return Q.head == nullptr;
}

// Membuat node baru
Paket* alokasi(string kode, int berat) {
    Paket* P = new(nothrow) Paket;

    if (P != nullptr) {
        P->kode = kode;
        P->berat = berat;
        P->next = nullptr;
    }

    return P;
}

// Menghapus node dari memori
void dealokasi(Paket* P) {
    if (P != nullptr) {
        delete P;
    }
}

// Menambahkan node ke belakang Queue
void enqueue(Queue &Q, Paket* P) {
    if (P == nullptr) return;

    P->next = nullptr;

    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

// Mengeluarkan node dari depan Queue
Paket* dequeue(Queue &Q) {
    if (isEmptyQueue(Q)) {
        return nullptr;
    }

    Paket* P = Q.head;
    Q.head = Q.head->next;
    P->next = nullptr;

    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }

    return P;
}

// Mencari node berdasarkan kode
Paket* findElm(Queue Q, string kode) {
    Paket* P = Q.head;

    while (P != nullptr) {
        if (P->kode == kode) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

// Memeriksa apakah alamat node menjadi anggota Queue
bool fFindElm(Queue Q, Paket* P) {
    Paket* current = Q.head;

    while (current != nullptr) {
        if (current == P) {
            return true;
        }

        current = current->next;
    }

    return false;
}

// Menghitung jumlah node
int nbList(Queue Q) {
    int jumlah = 0;
    Paket* P = Q.head;

    while (P != nullptr) {
        jumlah++;
        P = P->next;
    }

    return jumlah;
}

// Menampilkan seluruh isi Queue
void printInfo(Queue Q) {
    Paket* P = Q.head;

    if (isEmptyQueue(Q)) {
        cout << "Kosong";
        return;
    }

    while (P != nullptr) {
        cout << "[" << P->kode
             << " - " << P->berat << " gram]";

        if (P->next != nullptr) {
            cout << " -> ";
        }

        P = P->next;
    }
}

// Menghapus seluruh node dalam Queue
void delAll(Queue &Q) {
    Paket* P;

    while (!isEmptyQueue(Q)) {
        P = dequeue(Q);
        dealokasi(P);
    }
}
