#include <conio.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <windows.h>


class Game2048 {
private:
    int gamezone[4][4];
public:

    Game2048() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                gamezone[i][j] = 0;
            }
        }
    }

    void Start() {
        std::vector<std::pair<int, int>> empty_cel;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (gamezone[i][j] == 0) {
                    empty_cel.push_back({ i, j });
                }
            }
        }

        if (!empty_cel.empty()) {
            int random_value = rand() % empty_cel.size();
            int value = (rand() % 10 == 0) ? 4 : 2;
            gamezone[empty_cel[random_value].first][empty_cel[random_value].second] = value;
        }

    }

    void Draw() {
        system("cls");
        std::cout << "------------------------------" << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << "|";
            for (int j = 0; j < 4; j++) {
                if (gamezone[i][j] == 0) {
                    std::cout << std::setw(4) << " ";
                }
                else {
                    std::cout << std::setw(4) << gamezone[i][j];
                }
                std::cout << "|";
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------------------\n\n" << std::endl;
    }

    void Compress(int row[4]) {
        std::vector <int> temp = { 0, 0, 0, 0 };
        int count = 0;

        for (int i = 0; i < 4; i++) {
            if (row[i] != 0) {
                temp[count] = row[i];
                count++;
            }
        }

        for (int i = 0; i < 4; i++) {
            row[i] = temp[i];
        }
    }

    void Merger(int row[4]) {
        for (int i = 0; i < 3; i++) {
            if (row[i] == row[i + 1] && row[i] != 0) {
                row[i] *= 2;
                row[i + 1] = 0;
            }
        }
    }

    void MoveLeft() {
        for (int i = 0; i < 4; i++) {
            Compress(gamezone[i]);
            Merger(gamezone[i]);
            Compress(gamezone[i]);

        }

        Start();
    }


    void Reversed(int row[4]) {
        for (int i = 0; i < 2; i++) {
            int temp = row[i];
            row[i] = row[3 - i];
            row[3 - i] = temp;
        }
    }

    void MoveRight() {
        for (int i = 0; i < 4; i++) {
            Reversed(gamezone[i]);
            Compress(gamezone[i]);
            Merger(gamezone[i]);
            Compress(gamezone[i]);
            Reversed(gamezone[i]);
        }
        Start();
    }


    void MoveUp() {
        for (int j = 0; j < 4; j++) {
            int tempColumn[4];
            for (int i = 0; i < 4; i++) {
                tempColumn[i] = gamezone[i][j];
            }
            Compress(tempColumn);
            Merger(tempColumn);
            Compress(tempColumn);

            for (int i = 0; i < 4; i++) {
                gamezone[i][j] = tempColumn[i];
            }
        }
        Start();
    }

    void MoveDown() {
        for (int j = 0; j < 4; j++) {
            int tempColumn[4];
            for (int i = 0; i < 4; i++) {
                tempColumn[i] = gamezone[i][j];
            }
            Reversed(tempColumn);
            Compress(tempColumn);
            Merger(tempColumn);
            Compress(tempColumn);
            Reversed(tempColumn);

            for (int i = 0; i < 4; i++) {
                gamezone[i][j] = tempColumn[i];
            }

        }
        Start();
    }

    void CheckforWin() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (gamezone[i][j] == 2048) {
                    std::cout << "\nYou win!\n" << std::endl;
                    exit(0);
                }
            }
        }
    }
};


    int main() {
        srand(time(0));
        Game2048 game;
        game.Start();
        game.Start();
        game.Draw();

        while (true) {
            game.CheckforWin();
            if (_kbhit()) {
                switch (_getch()) {
                case 'a':
                    game.MoveLeft();
                    game.Draw();
                    break;
                case 'd':
                    game.MoveRight();
                    game.Draw();
                    break;
                case 'w':
                    game.MoveUp();
                    game.Draw();
                    break;
                case 's':
                    game.MoveDown();
                    game.Draw();
                    break;

                }
            }

        }
        return 0;
    }