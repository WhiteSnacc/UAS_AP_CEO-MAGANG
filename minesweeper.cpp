#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int size;
    int bombs;

    int board[10][10];      // -1 = bom, selain itu jumlah bom sekitar
    bool opened[10][10];
    bool flagged[10][10];

    bool gameOver;
    bool win;

    time_t startTime;

public:
    Minesweeper() {
        size = 0;
        bombs = 0;
        gameOver = false;
        win = false;
    }

    void initialize() {
        do {
            cout << "Ukuran papan (4 - 10): ";
            cin >> size;
        } while (size < 4 || size > 10);

        int maxBombs = size * size - 1;

        do {
            cout << "Jumlah bom (1 - " << maxBombs << "): ";
            cin >> bombs;
        } while (bombs < 1 || bombs > maxBombs);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                board[i][j] = 0;
                opened[i][j] = false;
                flagged[i][j] = false;
            }
        }

        placeBombs();
        calculateNumbers();

        gameOver = false;
        win = false;

        startTime = time(NULL);
    }

    void placeBombs() {
        int placed = 0;

        while (placed < bombs) {
            int r = rand() % size;
            int c = rand() % size;

            if (board[r][c] != -1) {
                board[r][c] = -1;
                placed++;
            }
        }
    }

    void calculateNumbers() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {

                if (board[r][c] == -1)
                    continue;

                int count = 0;

                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {

                        if (dr == 0 && dc == 0)
                            continue;

                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < size &&
                            nc >= 0 && nc < size &&
                            board[nr][nc] == -1) {
                            count++;
                        }
                    }
                }

                board[r][c] = count;
            }
        }
    }

    void display() {
        cout << "\n====================================\n";

        int flaggedCount = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (flagged[i][j])
                    flaggedCount++;
            }
        }

        cout << "Sisa bom (perkiraan): "
             << bombs - flaggedCount << endl;

        cout << "Waktu: "
             << (int)(time(NULL) - startTime)
             << " detik\n\n";

        cout << "    ";

        for (int c = 0; c < size; c++) {
            cout << c + 1 << " ";
        }

        cout << "\n";

        for (int r = 0; r < size; r++) {

            if (r + 1 < 10)
                cout << " ";

            cout << r + 1 << "  ";

            for (int c = 0; c < size; c++) {

                if (opened[r][c]) {

                    if (board[r][c] == 0)
                        cout << ". ";
                    else
                        cout << board[r][c] << " ";

                } else if (flagged[r][c]) {

                    cout << "F ";

                } else {

                    cout << "# ";
                }
            }

            cout << "\n";
        }

        cout << "====================================\n";
    }

    void revealBombs() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board[r][c] == -1)
                    opened[r][c] = true;
            }
        }
    }

    void floodFill(int r, int c) {
        if (r < 0 || r >= size || c < 0 || c >= size)
            return;

        if (opened[r][c] || flagged[r][c])
            return;

        opened[r][c] = true;

        if (board[r][c] != 0)
            return;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {

                if (dr == 0 && dc == 0)
                    continue;

                floodFill(r + dr, c + dc);
            }
        }
    }

    void openCell(int r, int c) {

        if (opened[r][c] || flagged[r][c])
            return;

        if (board[r][c] == -1) {
            gameOver = true;
            revealBombs();
            return;
        }

        floodFill(r, c);
    }

    void toggleFlag(int r, int c) {

        if (opened[r][c])
            return;

        flagged[r][c] = !flagged[r][c];
    }

    bool checkWin() {

        int correctFlags = 0;
        int totalFlags = 0;

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {

                if (flagged[r][c]) {
                    totalFlags++;

                    if (board[r][c] == -1)
                        correctFlags++;
                }
            }
        }

        if (correctFlags == bombs &&
            totalFlags == bombs) {

            win = true;
            return true;
        }

        return false;
    }

    void play() {

        initialize();

        while (!gameOver && !win) {

            display();

            char action;
            int row, col;

            cout << "\nO = Buka | F = Tandai\n";
            cout << "Masukkan aksi dan koordinat " << "(contoh: O 2 3): ";
            cin >> action >> row >> col;

            if ((action != 'O' && action != 'o') &&
                (action != 'F' && action != 'f')) {
                cout << "Aksi tidak valid!\n";
                continue;
            }

            if (row < 1 || row > size ||
                col < 1 || col > size) {
                cout << "Koordinat tidak valid!\n";
                continue;
            }

            row--;
            col--;

            if (action == 'O' || action == 'o')
                openCell(row, col);
            else
                toggleFlag(row, col);

            checkWin();
        }

        display();

        int elapsed = (int)(time(NULL) - startTime);

        if (win) {
            cout << "\n*** SELAMAT! ANDA MENANG! ***\n";
        } else {
            cout << "\n*** BOOM! ANDA KALAH! ***\n";
        }

        cout << "Waktu bermain: "
             << elapsed
             << " detik\n\n";
    }
};

int main() {

    srand(time(NULL));

    int choice;

    do {
        cout << "=============================\n";
        cout << "      MINESWEEPER GAME\n";
        cout << "=============================\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            Minesweeper game;
            game.play();
        }

    } while (choice != 2);

    cout << "Terima kasih telah bermain!\n";

    return 0;
}