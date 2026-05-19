#pragma once
#include <iostream>
#include <string>

namespace railway {
    /**
    * @brief абстрактный базовый класс Ограничение
    */
    class Restriction {
    public:
        /**
        * @brief виртуальный деструктор по умолчанию
        */
        virtual ~Restriction() = default;

        /**
        * @brief сериализация в строку (координаты в пикетах и значение ограничения)
        * @return строковое представление ограничения
        */
        virtual std::string ToString() const = 0;

        /**
        * @brief метод чтения из стандартного потока ввода
        * @param is - входной поток
        */
        virtual void read(std::istream& is) = 0;

        /**
        * @brief оператор вывода в поток
        */
        friend std::ostream& operator<<(std::ostream& os, const Restriction& r);

        /**
        * @brief оператор ввода из потока
        */
        friend std::istream& operator>>(std::istream& is, Restriction& r);

        /**
        * @brief статический метод сериализации в строку
        * @param r - ограничение
        * @return строковое представление
        */
        static std::string ToString(const Restriction& r);

        /**
        * @brief статический метод чтения из стандартного потока ввода
        * @param is - входной поток
        * @return указатель на созданное ограничение (nullptr в базовой реализации)
        */
        static Restriction* readFromStream(std::istream& is);
    };
}
