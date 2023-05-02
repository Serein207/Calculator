#include "StdInfixGenerator.h"

StdInfixGenerator::StdInfixGenerator(const QString& infix)
  : m_stdInfix(infix) {
}

void StdInfixGenerator::format(const QString& infix) {
  m_stdInfix = infix;

  auto iter =
    std::find_if(
      m_stdInfix.begin(),
      m_stdInfix.end(),
      [](const QChar ch) {
        return (ch == '-' || ch == '+');
      });
  if (iter == m_stdInfix.begin())
    m_stdInfix.insert(0, '0');
}

QString StdInfixGenerator::getFormat() const {
  return m_stdInfix;
}
