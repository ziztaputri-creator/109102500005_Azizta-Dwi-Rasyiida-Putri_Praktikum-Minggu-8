
#include "Buffer.h"
#include <iomanip>

// Membuat Queue kosong
Queue createQueue() {
    Queue Q;

    Q.head = -1;
    Q.tail = -1;
    Q.nomorBerikutnya = 1;
    Q.totalPergeseran = 0;

    for (int i = 0; i < KAPASITAS; i++) {
        Q.data[i].nomor = 0;
        Q.data[i].nilai = 0;
    }

    return Q;
}

// Memeriksa Queue kosong
bool isEmptyQueue(Queue Q) {
    return Q.head == -1;
}

// Menghitung jumlah data
int nbQueue(Queue Q) {
    if (isEmptyQueue(Q)) {
        return 0;
    }

    return Q.tail - Q.head + 1;
}

// Menambahkan data ke belakang
bool enqueue(Queue &Q, int nilai) {
    if (nbQueue(Q) >= KAPASITAS) {
        return false;
    }

    if (isEmptyQueue(Q)) {
        Q.head = 0;
        Q.tail = 0;
    } else {
        Q.tail++;
    }

    Q.data[Q.tail].nomor = Q.nomorBerikutnya;
    Q.data[Q.tail].nilai = nilai;

    Q.nomorBerikutnya++;

    return true;
}

// Mengambil data dari depan dan menggeser array
bool dequeue(Queue &Q, Rekaman &hasil) {
    if (isEmptyQueue(Q)) {
        return false;
    }

    hasil = Q.data[Q.head];

    // Menggeser seluruh data ke kiri
    for (int i = Q.head; i < Q.tail; i++) {
        Q.data[i] = Q.data[i + 1];
        Q.totalPergeseran++;
    }

    Q.tail--;

    // Jika Queue menjadi kosong
    if (Q.tail < 0) {
        Q.head = -1;
        Q.tail = -1;
    }

    return true;
}

// Menampilkan data berdasarkan urutan FIFO
void printInfo(Queue Q) {
    if (isEmptyQueue(Q)) {
        cout << "Kosong\n";
        return;
    }

    for (int i = Q.head; i <= Q.tail; i++) {
        cout << Q.data[i].nomor << ":"
             << Q.data[i].nilai;

        if (i < Q.tail) {
            cout << ", ";
        }
    }

    cout << "\n";
}

// Menampilkan kondisi setiap indeks fisik
void lihatFisik(Queue Q) {
    cout << "\n=== KONDISI FISIK ARRAY ===\n";

    for (int i = 0; i < KAPASITAS; i++) {
        cout << "Indeks " << i << ": ";

        if (!isEmptyQueue(Q) &&
            i >= Q.head && i <= Q.tail) {

            cout << Q.data[i].nomor << ":"
                 << Q.data[i].nilai;
        } else {
            cout << "Kosong";
        }

        cout << "\n";
    }

    cout << "Head: " << Q.head << "\n";
    cout << "Tail: " << Q.tail << "\n";
    cout << "Total pergeseran: "
         << Q.totalPergeseran << " rekaman\n";
}

// Menghitung ringkasan data
void ringkasQueue(Queue Q) {
    int jumlah = nbQueue(Q);
    long long total = 0;

    cout << "\n=== RINGKASAN DATA ===\n";
    cout << "Jumlah: " << jumlah << "\n";
    cout << "Total: ";

    if (jumlah == 0) {
        cout << "0\n";
        cout << "Minimum: TIDAK ADA\n";
        cout << "Maksimum: TIDAK ADA\n";
        cout << "Rata-rata: TIDAK ADA\n";
        return;
    }

    int minimum = Q.data[Q.head].nilai;
    int maksimum = Q.data[Q.head].nilai;

    for (int i = Q.head; i <= Q.tail; i++) {
        int nilai = Q.data[i].nilai;

        total += nilai;

        if (nilai < minimum) {
            minimum = nilai;
        }

        if (nilai > maksimum) {
            maksimum = nilai;
        }
    }

    double rataRata = static_cast<double>(total) / jumlah;

    cout << total << "\n";
    cout << "Minimum: " << minimum << "\n";
    cout << "Maksimum: " << maksimum << "\n";

    cout << fixed << setprecision(2);
    cout << "Rata-rata: " << rataRata << "\n";
}

// Mengosongkan Queue tanpa mereset nomor dan pergeseran
void kosongkanQueue(Queue &Q) {
    Q.head = -1;
    Q.tail = -1;

    for (int i = 0; i < KAPASITAS; i++) {
        Q.data[i].nomor = 0;
        Q.data[i].nilai = 0;
    }
}
