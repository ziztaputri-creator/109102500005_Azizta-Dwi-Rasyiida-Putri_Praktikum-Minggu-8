
#include "Buffer.h"
#include <iomanip>

// Membuat Queue kosong
Queue createQueue() {
    Queue Q;

    Q.head = 0;
    Q.count = 0;
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
    return Q.count == 0;
}

// Menghitung jumlah data
int nbQueue(Queue Q) {
    return Q.count;
}

// Menambahkan data menggunakan modulo
bool enqueue(Queue &Q, int nilai) {
    if (Q.count >= KAPASITAS) {
        return false;
    }

    int posisi = (Q.head + Q.count) % KAPASITAS;

    Q.data[posisi].nomor = Q.nomorBerikutnya;
    Q.data[posisi].nilai = nilai;

    Q.nomorBerikutnya++;
    Q.count++;

    return true;
}

// Mengambil data dari depan
bool dequeue(Queue &Q, Rekaman &hasil) {
    if (isEmptyQueue(Q)) {
        return false;
    }

    hasil = Q.data[Q.head];

    Q.data[Q.head].nomor = 0;
    Q.data[Q.head].nilai = 0;

    Q.head = (Q.head + 1) % KAPASITAS;
    Q.count--;

    if (Q.count == 0) {
        Q.head = 0;
    }

    return true;
}

// Menampilkan data berdasarkan urutan FIFO
void printInfo(Queue Q) {
    if (isEmptyQueue(Q)) {
        cout << "Kosong\n";
        return;
    }

    for (int i = 0; i < Q.count; i++) {
        int posisi = (Q.head + i) % KAPASITAS;

        cout << Q.data[posisi].nomor << ":"
             << Q.data[posisi].nilai;

        if (i < Q.count - 1) {
            cout << ", ";
        }
    }

    cout << "\n";
}

// Menampilkan kondisi fisik array
void lihatFisik(Queue Q) {
    cout << "\n=== KONDISI FISIK ARRAY ===\n";

    for (int i = 0; i < KAPASITAS; i++) {
        bool aktif = false;

        for (int j = 0; j < Q.count; j++) {
            int posisi = (Q.head + j) % KAPASITAS;

            if (posisi == i) {
                aktif = true;
                break;
            }
        }

        cout << "Indeks " << i << ": ";

        if (aktif) {
            cout << Q.data[i].nomor << ":"
                 << Q.data[i].nilai;
        } else {
            cout << "Kosong";
        }

        cout << "\n";
    }

    int posisiTulis = (Q.head + Q.count) % KAPASITAS;

    int posisiTerakhir = -1;

    if (Q.count > 0) {
        posisiTerakhir =
            (Q.head + Q.count - 1) % KAPASITAS;
    }

    cout << "Head: " << Q.head << "\n";
    cout << "Count: " << Q.count << "\n";

    cout << "Posisi tulis berikutnya: "
         << posisiTulis << "\n";

    cout << "Posisi data terakhir: "
         << posisiTerakhir << "\n";

    cout << "Total pergeseran: "
         << Q.totalPergeseran << " rekaman\n";
}

// Menghitung ringkasan data
void ringkasQueue(Queue Q) {
    int jumlah = Q.count;
    long long total = 0;

    cout << "\n=== RINGKASAN DATA ===\n";
    cout << "Jumlah: " << jumlah << "\n";

    if (jumlah == 0) {
        cout << "Total: 0\n";
        cout << "Minimum: TIDAK ADA\n";
        cout << "Maksimum: TIDAK ADA\n";
        cout << "Rata-rata: TIDAK ADA\n";
        return;
    }

    int posisiAwal = Q.head;

    int minimum = Q.data[posisiAwal].nilai;
    int maksimum = Q.data[posisiAwal].nilai;

    for (int i = 0; i < jumlah; i++) {
        int posisi = (Q.head + i) % KAPASITAS;
        int nilai = Q.data[posisi].nilai;

        total += nilai;

        if (nilai < minimum) {
            minimum = nilai;
        }

        if (nilai > maksimum) {
            maksimum = nilai;
        }
    }

    double rataRata =
        static_cast<double>(total) / jumlah;

    cout << "Total: " << total << "\n";
    cout << "Minimum: " << minimum << "\n";
    cout << "Maksimum: " << maksimum << "\n";

    cout << fixed << setprecision(2);
    cout << "Rata-rata: " << rataRata << "\n";
}

// Mengosongkan Queue tanpa mereset nomor
void kosongkanQueue(Queue &Q) {
    for (int i = 0; i < KAPASITAS; i++) {
        Q.data[i].nomor = 0;
        Q.data[i].nilai = 0;
    }

    Q.head = 0;
    Q.count = 0;
}

