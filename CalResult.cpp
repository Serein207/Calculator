#include "CalResult.h"

CalResult::CalResult(const QVector<QString>& postfix)
  : m_postfix(postfix) {
}

void CalResult::handleStack() {
  if (!m_figStack.empty()) {
    op2(m_figStack.top());
    m_figStack.pop();
  }
  if (!m_figStack.empty()) {
    op1(m_figStack.top());
    m_figStack.pop();
  }
}

void CalResult::other() {
  m_result = m_figStack.top();
  m_figStack.pop();
}

void CalResult::num(const QString& tmp) {
  m_figStack.push(tmp.toDouble());
}

void CalResult::add() {
  handleStack();
  m_figStack.push(op1() + op2());
}

void CalResult::sub() {
  handleStack();
  m_figStack.push(op1() - op2());
}

void CalResult::mul() {
  handleStack();
  m_figStack.push(op1() * op2());
}

void CalResult::div() {
  handleStack();
  if (op2() == 0.0)
    return;
  m_figStack.push(op1() / op2());
}


void CalResult::mod() {
  handleStack();
  if (op1() == 0.0)
    return;
  m_figStack.push(std::fmod(op1(), op2()));
}

void CalResult::pow(const bool isRec) {
  handleStack();
  if (isRec) op2(-1);
  m_figStack.push(std::powf(op1(), op2()));
}

