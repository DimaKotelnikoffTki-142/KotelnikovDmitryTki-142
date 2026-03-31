#include <iostream>
#include <vector>
#include <memory>
#include "Pyramid.h"
#include <clocale>

/**
 * @brief точка входа в программу
 * @return 0, если программа выполнена успешно
 */
int main(void) {
    setlocale(LC_ALL, "Russian");
    try {
        std::cout << "=== Демонстрация работы с классом Pyramid ===\n\n";

        std::cout << "1. Создание пирамиды через точки:\n";
        // Основание квадрата в плоскости Z=0: (0,0,0), (0,2,0), (2,2,0)
        // Вершина в центре над основанием: (1,1,2)
        geometry::Point3D b1(0, 0, 0);
        geometry::Point3D b2(0, 2, 0);
        geometry::Point3D b3(2, 2, 0);
        geometry::Point3D apex(1, 1, 2);
        
        geometry::Pyramid pyramid1(b1, b2, b3, apex);
        std::cout << "Пирамида 1: " << pyramid1 << "\n";
        std::cout << "Высота: " << pyramid1.getHeight() << "\n";
        std::cout << "Площадь боковой поверхности: " << pyramid1.getLateralSurfaceArea() << "\n";
        std::cout << "Объем: " << pyramid1.getVolume() << "\n\n";

        std::cout << "2. Создание пирамиды через координаты:\n";
        geometry::Pyramid pyramid2(5, 5, 0, 5, 7, 0, 7, 7, 0, 6, 6, 3);
        std::cout << "Пирамида 2: " << pyramid2 << "\n";
        std::cout << "Высота: " << pyramid2.getHeight() << "\n";
        std::cout << "Площадь боковой поверхности: " << pyramid2.getLateralSurfaceArea() << "\n\n";

        std::cout << "3. Коллекция объектов базового типа:\n";
        std::vector<std::unique_ptr<geometry::Solid>> solids;
        solids.push_back(std::make_unique<geometry::Pyramid>(pyramid1));
        solids.push_back(std::make_unique<geometry::Pyramid>(pyramid2));
        
        std::cout << "Итерация по коллекции:\n";
        for (size_t i = 0; i < solids.size(); ++i) {
            std::cout << "Объект " << (i + 1) << ": " << *solids[i] << "\n";
            std::cout << "  Объем: " << solids[i]->getVolume() << "\n";
            std::cout << "  Площадь поверхности: " << solids[i]->getSurfaceArea() << "\n\n";
        }

        std::cout << "4. Демонстрация операторов сравнения:\n";
        geometry::Pyramid pyramid3(0, 0, 0, 0, 2, 0, 2, 2, 0, 1, 1, 2);
        geometry::Pyramid pyramid4(0, 0, 0, 0, 2, 0, 2, 2, 0, 1, 1, 2);
        geometry::Pyramid pyramid5(0, 0, 0, 0, 3, 0, 3, 3, 0, 1.5, 1.5, 3);
        std::cout << "pyramid3 == pyramid4: " << (pyramid3 == pyramid4 ? "true" : "false") << "\n";
        std::cout << "pyramid3 == pyramid5: " << (pyramid3 == pyramid5 ? "true" : "false") << "\n";

        std::cout << "5. Попытка создания некорректной пирамиды (ожидается исключение):\n";
        try {
            // Точки не образуют прямой угол квадрата
            geometry::Pyramid invalidPyramid(0, 0, 0, 1, 1, 0, 2, 0, 0, 1, 1, 2);
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nПрограмма завершена успешно.\n";
    return 0;
}
