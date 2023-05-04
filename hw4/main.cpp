#include <iostream>
#define SELECTOR 100
#define GAME_ALL 0
#define GAME_HEADER 1
#define GAME_BLANK 2
#define GAME_1 3
#define GAME_2 4
#define GAME_BAR 5
#define GAME_BUT 6

class TicTacToe {
    private:
        int game;
        int player;
        int winner;
        char s[9];
        void printGame(int mode) {
            int t = mode / SELECTOR * 3;
            mode %= SELECTOR;
            switch (mode) {
                case GAME_ALL:
                    printGame(GAME_HEADER);
                    printGame(GAME_BLANK);
                    for (int i=0; i<3; i++) {
                        printGame(GAME_1);
                        printGame(GAME_2 + SELECTOR*i);
                        printGame(GAME_1);
                        if (i<2) {
                            printGame(GAME_BAR);
                        }
                    }
                    printGame(GAME_BLANK);
                    return;
                case GAME_HEADER:
                    printf("-- Tic Tac Toe -- CSIE@CGU\n");
                    printf("Player 1 (X)  -  Player 2 (O)\n");
                    return;
                case GAME_BLANK:
                    printf("\n");
                    return;
                case GAME_BAR:
                    for (int i=0; i<19; i++) {
                        printf("█");
                    }
                    printf("\n");
                    return;
                case GAME_1:
                    printf("　 　██　 　██\n");
                    return;
                case GAME_2:
                    printf("　%c　██　%c　██　%c\n", *(s+t), *(s+t+1), *(s+t+2));
                    return;
                case GAME_BUT:
                    printf("Player %d, 請輸入『1-9』的數字：", player);
                    return;
                default:
                    return;
            }
        }
        int checkGame() {
            // rows
            for (int r=0; r<3; r++) {
                if ((*(s+r*3) == *(s+r*3+1))*(*(s+r*3+1) == *(s+r*3+2))) {
                    return *(s+r*3);
                }
            }
            // columns
            for (int c=0; c<3; c++) {
                if ((*(s+0*3+c) == *(s+1*3+c))*(*(s+1*3+c) == *(s+2*3+c))) {
                    return *(s+0*3+c);
                }
            }
            // cross "\"
            if ((*s == *(s+4))*(*(s+4) == *(s+8))) {
                return *s;
            }
            // cross "/"
            if ((*(s+2) == *(s+4))*(*(s+4) == *(s+6))) {
                return *(s+2);
            }
            return 0;
        }
    public:
        TicTacToe() {
            for (int i=0; i<9; i++) {
                *(s+i) = i+1+'0';
            }
        }
        void run() {
            for (game=1; game<=9; game++) {
                player = (game % 2) ? 1 : 2;
                printGame(GAME_ALL);
                printGame(GAME_BUT);
                int n;
                while (1) {
                    scanf("%d", &n);
                    if (*(s+n-1) <= '9') {
                        *(s+n-1) = (player == 1) ? 'X' : 'O';
                        break;
                    }
                    printf("請重新輸入下一步\n");
                    printGame(GAME_ALL);
                    printGame(GAME_BUT);
                }
                if (winner = checkGame()) {
                    printGame(GAME_ALL);
                    printf("==>Player %d win\n", (winner=='X') ? 1 : 2);
                    return;
                }
            }
            printGame(GAME_ALL);
            printf("==>Game draw\n");
        }
};

int main() {
    TicTacToe game;
    game.run();
    return 0;
}
