#pragma once

#include "Calculator.h"
#include "ui_Calculator.h"
#include "CalResult.h"

QT_BEGIN_NAMESPACE

namespace Ui {
  class CalculatorClass;
};

QT_END_NAMESPACE

class Calculator : public QWidget {
  Q_OBJECT

public:
  Calculator(QWidget* parent = nullptr);
  ~Calculator();

public slots:
  void onButtonGroupClicked(const QAbstractButton* btn);

private:
  Ui::CalculatorClass* _ui;
  QVector<QString> m_postfix;
  QString m_infix;
  QString m_lastInfix;
  void iniUI();
  inline static bool m_equalIsPushed = false;
  inline static bool m_primarySymIsPushed = false;
  inline static bool m_powSymIsPushed = false;

public:
  double getResult();
};
