#pragma once
#include <QString>

class StdInfixGenerator {
public:
  [[nodiscard]] QString getFormat() const;
  explicit StdInfixGenerator(const QString& infix);

private:
  QString m_stdInfix;

  void format(const QString& infix);
};
