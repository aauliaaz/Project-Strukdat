#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const char KEY = 'K'; // Kunci untuk enkripsi XOR

string encrypt(string data) {
    for (char &c : data) c ^= KEY;
    return data;
}

string decrypt(string data) {
    return encrypt(data); // XOR ulang akan mengembalikan nilai asli
}

struct Mahasiswa {
    string nama;
    string nim;
};

struct Dosen {
    string nama;
    string nip;
};

struct JadwalBimbingan {
    string tanggal;
    string nim;
    string nip;
    int prioritas;
};

// Struktur untuk Queue manual
struct Queue {
    vector<JadwalBimbingan> data;

    void enqueue(JadwalBimbingan j) {
        data.push_back(j);
    }

    JadwalBimbingan dequeue() {
        if (data.empty()) {
            throw runtime_error("Queue kosong");
        }
        JadwalBimbingan j = data.front();
        data.erase(data.begin());
        return j;
    }

    bool empty() {
        return data.empty();
    }

    void tampilkan(string nip) {
        // Sorting berdasarkan tanggal naik dan prioritas naik (1 = prioritas tertinggi)
        vector<JadwalBimbingan> temp;
        for (auto &j : data) {
            if (decrypt(j.nip) == nip) {
                temp.push_back(j);
            }
        }
        sort(temp.begin(), temp.end(), [](const JadwalBimbingan &a, const JadwalBimbingan &b) {
            string ta = decrypt(a.tanggal);
            string tb = decrypt(b.tanggal);
            if (ta == tb)
                return a.prioritas < b.prioritas;
            return ta < tb;
        });

        for (auto &j : temp) {
            cout << decrypt(j.tanggal) << " | Mahasiswa: " << decrypt(j.nim) << " | Prioritas: " << j.prioritas << endl;
        }
    }

    void hapusSemua(string nip) {
        data.erase(remove_if(data.begin(), data.end(), [&](JadwalBimbingan j) {
            return decrypt(j.nip) == nip;
        }), data.end());
    }
};

vector<Mahasiswa> daftarMahasiswa;
vector<Dosen> daftarDosen;
Queue jadwalQueue;
vector<JadwalBimbingan> undoStack;

bool authMahasiswa(string nim) {
    for (auto &m : daftarMahasiswa) {
        if (m.nim == nim) return true;
    }
    return false;
}

bool authDosen(string nip) {
    for (auto &d : daftarDosen) {
        if (d.nip == nip) return true;
    }
    return false;
}

void tambahMahasiswa() {
    Mahasiswa m;
    cout << "\n[Tambah Mahasiswa]\n";
    cout << "Nama: "; getline(cin, m.nama);
    cout << "NIM : "; getline(cin, m.nim);
    daftarMahasiswa.push_back(m);
    cout << "Mahasiswa ditambahkan.\n";
}

void ubahMahasiswa() {
    string nim;
    cout << "\n[Ubah Mahasiswa]\n";
    cout << "Masukkan NIM: "; getline(cin, nim);
    for (auto &m : daftarMahasiswa) {
        if (m.nim == nim) {
            cout << "Nama baru: "; getline(cin, m.nama);
            cout << "NIM baru : "; getline(cin, m.nim);
            cout << "Data diubah.\n";
            return;
        }
    }
    cout << "Mahasiswa tidak ditemukan.\n";
}

void hapusMahasiswa() {
    string nim;
    cout << "\n[Hapus Mahasiswa]\n";
    cout << "Masukkan NIM: "; getline(cin, nim);
    daftarMahasiswa.erase(remove_if(daftarMahasiswa.begin(), daftarMahasiswa.end(),
        [&](Mahasiswa m){ return m.nim == nim; }), daftarMahasiswa.end());
    cout << "Mahasiswa dihapus jika ada.\n";
}

void kelolaMahasiswa() {
    int pil;
    do {
        cout << "\n[Kelola Mahasiswa]\n1. Tambah\n2. Ubah\n3. Hapus\n0. Kembali\nPilih: ";
        cin >> pil; cin.ignore();
        switch (pil) {
            case 1: tambahMahasiswa(); break;
            case 2: ubahMahasiswa(); break;
            case 3: hapusMahasiswa(); break;
        }
    } while (pil != 0);
}

