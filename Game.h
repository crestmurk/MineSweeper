//
// Created by vladi on 02.07.2022.
//

#ifndef UNTITLED27_GAME_H
#define UNTITLED27_GAME_H
#include <conio.h>
#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>
#include <windows.h>



const int32_t FLAG = 1000;
const int32_t EDGE = 100;
const int32_t MINE = 10;
const int32_t EMPTY = 0;

enum ConsoleColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GRAY = 7,
    DARK_GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};




class Field {
public:
    /// Дефолтный конструктор.
    Field();
    /// Функция проверки на границу.
    /// \param x Элемент по оси Х.
    /// \param y Элемент по оси Y.
    /// \return true если граница, false иначе.
    bool IsEdge(int32_t x, int32_t y);
    /// Функция инициализации вектора.
    /// \param v Вектор для инициализации.
    void Init(std::vector<std::vector<int32_t>>& v) const;
    /// Функция инициализации вектора поля.
    void InitField();
    /// Функция инициализации вектора маски.
    void InitMap();
    /// Функция инициализации вектора флага.
    void InitFlag();
    /// Функция проверки на то, можно ли поставить флаг.
    /// \param x Элемент по оси Х.
    /// \param y Элемент по оси Y.
    /// \return true в случае если флаг поставить можно, false иначе.
    bool FlagOrNot(int32_t x, int32_t y);
    /// Функция для проверки победы.
    /// \return true если игрок победил и false иначе.
    bool CheckWin();
    /// Функция для вывода сообщения о победе на экран.
    void Win();
    /// Функция возвращения стандартного цвета текста в консоли.
    static void GoBack();
    /// Функция для вывода поля.
    void Show();
    /// Функция для постановки / отмены флага.
    /// \param x Элемент по оси Х.
    /// \param y Элемент по оси Y.
    void ChangeFlag(int32_t x, int32_t y);
    /// Функция для вывода поля после наступления на мину.
    void Clear();
    /// Функция для расстановки мин.
    /// \param MinesCnt Количество мин.
    void SetMines(int32_t MinesCnt);
    /// Функция расстановки цифр.
    void SetNums();
    /// Функция для открытия клетки на поле.
    /// \param x Элемент по оси Х.
    /// \param y Элемент по оси Y.
    /// \return Результат - мина или пустое место.
    int32_t Open(int32_t x, int32_t y);
    /// Функция заливки пустых клеток на поле.
    /// \param px Копия на координаты исходной пустой клетки по оси Х.
    /// \param py Копия на координаты исходной пустой клетки по оси Y.
    void Fill(int32_t px, int32_t py);
    int32_t minescnt;
private:
    int32_t size_;
    std::vector<std::vector<int32_t>> field_;
    std::vector<std::vector<int32_t>> map_;
    std::vector<std::vector<int32_t>> flag_;
};

class Keyboard {
public:
    /// Дефолтный конструктор.
    Keyboard();
    /// Функция считывания символа как клавиши с клавиатуры.
    void WaitKey();
    /// Функция получения считанного символа.
    /// \return Копия считанного символа (его код).
    int32_t GetKey() const;
private:
    int32_t ch = 0;
};

class Cursor {
public:
    /// Функция сохранения значений по оси X и по оси Y во временные переменные для дальнейшей работы.
    void Save();
    /// Функция отката значений по оси Х и по оси Y назад (чтобы не было выхода за границы поля).
    void Undo();
    /// Функция увеличения значения по оси Х на 1.
    void IncX();
    /// Функция уменьшения значения по оси Х на 1.
    void DecX();
    /// Функция увеличения значения по оси Y на 1.
    void IncY();
    /// Функция уменьшения значения по оси Y на 1.
    void DecY();
    /// Функция получения координаты Х.
    /// \return Копия на координату Х.
    int32_t GetX() const;
    /// Функция получения координаты Y.
    /// \return Копия на координату Y.
    int32_t GetY() const;
private:
    int32_t x = 1, y = 1;
    int32_t tx = 1, ty = 1;
};

class Game {
public:
    /// Функция для завершения игры при проигрыше.
    static void GameOver();
    /// Функция для запуска главного меню и начала игры.
    static void Run();
    /// Функция выбора уровня сложности.
    void Choose();
private:
    /// Вывод иконки сапёра на экран.
    static void Icon();
};
#endif //UNTITLED27_GAME_H
