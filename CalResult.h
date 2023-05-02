#pragma once
#include "PostfixExprGenerator.h"

class CalResult {
public:
  explicit CalResult(const QVector<QString>& postfix);

  void op1(const double op) { m_op1 = op; }
  void op2(const double op) { m_op2 = op; }
  [[nodiscard]] double op1() const { return m_op1; }
  [[nodiscard]] double op2() const { return m_op2; }
  [[nodiscard]] double result() const { return m_result; }
  [[nodiscard]] bool isEmpty() const { return m_figStack.empty(); }

  void num(const QString& tmp);
  void add();
  void sub();
  void mul();
  void div();
  void mod();
  void pow(const bool isRec = false);
  void other();

private:
  double m_op1 = 0.0;
  double m_op2 = 0.0;
  double m_result = 0.0;
  std::stack<double> m_figStack;
  void handleStack();
  QVector<QString> m_postfix;
};
