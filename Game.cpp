//
// Created by vladi on 02.07.2022.
//
#include "Game.h"
#include "GUI.h"

int32_t ans;

void SetColor(int32_t text, int32_t bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void Goto(int32_t x, int32_t y) {
    COORD p = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void Field::GoBack() {
    SetColor(WHITE, BLACK);
}

void Field::Show() {
    Goto(0, 0);
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            if (map_[j][i] == EMPTY) {
                std::cout << '.';
                continue;
            }
            if (field_[j][i] == EDGE) {
                SetColor(LIGHT_BLUE, BLACK);
                std::cout << '#';
                GoBack();
            } else if (field_[j][i] == EMPTY) {
                std::cout << ' ';
            } else if (field_[j][i] == 1) {
                SetColor(BLUE, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 2) {
                SetColor(GREEN, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 3) {
                SetColor(RED, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 4) {
                SetColor(MAGENTA, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 5) {
                SetColor(BROWN, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 6) {
                SetColor(DARK_GRAY, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 7) {
                SetColor(LIGHT_GREEN, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == 8) {
                SetColor(YELLOW, BLACK);
                std::cout << field_[j][i];
                GoBack();
            } else if (field_[j][i] == MINE) {
                SetColor(RED, BLACK);
                std::cout << '*';
                GoBack();
            } else {
                SetColor(MAGENTA, BLACK);
                std::cout << '!';
                GoBack();
            }
        }
        std::cout << '\n';
    }
}

void Field::SetMines(int32_t MinesCnt) {
    /* if (MinesCnt >= (size_ - 2) * (size_ - 2)) {
        SetColor(RED, BLACK);
        std::cout << "Error. The number of mines is more than permitted value.";
        exit(0);
    } */
    SetColor(YELLOW, BLACK);
    std::cout << "Start!\n";
    Sleep(1000);
    system("cls");
    SetColor(5, 0);
    for (size_t i = 0; i < MinesCnt; ++i) {
        int32_t x, y;
        do {
            x = rand() % (size_ - 2) + 1;
            y = rand() % (size_ - 2) + 1;
        } while (field_[x][y] == MINE);
        field_[x][y] = MINE;
    }
}

Field::Field() {
    GUI x;
    if (ans == 1) {
        size_ = 9;
        minescnt = 10;
    } else if (ans == 2) {
        size_ = 16;
        minescnt = 40;
    } else if (ans == 3) {
        x.FontSize(26);
        size_ = 30;
        minescnt = 99;
    }
}

bool Field::IsEdge(int32_t x, int32_t y) {
    if (field_[x][y] == EDGE) {
        return true;
    }
    return false;
}

void Field::Init(std::vector<std::vector<int32_t>> &v) const {
    for (size_t i = 0; i < size_; ++i) {
        std::vector<int32_t> temp;
        for (size_t j = 0; j < size_; ++j) {
            if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1) {
                temp.emplace_back(EDGE);
            } else {
                temp.emplace_back(EMPTY);
            }
        }
        v.emplace_back(temp);
    }
}

void Field::InitField() {
    Init(field_);
}

void Field::InitMap() {
    Init(map_);
}

void Field::SetNums() {
    int32_t cnt = 0;
    for (size_t i = 1; i < size_ - 1; ++i) {
        for (size_t j = 1; j < size_ - 1; ++j) {
            if (field_[j][i] != MINE) {
                if (field_[j][i + 1] == MINE) {
                    cnt++;
                }
                if (field_[j][i - 1] == MINE) {
                    cnt++;
                }
                if (field_[j - 1][i] == MINE) {
                    cnt++;
                }
                if (field_[j + 1][i] == MINE) {
                    cnt++;
                }
                if (field_[j - 1][i - 1] == MINE) {
                    cnt++;
                }
                if (field_[j - 1][i + 1] == MINE) {
                    cnt++;
                }
                if (field_[j + 1][i - 1] == MINE) {
                    cnt++;
                }
                if (field_[j + 1][i + 1] == MINE) {
                    cnt++;
                }
                field_[j][i] = cnt;
                cnt = 0;
            }
        }
    }
}

int32_t Field::Open(int32_t x, int32_t y) {
    map_[x][y] = 1;
    int32_t res = 1;
    if (field_[x][y] == MINE) {
        res = MINE;
    } else if (field_[x][y] == EMPTY) {
        res = EMPTY;
    }
    Show();
    return res;
}

void Field::Fill(int32_t px, int32_t py) {
    std::stack<int> st;
    st.push(px);
    st.push(py);
    int32_t x, y;
    while (!st.empty()) {
        y = st.top();
        st.pop();
        x = st.top();
        st.pop();
        if (field_[x][y + 1] == FLAG) ChangeFlag(x, y + 1);
        if (field_[x][y + 1] == EMPTY && map_[x][y + 1] == EMPTY) {
            st.push(x);
            st.push(y + 1);
        }
        map_[x][y + 1] = 1;
        if (field_[x][y - 1] == FLAG) ChangeFlag(x, y - 1);
        if (field_[x][y - 1] == EMPTY && map_[x][y - 1] == EMPTY) {
            st.push(x);
            st.push(y - 1);
        }
        map_[x][y - 1] = 1;
        if (field_[x + 1][y] == FLAG) ChangeFlag(x + 1, y);
        if (field_[x + 1][y] == EMPTY && map_[x + 1][y] == EMPTY) {
            st.push(x + 1);
            st.push(y);
        }
        map_[x + 1][y] = 1;
        if (field_[x - 1][y] == FLAG) ChangeFlag(x - 1, y);
        if (field_[x - 1][y] == EMPTY && map_[x - 1][y] == EMPTY) {
            st.push(x - 1);
            st.push(y);
        }
        map_[x - 1][y] = 1;
        if (field_[x + 1][y + 1] == FLAG) ChangeFlag(x + 1, y + 1);
        if (field_[x + 1][y + 1] == EMPTY && map_[x + 1][y + 1] == EMPTY) {
            st.push(x + 1);
            st.push(y + 1);
        }
        map_[x + 1][y + 1] = 1;
        if (field_[x + 1][y - 1] == FLAG) ChangeFlag(x + 1, y - 1);
        if (field_[x + 1][y - 1] == EMPTY && map_[x + 1][y - 1] == EMPTY) {
            st.push(x + 1);
            st.push(y - 1);
        }
        map_[x + 1][y - 1] = 1;
        if (field_[x - 1][y + 1] == FLAG) ChangeFlag(x - 1, y + 1);
        if (field_[x - 1][y + 1] == EMPTY && map_[x - 1][y + 1] == EMPTY) {
            st.push(x - 1);
            st.push(y + 1);
        }
        map_[x - 1][y + 1] = 1;
        if (field_[x - 1][y - 1] == FLAG) ChangeFlag(x - 1, y - 1);
        if (field_[x - 1][y - 1] == EMPTY && map_[x - 1][y - 1] == EMPTY) {
            st.push(x - 1);
            st.push(y - 1);
        }
        map_[x - 1][y - 1] = 1;
    }
}

void Field::Clear() {
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            map_[j][i] = 1;
            if (field_[j][i] == FLAG) {
                field_[j][i] = flag_[j][i];
            }
        }
    }
    Show();
}

void Field::ChangeFlag(int32_t x, int32_t y) {
    map_[x][y] = 1;
    int32_t temp;
    if (field_[x][y] != FLAG) {
        flag_[x][y] = field_[x][y];
        field_[x][y] = FLAG;
    } else {
        map_[x][y] = EMPTY;
        field_[x][y] = flag_[x][y];
    }
    Show();
}

void Field::InitFlag() {
    Init(flag_);
}

bool Field::FlagOrNot(int32_t x, int32_t y) {
    if (map_[x][y] == EMPTY || flag_[x][y] != EMPTY) {
        return true;
    }
    return false;
}

bool Field::CheckWin() {
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            if (map_[j][i] == EMPTY && field_[j][i] != MINE) {
                return false;
            }
        }
    }
    return true;
}


void Game::GameOver() {
    SetColor(LIGHT_RED, BLACK);
    Goto(40, 9);
    std::cout << "Game over! You lost.\n";
    Goto(40, 10);
    std::cout << "Press Enter to start new game.\n";
    Goto(40, 11);
    std::cout << "Press any other button to exit.\n";
    SetColor(14, 0);
    Goto(0, 15);
    int32_t c = 0;
    c = getch();
    if (c == 13) {
        system("cls");
        Run();
    } else {
        exit(0);
    }
}

void Game::Run() {
    Icon();
    int32_t chs = 0;
    chs = _getch();
    if (chs == 27) {
        exit(0);
    }
    Game game;
    game.Choose();
    GUI x;
    Field field;
    field.InitField();
    field.InitMap();
    field.InitFlag();
    field.SetMines(field.minescnt);
    field.SetNums();
    field.Show();
    Keyboard kb;
    Cursor cs;
    Goto(1, 1);
    bool flag = false;
    while (!flag) {
        kb.WaitKey();
        cs.Save();
        switch (kb.GetKey()) {
            case 72: cs.DecY(); break;
            case 75: cs.DecX(); break;
            case 77: cs.IncX(); break;
            case 80: cs.IncY(); break;
            case 8:
                if (field.FlagOrNot(cs.GetX(), cs.GetY())) {
                    field.ChangeFlag(cs.GetX(), cs.GetY());
                }
                break;
            case 13:
                int32_t result = field.Open(cs.GetX(), cs.GetY());
                if (result == MINE) {
                    field.Clear();
                    GameOver();
                    flag = true;
                }
                if (result == EMPTY) {
                    field.Fill(cs.GetX(), cs.GetY());
                    field.Show();
                }
                if (field.CheckWin()) {
                    field.Clear();
                    SetColor(YELLOW, BLACK);
                    Goto(40, 9);
                    std::cout << "Congratulations! You won.\n";
                    Goto(40, 10);
                    std::cout << "Press Enter to start new game.\n";
                    Goto(40, 11);
                    std::cout << "Press any other button to exit.\n";
                    Goto(0, 15);
                    int32_t c = 0;
                    c = getch();
                    if (c == 13) {
                        system("cls");
                        Run();
                    } else {
                        exit(0);
                    }
                }
                break;
        }
        if (field.IsEdge(cs.GetX(), cs.GetY())) {
            cs.Undo();
        }
        Goto(cs.GetX(), cs.GetY());
    }
}

void Game::Icon() {
    SetColor(GREEN, BLACK);
    GUI x;
    x.FilePrint("mine.txt");
}

void Game::Choose() {
    SetColor(YELLOW, BLACK);
    GUI x;
    x.FilePrint("choose.txt");
    int32_t chss = getch();
    if (chss == 49) {
        ans = 1;
    } else if (chss == 50) {
        ans = 2;
    } else if (chss == 51) {
        ans = 3;
    }
}


Keyboard::Keyboard() {
    ch = 0;
}

void Keyboard::WaitKey() {
    ch = getch();
}

int32_t Keyboard::GetKey() const {
    return ch;
}

void Cursor::Save() {
    tx = x;
    ty = y;
}

void Cursor::Undo() {
    x = tx;
    y = ty;
}

void Cursor::IncX() {
    x++;
}

void Cursor::DecX() {
    x--;
}

void Cursor::IncY() {
    y++;
}

void Cursor::DecY() {
    y--;
}

int32_t Cursor::GetX() const {
    return x;
}

int32_t Cursor::GetY() const {
    return y;
}
