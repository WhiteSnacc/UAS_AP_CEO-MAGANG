#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int size, bombs;
    int board[10][10];
    bool opened[10][10];
    bool flagged[10][10];
    bool wrongFlag[10][10];

    bool gameOver;
    bool win;
    bool firstMove;

    time_t startTime;

    void placeBombs(int safeR, int safeC) {
        int placed = 0;

        while (placed < bombs) {
            int r = rand() % size;
            int c = rand() % size;

            if ((r == safeR && c == safeC) || board[r][c] == -1)
                continue;

            board[r][c] = -1;
            placed++;
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

                        if (dr == 0 && dc == 0) continue;

                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < size &&
                            nc >= 0 && nc < size &&
                            board[nr][nc] == -1)
                            count++;
                    }
                }

                board[r][c] = count;
            }
        }
    }

    void generateBoard(int safeR, int safeC) {
        placeBombs(safeR, safeC);
        calculateNumbers();
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

    void revealEndGame() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {

                if (board[r][c] == -1)
                    opened[r][c] = true;

                if (flagged[r][c] && board[r][c] != -1)
                    wrongFlag[r][c] = true;
            }
        }
    }

public:
    Minesweeper() {
        size = 0;
        bombs = 0;
        gameOver = false;
        win = false;
        firstMove = true;
    }

    void initialize() {
        do {
            cout << "Ukuran papan (4-10): ";
            cin >> size;
        } while (size < 4 || size > 10);

        int maxBombs = size * size - 1;

        do {
            cout << "Jumlah bom (1-" << maxBombs << "): ";
            cin >> bombs;
        } while (bombs < 1 || bombs > maxBombs);

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                board[i][j] = 0;
                opened[i][j] = false;
                flagged[i][j] = false;
                wrongFlag[i][j] = false;
            }
        }

        gameOver = false;
        win = false;
        firstMove = true;

        startTime = time(NULL);
    }

    void display() {
        int flagCount = 0;

        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                if (flagged[r][c]) flagCount++;

        cout << "\nBomb:" << bombs - flagCount
             << "  Flag:" << flagCount << "/" << bombs
             << "  Time:" << (int)(time(NULL) - startTime) << "s\n\n";

        cout << "   ";
        for (int c = 0; c < size; c++)
            cout << c + 1 << " ";
        cout << "\n";

        for (int r = 0; r < size; r++) {

            if (r + 1 < 10) cout << " ";

            cout << r + 1 << " ";

            for (int c = 0; c < size; c++) {

                if (wrongFlag[r][c])
                    cout << "X ";
                else if (opened[r][c]) {
                    if (board[r][c] == -1)
                        cout << "* ";
                    else if (board[r][c] == 0)
                        cout << ". ";
                    else
                        cout << board[r][c] << " ";
                }
                else if (flagged[r][c])
                    cout << "F ";
                else
                    cout << "# ";
            }

            cout << "\n";
        }
    }

    void openCell(int r, int c) {

        if (opened[r][c] || flagged[r][c])
            return;

        if (firstMove) {
            generateBoard(r, c);
            firstMove = false;
        }

        if (board[r][c] == -1) {
            gameOver = true;
            revealEndGame();
            return;
        }

        floodFill(r, c);
    }

    void toggleFlag(int r, int c) {

        if (opened[r][c])
            return;

        flagged[r][c] = !flagged[r][c];
    }

    void chordCell(int r, int c) {

        if (!opened[r][c] || board[r][c] <= 0)
            return;

        int flagCount = 0;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {

                int nr = r + dr;
                int nc = c + dc;

                if (nr >= 0 && nr < size &&
                    nc >= 0 && nc < size &&
                    flagged[nr][nc])
                    flagCount++;
            }
        }

        if (flagCount != board[r][c])
            return;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {

                int nr = r + dr;
                int nc = c + dc;

                if (nr >= 0 && nr < size &&
                    nc >= 0 && nc < size &&
                    !flagged[nr][nc])
                    openCell(nr, nc);
            }
        }
    }

    bool checkWin() {

        int totalFlags = 0;
        int correctFlags = 0;

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {

                if (flagged[r][c]) {
                    totalFlags++;

                    if (board[r][c] == -1)
                        correctFlags++;
                }
            }
        }

        if (totalFlags == bombs && correctFlags == bombs) {
            win = true;
            return true;
        }

        return false;
    }

    void offerAutoFlag() {

    int closedCount = 0;
    int flaggedCount = 0;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {

            if (flagged[r][c])
                flaggedCount++;

            if (!opened[r][c] && !flagged[r][c])
                closedCount++;
        }
    }

    int bombsLeft = bombs - flaggedCount;

    if (closedCount == bombsLeft && bombsLeft > 0) {

        char ans;

        cout << "\nSemua kotak tertutup yang tersisa "
             << "dipastikan bom.\n";

        cout << "Auto Flag semua? (Y/N): ";

        cin >> ans;

        if (ans == 'Y' || ans == 'y') {

            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {

                    if (!opened[r][c] && !flagged[r][c])
                        flagged[r][c] = true;
                }
            }
        }
    }}

    void play() {

        initialize();

        while (!gameOver && !win) {

            display();

            char action;
            int row, col;

            cout << "\nO=Open  F=Flag  C=Chord\n";
            cout << "Input Aksi-Baris-Kolom (contoh: O 2 3): ";

            cin >> action >> row >> col;

            if ((action != 'O' && action != 'o') &&
                (action != 'F' && action != 'f') &&
                (action != 'C' && action != 'c')) {
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
            else if (action == 'F' || action == 'f')
                toggleFlag(row, col);
            else
                chordCell(row, col);

            checkWin();
        }

        display();

        int elapsed = (int)(time(NULL) - startTime);

        if (win)
            cout << "\nSelamat, ANDA MENANG!\n";
        else
            cout << "\nANDA KALAH! (lol)\n";

        cout << "Waktu bermain: " << elapsed << " detik\n";
    }
};

int main() {

    srand((unsigned)time(NULL));

    int choice;

    do {
        cout << "\n===== MINESWEEPER =====\n";
        cout << "1. Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            Minesweeper game;
            game.play();
        }

    } while (choice != 2);

    cout << "Baiklah, sampai jumpa lain waktu!\n";

    return 0;
}
