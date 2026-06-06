#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    string daftar[] = {"apel", "Kursi", "kucing", "rumah", "buku", "ikan", "api", "televisi"};
    string clue[] = {"Buah yang sering dijadikan jus", "Tempat buat istirahat", "Hewan yang lucu", "Tempat tinggal manusia",
                     "Benda untuk menambah wawasan", "Hewan yang hidup di air", "Fenomena alam yang panas", "Alat untuk menonton acara"};
    int idx = rand() % 8;
    string kata = daftar[idx];
    string tampil(kata.length(), '_');
    int nyawa = 6;
    char tebak;

    cout << "TEBAK KATA :" << endl;
    cout << "Cluenya: " << clue[idx] << endl;
    cout << "Panjang katanya adalah: " << kata.length() << " huruf\n";

    while (nyawa > 0 && tampil != kata) {
        cout << "\nKata : " << tampil << endl;
        cout << "Nyawa: " << nyawa << endl;
        cout << "Tebak huruf: ";
        cin >> tebak;

        bool benar = false;
        for (int i = 0; i < kata.length(); i++) {
            if (kata[i] == tebak) {
                tampil[i] = tebak;
                benar = true;
            }
        }

        cout << (benar ? "Benar! Lanjutkan!" : "Salah! Hati-hati!") << endl;
        if (!benar) nyawa--;
    }

    if (tampil == kata)
        cout << "\nPintar Juga Kau! jawabannya adalah: " << kata << endl;
    else
        cout << "\nBanyakin Belajar Lagi! Jawabannya adalah: " << kata << endl;

    return 0;
}
