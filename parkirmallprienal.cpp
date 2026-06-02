#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>   
#include <ctime>     
#include <limits>

using namespace std;

const int MAKS_KAPASITAS = 20;

struct Petugas {
    string nama;
    string id;
};

struct Mobil {
    string plat;
    string merk;
    string warna;
    int jam = 0;
    int menit = 0;
    int detik = 0;
};

void inputPetugas(Petugas* p);
void menuUtama(const Petugas* p);
void tambahKendaraan(vector<Mobil>& daftarParkir);
void tampilkanKendaraan(const vector<Mobil>& daftarParkir);
void pembayaranParkir(vector<Mobil>& daftarParkir);

void bersihkanDanTahan() {
    cout << "Tekan Enter untuk kembali ke menu utama...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Menyapu bersih sisa karakter enter di memory
    cin.get(); // Menahan layar secara paksa sampai tombol enter ditekan
    cout << "\n";
}

int main() {
    srand(time(0));

    Petugas petugasAktif;
    vector<Mobil> daftarParkir;
    int opsi = 0;

    cout << "---------------------------------------------------------\n";
    cout << "                    SELAMAT DATANG                        \n";
    cout << "             DI PORTAL PARKIR KHUSUS MOBIL                \n";
    cout << "                      MALL PRIENAL                        \n";
    cout << "---------------------------------------------------------\n";
    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n\n";
    
    inputPetugas(&petugasAktif);
    cout << "\n";

    do {
        cout << "Nama Petugas : " << petugasAktif.nama << "\n";
        cout << "ID Petugas   : " << petugasAktif.id << "\n\n";
        
        menuUtama(&petugasAktif);
        
        cout << "Silahkan input opsi berikut dalam bentuk angka\n\n";
        cout << "1. Tambahkan Daftar Kendaraan\n";
        cout << "2. Tampilkan Daftar Kendaraan\n";
        cout << "3. Pembayaran\n";
        cout << "4. Keluar Program\n\n";
        
        cout << "Masukkan opsi : ";
        cin >> opsi;

        cout << "\n---------------------------------------------------------\n";

        if (opsi == 1) {
            tambahKendaraan(daftarParkir);
        } else if (opsi == 2) {
            tampilkanKendaraan(daftarParkir);
            bersihkanDanTahan();
        } else if (opsi == 3) {
            pembayaranParkir(daftarParkir);
            bersihkanDanTahan();
        } else if (opsi == 4) {
            cout << "Terima kasih! Program selesai.\n";
            break;
        } else {
            cout << "Opsi tidak valid!\n";
            bersihkanDanTahan();
        }

    } while (opsi != 4);

    return 0;
}

void inputPetugas(Petugas* p) {
    cout << "Masukkan nama : ";
    getline(cin, p->nama);
    cout << "Masukkan ID   : ";
    getline(cin, p->id);
}

void menuUtama(const Petugas* p) {
    cout << "---------------------------------------------------------\n";
    cout << "             TERIMA KASIH ATAS KERJASAMANYA !            \n";
    cout << "                     SELAMAT BERTUGAS                    \n";
    cout << "=========================================================\n\n";
}

// --- OPSI 1: TAMBAH KENDARAAN ---
void tambahKendaraan(vector<Mobil>& daftarParkir) {
    cout << "Masukan jumlah mobil yang akan di parkirkan : \n";
    
    if (daftarParkir.size() >= MAKS_KAPASITAS) {
        cout << "Maaf, parkiran hanya dapat memuat 20 mobil\n\n";
        bersihkanDanTahan();
        return;
    }

    int jumlah;
    cin >> jumlah;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < jumlah; i++) {
        if (daftarParkir.size() >= MAKS_KAPASITAS) {
            cout << "Maaf, parkiran hanya dapat memuat 20 mobil\n\n";
            break;
        }

        Mobil m;
        cout << "Mobil ke " << (daftarParkir.size() + 1) << "\n";
        cout << "Masukkan plat mobil : ";
        getline(cin, m.plat);
        cout << "Masukkan merk mobil : ";
        getline(cin, m.merk);
        cout << "Masukkan warna mobil : ";
        getline(cin, m.warna);

        m.jam   = rand() % 3;   
        m.menit = rand() % 60;  
        m.detik = rand() % 60;  

        daftarParkir.push_back(m);
        cout << "\n";
    }
    
    cout << "Data berhasil disimpan.\n";
    bersihkanDanTahan(); 
}

void tampilkanKendaraan(const vector<Mobil>& daftarParkir) {
    cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    cout << "=========================================================\n";
    
    if (daftarParkir.empty()) {
        cout << "Belum ada mobil terparkir.\n";
        cout << "=========================================================\n\n";
        return;
    }

    for (size_t i = 0; i < daftarParkir.size(); i++) {
        cout << "Mobil ke-" << (i + 1) << "\n";
        cout << "Plat mobil   : " << daftarParkir[i].plat << "\n";
        cout << "Merk mobil   : " << daftarParkir[i].merk << "\n";
        cout << "Warna mobil  : " << daftarParkir[i].warna << "\n";
        cout << "Waktu parkir : " << daftarParkir[i].jam << " jam " 
             << daftarParkir[i].menit << " menit " 
             << daftarParkir[i].detik << " detik\n";
        cout << "---------------------------------------------------------\n";
    }
    cout << "\n";
}

void pembayaranParkir(vector<Mobil>& daftarParkir) {
    cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
    cout << "=========================================================\n";
    
    if (daftarParkir.empty()) {
        cout << "Belum ada mobil terparkir.\n";
        cout << "=========================================================\n\n";
        return;
    }

    for (size_t i = 0; i < daftarParkir.size(); i++) {
        cout << "Mobil ke-" << (i + 1) << "\n";
        cout << "Plat mobil   : " << daftarParkir[i].plat << "\n";
        cout << "Merk mobil   : " << daftarParkir[i].merk << "\n";
        cout << "Warna mobil  : " << daftarParkir[i].warna << "\n";
        cout << "Waktu parkir : " << daftarParkir[i].jam << " jam " 
             << daftarParkir[i].menit << " menit " 
             << daftarParkir[i].detik << " detik\n";
        cout << "---------------------------------------------------------\n";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    string cariPlat;
    cout << "Masukkan plat mobil yang ingin dibayar : ";
    getline(cin, cariPlat);
    
    int index = -1;
    for (size_t i = 0; i < daftarParkir.size(); i++) {
        if (daftarParkir[i].plat == cariPlat) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "PLAT TIDAK DITEMUKAN !\n\n";
        cout << "Masukkan plat mobil yang ingin dibayar : ";
        getline(cin, cariPlat);
        
        for (size_t i = 0; i < daftarParkir.size(); i++) {
            if (daftarParkir[i].plat == cariPlat) {
                index = i;
                break;
            }
        }
    }

    if (index != -1) {
        int totalWaktuDetik = (daftarParkir[index].jam * 3600) + (daftarParkir[index].menit * 60) + daftarParkir[index].detik;
        // Rumus biaya dinamis berbasis detik acak agar hasil bervariasi logis
        int biaya = 2000 + (totalWaktuDetik % 1000); 

        cout << "\nB I A Y A   P A R K I R : Rp" << biaya << "\n\n";
    
        daftarParkir.erase(daftarParkir.begin() + index);
    } else {
        cout << "Transaksi gagal, plat tetap tidak ditemukan.\n\n";
    }
}