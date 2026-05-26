#pragma once
#include <iostream>
#include <string>

namespace railway {
    /**
    * @brief класс Пикет — единица измерения расстояния на железной дороге
    */
    class Picket {
    private:
        /**
        * @brief number — номер пикета (целое число, обычно = 100 м)
        */
        int number;

        /**
        * @brief shift — смещение (дробная часть, в метрах)
        */
        double shift;

        /**
        * @brief length — длина пикета в метрах
        */
        double length;

        /**
        * @brief isStandard — true, если длина пикета равна 100 м (мерный),
        *                      false — немерный пикет
        */
        bool isStandard;

    public:
        /**
        * @brief конструктор по умолчанию
        */
        Picket();

        /**
        * @brief конструктор с параметрами
        * @param number  - номер пикета
        * @param shift   - смещение в метрах
        * @param length  - длина пикета (по умолчанию 100)
        */
        Picket(const int number, const double shift, const double length = 100.0);

        /**
        * @brief получение номера пикета
        */
        int getNumber() const;

        /**
        * @brief получение смещения
        */
        double getShift() const;

        /**
        * @brief получение длины пикета
        */
        double getLength() const;

        /**
        * @brief проверка, является ли пикет стандартным (мерным)
        */
        bool getIsStandard() const;

        /**
        * @brief сериализация в строку вида «ПК Номер+Смещение»
        *        положительные: «ПК 12+28.37»
        *        отрицательные: «ПК 012+28.37»
        */
        std::string ToString() const;

        /**
        * @brief расстояние от начала трассы в метрах (number * length + shift)
        */
        double toMeters() const;

        /**
        * @brief оператор сравнения "равно"
        * @param other пикет для сравнения
        * @return true, если текущий пикет равен other, иначе false
        */
        bool operator==(const Picket& other) const;
        /**
        * @brief оператор сравнения "не равно"
        * @param other пикет для сравнения
        * @return true, если текущий пикет не равен other, иначе false
        */
        bool operator!=(const Picket& other) const;
        /**
        * @brief оператор сравнения "меньше"
        * @param other пикет для сравнения
        * @return true, если текущий пикет меньше other, иначе false
        */
        bool operator<(const Picket& other)  const;
        /**
        * @brief оператор сравнения "меньше или равно"
        * @param other пикет для сравнения
        * @return true, если текущий пикет меньше или равен other, иначе false
        */
        bool operator<=(const Picket& other) const;
        /**
        * @brief оператор сравнения "больше"
        * @param other пикет для сравнения
        * @return true, если текущий пикет больше other, иначе false
        */
        bool operator>(const Picket& other)  const;
        /**
        * @brief оператор сравнения "больше или равно"
        * @param other пикет для сравнения
        * @return true, если текущий пикет больше или равен other, иначе false
        */
        bool operator>=(const Picket& other) const;

        /**
        * @brief оператор вывода в поток
        */
        friend std::ostream& operator<<(std::ostream& os, const Picket& p);

        /**
        * @brief оператор ввода из потока (формат: number shift length)
        */
        friend std::istream& operator>>(std::istream& is, Picket& p);
    };
}
