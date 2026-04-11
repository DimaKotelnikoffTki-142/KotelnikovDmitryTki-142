#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Point3D.h"

namespace geometry {
    /**
     * @brief Базовый класс для трехмерных тел
     */
    class Solid {
    protected:
        std::vector<Point3D> vertices;
    public:
        /**
         * @brief конструктор, стандартной реализации
         */
        Solid() = default;

        /**
         * @brief виртуальный деструктор по умолчанию
         */
        virtual ~Solid() = default;

        /**
         * @brief сериализация в строку
         */
        virtual std::string ToString() const = 0;

        /**
         * @brief высчитывает объем тела
         * @return объем
         */
        virtual double getVolume() const = 0;

        /**
         * @brief высчитывает полную площадь поверхности
         * @return площадь
         */
        virtual double getSurfaceArea() const = 0;

        /**
         * @brief метод чтения из стандартного потока ввода
         */
        virtual void read(std::istream& is) = 0;

        /**
         * @brief получение "разрешения" у класса на доступ к private для вывода
         * @param os
         * @param solid - тело, для вывода
         */
        friend std::ostream& operator<<(std::ostream& os, const Solid& solid);

        /**
         * @brief получение "разрешения" у класса на доступ к private для ввода
         * @param is
         * @param solid - тело, для ввода
         */
        friend std::istream& operator>>(std::istream& is, Solid& solid);

        /**
         * @brief сериализация в строку (статический метод)
         */
        static std::string ToString(const Solid& solid);
    };
}
