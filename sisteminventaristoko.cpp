#include <iostream>
#include <iomanip>
using namespace std;

struct Barang {
    string kode;
    string nama;
    int stok;
    double harga;
};

Barang inventaris[100];
int jumlahBarang = 0;

void tambahBarang() {
    cout << "\n=== TAMBAH BARANG ===\n";

    cout << "Kode Barang : ";
    cin >> inventaris[jumlahBarang].kode;

    cin.ignore();

    cout << "Nama Barang : ";
    getline(cin, inventaris[jumlahBarang].nama);

    cout << "Stok Barang : ";
    cin >> inventaris[jumlahBarang].stok;

    cout << "Harga Barang : ";
    cin >> inventaris[jumlahBarang].harga;

    jumlahBarang++;

    cout << "\nBarang berhasil ditambahkan!\n";
}

void tampilBarang() {
    if (jumlahBarang == 0) {
        cout << "\nInventaris kosong!\n";
        return;
    }

    cout << "\n=== DATA INVENTARIS ===\n";

    cout << left
         << setw(15) << "Kode"
         << setw(25) << "Nama"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;

    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < jumlahBarang; i++) {
        cout << left
             << setw(15) << inventaris[i].kode
             << setw(25) << inventaris[i].nama
             << setw(10) << inventaris[i].stok
             << setw(15) << inventaris[i].harga
             << endl;
    }
}

void cariBarang() {
    string cariKode;
    bool ditemukan = false;

    cout << "\nMasukkan kode barang: ";
    cin >> cariKode;

    for (int i = 0; i < jumlahBarang; i++) {
        if (inventaris[i].kode == cariKode) {
            cout << "\nBarang ditemukan!\n";
            cout << "Kode  : " << inventaris[i].kode << endl;
            cout << "Nama  : " << inventaris[i].nama << endl;
            cout << "Stok  : " << inventaris[i].stok << endl;
            cout << "Harga : " << inventaris[i].harga << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

void updateStok() {
    string kode;
    bool ditemukan = false;

    cout << "\nMasukkan kode barang: ";
    cin >> kode;

    for (int i = 0; i < jumlahBarang; i++) {
        if (inventaris[i].kode == kode) {
            cout << "Stok lama : " << inventaris[i].stok << endl;

            cout << "Stok baru : ";
            cin >> inventaris[i].stok;

            cout << "\nStok berhasil diperbarui!\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

void hapusBarang() {
    string kode;
    bool ditemukan = false;

    cout << "\nMasukkan kode barang yang akan dihapus: ";
    cin >> kode;

    for (int i = 0; i < jumlahBarang; i++) {
        if (inventaris[i].kode == kode) {

            for (int j = i; j < jumlahBarang - 1; j++) {
                inventaris[j] = inventaris[j + 1];
            }

            jumlahBarang--;

            cout << "\nBarang berhasil dihapus!\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nBarang tidak ditemukan!\n";
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n================================";
        cout << "\n SISTEM MANAJEMEN INVENTARIS TOKO";
        cout << "\n================================";
        cout << "\n1. Tambah Barang";
        cout << "\n2. Tampilkan Inventaris";
        cout << "\n3. Cari Barang";
        cout << "\n4. Update Stok";
        cout << "\n5. Hapus Barang";
        cout << "\n0. Keluar";
        cout << "\n\nPilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;

            case 2:
                tampilBarang();
                break;

            case 3:
                cariBarang();
                break;

            case 4:
                updateStok();
                break;

            case 5:
                hapusBarang();
                break;

            case 0:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 0);

}