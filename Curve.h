#pragma once
#include "Restriction.h"
#include "Picket.h"

namespace railway {
    /**
    * @brief класс Кривая — ограничение на участке трассы
    *
    * Хранит:
    *   - значение радиуса кривой (> 60 м)
    *   - начало кривой (пикет)
    *   - конец кривой (пикет)
    */
    class Curve : public Restriction {
    private:
        /**
        * @brief radius — радиус кривой в метрах (> 60)
        */
        double radius;

        /**
        * @brief start — начало кривой в пикетах
        */
        Picket start;

        /**
        * @brief end_ — конец кривой в пикетах
        */
        Picket end_;

        /**
        * @brief минимально допустимый радиус кривой
        */
        static constexpr double MIN_RADIUS = 60.0;

        /**
        * @brief проверяет корректность параметров кривой
        */
        void validate() const;

    public:
        /**
        * @brief конструктор по умолчанию
        */
        Curve();

        /**
        * @brief конструктор с параметрами
        * @param radius - радиус кривой (должен быть > 60 м)
        * @param start  - начало кривой (пикет)
        * @param end_   - конец кривой (пикет)
        */
        Curve(const double radius, const Picket& start, const Picket& end_);

        /**
        * @brief конструктор копирования
        */
        Curve(const Curve& other) = default;

        /**
        * @brief оператор присваивания
        */
        Curve& operator=(const Curve& other) = default;

        /**
        * @brief получение радиуса кривой
        */
        double getRadius() const;

        /**
        * @brief получение начала кривой
        */
        Picket getStart() const;

        /**
        * @brief получение конца кривой
        */
        Picket getEnd() const;

        /**
        * @brief длина кривой в метрах
        */
        double getLength() const;

        // ---- переопределение виртуальных методов ----

        /**
        * @brief сериализация в строку:
        *        «Кривая R=<radius> м, от <start> до <end>»
        */
        std::string ToString() const override;

        /**
        * @brief чтение из потока (radius start_num start_shift end_num end_shift)
        */
        void read(std::istream& is) override;

        // ---- операторы сравнения ----
        bool operator==(const Curve& other) const;
        bool operator!=(const Curve& other) const;

        /**
        * @brief статический метод чтения из потока
        * @param is - входной поток
        * @return созданная кривая
        */
        static Curve readFromStream(std::istream& is);

        /**
        * @brief статический метод сериализации
        */
        static std::string ToString(const Curve& curve);
    };
}
