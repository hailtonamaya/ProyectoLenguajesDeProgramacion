#include "pch.h"
#include "C:\Users\brand\source\repos\Pr\ProyectoLenguajes\Evaluador.cpp"
#include <gtest/gtest.h>

TEST(TestSuccess1, TestInfijaPostfija1) {
  EXPECT_EQ("13, 2, +", infijaAPostfija("13+2"));
  EXPECT_TRUE(true);
}

TEST(TestSuccess2, TestEvaluarPostfija2) {
	EXPECT_EQ(15, evaluarPostfija("12,3,+"));
	EXPECT_TRUE(true);
}

TEST(TestSuccess3, TestEvaluarPostfija3) {
	EXPECT_EQ(46.2, evaluarPostfija("15.4,3,*"));
	EXPECT_TRUE(true);
}

//------------------------------------------------------------------------------------------------------------------

TEST(TestFailed1, TestInfijaPostfija1) {
	EXPECT_EQ("10, 2, 2, 2, +, -, +", infijaAPostfija("10+2-(2+2)"));
	EXPECT_TRUE(true);
}

TEST(TestFailed2, TestInfijaPostfija2) {
	EXPECT_EQ("3, 10, 2, 2, +, -, +", infijaAPostfija("10+3-(2+2)"));
	EXPECT_TRUE(true);
}

TEST(TestFailed3, TestEvaluarPostfija4) {
	EXPECT_EQ(207, evaluarPostfija("180+23-2+3*2"));
	EXPECT_TRUE(true);
}
