#include "Picket.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

namespace railway {

    Picket::Picket()
        : number(0), shift(0.0), length(100.0), isStandard(true) {
    }

    Picket::Picket(const int number, const double shift, const double length)
        : number(number), shift(shift), length(length)
    {
        if (length <= 0.0) {
            throw std::invalid_argument("Длина пикета должна быть положительной");
        }
        isStandard = (std::abs(length - 100.0) < 1e-9);
    }

    int    Picket::getNumber()     const { return number; }
    double Picket::getShift()      const { return shift; }
    double Picket::getLength()     const { return length; }
    bool   Picket::getIsStandard() const { return isStandard; }

    double Picket::toMeters() const {
        return number * length + shift;
    }

    std::string Picket::ToString() const {
        std::ostringstream oss;
        // отрицательные пикеты — префикс «0» перед номером
        if (number < 0) {
            oss << "ПК 0" << std::abs(number);
        }
        else {
            oss << "ПК " << number;
        }
        // смещение с двумя знаками после запятой
        oss << "+" << std::fixed << std::setprecision(2) << shift;
        if (!isStandard) {
            oss << " (немерный, L=" << std::fixed << std::setprecision(2) << length << " м)";
        }
        return oss.str();
    }

    // ---- операторы сравнения (по абсолютному расстоянию) ----
    bool Picket::operator==(const Picket& o) const {
        return std::abs(toMeters() - o.toMeters()) < 1e-9;
    }
    bool Picket::operator!=(const Picket& o) const { return !(*this == o); }
    bool Picket::operator<(const Picket& o)  const { return toMeters() < o.toMeters() - 1e-9; }
    bool Picket::operator<=(const Picket& o) const { return !(o < *this); }
    bool Picket::operator>(const Picket& o)  const { return o < *this; }
    bool Picket::operator>=(const Picket& o) const { return !(*this < o); }

    // ---- потоковые операторы ----
    std::ostream& operator<<(std::ostream& os, const Picket& p) {
        os << p.ToString();
        return os;
    }

    // Формат ввода: number shift [length]
    // Пример: "12 28.37" или "12 28.37 80.5"
    std::istream& operator>>(std::istream& is, Picket& p) {
        int    num;
        double sh, len = 100.0;
        is >> num >> sh;
        // если в потоке ещё есть число — читаем длину
        if (is.peek() != '\n' && is.peek() != EOF && is.peek() != ' ') {
            // ничего
        }
        else {
            // попробуем прочитать длину
            char c = is.peek();
            if (c == ' ' || c == '\t') {
                std::streampos pos = is.tellg();
                double tmp;
                if (is >> tmp) {
                    len = tmp;
                }
                else {
                    is.clear();
                    is.seekg(pos);
                }
            }
        }
        p = Picket(num, sh, len);
        return is;
    }
}
