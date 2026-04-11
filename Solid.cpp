#include "Solid.h"
#include <sstream>

namespace geometry {
    std::ostream& operator<<(std::ostream& os, const Solid& solid) {
        os << solid.ToString();
        return os;
    }

    std::istream& operator>>(std::istream& is, Solid& solid) {
        solid.read(is);
        return is;
    }

    std::string Solid::ToString(const Solid& solid) {
        return solid.ToString();
    }
}
