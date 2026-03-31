#define _USE_MATH_DEFINES
#include <string>
#include <iostream>
#include "Point3D.h"
#include <cmath>
#include <limits>

using namespace std;

namespace geometry {
    Point3D::Point3D(const double x, const double y, const double z) : x(x), y(y), z(z)
    {
    }

    double Point3D::getX() const
    {
        return x;
    }

    double Point3D::getY() const
    {
        return y;
    }

    double Point3D::getZ() const
    {
        return z;
    }

    bool Point3D::operator==(const Point3D& other) const {
        return std::abs(x - other.x) < std::numeric_limits<double>::epsilon() &&
               std::abs(y - other.y) < std::numeric_limits<double>::epsilon() &&
               std::abs(z - other.z) < std::numeric_limits<double>::epsilon();
    }

    std::ostream& operator<<(std::ostream& os, const Point3D& point) {
        os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }

    std::istream& operator>>(std::istream& is, Point3D& point) {
        char comma, bracket;
        is >> bracket >> point.x >> comma >> point.y >> comma >> point.z >> bracket;
        return is;
    }

    bool Point3D::operator!=(const Point3D& other) const {
        return !(*this == other);
    }
    
    double Point3D::distanceTo(const Point3D& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
}
