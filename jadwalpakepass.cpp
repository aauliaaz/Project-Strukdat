#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional> // Untuk std::hash
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    string passwordHash;
};

struct Dosen {
    string nama;
    string nip;
    string passwordHash;
};

struct JadwalBimbingan {
    string tanggal;
    string nim;
    string nip;
    int prioritas;
};

vector<Mahasiswa> daftarMahasiswa;
vector<Dosen> daftarDosen;
vector<JadwalBimbingan> jadwal;

string simpleHash(string input) {
    hash<string> hasher;
    return to_string(hasher(input));
}

void tambahMahasiswa() {
    Mahasiswa m;
    string pass;
    cout << "\n[Tambah Mahasiswa]\n";
    cout << "Nama: "; getline(cin, m.nama);
    cout << "NIM : "; getline(cin, m.nim);
    cout << "Password: "; getline(cin, pass);
    m.passwordHash = simpleHash(pass);
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
            cout << "Password baru: "; 
            string pass; getline(cin, pass);
            m.passwordHash = simpleHash(pass);
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
    string pass;
    cout << "\n[Tambah Dosen]\n";
    cout << "Nama: "; getline(cin, d.nama);
    cout << "NIP : "; getline(cin, d.nip);
    cout << "Password: "; getline(cin, pass);
    d.passwordHash = simpleHash(pass);
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
            cout << "Password baru: ";
            string pass; getline(cin, pass);
            d.passwordHash = simpleHash(pass);
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
    j.nim = nim;
    cout << "Tanggal (yyyy-mm-dd): "; getline(cin, j.tanggal);
    cout << "NIP Dosen: "; getline(cin, j.nip);
    cout << "Prioritas (1=sangat penting): "; cin >> j.prioritas; cin.ignore();
    jadwal.push_back(j);
    cout << "Jadwal ditambahkan.\n";
}

void tampilkanJadwalMahasiswa(string nim) {
    cout << "\n[Jadwal Anda]\n";
    for (auto &j : jadwal) {
        if (j.nim == nim)
            cout << j.tanggal << " | Dosen: " << j.nip << " | Prioritas: " << j.prioritas << endl;
    }
}

void hapusJadwalMahasiswa(string nim) {
    jadwal.erase(remove_if(jadwal.begin(), jadwal.end(),
        [&](JadwalBimbingan j){ return j.nim == nim; }), jadwal.end());
    cout << "Jadwal Anda dihapus.\n";
}

void menuMahasiswa() {
    string nim, pass;
    cout << "Masukkan NIM: "; getline(cin, nim);
    cout << "Masukkan Password: "; getline(cin, pass);
    for (auto &m : daftarMahasiswa) {
        if (m.nim == nim && m.passwordHash == simpleHash(pass)) {
            int pil;
            do {
                cout << "\n[Menu Mahasiswa]\n1. Tambah Jadwal\n2. Lihat Jadwal\n3. Hapus Jadwal\n0. Logout\nPilih: ";
                cin >> pil; cin.ignore();
                switch (pil) {
                    case 1: tambahJadwalMahasiswa(nim); break;
                    case 2: tampilkanJadwalMahasiswa(nim); break;
                    case 3: hapusJadwalMahasiswa(nim); break;
                }
            } while (pil != 0);
            return;
        }
    }
    cout << "Akses ditolak. NIM/Password salah.\n";
}

void tampilkanJadwalDosen(string nip) {
    cout << "\n[Jadwal Dosen]\n";
    for (auto &j : jadwal) {
        if (j.nip == nip)
            cout << j.tanggal << " | Mahasiswa: " << j.nim << " | Prioritas: " << j.prioritas << endl;
    }
}

void hapusJadwalDosen(string nip) {
    jadwal.erase(remove_if(jadwal.begin(), jadwal.end(),
        [&](JadwalBimbingan j){ return j.nip == nip; }), jadwal.end());
    cout << "Semua jadwal bimbingan Anda dihapus.\n";
}

void menuDosen() {
    string nip, pass;
    cout << "Masukkan NIP: "; getline(cin, nip);
    cout << "Masukkan Password: "; getline(cin, pass);
    for (auto &d : daftarDosen) {
        if (d.nip == nip && d.passwordHash == simpleHash(pass)) {
            int pil;
            do {
                cout << "\n[Menu Dosen]\n1. Lihat Jadwal\n2. Hapus Jadwal\n0. Logout\nPilih: ";
                cin >> pil; cin.ignore();
                switch (pil) {
                    case 1: tampilkanJadwalDosen(nip); break;
                    case 2: hapusJadwalDosen(nip); break;
                }
            } while (pil != 0);
            return;
        }
    }
    cout << "Akses ditolak. NIP/Password salah.\n";
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
    menuUtama();
    return 0;
}
