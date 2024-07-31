#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <cstring>
#include <vector>

#include "./Calculator/my_smartcalc.h"

TEST(binary, test1) {
  std::string input_string = "3 + 2";
  std::string x{};
  my::ControllerSmartCalc controller;
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = 3.0 + 2;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(binary, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "3.5 * 2";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = 3.5 * 2;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(binary, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "3.5 / 7";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = 3.5 / 7;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(binary, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "3.5 - 7";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = 3.5 - 7;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(binary, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "7 mod 3";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = 7 % 3;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-1";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = -1;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "cos(3.5) - 7";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = cos(3.5) - 7;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-cos(3.5) * 7";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = -cos(3.5) * 7;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-log(3.5) * 7";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = -log10(3.5) * 7;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "+tan(1/3.5) / 7";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = +tan(1 / 3.5) / 7;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test6) {
  my::ControllerSmartCalc controller;
  std::string input_string = "+37-(2/3.3)-97";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = +37 - (2 / 3.3) - 97;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test7) {
  my::ControllerSmartCalc controller;
  std::string input_string = "+5+8";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = +5 + 8;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test8) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-5+8";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = -5 + 8;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test9) {
  my::ControllerSmartCalc controller;
  std::string input_string = "cos(-3)";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = cos(-3);
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(unary, test10) {
  my::ControllerSmartCalc controller;
  std::string input_string = "+10";
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  double result = +10;
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "12+5";
  double result = 12 + 5;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "12+0.0";
  double result = 12 + 0.0;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-12+2.34";
  double result = -12 + 2.34;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "100+-234.";
  double result = 100 + -234.;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "9+(8+6)+1+(3+9)";
  double result = 9 + (8 + 6) + 1 + (3 + 9);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test6) {
  my::ControllerSmartCalc controller;
  std::string input_string = "21892683+(+60607476)";
  double result = 21892683 + (+60607476);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(add, test7) {
  my::ControllerSmartCalc controller;
  std::string input_string = "794+(101+110)+387";
  double result = 794 + (101 + 110) + 387;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}
TEST(add, test8) {
  my::ControllerSmartCalc controller;
  std::string input_string = "794+(-101+-110)+387";
  double result = 794 + (-101 + -110) + 387;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(sub, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "416-434-(190-490)";
  double result = 416 - 434 - (190 - 490);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(sub, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "107-(928-166-438)";
  double result = 107 - (928 - 166 - 438);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(sub, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(399-985)-63-352";
  double result = (399 - 985) - 63 - 352;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(sub, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "317-141-(118-695)";
  double result = 317 - 141 - (118 - 695);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(sub, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string =
      "-(3879294-5309583)-(3744311-2467480-4787696)-3324295";
  double result =
      -(3879294 - 5309583) - (3744311 - 2467480 - 4787696) - 3324295;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "65991.*(0.5312*5213.)*-(0.9450*897643.)";
  double result = 65991. * (0.5312 * 5213.) * -(0.9450 * 897643.);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(5*2)*6";
  double result = (5 * 2) * 6;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(-0.38227*7856.815-0.)*(7759.3*-51507.96)";
  double result = (-0.38227 * 7856.815 - 0.) * (7759.3 * -51507.96);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "6916.08*-(5855.31*75.6934)*-(-3272.10*4382.36)";
  double result = 6916.08 * -(5855.31 * 75.6934) * -(-3272.10 * 4382.36);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(91.226*-51.9)*(7.797*85.481)";
  double result = (91.226 * -51.9) * (7.797 * 85.481);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test6) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-25.9655*-(-626.93*508.657)*(85.108*400.162)";
  double result = -25.9655 * -(-626.93 * 508.657) * (85.108 * 400.162);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test7) {
  my::ControllerSmartCalc controller;
  std::string input_string =
      "-(-356.081*4598.63)*803.928*(70.592*0.1569)*-36.1566";
  double result =
      -(-356.081 * 4598.63) * 803.928 * (70.592 * 0.1569) * -36.1566;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mult, test8) {
  my::ControllerSmartCalc controller;
  std::string input_string = "2cos(-5)tan(4(2-3))(8-11)";
  double result = 2 * cos(-5) * tan(4 * (2 - 3)) * (8 - 11);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(div, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(432/9.57/321)/(76.4/78.0)/-35.8";
  double result = (432 / 9.57 / 321) / (76.4 / 78.0) / -35.8;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(div, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "43.1/(495.5/711.)/28.7";
  double result = 43.1 / (495.5 / 711.) / 28.7;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(div, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(0.5757/23.3/704.1/-31.27)";
  double result = (0.5757 / 23.3 / 704.1 / -31.27);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(div, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(2451.0/43.94/-1.759)/62.72";
  double result = (2451.0 / 43.94 / -1.759) / 62.72;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(div, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(3*2451.0/43.94/11/2.7*27/-1.759*18)/62.72*3";
  double result =
      (3 * 2451.0 / 43.94 / 11 / 2.7 * 27 / -1.759 * 18) / 62.72 * 3;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(pow, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "8^(3^4)";
  double result = pow(8, pow(3, 4));
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(pow, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "2^5^3";
  double result = pow(2, pow(5, 3));
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mod, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(45.34mod55.23)mod79.4";
  double result = fmod(fmod(45.34, 55.23), 79.4);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mod, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "15.234mod(0.52mod0.034)";
  double result = fmod(15.234, fmod(0.52, 0.034));
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(mod, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "15.234mod0.52mod0.034";
  double result = fmod(fmod(15.234, 0.52), 0.034);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(all, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(72*533+-615)";
  double result = (72 * 533 + -615);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(all, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "826-(738-+243)";
  double result = 826 - (738 - +243);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(all, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "826-(738+-243)";
  double result = 826 - (738 + -243);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(all, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "17mod863*-173";
  double result = fmod(17, 863) * -173;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(all, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "40.34*(-0.424/-252)";
  double result = 40.34 * (-0.424 / -252);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(all, test6) {
  my::ControllerSmartCalc controller;
  std::string input_string = "8mod33.5^(2)/2.6/5";
  double result = fmod(8, pow(33.5, 2)) / 2.6 / 5;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(x, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "2(X)+3";
  double result = 2 * 4.5 + 3;
  std::string x = "4.5";
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(x, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "cos(x)";
  double result = cos(-3.5);
  std::string x = "-3.5";
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(e, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "cos(1.27e+4)";
  double result = cos(1.27e+4);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(e, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "cos(0.5)x";
  double result = cos(0.5) * 0.517e+2;
  std::string x = "0.517e+2";
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test1) {
  my::ControllerSmartCalc controller;
  std::string input_string = "acos(0.1)*sin(1)";
  double result = acos(0.1) * sin(1);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "cos(-1.34)+tan(+2.0)";
  double result = cos(-1.34) + tan(+2.0);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "-(asin(+0.3465346)/2)";
  double result = -(asin(+0.3465346) / 2);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "+atan(1.302+0.5)-1.2";
  double result = +atan(1.302 + 0.5) - 1.2;
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "123mod(sqrt(100))";
  double result = fmod(123, sqrt(100));
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test6) {
  my::ControllerSmartCalc controller;
  std::string input_string = "ln(256-3)";
  double result = log(256 - 3);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(func, test7) {
  my::ControllerSmartCalc controller;
  std::string input_string = "log(+123.345)";
  double result = log10(+123.345);
  std::string x{};
  controller.CalculateExpression(input_string, x);
  double output = controller.GetExpressionResult();
  ASSERT_DOUBLE_EQ(result, output);
}

TEST(wrong, test2) {
  my::ControllerSmartCalc controller;
  std::string input_string = "5--+7";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test3) {
  my::ControllerSmartCalc controller;
  std::string input_string = "5++-7";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test4) {
  my::ControllerSmartCalc controller;
  std::string input_string = "5cosinus3";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test5) {
  my::ControllerSmartCalc controller;
  std::string input_string = "*13/5";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test6) {
  my::ControllerSmartCalc controller;
  std::string input_string = "3*cos";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test7) {
  my::ControllerSmartCalc controller;
  std::string input_string = "189.3//11.1";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test8) {
  my::ControllerSmartCalc controller;
  std::string input_string = "(8";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(wrong, test9) {
  my::ControllerSmartCalc controller;
  std::string input_string = "3)";
  std::string x{};
  ASSERT_ANY_THROW(controller.CalculateExpression(input_string, x));
}

TEST(banc_annu, test1) {
  my::ControllerBankCalc controller;
  std::vector<double> input = {300000, 5 * 12, 16.3};
  std::vector<double> result = {7343.32, 140599.2, 440599.2};
  controller.CalculateAnnuietet(input[0], input[1], input[2]);
  std::vector<double> output = controller.GetCreditResult();
  ASSERT_DOUBLE_EQ(result[0], output[0]);
  ASSERT_DOUBLE_EQ(result[1], output[1]);
  ASSERT_DOUBLE_EQ(result[2], output[2]);
}

TEST(banc_dif, test1) {
  my::ControllerBankCalc controller;
  std::vector<double> input = {300000, 1 * 6, 16.3};
  std::vector<double> result = {314262.5, 300000, 14262.5};
  controller.CalculateDifferPayment(input[0], input[1], input[2]);
  std::vector<double> output = controller.GetCreditResult();
  ASSERT_DOUBLE_EQ(result[0], output[25]);
  ASSERT_DOUBLE_EQ(result[1], output[26]);
  ASSERT_DOUBLE_EQ(result[2], output[27]);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
