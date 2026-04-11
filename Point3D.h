#pragma once
#include <iostream>
#include <cmath>
#include <limits>

namespace geometry {
    /**
     * @brief Класс точки в трехмерном пространстве
     */
    class Point3D {
    private:
        /**
         * @brief x - координата точки по оси OX
         */
        double x;
        /**
         * @brief y - координата точки по оси OY
         */
        double y;
        /**
         * @brief z - координата точки по оси OZ
         */
        double z;
    public:
        /**
         * @brief конструктор, создает точку с координатами x, y, z
         * @param x - координата точки по оси OX
         * @param y - координата точки по оси OY
         * @param z - координата точки по оси OZ
         */
        Point3D(double x = 0.0, double y = 0.0, double z = 0.0);

        /**
         * @brief получение координаты x
         * @return x
         */
        double getX() const;

        /**
         * @brief получение координаты y
         * @return y
         */
        double getY() const;

        /**
         * @brief получение координаты z
         * @return z
         */
        double getZ() const;

        /**
         * @brief проверяет точки на совпадение
         * @param other - другая точка
         * @return true, если точки совпадают
         */
        bool operator==(const Point3D& other) const;

        /**
         * @brief проверяет точки на несовпадение
         * @param other - другая точка
         * @return true, если точки не совпадают
         */
        bool operator!=(const Point3D& other) const;

        /**
         * @brief получение "разрешения" у класса на доступ к private для вывода
         * @param os
         * @param point - точка, для вывода
         */
        friend std::ostream& operator<<(std::ostream& os, const Point3D& point);

        /**
         * @brief получение "разрешения" у класса на доступ к private для ввода
         * @param is
         * @param point - точка, для ввода
         */
        friend std::istream& operator>>(std::istream& is, Point3D& point);
        
        /**
         * @brief вычисляет расстояние до другой точки
         * @param other - другая точка
         * @return расстояние
         */
        double distanceTo(const Point3D& other) const;
    };
}
