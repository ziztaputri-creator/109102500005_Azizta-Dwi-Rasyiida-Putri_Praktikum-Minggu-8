
#include "Buffer.h"
#include <sstream>
#include <string>

int main() {
    Queue Q = createQueue();

    string input, perintah;

    cout << "====================================\n";
    cout << "       BUFFER PENCATATAN HASIL UKUR\n";
    cout << "       VERSI 3 - CIRCULAR QUEUE\n";
    cout << "====================================\n";

    while (true) {
        cout << "\nMasukkan perintah: ";
        getline(cin, input);

        stringstream ss(input);
        perintah = "";

        if (!(ss >> perintah)) {
            cout << "Perintah kosong.\n";
            continue;
        }

        // TULIS
        if (perintah == "TULIS") {
            int k;
            int nilai[KAPASITAS];
            string tambahan;

            if (!(ss >> k)) {
                cout << "Format salah! TULIS k v1 ... vk\n";
                continue;
            }

            if (k < 1 || k > KAPASITAS) {
                cout << "Ditolak: k harus 1-6.\n";
                continue;
            }

            bool valid = true;

            for (int i = 0; i < k; i++) {
                if (!(ss >> nilai[i])) {
                    valid = false;
                    break;
                }

                if (nilai[i] < -1000 || nilai[i] > 1000) {
                    valid = false;
                }
            }

            if (ss >> tambahan) {
                valid = false;
            }

            if (!valid) {
                cout << "Ditolak: format atau nilai tidak valid.\n";
            }
            else if (KAPASITAS - nbQueue(Q) < k) {
                cout << "Ditolak: ruang kosong tidak mencukupi.\n";
                cout << "Ruang tersedia: "
                     << KAPASITAS - nbQueue(Q) << "\n";
            }
            else {
                for (int i = 0; i < k; i++) {
                    enqueue(Q, nilai[i]);
                }

                cout << k << " rekaman berhasil ditulis.\n";
            }
        }

        // AMBIL
        else if (perintah == "AMBIL") {
            int k;
            string tambahan;

            if (!(ss >> k) || (ss >> tambahan)) {
                cout << "Format salah! AMBIL k\n";
                continue;
            }

            if (k <= 0 || k > nbQueue(Q)) {
                cout << "Ditolak: jumlah data tidak valid.\n";
                cout << "Data tersedia: " << nbQueue(Q) << "\n";
            }
            else {
                Rekaman hasil;

                cout << "Data yang diambil:\n";

                for (int i = 0; i < k; i++) {
                    dequeue(Q, hasil);

                    cout << hasil.nomor << ":"
                         << hasil.nilai << "\n";
                }

                cout << k << " rekaman berhasil diambil.\n";
            }
        }

        // LIHAT
        else if (perintah == "LIHAT") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Format salah! Gunakan LIHAT\n";
            }
            else {
                cout << "\nUrutan FIFO:\n";
                printInfo(Q);

                lihatFisik(Q);
            }
        }

        // RINGKAS
        else if (perintah == "RINGKAS") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Format salah! Gunakan RINGKAS\n";
            }
            else {
                ringkasQueue(Q);
            }
        }

        // KOSONGKAN
        else if (perintah == "KOSONGKAN") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Format salah! Gunakan KOSONGKAN\n";
            }
            else {
                kosongkanQueue(Q);

                cout << "Buffer berhasil dikosongkan.\n";
                cout << "Nomor berikutnya: "
                     << Q.nomorBerikutnya << "\n";

                cout << "Total pergeseran: "
                     << Q.totalPergeseran << "\n";
            }
        }

        // SELESAI
        else if (perintah == "SELESAI") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Format salah! Gunakan SELESAI\n";
                continue;
            }

            cout << "Program selesai.\n";
            break;
        }

        else {
            cout << "Perintah tidak dikenal.\n";
        }
    }

    return 0;
}
