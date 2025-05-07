#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Struktur data mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    int prioritas;
};

//queue manual
const int MAKS = 100;
Mahasiswa antrianManual[MAKS];
int front = 0, rear = 0;

bool isAntrianKosong() {
    return front == rear;
}

bool isAntrianPenuh() {
    return rear == MAKS;
}

void enqueue(Mahasiswa m) {
    if (!isAntrianPenuh()) {
        antrianManual[rear++] = m;
    } else {
        cout << "Antrian penuh, tidak bisa menambahkan mahasiswa.\n";
    }
}

Mahasiswa dequeue() {
    if (!isAntrianKosong()) {
        return antrianManual[front++];
    } else {
        cout << "Antrian kosong.\n";
        return Mahasiswa(); // Mahasiswa kosong
    }
}

void resetAntrian() {
    front = rear = 0;
}

//data
stack<vector<Mahasiswa>> historiJadwal;
vector<Mahasiswa> jadwal;

// Fungsi enkripsi sederhana
string enkripsi(string data, int kunci = 3) {
    for (char &c : data) {
        if (isalpha(c))
            c = (isupper(c) ? 'A' + (c - 'A' + kunci) % 26 : 'a' + (c - 'a' + kunci) % 26);
    }
    return data;
}

// Tambah mahasiswa ke antrian
void daftarMahasiswa() {
    Mahasiswa m;
    cout << "\n[+] Pendaftaran Konsultasi Mahasiswa\n";
    cin.ignore();
    cout << "Nama  : "; getline(cin, m.nama);
    cout << "NIM   : "; getline(cin, m.nim);
    cout << "Prioritas (1=sangat penting, 10=biasa): "; cin >> m.prioritas;
    enqueue(m);
    cout << "Mahasiswa berhasil didaftarkan ke antrian.\n";
}


// Tampilkan isi antrian
void tampilkanAntrian() {
    cout << "\n[Daftar Antrian Mahasiswa]\n";
    if (isAntrianKosong()) {
        cout << "(Antrian kosong)\n";
        return;
    }
    for (int i = front; i < rear; ++i) {
        Mahasiswa m = antrianManual[i];
        printf("%2d. %-20s | NIM: %-10s | Prioritas: %d\n", i - front + 1, m.nama.c_str(), m.nim.c_str(), m.prioritas);
    }
}


// Proses antrian ke jadwal (sorting)
void prosesAntrianKeJadwal() {
    while (!isAntrianKosong()) {
        jadwal.push_back(dequeue());
    }
    sort(jadwal.begin(), jadwal.end(), [](Mahasiswa a, Mahasiswa b) {
        return a.prioritas < b.prioritas;
    });
    cout << "Antrian diproses menjadi jadwal bimbingan berdasarkan prioritas.\n";
}


// Tampilkan jadwal
void tampilkanJadwal(bool terenkripsi = false) {
    cout << "\n[Jadwal Bimbingan Mahasiswa]\n";
    if (jadwal.empty()) {
        cout << "(Belum ada jadwal)\n";
        return;
    }
    for (int i = 0; i < jadwal.size(); ++i) {
        Mahasiswa m = jadwal[i];
        string nama = terenkripsi ? enkripsi(m.nama) : m.nama;
        string nim  = terenkripsi ? enkripsi(m.nim) : m.nim;
        printf("%2d. %-20s | NIM: %-10s | Prioritas: %d\n", i + 1, nama.c_str(), nim.c_str(), m.prioritas);
    }
}

// Ubah data jadwal
void ubahJadwal() {
    if (jadwal.empty()) {
        cout << "(Tidak ada jadwal yang bisa diubah)\n";
        return;
    }
    historiJadwal.push(jadwal);
    int idx;
    cout << "\n[Ubah Jadwal Mahasiswa]\n";
    cout << "Nomor mahasiswa yang ingin diubah: "; cin >> idx;
    if (idx < 1 || idx > jadwal.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }
    cin.ignore();
    cout << "Nama baru    : "; getline(cin, jadwal[idx-1].nama);
    cout << "NIM baru     : "; getline(cin, jadwal[idx-1].nim);
    cout << "Prioritas baru: "; cin >> jadwal[idx-1].prioritas;
    cout << "Data mahasiswa berhasil diubah.\n";
}

// Undo perubahan jadwal
void undoJadwal() {
    if (historiJadwal.empty()) {
        cout << "(Tidak ada histori untuk undo)\n";
        return;
    }
    jadwal = historiJadwal.top();
    historiJadwal.pop();
    cout << "Perubahan terakhir berhasil dibatalkan.\n";
}

// Cari mahasiswa dalam jadwal
void cariMahasiswa() {
    if (jadwal.empty()) {
        cout << "(Jadwal kosong)\n";
        return;
    }
    cin.ignore();
    string key;
    cout << "\n[Cari Mahasiswa]\n";
    cout << "Masukkan nama atau NIM: ";
    getline(cin, key);
    bool ketemu = false;
    for (const auto &m : jadwal) {
        if (m.nama.find(key) != string::npos || m.nim.find(key) != string::npos) {
            cout << "✓ " << m.nama << " | NIM: " << m.nim << " | Prioritas: " << m.prioritas << "\n";
            ketemu = true;
        }
    }
    if (!ketemu)
        cout << "Mahasiswa tidak ditemukan.\n";
}

// Ekspor jadwal ke file
void eksporJadwal() {
    ofstream file("jadwal_bimbingan.txt");
    if (!file) {
        cout << "Gagal membuat file jadwal_bimbingan.txt\n";
        return;
    }
    for (const auto &m : jadwal)
        file << m.nama << "\t" << m.nim << "\t" << m.prioritas << "\n";
    file.close();
    cout << "Jadwal disimpan ke 'jadwal_bimbingan.txt'\n";
}

// Menu utama
void menu() {
    int pil;
    do {
        cout << "\n+==============================================+\n";
        cout << "|   APLIKASI PENJADWALAN KONSULTASI GURU BIMBINGAN     |\n";
        cout << "+==============================================+\n";
        cout << " 1. Daftar Konsultasi Mahasiswa\n";
        cout << " 2. Lihat Antrian Mahasiswa\n";
        cout << " 3. Proses Antrian ke Jadwal\n";
        cout << " 4. Lihat Jadwal Bimbingan\n";
        cout << " 5. Lihat Jadwal (Terenkripsi)\n";
        cout << " 6. Ubah Jadwal Mahasiswa\n";
        cout << " 7. Undo Perubahan Jadwal\n";
        cout << " 8. Cari Mahasiswa\n";
        cout << " 9. Ekspor Jadwal ke File\n";
        cout << " 0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pil;

        switch (pil) {
            case 1: daftarMahasiswa(); break;
            case 2: tampilkanAntrian(); break;
            case 3: prosesAntrianKeJadwal(); break;
            case 4: tampilkanJadwal(false); break;
            case 5: tampilkanJadwal(true); break;
            case 6: ubahJadwal(); break;
            case 7: undoJadwal(); break;
            case 8: cariMahasiswa(); break;
            case 9: eksporJadwal(); break;
            case 0: cout << "Terima kasih. Program selesai.\n"; break;
            default: cout << "Menu tidak valid.\n";
        }
    } while (pil != 0);
}

// Fungsi utama
int main() {
    menu();
    return 0;
}