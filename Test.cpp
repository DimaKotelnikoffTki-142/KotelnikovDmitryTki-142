#include "CppUnitTest.h"
#include "../Project25/Picket.h"
#include "../Project25/Curve.h"
#include "../Project25/Restriction.h"
#include "../Project25/Picket.cpp"
#include "../Project25/Curve.cpp"
#include "../Project25/Restriction.cpp"
#include <sstream>
#include <cmath>
#include <memory>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace railway;

namespace Tests
{
    // ================================================================
    //  Тесты класса Picket
    // ================================================================
    TEST_CLASS(PicketTests)
    {
    public:
        // 1. Конструктор по умолчанию
        TEST_METHOD(DefaultConstructor_Success)
        {
            // Arrange & Act
            Picket p;

            // Assert
            Assert::AreEqual(0,    p.getNumber());
            Assert::AreEqual(0.0,  p.getShift());
            Assert::AreEqual(100.0, p.getLength());
            Assert::IsTrue(p.getIsStandard());
        }

        // 2. Конструктор с параметрами — стандартный пикет
        TEST_METHOD(ParameterizedConstructor_Standard_Success)
        {
            // Arrange & Act
            Picket p(12, 28.37);

            // Assert
            Assert::AreEqual(12,    p.getNumber());
            Assert::AreEqual(28.37, p.getShift(),  1e-9);
            Assert::AreEqual(100.0, p.getLength(), 1e-9);
            Assert::IsTrue(p.getIsStandard());
        }

        // 3. Конструктор с параметрами — немерный пикет
        TEST_METHOD(ParameterizedConstructor_NonStandard_Success)
        {
            // Arrange & Act
            Picket p(7, 33.00, 80.5);

            // Assert
            Assert::AreEqual(7,    p.getNumber());
            Assert::AreEqual(33.0, p.getShift(),  1e-9);
            Assert::AreEqual(80.5, p.getLength(), 1e-9);
            Assert::IsFalse(p.getIsStandard());
        }

        // 4. toMeters — стандартный пикет
        TEST_METHOD(ToMeters_Standard_Success)
        {
            // Arrange
            Picket p(12, 28.37);
            double expected = 12 * 100.0 + 28.37; // 1228.37

            // Act
            double result = p.toMeters();

            // Assert
            Assert::AreEqual(expected, result, 1e-9);
        }

        // 5. toMeters — немерный пикет
        TEST_METHOD(ToMeters_NonStandard_Success)
        {
            // Arrange
            Picket p(7, 33.00, 80.5);
            double expected = 7 * 80.5 + 33.00; // 596.5

            // Act
            double result = p.toMeters();

            // Assert
            Assert::AreEqual(expected, result, 1e-9);
        }

        // 6. ToString — положительный пикет
        TEST_METHOD(ToString_Positive_Success)
        {
            // Arrange
            Picket p(12, 28.37);

            // Act
            std::string result = p.ToString();

            // Assert
            Assert::IsTrue(result.find("ПК 12")  != std::string::npos);
            Assert::IsTrue(result.find("+28.37") != std::string::npos);
        }

        // 7. ToString — отрицательный пикет (должен содержать "0" перед номером)
        TEST_METHOD(ToString_Negative_Success)
        {
            // Arrange
            Picket p(-3, 12.50);

            // Act
            std::string result = p.ToString();

            // Assert
            // формат «ПК 03+12.50»
            Assert::IsTrue(result.find("ПК 0") != std::string::npos);
            Assert::IsTrue(result.find("3")    != std::string::npos);
            Assert::IsTrue(result.find("+")    != std::string::npos);
        }

        // 8. ToString — немерный пикет содержит пометку
        TEST_METHOD(ToString_NonStandard_ContainsLabel)
        {
            // Arrange
            Picket p(7, 33.00, 80.5);

            // Act
            std::string result = p.ToString();

            // Assert
            Assert::IsTrue(result.find("немерный") != std::string::npos);
        }

        // 9. Оператор ==
        TEST_METHOD(EqualityOperator_Success)
        {
            // Arrange
            Picket p1(12, 28.37);
            Picket p2(12, 28.37);
            Picket p3(15, 50.00);

            // Act & Assert
            Assert::IsTrue(p1  == p2);
            Assert::IsFalse(p1 == p3);
        }

        // 10. Оператор !=
        TEST_METHOD(InequalityOperator_Success)
        {
            // Arrange
            Picket p1(12, 28.37);
            Picket p2(12, 28.37);
            Picket p3(15, 50.00);

            // Act & Assert
            Assert::IsFalse(p1 != p2);
            Assert::IsTrue(p1  != p3);
        }

        // 11. Оператор <
        TEST_METHOD(LessOperator_Success)
        {
            // Arrange
            Picket p1(12, 28.37);
            Picket p2(15, 50.00);

            // Act & Assert
            Assert::IsTrue(p1  < p2);
            Assert::IsFalse(p2 < p1);
        }

        // 12. Оператор >
        TEST_METHOD(GreaterOperator_Success)
        {
            // Arrange
            Picket p1(12, 28.37);
            Picket p2(15, 50.00);

            // Act & Assert
            Assert::IsTrue(p2  > p1);
            Assert::IsFalse(p1 > p2);
        }

        // 13. Оператор <=
        TEST_METHOD(LessOrEqualOperator_Success)
        {
            // Arrange
            Picket p1(12, 28.37);
            Picket p2(12, 28.37);
            Picket p3(15, 50.00);

            // Act & Assert
            Assert::IsTrue(p1 <= p2);
            Assert::IsTrue(p1 <= p3);
            Assert::IsFalse(p3 <= p1);
        }

        // 14. Оператор >=
        TEST_METHOD(GreaterOrEqualOperator_Success)
        {
            // Arrange
            Picket p1(12, 28.37);
            Picket p2(12, 28.37);
            Picket p3(15, 50.00);

            // Act & Assert
            Assert::IsTrue(p1  >= p2);
            Assert::IsTrue(p3  >= p1);
            Assert::IsFalse(p1 >= p3);
        }

        // 15. Оператор вывода <<
        TEST_METHOD(OutputStreamOperator_Success)
        {
            // Arrange
            Picket p(12, 28.37);
            std::stringstream ss;

            // Act
            ss << p;
            std::string result = ss.str();

            // Assert
            Assert::IsTrue(result.find("ПК") != std::string::npos);
            Assert::IsTrue(result.find("+")  != std::string::npos);
        }

        // 16. Оператор ввода >>
        TEST_METHOD(InputStreamOperator_Success)
        {
            // Arrange
            Picket p;
            std::stringstream ss("8 44.75");

            // Act
            ss >> p;

            // Assert
            Assert::AreEqual(8,     p.getNumber());
            Assert::AreEqual(44.75, p.getShift(), 1e-9);
        }

        // 17. Исключение при отрицательной длине пикета
        TEST_METHOD(NegativeLength_ThrowsException)
        {
            // Act & Assert
            auto func = []() {
                Picket p(5, 10.0, -50.0);
            };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 18. Исключение при нулевой длине пикета
        TEST_METHOD(ZeroLength_ThrowsException)
        {
            // Act & Assert
            auto func = []() {
                Picket p(5, 10.0, 0.0);
            };
            Assert::ExpectException<std::invalid_argument>(func);
        }
    };

    // ================================================================
    //  Тесты класса Curve
    // ================================================================
    TEST_CLASS(CurveTests)
    {
    public:
        // 19. Конструктор по умолчанию
        TEST_METHOD(DefaultConstructor_Success)
        {
            // Arrange & Act
            Curve c;

            // Assert — радиус по умолчанию должен быть > 60
            Assert::IsTrue(c.getRadius() > 60.0);
        }

        // 20. Конструктор с параметрами
        TEST_METHOD(ParameterizedConstructor_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            double radius = 200.0;

            // Act
            Curve c(radius, start, end_);

            // Assert
            Assert::AreEqual(radius, c.getRadius(), 1e-9);
            Assert::IsTrue(c.getStart() == start);
            Assert::IsTrue(c.getEnd()   == end_);
        }

        // 21. Конструктор копирования
        TEST_METHOD(CopyConstructor_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve original(200.0, start, end_);

            // Act
            Curve copy(original);

            // Assert
            Assert::IsTrue(original == copy);
        }

        // 22. Оператор присваивания
        TEST_METHOD(AssignmentOperator_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve original(200.0, start, end_);
            Curve assigned;

            // Act
            assigned = original;

            // Assert
            Assert::IsTrue(original == assigned);
        }

        // 23. getLength — длина кривой
        TEST_METHOD(GetLength_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            double expected = end_.toMeters() - start.toMeters(); // 321.63

            // Act
            Curve c(200.0, start, end_);

            // Assert
            Assert::AreEqual(expected, c.getLength(), 1e-9);
        }

        // 24. ToString содержит радиус и пикеты
        TEST_METHOD(ToString_ContainsFields_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve c(200.0, start, end_);

            // Act
            std::string result = c.ToString();

            // Assert
            Assert::IsTrue(result.find("200")  != std::string::npos);
            Assert::IsTrue(result.find("12")   != std::string::npos);
            Assert::IsTrue(result.find("15")   != std::string::npos);
            Assert::IsTrue(result.find("R=")   != std::string::npos);
        }

        // 25. Оператор вывода <<
        TEST_METHOD(OutputStreamOperator_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve c(200.0, start, end_);
            std::stringstream ss;

            // Act
            ss << c;
            std::string result = ss.str();

            // Assert
            Assert::IsTrue(result.find("Кривая") != std::string::npos);
        }

        // 26. Оператор ==
        TEST_METHOD(EqualityOperator_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve c1(200.0, start, end_);
            Curve c2(200.0, start, end_);
            Curve c3(500.0, start, end_);

            // Act & Assert
            Assert::IsTrue(c1  == c2);
            Assert::IsFalse(c1 == c3);
        }

        // 27. Оператор !=
        TEST_METHOD(InequalityOperator_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve c1(200.0, start, end_);
            Curve c2(200.0, start, end_);
            Curve c3(500.0, start, end_);

            // Act & Assert
            Assert::IsFalse(c1 != c2);
            Assert::IsTrue(c1  != c3);
        }

        // 28. Статический метод ToString
        TEST_METHOD(StaticToString_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve c(200.0, start, end_);

            // Act
            std::string result = Curve::ToString(c);

            // Assert
            Assert::IsTrue(result.find("Кривая") != std::string::npos);
            Assert::IsTrue(result.find("200")    != std::string::npos);
        }

        // 29. Чтение через статический readFromStream
        TEST_METHOD(ReadFromStream_Success)
        {
            // Arrange
            std::istringstream iss("350.0 20 0.00 25 50.00");
            double expectedRadius  = 350.0;
            double expectedLength  = 25 * 100.0 + 50.00 - (20 * 100.0 + 0.00); // 550.0

            // Act
            Curve c = Curve::readFromStream(iss);

            // Assert
            Assert::AreEqual(expectedRadius, c.getRadius(), 1e-9);
            Assert::AreEqual(expectedLength, c.getLength(), 1e-9);
        }

        // 30. Чтение через оператор >>
        TEST_METHOD(InputStreamOperator_Success)
        {
            // Arrange
            std::istringstream iss("1200.0 30 12.50 35 80.00");
            double expectedRadius = 1200.0;

            // Act
            Curve c;
            iss >> c;

            // Assert
            Assert::AreEqual(expectedRadius, c.getRadius(), 1e-9);
            Assert::AreEqual(30, c.getStart().getNumber());
            Assert::AreEqual(35, c.getEnd().getNumber());
        }

        // 31. Полиморфизм — через указатель на базовый класс
        TEST_METHOD(Polymorphism_Success)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);
            Curve c(200.0, start, end_);

            // Act
            Restriction* r = &c;
            std::string result = r->ToString();

            // Assert
            Assert::IsTrue(result.find("Кривая") != std::string::npos);
        }

