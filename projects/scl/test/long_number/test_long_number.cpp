#include <gtest/gtest.h>

#include "long_number.hpp"

TEST(get_digits_number, check_positive) {
    VBek::LongNumber x("12345");
    ASSERT_EQ(5, x.get_digits_number())
        << "Неправильно подсчитано количество разрядов в числе " << x;
}

TEST(get_digits_number, check_negative) {
    VBek::LongNumber x("-1");
    ASSERT_EQ(1, x.get_digits_number())
        << "Неправильно подсчитано количество разрядов в числе " << x;
}

class LongNumberFixture : public testing::Test {
public:
    VBek::LongNumber zero = VBek::LongNumber("0");
    VBek::LongNumber one_v1 = VBek::LongNumber("1");
    VBek::LongNumber one_v2 = VBek::LongNumber("1");
    VBek::LongNumber two = VBek::LongNumber("2");
    VBek::LongNumber three = VBek::LongNumber("3");
    VBek::LongNumber five = VBek::LongNumber("5");
    VBek::LongNumber six = VBek::LongNumber("6");
    VBek::LongNumber twelve = VBek::LongNumber("12");
    VBek::LongNumber negative_one_v1 = VBek::LongNumber("-1");
    VBek::LongNumber negative_two = VBek::LongNumber("-2");
    VBek::LongNumber negative_five = VBek::LongNumber("-5");
    VBek::LongNumber big_number = VBek::LongNumber("123456789101112131415");
};

TEST_F(LongNumberFixture, equality) {
    ASSERT_TRUE(one_v1 == one_v2) << "Проверка " << one_v1 << " == " << one_v2;
    ASSERT_FALSE(one_v1 == twelve) << "Проверка " << one_v1 << " == " << twelve;
    ASSERT_FALSE(one_v1 == negative_one_v1) << "Проверка " << one_v1 << " == " << negative_one_v1;
}

TEST_F(LongNumberFixture, greater) {
    ASSERT_TRUE(two > one_v1) << "Проверка " << two << " > " << one_v1;
    ASSERT_FALSE(one_v1 > two) << "Проверка " << one_v1 << " > " << two;
    ASSERT_FALSE(one_v1 > one_v1) << "Проверка " << one_v1 << " > " << one_v1;
    ASSERT_FALSE(zero > one_v1) << "Проверка " << zero << " > " << one_v1;
    //ASSERT_FALSE(negative_one_v1 > one_v1) << "Проверка " << negative_one_v1 << " > " << one_v1;
}

TEST_F(LongNumberFixture, less) {
    ASSERT_TRUE(one_v1 < two) << "Проверка " << one_v1 << " < " << two;
    ASSERT_FALSE(two < one_v1) << "Проверка " << two << " < " << one_v1;
    ASSERT_FALSE(one_v1 < one_v1) << "Проверка " << one_v1 << " < " << one_v1;
    ASSERT_FALSE(one_v1 < zero) << "Проверка " << one_v1 << " < " << zero;
    //ASSERT_FALSE(one_v1 < negative_one_v1) << "Проверка " << one_v1 << " < " << negative_one_v1;
}

TEST_F(LongNumberFixture, addition) {
    VBek::LongNumber sum_v1 = one_v1 + two;
    ASSERT_EQ(three, sum_v1);
    ASSERT_FALSE(sum_v1.is_negative());
}

//TEST_F(LongNumberFixture, addition_negative) {
//    VBek::LongNumber nsum = two + negative_one_v1;
//    ASSERT_EQ(one_v1, nsum);
//    ASSERT_FALSE(nsum.is_negative());
//}

TEST_F(LongNumberFixture, addition_zero) {
    VBek::LongNumber sum_v2 = zero + zero;
    ASSERT_EQ(zero, sum_v2);
}
TEST_F(LongNumberFixture, addition_big) {
    VBek::LongNumber sum_big = big_number + twelve;
    ASSERT_EQ(VBek::LongNumber("123456789101112131427"), sum_big);
}

