#include "Restriction.h"

namespace railway {
    std::ostream& operator<<(std::ostream& os, const Restriction& r) {
        os << r.ToString();
        return os;
    }

    std::istream& operator>>(std::istream& is, Restriction& r) {
        r.read(is);
        return is;
    }

    std::string Restriction::ToString(const Restriction& r) {
        return r.ToString();
    }

    Restriction* Restriction::readFromStream(std::istream& is) {
        return nullptr;
    }
}
