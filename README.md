# Aplikasi Penjadwalan Konsultasi Guru Bimbingan

Aplikasi ini dirancang untuk memudahkan manajemen jadwal konsultasi antara mahasiswa dan dosen. Mahasiswa dapat mengatur jadwal bimbingan mereka, sedangkan dosen dapat melihat dan mengelola jadwal tersebut.

## Fitur Utama

### 1. **Manajemen Data Mahasiswa dan Dosen**
   - **Tambah Mahasiswa/Dosen**: Menambahkan data mahasiswa atau dosen baru.
   - **Ubah Mahasiswa/Dosen**: Mengubah informasi mahasiswa atau dosen yang sudah ada.
   - **Hapus Mahasiswa/Dosen**: Menghapus data mahasiswa atau dosen.

### 2. **Manajemen Jadwal Konsultasi**
   - **Tambah Jadwal**: Mahasiswa dapat menambahkan jadwal konsultasi dengan dosen, lengkap dengan tanggal, NIP dosen, dan prioritas.
   - **Lihat Jadwal**: Mahasiswa dapat melihat jadwal konsultasi mereka yang telah terdaftar.
   - **Undo Jadwal Terakhir**: Mahasiswa dapat membatalkan jadwal terakhir yang telah ditambahkan.
   - **Hapus Jadwal**: Dosen dapat menghapus jadwal konsultasi yang terdaftar sesuai dengan kebutuhan.

### 3. **Validasi Data**
   - **Enkripsi Data**: NIM mahasiswa, NIP dosen, dan tanggal jadwal bimbingan dienkripsi menggunakan metode XOR untuk meningkatkan keamanan.
   - **Validasi Tanggal**: Memastikan format tanggal yang dimasukkan oleh mahasiswa dan dosen sesuai dengan format `yyyy-mm-dd` dan tanggal yang valid (termasuk pengecekan jumlah hari pada setiap bulan).

### 4. **Antarmuka Pengguna**
   - **Menu Mahasiswa**: Mahasiswa dapat memilih untuk menambah, melihat, atau membatalkan jadwal bimbingan.
   - **Menu Dosen**: Dosen dapat melihat jadwal konsultasi dan menghapus jadwal yang tidak diperlukan.