TEST_F(LongNumberFixture, subtraction_v1) {
    VBek::LongNumber dif_v1 = one_v1 - two;
    ASSERT_EQ(negative_one_v1, dif_v1);
    ASSERT_TRUE(dif_v1.is_negative());
}

TEST_F(LongNumberFixture, subtraction_v2) {
    VBek::LongNumber dif_v1 = five - two;
    ASSERT_EQ(three, dif_v1);
    ASSERT_FALSE(dif_v1.is_negative());
}

TEST_F(LongNumberFixture, subtraction_v3) {
    VBek::LongNumber dif_v2 = two - two;
    ASSERT_EQ(zero, dif_v2);
}

TEST_F(LongNumberFixture, subtraction_zero) {
    VBek::LongNumber dif_v2 = zero - zero;
    ASSERT_EQ(zero, dif_v2);
}

TEST_F(LongNumberFixture, subtraction_big) {
    VBek::LongNumber dif_big = big_number - twelve;
    ASSERT_EQ(VBek::LongNumber("123456789101112131403"), dif_big);
}

TEST_F(LongNumberFixture, multiplication) {
    VBek::LongNumber comp_v1 = one_v1 * two;
    ASSERT_EQ(two, comp_v1);
    ASSERT_FALSE(comp_v1.is_negative());
}

TEST_F(LongNumberFixture, multiplication_negative) {
    VBek::LongNumber ncomp = two * negative_one_v1;
    ASSERT_EQ(negative_two, ncomp);
    ASSERT_TRUE(ncomp.is_negative());
}

TEST_F(LongNumberFixture, multiplication_zero) {
    VBek::LongNumber comp_v2 = zero * one_v1;
    ASSERT_EQ(zero, comp_v2);
}

TEST_F(LongNumberFixture, multiplication_big) {
    VBek::LongNumber comp_big = big_number * two;
    ASSERT_EQ(VBek::LongNumber("246913578202224262830"), comp_big);
}

//TEST_F(LongNumberFixture, division) {
//    VBek::LongNumber divisible(twelve);
//    VBek::LongNumber divider(two);
//    VBek::LongNumber priv_v1 = divisible / divider;
//    ASSERT_EQ(six, priv_v1);
//    ASSERT_FALSE(priv_v1.is_negative());
//}
//
//TEST_F(LongNumberFixture, division_negative) {
//    VBek::LongNumber npriv = two / negative_one_v1;
//    ASSERT_EQ(negative_two, npriv);
//    ASSERT_TRUE(npriv.is_negative());
//}
//
//TEST_F(LongNumberFixture, division_zero_v1) {
//    VBek::LongNumber priv_v2 = zero / two;
//    ASSERT_EQ(zero, priv_v2);
//}
//
//TEST_F(LongNumberFixture, division_big) {
//    VBek::LongNumber priv_big = big_number / three;
//    ASSERT_EQ(VBek::LongNumber("41152263033704043805"), priv_big);
//}

//TEST_F(LongNumberFixture, remainder_of_division) {
//    VBek::LongNumber divisible(twelve);
//    VBek::LongNumber divider(five);
//    VBek::LongNumber remains_v1 = divisible % divider;
//    ASSERT_EQ(two, remains_v1);
//    ASSERT_FALSE(remains_v1.is_negative());
//}
//
//TEST_F(LongNumberFixture, remainder_of_division_negative) {
//    VBek::LongNumber nremains = twelve % negative_five;
//    ASSERT_EQ(two, nremains);
//}
//
//TEST_F(LongNumberFixture, remainder_of_division_zero) {
//    VBek::LongNumber remains_v2 = zero % five;
//    ASSERT_EQ(zero, remains_v2);
//}
//
////TEST_F(LongNumberFixture, remainder_of_division_big) {
////    VBek::LongNumber remains_big = big_number % two;
////    ASSERT_EQ(one_v1, remains_big);
////}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
