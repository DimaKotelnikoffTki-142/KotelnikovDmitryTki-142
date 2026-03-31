#pragma once
#include "Solid.h"
#include <vector>

namespace geometry {
    /**
     * @brief Класс Правильная четырехугольная пирамида
     */
    class Pyramid : public Solid {
    private:
        /**
         * @brief BASE_VERTEX_COUNT - постоянное количество вершин основания (квадрат)
         */
        static const int BASE_VERTEX_COUNT = 4;
        /**
         * @brief TOTAL_VERTEX_COUNT - общее количество вершин (4 основания + 1 вершина)
         */
        static const int TOTAL_VERTEX_COUNT = 5;

        /**
         * @brief проверяет корректность пирамиды (квадратное основание, равные боковые ребра)
         * @return true, если все условия выполнены
         */
        bool isValidPyramid() const;
        
        /**
         * @brief вычисляет площадь треугольника по трем точкам
         * @param p1, p2, p3 - вершины треугольника
         * @return площадь
         */
        double triangleArea(const Point3D& p1, const Point3D& p2, const Point3D& p3) const;

    public:
        /**
         * @brief конструктор, создает пирамиду по умолчанию
         */
        Pyramid();

        /**
         * @brief конструктор, создает пирамиду по 3 точкам основания и вершине
         * @param p1, p2, p3 - точки основания (последовательные вершины квадрата)
         * @param apex - вершина пирамиды
         */
        Pyramid(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& apex);

        /**
         * @brief конструктор, создает пирамиду по координатам
         * @param x1, y1, z1 ... x4, y4, z4 - координаты 3 точек основания и вершины
         */
        Pyramid(double x1, double y1, double z1, double x2, double y2, double z2, 
                double x3, double y3, double z3, double x4, double y4, double z4);

        /**
         * @brief сериализация в строку
         */
        std::string ToString() const override;

        /**
         * @brief высчитывает объем пирамиды
         * @return V
         */
        double getVolume() const override;

        /**
         * @brief высчитывает полную площадь поверхности
         * @return S full
         */
        double getSurfaceArea() const override;

        /**
         * @brief находит высоту пирамиды
         * @return h
         */
        double getHeight() const;

        /**
         * @brief рассчитывает площадь боковой поверхности
         * @return S lateral
         */
        double getLateralSurfaceArea() const;

        /**
         * @brief метод чтения из стандартного потока ввода
         */
        void read(std::istream& is) override;

        /**
         * @brief проверяет пирамиды на совпадение
         * @param other - другая пирамида
         * @return true, если пирамиды совпадают
         */
        bool operator==(const Pyramid& other) const;

        /**
         * @brief проверяет пирамиды на несовпадение
         * @param other - другая пирамида
         * @return true, если пирамиды не совпадают
         */
        bool operator!=(const Pyramid& other) const;

        /**
         * @brief сериализация в строку (статический метод)
         */
        static std::string ToString(const Pyramid& pyramid);
    };
}
