#include "Curve.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

namespace railway {

    // ---- вспомогательная валидация ----
    void Curve::validate() const {
        if (radius <= MIN_RADIUS) {
            throw std::invalid_argument(
                "Радиус кривой должен быть больше " +
                std::to_string(static_cast<int>(MIN_RADIUS)) + " м");
        }
        if (end_ < start) {
            throw std::invalid_argument(
                "Конец кривой должен быть не раньше её начала");
        }
    }

    // ---- конструкторы ----
    Curve::Curve()
        : radius(61.0), start(Picket(0, 0.0)), end_(Picket(0, 0.0)) {
    }

    Curve::Curve(const double radius, const Picket& start, const Picket& end_)
        : radius(radius), start(start), end_(end_)
    {
        validate();
    }

    double Curve::getRadius() const { return radius; }
    Picket Curve::getStart()  const { return start; }
    Picket Curve::getEnd()    const { return end_; }

    double Curve::getLength() const {
        return end_.toMeters() - start.toMeters();
    }

    // ---- ToString ----
    std::string Curve::ToString() const {
        std::ostringstream oss;
        oss << "Кривая: R=" << std::fixed << std::setprecision(2) << radius
            << " м, от " << start.ToString()
            << " до " << end_.ToString()
            << ", длина=" << std::fixed << std::setprecision(2) << getLength() << " м";
        return oss.str();
    }

    // ---- read ----
    // Формат ввода: radius start_num start_shift end_num end_shift
    // Пример: "200.5 12 28.37 15 50.00"
    void Curve::read(std::istream& is) {
        double r;
        int    sNum, eNum;
        double sSh, eSh;

        is >> r >> sNum >> sSh >> eNum >> eSh;

        radius = r;
        start = Picket(sNum, sSh);
        end_ = Picket(eNum, eSh);

        validate();
    }

    // ---- операторы сравнения ----
    bool Curve::operator==(const Curve& o) const {
        return std::abs(radius - o.radius) < 1e-9 &&
            start == o.start &&
            end_ == o.end_;
    }
    bool Curve::operator!=(const Curve& o) const { return !(*this == o); }

    // ---- статические методы ----
    Curve Curve::readFromStream(std::istream& is) {
        Curve c;
        c.read(is);
        return c;
    }

    std::string Curve::ToString(const Curve& curve) {
        return curve.ToString();
    }
}
