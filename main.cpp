#include <iostream>
#include <stdexcept>

#include "RingList.h"

int main()
{
    try
    {
        RingList list{ 10, 20, 30, 40, 50 };
        std::cout << "Initial list:        " << list.toString() << "\n";

        list.pushFront(5);
        list.pushBack(60);
        std::cout << "After push 5 & 60:   " << list.toString() << "\n";

        list.insert(3, 25);
        std::cout << "After insert(3, 25): " << list.toString() << "\n";

        list.erase(0);
        std::cout << "After erase(0):      " << list.toString() << "\n";

        bool removed = list.remove(40);
        std::cout << "remove(40) = " << (removed ? "true" : "false")
            << ", list: " << list.toString() << "\n";

        int idx = list.find(25);
        std::cout << "find(25) = " << idx << "\n";

        std::cout << "list[0] = " << list[0]
            << ", list[2] = " << list[2] << "\n";
        list[0] = 11;
        std::cout << "After list[0] = 11:  " << list.toString() << "\n";

        RingList shiftedLeft = list << 2;
        RingList shiftedRight = list >> 2;
        std::cout << "Shift left  by 2:    " << shiftedLeft.toString() << "\n";
        std::cout << "Shift right by 2:    " << shiftedRight.toString() << "\n";

        list <<= 1;
        std::cout << "list <<= 1:          " << list.toString() << "\n";
        list >>= 1;
        std::cout << "list >>= 1:          " << list.toString() << "\n";

        RingList copy(list);
        copy[0] = 999;
        std::cout << "Original after copy: " << list.toString() << "\n";
        std::cout << "Copy (copy[0]=999):  " << copy.toString() << "\n";

        RingList moved(std::move(copy));
        std::cout << "Moved list:          " << moved.toString() << "\n";
        std::cout << "copy after move (empty?): "
            << (copy.empty() ? "yes" : "no") << "\n";

        std::cout << "moved.size() = " << moved.size() << "\n";

        moved.clear();
        std::cout << "After clear:         " << moved.toString() << "\n";
        std::cout << "Empty? " << (moved.empty() ? "yes" : "no") << "\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
