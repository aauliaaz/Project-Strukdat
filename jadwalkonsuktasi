#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Siswa
{
    string id_terenkripsi;
    string nama_terenkripsi;
    string jadwal;
    int prioritas;
};

queue<Siswa> antrianKonsultasi;
stack<queue<Siswa>> undoStack;

// Fungsi enkripsi sederhana (Caesar Cipher)
string enkripsi(string teks, int kunci = 3)
{
    for (char &c : teks)
    {
        if (isalpha(c))
        {
            c = (isupper(c)) ? ((c - 'A' + kunci) % 26 + 'A') : ((c - 'a' + kunci) % 26 + 'a');
        }
    }
    return teks;
}

// Fungsi untuk menambahkan jadwal konsultasi
void tambahKonsultasi()
{
    Siswa siswa;
    string id, nama, jadwal;
    int prioritas;

    cout << "ID Siswa: ";
    cin >> id;
    cout << "Nama Siswa: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Jadwal Konsultasi (contoh: Senin 09:00): ";
    getline(cin, jadwal);
    cout << "Prioritas (semakin kecil semakin penting): ";
    cin >> prioritas;

    siswa.id_terenkripsi = enkripsi(id);
    siswa.nama_terenkripsi = enkripsi(nama);
    siswa.jadwal = jadwal;
    siswa.prioritas = prioritas;

    // Simpan state sebelumnya untuk undo
    undoStack.push(antrianKonsultasi);
    antrianKonsultasi.push(siswa);

    cout << "✅ Jadwal berhasil ditambahkan.\n";
}

// Fungsi untuk menampilkan antrian
void tampilkanJadwal()
{
    queue<Siswa> temp = antrianKonsultasi;
    int i = 1;
    cout << "\n📅 Jadwal Konsultasi:\n";
    while (!temp.empty())
    {
        Siswa s = temp.front();
        temp.pop();
        cout << i++ << ". Jadwal: " << s.jadwal << " | Prioritas: " << s.prioritas << endl;
    }
}

// Fungsi untuk menyusun prioritas (sorting)
void urutkanBerdasarkanPrioritas()
{
    vector<Siswa> daftar;
    while (!antrianKonsultasi.empty())
    {
        daftar.push_back(antrianKonsultasi.front());
        antrianKonsultasi.pop();
    }

    sort(daftar.begin(), daftar.end(), [](Siswa a, Siswa b)
         { return a.prioritas < b.prioritas; });

    undoStack.push(antrianKonsultasi); // Simpan sebelum sorting
    for (auto &s : daftar)
    {
        antrianKonsultasi.push(s);
    }

    cout << "✅ Jadwal diurutkan berdasarkan prioritas.\n";
}

// Fungsi undo
void undo()
{
    if (!undoStack.empty())
    {
        antrianKonsultasi = undoStack.top();
        undoStack.pop();
        cout << "↩  Undo berhasil dilakukan.\n";
    }
    else
    {
        cout << "⚠  Tidak ada tindakan untuk di-undo.\n";
    }
}

// Menu utama
void menu()
{
    int pilihan;
    do
    {
        cout << "\n=== Aplikasi Penjadwalan Konsultasi Guru Bimbingan ===\n";
        cout << "1. Tambah Jadwal Konsultasi\n";
        cout << "2. Urutkan Berdasarkan Prioritas\n";
        cout << "3. Tampilkan Jadwal\n";
        cout << "4. Undo\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahKonsultasi();
            break;
        case 2:
            urutkanBerdasarkanPrioritas();
            break;
        case 3:
            tampilkanJadwal();
            break;
        case 4:
            undo();
            break;
        case 0:
            cout << "👋 Keluar dari aplikasi.\n";
            break;
        default:
            cout << "❌ Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

int main()
{
    menu();
    return 0;
}
