#include "PostfixExprGenerator.h"

PostfixExprGenerator::PostfixExprGenerator(const StdInfixGenerator& infix) noexcept
  : m_infix(infix) {
}

void PostfixExprGenerator::handleSymbol(const QString& stdInfix, const qsizetype index) {
  QString tmp = "";
  if (m_symStack.empty()) {
    m_symStack.push(stdInfix[index]);
  }
  else {
    while (!m_symStack.empty() &&
      (Tools::getPrior(m_symStack.top()) >= Tools::getPrior(stdInfix[index]))) {
      tmp += m_symStack.top();
      m_postfix.push_back(tmp);
      m_symStack.pop();
      tmp = "";
    }
    m_symStack.push(stdInfix[index]);
  }
}

void PostfixExprGenerator::handleFigure(const QString& stdInfix, qsizetype& index) {
  QString tmp = "";
  tmp += stdInfix[index];
  while (index + 1 < stdInfix.length() &&
    (stdInfix[index + 1] >= '0' &&
      stdInfix[index + 1] <= '9' ||
      stdInfix[index + 1] == '.')) {
    tmp += stdInfix[index + 1];
    index++;
  }
  if (tmp[tmp.length() - 1] == '.') {
    tmp += '0';
  }
  m_postfix.push_back(tmp);
}

QVector<QString> PostfixExprGenerator::getPostfix() {
  generator();
  return m_postfix;
}

void PostfixExprGenerator::generator() {
  QString stdInfix = m_infix.getFormat();
  for (qsizetype i = 0; i < stdInfix.size(); i++) {
    if (Tools::isPrimarySym(stdInfix[i]) || stdInfix[i] == '^') {
      handleSymbol(stdInfix, i);
    }
    if ((stdInfix[i] >= '0' && stdInfix[i] <= '9')) {
      handleFigure(stdInfix, i);
    }
  }
  
  while (!m_symStack.empty()) {
    QString tmp = "";
    tmp += m_symStack.top();
    m_postfix.push_back(tmp);
    m_symStack.pop();
  }
}
