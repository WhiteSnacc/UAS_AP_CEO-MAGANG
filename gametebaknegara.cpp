#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct DataNegara {
    string soal;
    string jawaban;
};

void jalankanGame() {
    vector<DataNegara> daftar_negara = {
        {"i n d _ n _ s _ a", "indonesia"},
        {"j _ p _ n g", "jepang"},
        {"k _ n _ d _", "kanada"},
        {"b _ a z _ l", "brazil"},
        {"p _ a n c _ s", "prancis"},
        {"m _ s _ r", "mesir"},
    };

    srand(time(0));
    int skor = 0;
    char pilihan;

    do {
        int index = rand() % daftar_negara.size();
        string tebakan_user;

        cout << "Tebak negara: " << daftar_negara[index].soal << endl;
        cout << "Negara apakah yang dimaksud? ";
        cin >> tebakan_user;

        if (tebakan_user == daftar_negara[index].jawaban) {
            cout << "Selamat! Anda benar." << endl;
            skor++;
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi." << endl;
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> pilihan;
        cout << endl;

    } while (pilihan == 'y' || pilihan == 'Y');

    cout << "Game Selesai :D" << endl;
}

int main() {
    jalankanGame();
    return 0;
}