void tambahDosen() {
    Dosen d;
    cout << "\n[Tambah Dosen]\n";
    cout << "Nama: "; getline(cin, d.nama);
    cout << "NIP : "; getline(cin, d.nip);
    daftarDosen.push_back(d);
    cout << "Dosen ditambahkan.\n";
}

void ubahDosen() {
    string nip;
    cout << "\n[Ubah Dosen]\n";
    cout << "Masukkan NIP: "; getline(cin, nip);
    for (auto &d : daftarDosen) {
        if (d.nip == nip) {
            cout << "Nama baru: "; getline(cin, d.nama);
            cout << "NIP baru : "; getline(cin, d.nip);
            cout << "Data diubah.\n";
            return;
        }
    }
    cout << "Dosen tidak ditemukan.\n";
}

void hapusDosen() {
    string nip;
    cout << "\n[Hapus Dosen]\n";
    cout << "Masukkan NIP: "; getline(cin, nip);
    daftarDosen.erase(remove_if(daftarDosen.begin(), daftarDosen.end(),
        [&](Dosen d){ return d.nip == nip; }), daftarDosen.end());
    cout << "Dosen dihapus jika ada.\n";
}

void kelolaDosen() {
    int pil;
    do {
        cout << "\n[Kelola Dosen]\n1. Tambah\n2. Ubah\n3. Hapus\n0. Kembali\nPilih: ";
        cin >> pil; cin.ignore();
        switch (pil) {
            case 1: tambahDosen(); break;
            case 2: ubahDosen(); break;
            case 3: hapusDosen(); break;
        }
    } while (pil != 0);
}

void tambahJadwalMahasiswa(string nim) {
    JadwalBimbingan j;
    j.nim = encrypt(nim);
    cout << "Tanggal (yyyy-mm-dd): "; getline(cin, j.tanggal);
    j.tanggal = encrypt(j.tanggal);
    cout << "NIP Dosen: "; getline(cin, j.nip);
    j.nip = encrypt(j.nip);
    cout << "Prioritas (1=sangat penting): "; cin >> j.prioritas; cin.ignore();
    jadwalQueue.enqueue(j);
    undoStack.push_back(j);
    cout << "Jadwal ditambahkan.\n";
}

void tampilkanJadwalMahasiswa(string nim) {
    cout << "\n[Jadwal Anda]\n";

    // Sorting jadwal mahasiswa (tanggal naik, prioritas naik)
    vector<JadwalBimbingan> temp;
    for (auto &j : jadwalQueue.data) {
        if (decrypt(j.nim) == nim) {
            temp.push_back(j);
        }
    }
    sort(temp.begin(), temp.end(), [](const JadwalBimbingan &a, const JadwalBimbingan &b) {
        string ta = decrypt(a.tanggal);
        string tb = decrypt(b.tanggal);
        if (ta == tb)
            return a.prioritas < b.prioritas;
        return ta < tb;
    });

    for (auto &j : temp) {
        cout << decrypt(j.tanggal) << " | Dosen: " << decrypt(j.nip) << " | Prioritas: " << j.prioritas << endl;
    }
}

void undoJadwalMahasiswa(string nim) {
    for (int i = undoStack.size() - 1; i >= 0; --i) {
        if (decrypt(undoStack[i].nim) == nim) {
            JadwalBimbingan j = undoStack[i];
            undoStack.erase(undoStack.begin() + i);
            jadwalQueue.data.erase(remove_if(jadwalQueue.data.begin(), jadwalQueue.data.end(), [&](JadwalBimbingan x) {
                return x.nim == j.nim && x.nip == j.nip && x.tanggal == j.tanggal && x.prioritas == j.prioritas;
            }), jadwalQueue.data.end());
            cout << "Jadwal terakhir dibatalkan.\n";
            return;
        }
    }
    cout << "Tidak ada jadwal untuk dibatalkan.\n";
}

