#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

const char KEY = 'K'; // Kunci untuk enkripsi XOR

string encrypt(string data) {
    for (char &c : data) c ^= KEY;
    return data;
}

string decrypt(string data) {
    return encrypt(data); // XOR ulang akan mengembalikan nilai asli
}

struct siswa {
    string nama;
    string nisn;
};

struct Guru {
    string nama;
    string nip;
};

struct JadwalBimbingan {
    string tanggal;
    string nisn;
    string nip;
    int prioritas;
};

// Fungsi validasi tanggal yyyy-mm-dd dengan cek bulan dan hari valid
bool validasiTanggal(const string& tanggal) {
    if (tanggal.length() != 10) return false;
    if (tanggal[4] != '-' || tanggal[7] != '-') return false;

    for (int i = 0; i < 4; ++i)
        if (!isdigit(tanggal[i])) return false;

    if (!isdigit(tanggal[5]) || !isdigit(tanggal[6])) return false;
    int bulan = stoi(tanggal.substr(5, 2));
    if (bulan < 1 || bulan > 12) return false;

    if (!isdigit(tanggal[8]) || !isdigit(tanggal[9])) return false;
    int hari = stoi(tanggal.substr(8, 2));

    // Jumlah hari per bulan (Februari 28, belum cek kabisat)
    int maxHari[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (hari < 1 || hari > maxHari[bulan - 1]) return false;

    return true;
}

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
            cout << decrypt(j.tanggal) << " | siswa: " << decrypt(j.nisn) << " | Prioritas: " << j.prioritas << endl;
        }
    }

    void hapusSemua(string nip) {
        data.erase(remove_if(data.begin(), data.end(), [&](JadwalBimbingan j) {
            return decrypt(j.nip) == nip;
        }), data.end());
    }
};

vector<siswa> daftarSiswa;
vector<Guru> daftarGuru;
Queue jadwalQueue;
vector<JadwalBimbingan> undoStack;

bool authSiswa(string nisn) {
    for (auto &m : daftarSiswa) {
        if (m.nisn == nisn) return true;
    }
    return false;
}

bool authGuru(string nip) {
    for (auto &d : daftarGuru) {
        if (d.nip == nip) return true;
    }
    return false;
}

void tambahSiswa() {
    siswa m;
    cout << "\n[Tambah siswa]\n";
    cout << "Nama: "; getline(cin, m.nama);
    if (m.nama.empty()) {
        cout << "Nama tidak boleh kosong.\n";
        return;
    }
    cout << "NISN : "; getline(cin, m.nisn);
    if (m.nisn.empty()) {
        cout << "NISN tidak boleh kosong.\n";
        return;
    }
    daftarSiswa.push_back(m);
    cout << "siswa ditambahkan.\n";
}

void ubahSiswa() {
    string nisn;
    cout << "\n[Ubah siswa]\n";
    cout << "Masukkan NISN: "; getline(cin, nisn);
    for (auto &m : daftarSiswa) {
        if (m.nisn == nisn) {
            cout << "Nama baru: "; getline(cin, m.nama);
            if (m.nama.empty()) {
                cout << "Nama tidak boleh kosong.\n";
                return;
            }
            cout << "NISN baru : "; getline(cin, m.nisn);
            if (m.nisn.empty()) {
                cout << "NISN tidak boleh kosong.\n";
                return;
            }
            cout << "Data diubah.\n";
            return;
        }
    }
    cout << "siswa tidak ditemukan.\n";
}

void hapusSiswa() {
    string nisn;
    cout << "\n[Hapus siswa]\n";
    cout << "Masukkan NISN: "; getline(cin, nisn);
    size_t before = daftarSiswa.size();
    daftarSiswa.erase(remove_if(daftarSiswa.begin(), daftarSiswa.end(),
        [&](siswa m){ return m.nisn == nisn; }), daftarSiswa.end());
    if (daftarSiswa.size() < before)
        cout << "siswa dihapus.\n";
    else
        cout << "siswa tidak ditemukan.\n";
}

