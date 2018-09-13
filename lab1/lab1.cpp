#include <cstdio>
#include <climits>
#include <iostream>
#include <ctime>
#include <cmath>
#include <exception>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

class DGame
{
int **board;
int n,m;
int x, y;

public:
    DGame(int n=4, int m=4) {


        board = new int* [n];

        int *t = new int[n * m];
        for(int i = 0; i < n * m; i++)
            t[i] = i;

        shuffle(t, t + n*m, default_random_engine(0));


        for(int i = 0; i < n; i++) {
            board[i] = new int[m];
            for(int j = 0; j < m; j++) {
                board[i][j] = t[i*n + j];
                if(board[i][j] == 0) {
                    x = i, y = j;
                }
            }
        }

        this->n = n, this->m = m;
    }

    ~DGame() {
        for(int i = 0; i < n; i++) {
            delete board[i];
        }
        delete board;
    }

    void up() {
        if(x - 1 < 0)
            return;

        swap(board[x][y], board[x - 1][y]);
        x--;
    }
    void down() {
        if(x + 1 >= n)
            return;

        swap(board[x][y], board[x + 1][y]);
        x++;
    }
    void right() {
        if(y + 1 >= m)
            return;

        swap(board[x][y], board[x][y + 1]);
        y++;
    }
    void left() {
        if(y - 1 < 0)
            return;

        swap(board[x][y], board[x][y - 1]);   
        y--;
    }
    bool ready() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] != i * n + j)
                    return false;
            }
        }

        return true;
    }

    void random(int n=100) {

        for(int i = 0; i < n; i++) {
            int t = rand()%4;

            switch(t) {
                case 0: up(); break;
                case 1: down(); break;
                case 2: right(); break;
                case 3: left(); break;
            }
        }
    }

    void print() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (board[i][j] != 0)
                    printf("%2d ", board[i][j]);
                else
                    cout << "__ ";
            }
            cout << '\n';
        }
    }
};

int main() {
    DGame game = DGame(5, 5);

    game.print();
    game.down();
    cout << '\n';
    game.print();

    game.down();
    cout << '\n';
    game.print();

    game.down();
    cout << '\n';
    game.print();

    game.left();
    cout << '\n';
    game.print();

    game.right();
    cout << '\n';
    game.print();

    game.up();
    cout << '\n';
    game.print();
}