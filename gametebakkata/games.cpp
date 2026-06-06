#include "TebakKata.h"

int main() {
    KataGame game;
    inisialisasi(&game);  
    tampilHeader(&game);

    char huruf;
    while (game.nyawa > 0 && !cekMenang(&game)) {
        tampilStatus(&game);
        cout << "Tebak huruf: ";
        cin >> huruf;
        prosesTebakan(&game, huruf);  
    }

    if (cekMenang(&game))
        cout << "\nPintar! Kata yang benar: " << game.kata << endl;
    else
        cout << "\nGame Over! Jawabannya: " << game.kata << endl;

    return 0;
}