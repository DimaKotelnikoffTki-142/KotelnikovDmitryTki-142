#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include "Picket.h"
#include "Curve.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
* @brief точка входа в программу
* @return 0, если программа выполнена успешно
*/
int main(void) {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "=== Демонстрация работы с классами Restriction, Picket, Curve ===\n\n";

        std::cout << "1. Создание пикетов:\n";

        railway::Picket pk1(12, 28.37);           // мерный, стандартный
        railway::Picket pk2(15, 50.00);           // мерный, стандартный
        railway::Picket pk3(-3, 12.50);           // отрицательный пикет
        railway::Picket pk4(7, 33.00, 80.5);     // немерный пикет

        std::cout << "Пикет 1: " << pk1 << "\n";
        std::cout << "Пикет 2: " << pk2 << "\n";
        std::cout << "Пикет 3 (отрицательный): " << pk3 << "\n";
        std::cout << "Пикет 4 (немерный): " << pk4 << "\n\n";

        std::cout << "2. Расстояние от начала трассы:\n";
        std::cout << pk1.ToString() << " -> " << pk1.toMeters() << " м\n";
        std::cout << pk4.ToString() << " -> " << pk4.toMeters() << " м\n\n";

        std::cout << "3. Сравнение пикетов:\n";
        std::cout << pk1 << " == " << pk1 << " : " << (pk1 == pk1 ? "true" : "false") << "\n";
        std::cout << pk1 << " != " << pk2 << " : " << (pk1 != pk2 ? "true" : "false") << "\n";
        std::cout << pk1 << " <  " << pk2 << " : " << (pk1 < pk2 ? "true" : "false") << "\n";
        std::cout << pk2 << " >  " << pk1 << " : " << (pk2 > pk1 ? "true" : "false") << "\n\n";

        std::cout << "4. Создание кривых:\n";

        railway::Curve curve1(200.0, pk1, pk2);
        railway::Curve curve2(500.0,
            railway::Picket(0, 0.0),
            railway::Picket(3, 75.50));

        std::cout << "Кривая 1: " << curve1 << "\n";
        std::cout << "  Радиус: " << curve1.getRadius() << " м\n";
        std::cout << "  Длина:  " << curve1.getLength() << " м\n\n";

        std::cout << "Кривая 2: " << curve2 << "\n\n";

        std::cout << "5. Коллекция ограничений (полиморфизм):\n";
        std::vector<std::unique_ptr<railway::Restriction>> restrictions;
        restrictions.push_back(std::make_unique<railway::Curve>(curve1));
        restrictions.push_back(std::make_unique<railway::Curve>(curve2));

        for (size_t i = 0; i < restrictions.size(); ++i) {
            std::cout << "Ограничение " << (i + 1) << ": " << *restrictions[i] << "\n";
        }
        std::cout << "\n";

        std::cout << "6. Сравнение кривых:\n";
        railway::Curve curve1copy = curve1;
        std::cout << "curve1 == curve1copy : " << (curve1 == curve1copy ? "true" : "false") << "\n";
        std::cout << "curve1 != curve2     : " << (curve1 != curve2 ? "true" : "false") << "\n\n";

        std::cout << "7. Статический метод ToString:\n";
        std::cout << railway::Curve::ToString(curve1) << "\n\n";

        std::cout << "8. Чтение кривой из потока (статический readFromStream):\n";
        std::istringstream iss("350.0 20 0.00 25 50.00");
        railway::Curve curve3 = railway::Curve::readFromStream(iss);
        std::cout << "Прочитана: " << curve3 << "\n\n";

        std::cout << "9. Чтение кривой через оператор >> из строкового потока:\n";
        std::istringstream iss2("1200.0 30 12.50 35 80.00");
        railway::Curve curve4;
        iss2 >> curve4;
        std::cout << "Прочитана: " << curve4 << "\n\n";

        std::cout << "10. Чтение пикета через оператор >> из строкового потока:\n";
        std::istringstream issP("8 44.75");
        railway::Picket pkRead;
        issP >> pkRead;
        std::cout << "Прочитан: " << pkRead << "\n\n";

        std::cout << "11. Попытка создать кривую с R=60 м (ожидается исключение):\n";
        try {
            railway::Curve badCurve(60.0, pk1, pk2);
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        }
        std::cout << "\n";

        std::cout << "12. Попытка создать кривую, где конец < начала (ожидается исключение):\n";
        try {
            railway::Curve badCurve2(200.0, pk2, pk1);   // pk2 > pk1
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        }
        std::cout << "\n";

        std::cout << "13. Попытка создать пикет с отрицательной длиной (ожидается исключение):\n";
        try {
            railway::Picket badPk(5, 10.0, -50.0);
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        }
        std::cout << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Необработанная ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Программа завершена успешно.\n";
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
