//
// Created by vladi on 06.07.2022.
//

#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <windows.h>
#include "GUI.h"

void GUI::ClearRow(int16_t row, uint16_t sym_amo) {
    HANDLE h_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, static_cast<int16_t>(row - 1)};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h_std_out, &csbi);
    DWORD dwNumWritten;
    FillConsoleOutputCharacter(h_std_out, ' ', sym_amo, coord, &dwNumWritten);
    SetConsoleCursorPosition(h_std_out, csbi.dwCursorPosition);
}

void GUI::WindowMax() {
    HWND h_wnd = GetForegroundWindow();
    ShowWindow(h_wnd, SW_MAXIMIZE);
    COORD position = {0,0};
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h_console, position);
}

void GUI::SetColor(uint16_t text, uint16_t bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int16_t GUI::Menu(std::string a[], uint32_t n) {
    system("cls");
    FilePrint(a[0]);
    int32_t i = 0;
    while (true) {
        WindowMax();
        uint32_t code = getch();
        if (code == 80 || code == 75) {
            system("cls");
            i++;
            if(i == n) {
                i = 0;
            }
            if(i == 0) {
                i = 1;
            }
            FilePrint(a[i]);
        } else if (code == 72 || code == 77) {
            system("cls");
            i--;
            if(i <= 0) {
                i = n - 1;
            }
            FilePrint(a[i]);
        } else if (code == 13)  {
            if(i != 0) {
                system("cls");
                return menu_status_;
            }
        } else if (code == 27) {
            exit(0);
        }
        menu_status_ = i;
    }
}

void GUI::FontSize(int16_t font_size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx( hConsole, TRUE, &fontInfo);
    wcscpy(fontInfo.FaceName, L"Consolas");
    fontInfo.dwFontSize.Y = font_size;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
}

void GUI::PreString(std::string a) {
    for(int i = 0; i < 111 - a.size(); ++i) {
        std::cout << ' ';
    }
    std::cout << a;
    for(int i = 0; i < 111 - a.size(); ++i) {
        std::cout << ' ';
    }
    std::cout << '\n';
}

void GUI::WinString(uint16_t font_size, uint16_t text_color) {
    system("cls");
    FontSize(font_size);
    SetColor(text_color, 0);
    std::cout << "                            You won! Congratulations! Press Enter. \n";
    uint16_t button = getch();
    while (button != 13) {
        button = getch();
    }
    FontSize();
    SetColor();
}

void GUI::LoseString(uint16_t font_size, uint16_t text_color) {
    system("cls");
    FontSize(font_size);
    SetColor(text_color, 0);
    std::cout << "                          You lost! Good luck next time! Press Enter. \n";
    uint16_t button = getch();
    while (button != 13) {
        button = getch();
    }
    FontSize();
    SetColor();
}

void GUI::Loading(uint32_t sec) {
    FontSize(34);
    for(uint16_t i = 0; i < 53; ++i) {
        std::cout << '\n';
    }
    for(uint32_t i = 0; i < sec; ++i) {
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '|';
        Sleep(125);
        system("cls");
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '\\';
        Sleep(125);
        Cls();
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '-';
        Sleep(125);
        Cls();
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '/';
        Sleep(125);
        Cls();
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '|';
        Sleep(125);
        Cls();
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '\\';
        Sleep(125);
        Cls();
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '-';
        Sleep(125);
        Cls();
        for(int i = 0; i < 2; ++i) {
            std::cout << '\n';
        }
        for(int i = 0; i < 3; ++i) {
            std::cout << ' ';
        }
        std::cout << '/';
        Sleep(125);
        Cls();
    }
    FontSize();
}

void GUI::FilePrint(std::string file_name) {
    std::ifstream file(file_name);
    std::string str;
    while (getline(file, str)) {
        std::cout << str << '\n';
    }
    file.close();
}

void GUI::SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GUI::Cls() {
    SetCursorPosition(0, 0);
}

void GUI::FancyFrame(std::string x, uint32_t spaces) const {
    for(uint32_t i = 0; i < spaces; ++i) {
        std::cout << ' ';
    }
    std::cout << ".-";
    for(uint32_t i = 0; i < x.size(); ++i) {
        std::cout << '-';
    }
    std::cout << "-.\n";
    for(uint32_t i = 0; i < spaces; ++i) {
        std::cout << ' ';
    }
    std::cout << "  " << x << "  \n";
    for(uint32_t i = 0; i < spaces; ++i) {
        std::cout << ' ';
    }
    std::cout << "\'-";
    for(uint32_t i = 0; i < x.size(); ++i) {
        std::cout << '-';
    }
    std::cout << "-\'";
}

std::pair<int32_t, int32_t> GUI::ClickCoord() {
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD coord;
    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
    while (true) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            return(std::make_pair(-1 * static_cast<int32_t>(coord.X), -1 * static_cast<int32_t>(coord.Y)));
        } else if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            return(std::make_pair(static_cast<int32_t>(coord.X), static_cast<int32_t>(coord.Y)));
        }
    }
}