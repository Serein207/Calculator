#pragma once
#include <stack>
#include <QVector>
#include "StdInfixGenerator.h"
#include "Tools.h"

class PostfixExprGenerator {
public:
  explicit PostfixExprGenerator(const StdInfixGenerator& infix) noexcept;
  QVector<QString> getPostfix();

private:
  std::stack<QString> m_symStack;
  QVector<QString> m_postfix;
  const StdInfixGenerator& m_infix;
  void handleSymbol(const QString& stdInfix, const qsizetype index);
  void handleFigure(const QString& stdInfix, qsizetype& index);
  void generator();
};
