#pragma once
#include <QString>

class Tools {
public:
  static bool isPrimarySym(const QString& symbol) {
    return (symbol == "+") ||
      (symbol == "-") ||
      (symbol == "×") ||
      (symbol == "÷") ||
      (symbol == "%") ||
      (symbol == "+/-");
  }

  static bool isPowSym(const QString& symbol) {
    return (symbol == "1/x") ||
      (symbol == "\342\210\232x") ||
      (symbol == "x\302\262");
  }

  enum class Priority_Lv {
    Level0,
    Level1,
    Level2,
    Level3
  };

  static Priority_Lv getPrior(const QString& symbol) {
    if (symbol == "+" || symbol == "-" || symbol == "+/-")
      return Priority_Lv::Level1;
    if (symbol == "×" || symbol == "÷")
      return Priority_Lv::Level2;
    if (symbol == "%" || symbol == "^")
      return Priority_Lv::Level3;
    return Priority_Lv::Level0;
  }
};