        // 32. Коллекция базового типа
        TEST_METHOD(Collection_Polymorphism_Success)
        {
            // Arrange
            Picket s1(0,  0.00);
            Picket e1(3, 75.50);
            Picket s2(12, 28.37);
            Picket e2(15, 50.00);

            std::vector<std::unique_ptr<Restriction>> restrictions;
            restrictions.push_back(std::make_unique<Curve>(500.0, s1, e1));
            restrictions.push_back(std::make_unique<Curve>(200.0, s2, e2));

            // Act & Assert
            Assert::AreEqual(size_t(2), restrictions.size());
            for (const auto& r : restrictions) {
                std::string str = r->ToString();
                Assert::IsTrue(str.find("Кривая") != std::string::npos);
            }
        }

        // 33. Исключение: радиус == 60 (не больше 60)
        TEST_METHOD(RadiusEqualTo60_ThrowsException)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);

            // Act & Assert
            auto func = [&]() {
                Curve c(60.0, start, end_);
            };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 34. Исключение: радиус меньше 60
        TEST_METHOD(RadiusLessThan60_ThrowsException)
        {
            // Arrange
            Picket start(12, 28.37);
            Picket end_(15, 50.00);

            // Act & Assert
            auto func = [&]() {
                Curve c(30.0, start, end_);
            };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 35. Исключение: конец раньше начала
        TEST_METHOD(EndBeforeStart_ThrowsException)
        {
            // Arrange
            Picket start(15, 50.00);
            Picket end_(12, 28.37);  // end < start

            // Act & Assert
            auto func = [&]() {
                Curve c(200.0, start, end_);
            };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 36. Исключение: некорректные данные при чтении из потока (R=60)
        TEST_METHOD(ReadFromStream_InvalidRadius_ThrowsException)
        {
            // Arrange
            std::istringstream iss("60.0 12 28.37 15 50.00");

            // Act & Assert
            auto func = [&]() {
                Curve c = Curve::readFromStream(iss);
            };
            Assert::ExpectException<std::invalid_argument>(func);
        }
    };
}