void kelolaSiswa() {
    int pil;
    do {
        cout << "\n[Kelola siswa]\n1. Tambah\n2. Ubah\n3. Hapus\n0. Kembali\nPilih: ";
        cin >> pil; cin.ignore();
        if (pil < 0 || pil > 3) {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        switch (pil) {
            case 1: tambahSiswa(); break;
            case 2: ubahSiswa(); break;
            case 3: hapusSiswa(); break;
        }
    } while (pil != 0);
}

void tambahGuru() {
    Guru d;
    cout << "\n[Tambah Guru]\n";
    cout << "Nama: "; getline(cin, d.nama);
    if (d.nama.empty()) {
        cout << "Nama tidak boleh kosong.\n";
        return;
    }
    cout << "NIP : "; getline(cin, d.nip);
    if (d.nip.empty()) {
        cout << "NIP tidak boleh kosong.\n";
        return;
    }
    daftarGuru.push_back(d);
    cout << "Guru ditambahkan.\n";
}

void ubahGuru() {
    string nip;
    cout << "\n[Ubah Guru]\n";
    cout << "Masukkan NIP: "; getline(cin, nip);
    for (auto &d : daftarGuru) {
        if (d.nip == nip) {
            cout << "Nama baru: "; getline(cin, d.nama);
            if (d.nama.empty()) {
                cout << "Nama tidak boleh kosong.\n";
                return;
            }
            cout << "NIP baru : "; getline(cin, d.nip);
            if (d.nip.empty()) {
                cout << "NIP tidak boleh kosong.\n";
                return;
            }
            cout << "Data diubah.\n";
            return;
        }
    }
    cout << "Guru tidak ditemukan.\n";
}

void hapusGuru() {
    string nip;
    cout << "\n[Hapus Guru]\n";
    cout << "Masukkan NIP: "; getline(cin, nip);
    size_t before = daftarGuru.size();
    daftarGuru.erase(remove_if(daftarGuru.begin(), daftarGuru.end(),
        [&](Guru d){ return d.nip == nip; }), daftarGuru.end());
    if (daftarGuru.size() < before)
        cout << "Guru dihapus.\n";
    else
        cout << "Guru tidak ditemukan.\n";
}

void kelolaGuru() {
    int pil;
    do {
        cout << "\n[Kelola Guru]\n1. Tambah\n2. Ubah\n3. Hapus\n0. Kembali\nPilih: ";
        cin >> pil; cin.ignore();
        if (pil < 0 || pil > 3) {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        switch (pil) {
            case 1: tambahGuru(); break;
            case 2: ubahGuru(); break;
            case 3: hapusGuru(); break;
        }
    } while (pil != 0);
}

void tambahJadwalSiswa(string nisn) {
    JadwalBimbingan j;
    j.nisn = encrypt(nisn);
    cout << "Tanggal (yyyy-mm-dd): ";
    getline(cin, j.tanggal);
    if (!validasiTanggal(j.tanggal)) {
        cout << "Format tanggal tidak valid. Harus yyyy-mm-dd dan tanggal benar.\n";
        return;
    }
    j.tanggal = encrypt(j.tanggal);

    cout << "NIP Guru: ";
    getline(cin, j.nip);
    if (j.nip.empty()) {
        cout << "NIP tidak boleh kosong.\n";
        return;
    }
    j.nip = encrypt(j.nip);

    cout << "Prioritas (1 = sangat penting): ";
    cin >> j.prioritas; cin.ignore();
    if (j.prioritas <= 0) {
        cout << "Prioritas harus angka positif.\n";
        return;
    }

    jadwalQueue.enqueue(j);
    undoStack.push_back(j);
    cout << "Jadwal ditambahkan.\n";
}

void tampilkanJadwalSiswa(string nisn) {
    cout << "\n[Jadwal Anda]\n";
    vector<JadwalBimbingan> temp;
    for (auto &j : jadwalQueue.data) {
        if (decrypt(j.nisn) == nisn) {
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
        cout << decrypt(j.tanggal) << " | Guru: " << decrypt(j.nip) << " | Prioritas: " << j.prioritas << endl;
    }
}

void undoJadwalSiswa(string nisn) {
    for (int i = (int)undoStack.size() - 1; i >= 0; --i) {
        if (decrypt(undoStack[i].nisn) == nisn) {
            JadwalBimbingan j = undoStack[i];
            undoStack.erase(undoStack.begin() + i);
            jadwalQueue.data.erase(remove_if(jadwalQueue.data.begin(), jadwalQueue.data.end(), [&](JadwalBimbingan x) {
                return x.nisn == j.nisn && x.nip == j.nip && x.tanggal == j.tanggal && x.prioritas == j.prioritas;
            }), jadwalQueue.data.end());
            cout << "Jadwal terakhir dibatalkan.\n";
            return;
        }
    }
    cout << "Tidak ada jadwal untuk dibatalkan.\n";
}

void menuSiswa() {
    string nisn;
    cout << "Masukkan NISN: "; getline(cin, nisn);
    if (!authSiswa(nisn)) {
        cout << "Akses ditolak.\n";
        return;
    }
    int pil;
    do {
        cout << "\n[Menu siswa]\n1. Tambah Jadwal\n2. Lihat Jadwal\n3. Undo Jadwal Terakhir\n0. Logout\nPilih: ";
        cin >> pil; cin.ignore();
        if (pil < 0 || pil > 3) {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        switch (pil) {
            case 1: tambahJadwalSiswa(nisn); break;
            case 2: tampilkanJadwalSiswa(nisn); break;
            case 3: undoJadwalSiswa(nisn); break;
        }
    } while (pil != 0);
}

void tampilkanJadwalGuru(string nip) {
    cout << "\n[Jadwal Guru]\n";
    jadwalQueue.tampilkan(nip);
}

void hapusJadwalGuruPerItem(string nip) {
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
             << " | siswa: " << decrypt(temp[i].nisn)
             << " | Prioritas: " << temp[i].prioritas << endl;
    }
    cout << "Masukkan nomor jadwal yang ingin dihapus (0 batal): ";
    int pilihan;
    cin >> pilihan; cin.ignore();
    if (pilihan == 0) {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }
    if (pilihan < 1 || pilihan > (int)temp.size()) {
        cout << "Nomor pilihan tidak valid. Silakan coba lagi.\n";
        return;
    }
    JadwalBimbingan ygDihapus = temp[pilihan - 1];
    jadwalQueue.data.erase(remove_if(jadwalQueue.data.begin(), jadwalQueue.data.end(),
        [&](JadwalBimbingan j){
            return j.nisn == ygDihapus.nisn && j.nip == ygDihapus.nip
                && j.tanggal == ygDihapus.tanggal && j.prioritas == ygDihapus.prioritas;
        }), jadwalQueue.data.end());
    cout << "Jadwal berhasil dihapus.\n";
}

void menuGuru() {
    string nip;
    cout << "Masukkan NIP: "; getline(cin, nip);
    if (!authGuru(nip)) {
        cout << "Akses ditolak.\n";
        return;
    }
    int pil;
    do {
        cout << "\n[Menu Guru]\n1. Lihat Jadwal\n2. Hapus Jadwal\n0. Logout\nPilih: ";
        cin >> pil; cin.ignore();
        if (pil < 0 || pil > 2) {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        switch (pil) {
            case 1: tampilkanJadwalGuru(nip); break;
            case 2: hapusJadwalGuruPerItem(nip); break;
        }
    } while (pil != 0);
}

void menuUtama() {
    int pil;
    do {
        cout << "\n+===============================+\n";
        cout << "|  APLIKASI JADWAL BIMBINGAN   |\n";
        cout << "+===============================+\n";
        cout << "1. Login siswa\n";
        cout << "2. Login Guru\n";
        cout << "3. Kelola siswa\n";
        cout << "4. Kelola Guru\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pil; cin.ignore();
        if (pil < 0 || pil > 4) {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            continue;
        }
        switch (pil) {
            case 1: menuSiswa(); break;
            case 2: menuGuru(); break;
            case 3: kelolaSiswa(); break;
            case 4: kelolaGuru(); break;
        }
    } while (pil != 0);
}

int main() {
    daftarSiswa.push_back({"Aul", "M001"});
    daftarGuru.push_back({"Pak Paul", "D001"});
    menuUtama();
    cout << "Terima kasih sudah menggunakan aplikasi.\n";
    return 0;
}