#ifndef TEBAK_KATA_H
#define TEBAK_KATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int JUMLAH_KATA = 8;
const int MAX_NYAWA   = 6;

string daftar[JUMLAH_KATA] = {
    "apel", "kursi", "kucing", "rumah",
    "buku", "ikan", "api", "televisi"
};

string clue[JUMLAH_KATA] = {
    "Buah yang sering dijadikan jus",
    "Tempat buat istirahat",
    "Hewan yang lucu",
    "Tempat tinggal manusia",
    "Benda untuk menambah wawasan",
    "Hewan yang hidup di air",
    "Fenomena alam yang panas",
    "Alat untuk menonton acara"
};

struct KataGame {
    string kata;      
    string tampil;    
    string clueKata;  
    int nyawa;        
};

void inisialisasi(KataGame* game) {
    srand(time(0));
    int idx     = rand() % JUMLAH_KATA;
    game->kata     = daftar[idx];
    game->clueKata = clue[idx];
    game->tampil   = string(game->kata.length(), '_');
    game->nyawa    = MAX_NYAWA;
}

void prosesTebakan(KataGame* game, char huruf) {
    bool benar = false;
    for (int i = 0; i < game->kata.length(); i++) {
        if (game->kata[i] == huruf) {
            game->tampil[i] = huruf;
            benar = true;
        }
    }
    if (!benar) {
        game->nyawa--;   // kurangi nyawa lewat pointer
        cout << "Salah! Sisa nyawa: " << game->nyawa << endl;
    } else {
        cout << "Benar!" << endl;
    }
}

bool cekMenang(KataGame* game) {
    return game->tampil == game->kata;
}

void tampilHeader(KataGame* game) {
    cout << "=== TEBAK KATA ===" << endl;
    cout << "Clue   : " << game->clueKata << endl;
    cout << "Panjang: " << game->kata.length() << " huruf" << endl;
}
void tampilStatus(KataGame* game) {
    cout << "\nKata : " << game->tampil << endl;
    cout << "Nyawa: " << game->nyawa << endl;
}

#endif