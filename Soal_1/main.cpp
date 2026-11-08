
#include "Queue.h"
#include <sstream>
#include <new>
#include <limits>

// Menampilkan kondisi Queue A dan B
void tampilkanQueue(Queue A, Queue B) {
    cout << "\n========== KONDISI QUEUE ==========\n";

    cout << "Queue A (Menunggu Sortir): ";
    printInfo(A);

    cout << "\nQueue B (Siap Kirim): ";
    printInfo(B);

    cout << "\n===================================\n";
}

int main() {
    Queue A = createQueue();
    Queue B = createQueue();

    int jumlahTerkirim = 0;
    long long totalBeratTerkirim = 0;

    string input, perintah;

    cout << "====================================\n";
    cout << " SISTEM SORTIR DAN PENGIRIMAN PAKET\n";
    cout << "====================================\n";

    while (true) {
        cout << "\nMasukkan perintah: ";
        getline(cin, input);

        stringstream ss(input);
        perintah = "";

        if (!(ss >> perintah)) {
            cout << "Perintah kosong.\n";
            tampilkanQueue(A, B);
            continue;
        }

        // =================================
        // MASUK
        // =================================
        if (perintah == "MASUK") {
            string kode, tambahan;
            int berat;

            if (!(ss >> kode >> berat) || (ss >> tambahan)) {
                cout << "Format salah! MASUK kode berat\n";
            }
            else if (kode.length() < 1 || kode.length() > 10) {
                cout << "Ditolak: kode harus 1-10 karakter.\n";
            }
            else if (berat < 1 || berat > 5000) {
                cout << "Ditolak: berat harus 1-5000 gram.\n";
            }
            else if (findElm(A, kode) != nullptr ||
                     findElm(B, kode) != nullptr) {
                cout << "Ditolak: kode sudah digunakan.\n";
            }
            else {
                Paket* P = alokasi(kode, berat);

                if (P == nullptr) {
                    cout << "Ditolak: alokasi memori gagal.\n";
                }
                else {
                    enqueue(A, P);
                    cout << "Paket " << kode
                         << " berhasil masuk ke A.\n";
                }
            }
        }

        // =================================
        // PINDAH
        // =================================
        else if (perintah == "PINDAH") {
            int n;
            string tambahan;

            if (!(ss >> n) || (ss >> tambahan)) {
                cout << "Format salah! PINDAH n\n";
            }
            else if (n <= 0 || n > nbList(A)) {
                cout << "Ditolak: jumlah paket tidak valid.\n";
                cout << "A hanya berisi "
                     << nbList(A) << " paket.\n";
            }
            else {
                cout << "Proses pemindahan:\n";

                for (int i = 0; i < n; i++) {
                    Paket* P = dequeue(A);

                    enqueue(B, P);

                    cout << "Paket " << P->kode
                         << " berhasil dipindahkan.\n";

                    cout << "Alamat node: " << P << "\n";
                    cout << "Terdaftar di B: "
                         << (fFindElm(B, P) ? "Ya" : "Tidak")
                         << "\n";
                }

                cout << n << " paket berhasil dipindahkan.\n";
            }
        }

        // =================================
        // KIRIM
        // =================================
        else if (perintah == "KIRIM") {
            int n;
            string tambahan;

            if (!(ss >> n) || (ss >> tambahan)) {
                cout << "Format salah! KIRIM n\n";
            }
            else if (n <= 0 || n > nbList(B)) {
                cout << "Ditolak: jumlah paket tidak valid.\n";
                cout << "B hanya berisi "
                     << nbList(B) << " paket.\n";
            }
            else {
                cout << "Proses pengiriman:\n";

                for (int i = 0; i < n; i++) {
                    Paket* P = dequeue(B);

                    cout << "Paket terkirim: "
                         << P->kode << " - "
                         << P->berat << " gram\n";

                    jumlahTerkirim++;
                    totalBeratTerkirim += P->berat;

                    dealokasi(P);
                }

                cout << n << " paket berhasil dikirim.\n";
            }
        }

        // =================================
        // CARI
        // =================================
        else if (perintah == "CARI") {
            string kode, tambahan;

            if (!(ss >> kode) || (ss >> tambahan)) {
                cout << "Format salah! CARI kode\n";
            }
            else {
                Paket* P = A.head;
                int posisi = 1;
                bool ditemukan = false;

                while (P != nullptr) {
                    if (P->kode == kode) {
                        cout << "Ditemukan di A.\n";
                        cout << "Posisi: " << posisi << "\n";
                        cout << "Berat: " << P->berat
                             << " gram\n";

                        ditemukan = true;
                        break;
                    }

                    P = P->next;
                    posisi++;
                }

                if (!ditemukan) {
                    P = B.head;
                    posisi = 1;

                    while (P != nullptr) {
                        if (P->kode == kode) {
                            cout << "Ditemukan di B.\n";
                            cout << "Posisi: " << posisi << "\n";
                            cout << "Berat: " << P->berat
                                 << " gram\n";

                            ditemukan = true;
                            break;
                        }

                        P = P->next;
                        posisi++;
                    }
                }

                if (!ditemukan) {
                    cout << "TIDAK DITEMUKAN\n";
                }
            }
        }

        // =================================
        // LIHAT
        // =================================
        else if (perintah == "LIHAT") {
            cout << "Menampilkan seluruh antrean.\n";
        }

        // =================================
        // REKAP
        // =================================
        else if (perintah == "REKAP") {
            long long beratA = 0;
            long long beratB = 0;

            Paket* P = A.head;

            while (P != nullptr) {
                beratA += P->berat;
                P = P->next;
            }

            P = B.head;

            while (P != nullptr) {
                beratB += P->berat;
                P = P->next;
            }

            cout << "\n========== REKAP PAKET ==========\n";

            cout << "QUEUE A:\n";
            cout << "Jumlah paket: " << nbList(A) << "\n";
            cout << "Total berat: " << beratA << " gram\n";

            cout << "\nQUEUE B:\n";
            cout << "Jumlah paket: " << nbList(B) << "\n";
            cout << "Total berat: " << beratB << " gram\n";

            cout << "\nPAKET TERKIRIM:\n";
            cout << "Jumlah paket: " << jumlahTerkirim << "\n";
            cout << "Total berat: "
                 << totalBeratTerkirim << " gram\n";

            cout << "================================\n";
        }

        // =================================
        // BERSIHKAN
        // =================================
        else if (perintah == "BERSIHKAN") {
            delAll(A);
            delAll(B);

            cout << "Seluruh paket di A dan B berhasil dihapus.\n";
            cout << "Statistik terkirim tetap dipertahankan.\n";
        }

        // =================================
        // SELESAI
        // =================================
        else if (perintah == "SELESAI") {
            delAll(A);
            delAll(B);

            cout << "Seluruh sisa node berhasil dibebaskan.\n";
            cout << "Program selesai.\n";

            break;
        }

        // =================================
        // PERINTAH TIDAK DIKENAL
        // =================================
        else {
            cout << "Perintah tidak dikenal.\n";
        }

        // Otomatis menampilkan kondisi setelah setiap perintah
        tampilkanQueue(A, B);
    }

    return 0;
}
