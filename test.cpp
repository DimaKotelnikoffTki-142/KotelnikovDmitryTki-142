#include <gtest/gtest.h>
#include <stdexcept>

#include "../Project26/RingList.cpp"
#include "../Project26/Node.cpp"
#include "../Project26/RingList.h"
#include "../Project26/Node.h"

// ====================================================================
// Конструкторы и базовые запросы
// ====================================================================

TEST(RingList, DefaultConstructor_IsEmpty)
{
    RingList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
    EXPECT_EQ(list.toString(), "( empty )");
}

TEST(RingList, InitializerList_CorrectOrder)
{
    RingList list{ 1, 2, 3, 4, 5 };
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 5u);
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> 4 -> 5 -> ... )");
}

// ====================================================================
// Вставка
// ====================================================================

TEST(RingList, PushFront_PrependsElement)
{
    RingList list{ 2, 3 };
    list.pushFront(1);
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

TEST(RingList, PushBack_AppendsElement)
{
    RingList list{ 1, 2 };
    list.pushBack(3);
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

TEST(RingList, Insert_MiddlePosition)
{
    RingList list{ 1, 3, 4 };
    list.insert(1, 2);
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> 4 -> ... )");
}

TEST(RingList, Insert_AtEnd_EquivalentToPushBack)
{
    RingList list{ 1, 2 };
    list.insert(list.size(), 3);
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

TEST(RingList, Insert_OutOfRange_Throws)
{
    RingList list{ 1, 2 };
    EXPECT_THROW(list.insert(10, 99), std::out_of_range);
}

// ====================================================================
// Удаление
// ====================================================================

TEST(RingList, Erase_FirstElement)
{
    RingList list{ 10, 20, 30 };
    list.erase(0);
    EXPECT_EQ(list.toString(), "( 20 -> 30 -> ... )");
}

TEST(RingList, Erase_LastElement)
{
    RingList list{ 10, 20, 30 };
    list.erase(2);
    EXPECT_EQ(list.toString(), "( 10 -> 20 -> ... )");
}

TEST(RingList, Erase_SingleElement_BecomesEmpty)
{
    RingList list{ 42 };
    list.erase(0);
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.toString(), "( empty )");
}

TEST(RingList, Erase_OutOfRange_Throws)
{
    RingList list{ 1, 2 };
    EXPECT_THROW(list.erase(5), std::out_of_range);
}

TEST(RingList, Remove_ExistingValue_ReturnsTrue)
{
    RingList list{ 1, 2, 3 };
    EXPECT_TRUE(list.remove(2));
    EXPECT_EQ(list.toString(), "( 1 -> 3 -> ... )");
}

TEST(RingList, Remove_AbsentValue_ReturnsFalse)
{
    RingList list{ 1, 2, 3 };
    EXPECT_FALSE(list.remove(99));
    EXPECT_EQ(list.size(), 3u);
}

TEST(RingList, Clear_MakesListEmpty)
{
    RingList list{ 5, 10, 15 };
    list.clear();
    EXPECT_TRUE(list.empty());
}

// ====================================================================
// Поиск и доступ
// ====================================================================

TEST(RingList, Find_ExistingValue)
{
    RingList list{ 10, 20, 30 };
    EXPECT_EQ(list.find(20), 1);
    EXPECT_EQ(list.find(10), 0);
    EXPECT_EQ(list.find(30), 2);
}

TEST(RingList, Find_AbsentValue_ReturnsMinusOne)
{
    RingList list{ 1, 2, 3 };
    EXPECT_EQ(list.find(99), -1);
}

TEST(RingList, IndexOperator_Read)
{
    RingList list{ 7, 14, 21 };
    EXPECT_EQ(list[0], 7);
    EXPECT_EQ(list[1], 14);
    EXPECT_EQ(list[2], 21);
}

TEST(RingList, IndexOperator_Write)
{
    RingList list{ 1, 2, 3 };
    list[1] = 200;
    EXPECT_EQ(list[1], 200);
    EXPECT_EQ(list.toString(), "( 1 -> 200 -> 3 -> ... )");
}

TEST(RingList, IndexOperator_OutOfRange_Throws)
{
    RingList list{ 1, 2 };
    EXPECT_THROW(list[5], std::out_of_range);
}

// ====================================================================
// Циклический сдвиг
// ====================================================================

TEST(RingList, LeftShiftInPlace_ShiftsByN)
{
    RingList list{ 1, 2, 3, 4, 5 };
    list <<= 2;
    EXPECT_EQ(list.toString(), "( 3 -> 4 -> 5 -> 1 -> 2 -> ... )");
}

TEST(RingList, RightShiftInPlace_ShiftsByN)
{
    RingList list{ 1, 2, 3, 4, 5 };
    list >>= 2;
    EXPECT_EQ(list.toString(), "( 4 -> 5 -> 1 -> 2 -> 3 -> ... )");
}

TEST(RingList, LeftShift_ReturnsCopy_OriginalUnchanged)
{
    RingList list{ 1, 2, 3 };
    RingList shifted = list << 1;
    EXPECT_EQ(shifted.toString(), "( 2 -> 3 -> 1 -> ... )");
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

TEST(RingList, RightShift_ReturnsCopy_OriginalUnchanged)
{
    RingList list{ 1, 2, 3 };
    RingList shifted = list >> 1;
    EXPECT_EQ(shifted.toString(), "( 3 -> 1 -> 2 -> ... )");
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

TEST(RingList, Shift_ByFullSize_NoChange)
{
    RingList list{ 1, 2, 3 };
    list <<= 3;
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
    list >>= 3;
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

// ====================================================================
// Конструктор копирования и перемещения
// ====================================================================

TEST(RingList, CopyConstructor_DeepCopy)
{
    RingList original{ 1, 2, 3 };
    RingList copy(original);
    copy[0] = 100;

    EXPECT_EQ(original[0], 1);     // оригинал не изменился
    EXPECT_EQ(copy[0], 100);
}

TEST(RingList, CopyAssignment_DeepCopy)
{
    RingList a{ 1, 2, 3 };
    RingList b{ 9, 8, 7 };
    b = a;
    b[0] = 50;

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(b[0], 50);
}

TEST(RingList, MoveConstructor_TransfersOwnership)
{
    RingList source{ 1, 2, 3 };
    RingList dest(std::move(source));

    EXPECT_EQ(dest.toString(), "( 1 -> 2 -> 3 -> ... )");
    EXPECT_TRUE(source.empty());
}

TEST(RingList, MoveAssignment_TransfersOwnership)
{
    RingList source{ 4, 5, 6 };
    RingList dest;
    dest = std::move(source);

    EXPECT_EQ(dest.size(), 3u);
    EXPECT_TRUE(source.empty());
}

TEST(RingList, SelfAssignment_Safe)
{
    RingList list{ 1, 2, 3 };
    list = list;
    EXPECT_EQ(list.toString(), "( 1 -> 2 -> 3 -> ... )");
}

// ====================================================================
// Граничные случаи
// ====================================================================

TEST(RingList, SingleElement_AllOperationsWork)
{
    RingList list{ 42 };
    EXPECT_EQ(list.find(42), 0);
    EXPECT_EQ(list[0], 42);
    list <<= 5;
    EXPECT_EQ(list.toString(), "( 42 -> ... )");
    list >>= 5;
    EXPECT_EQ(list.toString(), "( 42 -> ... )");
}
