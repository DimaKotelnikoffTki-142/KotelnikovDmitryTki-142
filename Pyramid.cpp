#define _USE_MATH_DEFINES
#include "Pyramid.h"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <limits>

namespace geometry {
    Pyramid::Pyramid()
    {
    }

    Pyramid::Pyramid(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& apex)
    {
        // Проверка, образуют ли p1, p2, p3 угол квадрата (p2 - вершина угла)
        // Векторы p2->p1 и p2->p3
        double v1x = p1.getX() - p2.getX();
        double v1y = p1.getY() - p2.getY();
        double v1z = p1.getZ() - p2.getZ();
        
        double v2x = p3.getX() - p2.getX();
        double v2y = p3.getY() - p2.getY();
        double v2z = p3.getZ() - p2.getZ();

        double len1 = std::sqrt(v1x*v1x + v1y*v1y + v1z*v1z);
        double len2 = std::sqrt(v2x*v2x + v2y*v2y + v2z*v2z);
        double dot = v1x*v2x + v1y*v2y + v1z*v2z;

        // Проверка на перпендикулярность и равенство сторон
        if (std::abs(dot) > std::numeric_limits<double>::epsilon() || 
            std::abs(len1 - len2) > std::numeric_limits<double>::epsilon() ||
            len1 < std::numeric_limits<double>::epsilon()) {
            throw std::invalid_argument("Точки основания не образуют угол квадрата");
        }

        // Вычисляем 4-ю точку основания: p4 = p1 + p3 - p2
        Point3D p4(p1.getX() + p3.getX() - p2.getX(), 
                   p1.getY() + p3.getY() - p2.getY(), 
                   p1.getZ() + p3.getZ() - p2.getZ());

        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
        vertices.push_back(p4);
        vertices.push_back(apex);

        if (!isValidPyramid()) {
            throw std::invalid_argument("Некорректные вершины для правильной пирамиды");
        }
    }

    Pyramid::Pyramid(double x1, double y1, double z1, double x2, double y2, double z2, 
                     double x3, double y3, double z3, double x4, double y4, double z4)
        : Pyramid(Point3D(x1, y1, z1), Point3D(x2, y2, z2), Point3D(x3, y3, z3), Point3D(x4, y4, z4))
    {
    }

    bool Pyramid::isValidPyramid() const {
        if (vertices.size() != TOTAL_VERTEX_COUNT) {
            return false;
        }

        // Проверка равных боковых ребер (расстояние от вершины до всех точек основания)
        const Point3D& apex = vertices[4];
        double dist0 = apex.distanceTo(vertices[0]);
        
        for (size_t i = 1; i < BASE_VERTEX_COUNT; ++i) {
            if (std::abs(apex.distanceTo(vertices[i]) - dist0) > std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
        return true;
    }

    double Pyramid::triangleArea(const Point3D& p1, const Point3D& p2, const Point3D& p3) const {
        // Векторы
        double ax = p2.getX() - p1.getX();
        double ay = p2.getY() - p1.getY();
        double az = p2.getZ() - p1.getZ();

        double bx = p3.getX() - p1.getX();
        double by = p3.getY() - p1.getY();
        double bz = p3.getZ() - p1.getZ();

        // Векторное произведение
        double cx = ay * bz - az * by;
        double cy = az * bx - ax * bz;
        double cz = ax * by - ay * bx;

        return 0.5 * std::sqrt(cx * cx + cy * cy + cz * cz);
    }

    std::string Pyramid::ToString() const {
        std::stringstream ss;
        ss << "Pyramid: Base=[";
        for (size_t i = 0; i < BASE_VERTEX_COUNT; ++i) {
            ss << vertices[i];
            if (i < BASE_VERTEX_COUNT - 1) ss << ", ";
        }
        ss << "], Apex=" << vertices[4];
        return ss.str();
    }

    double Pyramid::getVolume() const {
        double baseArea = getSurfaceArea() - getLateralSurfaceArea(); // S_full - S_lat = S_base
        // Или проще: сторона квадрата ^ 2
        double side = vertices[0].distanceTo(vertices[1]);
        baseArea = side * side;
        return (1.0 / 3.0) * baseArea * getHeight();
    }

    double Pyramid::getSurfaceArea() const {
        return getLateralSurfaceArea() + (vertices[0].distanceTo(vertices[1]) * vertices[0].distanceTo(vertices[1]));
    }

    double Pyramid::getHeight() const {
        // Расстояние от вершины до плоскости основания
        // Плоскость задана точками 0, 1, 2
        // Нормаль к плоскости
        double ax = vertices[1].getX() - vertices[0].getX();
        double ay = vertices[1].getY() - vertices[0].getY();
        double az = vertices[1].getZ() - vertices[0].getZ();

        double bx = vertices[2].getX() - vertices[0].getX();
        double by = vertices[2].getY() - vertices[0].getY();
        double bz = vertices[2].getZ() - vertices[0].getZ();

        double nx = ay * bz - az * by;
        double ny = az * bx - ax * bz;
        double nz = ax * by - ay * bx;
        
        double normLen = std::sqrt(nx*nx + ny*ny + nz*nz);
        if (normLen < std::numeric_limits<double>::epsilon()) return 0.0;

        // Уравнение плоскости: nx*x + ny*y + nz*z + d = 0
        // d = - (nx*x0 + ny*y0 + nz*z0)
        double d = -(nx * vertices[0].getX() + ny * vertices[0].getY() + nz * vertices[0].getZ());

        // Расстояние от точки (apex) до плоскости
        const Point3D& apex = vertices[4];
        double dist = std::abs(nx * apex.getX() + ny * apex.getY() + nz * apex.getZ() + d) / normLen;
        return dist;
    }

    double Pyramid::getLateralSurfaceArea() const {
        // 4 одинаковых треугольника
        return 4.0 * triangleArea(vertices[4], vertices[0], vertices[1]);
    }

    void Pyramid::read(std::istream& is) {
        std::vector<Point3D> newVertices;
        newVertices.resize(TOTAL_VERTEX_COUNT);
        char bracket, comma;
        double x, y, z;
        for (int i = 0; i < TOTAL_VERTEX_COUNT; ++i) {
            is >> bracket >> x >> comma >> y >> comma >> z >> bracket;
            newVertices[i] = Point3D(x, y, z);
        }
        vertices = newVertices;
        if (!isValidPyramid()) {
            throw std::invalid_argument("Некорректные вершины для пирамиды при чтении");
        }
    }

    bool Pyramid::operator==(const Pyramid& other) const {
        if (vertices.size() != other.vertices.size()) {
            return false;
        }
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i] != other.vertices[i]) {
                return false;
            }
        }
        return true;
    }

    bool Pyramid::operator!=(const Pyramid& other) const {
        return !(*this == other);
    }

    std::string Pyramid::ToString(const Pyramid& pyramid) {
        return pyramid.ToString();
    }
}
