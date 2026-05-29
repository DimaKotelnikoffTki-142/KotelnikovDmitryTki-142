#pragma once

/**
 * @brief Узел циклического односвязного списка.
 *
 * Хранит целочисленное значение и указатель на следующий узел.
 */
class Node
{
public:
    /**
     * @brief Создаёт узел.
     * @param value  Хранимое значение.
     * @param next   Следующий узел (по умолчанию nullptr).
     */
    explicit Node(int value, Node* next = nullptr);

    /** @brief Возвращает значение узла (копия). */
    int   value() const;

    /** @brief Возвращает изменяемую ссылку на значение узла. */
    int& valueRef();

    /** @brief Устанавливает новое значение. */
    void  setValue(int newValue);

    /** @brief Возвращает указатель на следующий узел. */
    Node* next() const;

    /** @brief Устанавливает следующий узел. */
    void  setNext(Node* node);

private:
    int   m_value;
    Node* m_next;
};
