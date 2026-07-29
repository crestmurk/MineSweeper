//
// Created by vladi on 06.07.2022.
//

#ifndef UNTITLED27_GUI_H
#define UNTITLED27_GUI_H

#include <cstdint>
#include <ostream>
#include <string>
#include <utility>

class GUI {
public:
    int16_t size;
    int16_t add_up;
    /// Очищает некоторое кол-во символов в некоторой строке в консоли.
    /// \param row Номер ряда.
    /// \param sym_amo Кол-во символов.
    void ClearRow(int16_t row, uint16_t sym_amo = 210);
    /// Открывает консоль Windows в полный экран и ставит курсор в начало.
    static void WindowMax();
    /// Меняет цвет текста в консоли.
    /// \param text Номер цвета текста.
    /// \param bg Номер цвета фона текста.
    static void SetColor(uint16_t text = 7, uint16_t bg = 0);
    /// Позволяет игроку взаимодействовать с меню с помощью стрелок вверх-вниз/право-лево.
    /// \param a Массив строк - названий файлов, каждый из которых является "сценой"/состоянием меню.
    /// \param n Размер массива.
    /// \return Номер файла в массиве, на котором находился игрок во время нажатия клавиши Enter.
    int16_t Menu(std::string a[], uint32_t n = 1);
    /// Меняет размер шрифта в консоли.
    /// \param font_size Необходимый размер шрифта.
    static void FontSize(int16_t font_size = 16);
    /// Вывод некоторой строки по середине экрана.
    /// \param size Размер карты.
    static void PreString(std::string a);
    /// Вывод сообщения о победе.
    /// \param size Размер карты.
    static void WinString(uint16_t font_size = 16, uint16_t text_color = 14);
    /// Вывод сообщения о поражении.
    /// \param size Размер карты.
    static void LoseString(uint16_t font_size = 16, uint16_t text_color = 9);
    /// Декоративная загрузка
    /// \param sec Кол-во секунд загрузки.
    static void Loading(uint32_t sec);
    /// Очистка Экрана
    static void Cls();
    /// Установка курсора на координату (x, y);
    /// \param x Координата X курсора.
    /// \param y Координата Y курсора.
    static void SetCursorPosition(int x, int y);
    /// Вывыодит строку в рамке.
    /// \param x Строка, которую надо вывести внутри рамки.
    /// \param spaces Кол-во пробелов от рамки.
    void FancyFrame(std::string x, uint32_t spaces = 0) const;
    /// Координаты клика игрока.
    /// \return Возвращает положительные координаты X Y если клик был левой кнокой мыши и отрицательные если правой, где X - номер символа в строке, а Y - номер строки.
    std::pair<int32_t, int32_t> ClickCoord();

/// Выводит содержимое файла.
/// \param file_name Название файла.
static void FilePrint(std::string file_name);

private:
    int16_t menu_status_ = 0;
};

#endif //UNTITLED27_GUI_H