void menuMahasiswa() {
    string nim;
    cout << "Masukkan NIM: "; getline(cin, nim);
    if (!authMahasiswa(nim)) {
        cout << "Akses ditolak.\n";
        return;
    }
    int pil;
    do {
        cout << "\n[Menu Mahasiswa]\n1. Tambah Jadwal\n2. Lihat Jadwal\n3. Undo Jadwal Terakhir\n0. Logout\nPilih: ";
        cin >> pil; cin.ignore();
        switch (pil) {
            case 1: tambahJadwalMahasiswa(nim); break;
            case 2: tampilkanJadwalMahasiswa(nim); break;
            case 3: undoJadwalMahasiswa(nim); break;
        }
    } while (pil != 0);
}

void tampilkanJadwalDosen(string nip) {
    cout << "\n[Jadwal Dosen]\n";
    jadwalQueue.tampilkan(nip);
}

void hapusJadwalDosenPerItem(string nip) {
    // Ambil semua jadwal dosen tersebut ke vector sementara
    vector<JadwalBimbingan> temp;
    for (auto &j : jadwalQueue.data) {
        if (decrypt(j.nip) == nip) {
            temp.push_back(j);
        }
    }

    if (temp.empty()) {
        cout << "Tidak ada jadwal untuk dihapus.\n";
        return;
    }

    // Sorting supaya tampil rapi (tanggal asc, prioritas asc)
    sort(temp.begin(), temp.end(), [](const JadwalBimbingan &a, const JadwalBimbingan &b) {
        string ta = decrypt(a.tanggal);
        string tb = decrypt(b.tanggal);
        if (ta == tb)
            return a.prioritas < b.prioritas;
        return ta < tb;
    });

    cout << "\n[Jadwal Anda]\n";
    for (size_t i = 0; i < temp.size(); ++i) {
        cout << i+1 << ". " << decrypt(temp[i].tanggal) 
             << " | Mahasiswa: " << decrypt(temp[i].nim)
             << " | Prioritas: " << temp[i].prioritas << endl;
    }

    cout << "Masukkan nomor jadwal yang ingin dihapus (0 batal): ";
    int pilihan;
    cin >> pilihan; cin.ignore();

    if (pilihan < 1 || pilihan > (int)temp.size()) {
        cout << "Batal hapus.\n";
        return;
    }

    JadwalBimbingan ygDihapus = temp[pilihan - 1];

    // Hapus dari queue asli
    jadwalQueue.data.erase(remove_if(jadwalQueue.data.begin(), jadwalQueue.data.end(),
        [&](JadwalBimbingan j){
            return j.nim == ygDihapus.nim && j.nip == ygDihapus.nip
                && j.tanggal == ygDihapus.tanggal && j.prioritas == ygDihapus.prioritas;
        }), jadwalQueue.data.end());

    cout << "Jadwal berhasil dihapus.\n";
}

void menuDosen() {
    string nip;
    cout << "Masukkan NIP: "; getline(cin, nip);
    if (!authDosen(nip)) {
        cout << "Akses ditolak.\n";
        return;
    }
    int pil;
    do {
        cout << "\n[Menu Dosen]\n1. Lihat Jadwal\n2. Hapus Jadwal\n0. Logout\nPilih: ";
        cin >> pil; cin.ignore();
        switch (pil) {
            case 1: tampilkanJadwalDosen(nip); break;
            case 2: hapusJadwalDosenPerItem(nip); break;
        }
    } while (pil != 0);
}

void menuUtama() {
    int pil;
    do {
        cout << "\n+===============================+\n";
        cout << "|  APLIKASI JADWAL BIMBINGAN   |\n";
        cout << "+===============================+\n";
        cout << "1. Login Mahasiswa\n";
        cout << "2. Login Dosen\n";
        cout << "3. Kelola Mahasiswa\n";
        cout << "4. Kelola Dosen\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pil; cin.ignore();
        switch (pil) {
            case 1: menuMahasiswa(); break;
            case 2: menuDosen(); break;
            case 3: kelolaMahasiswa(); break;
            case 4: kelolaDosen(); break;
        }
    } while (pil != 0);
}

int main() {
    // Contoh data awal
    daftarMahasiswa.push_back({"Abdul", "M001"});
    daftarDosen.push_back({"Pak Budi", "D001"});
    menuUtama();
    cout << "Terima kasih sudah menggunakan aplikasi.\n";
    return 0;
}