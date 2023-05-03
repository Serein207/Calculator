#include "Calculator.h"
#include <QButtonGroup>

Calculator::Calculator(QWidget* parent)
  : QWidget(parent)
    , _ui(new Ui::CalculatorClass()) {
  _ui->setupUi(this);
  iniUI();
}

Calculator::~Calculator() {
  delete _ui;
}

void Calculator::iniUI() {
  const auto buttonGroup = new QButtonGroup(this);
  auto btnList = findChildren<QPushButton*>();
  for (const auto& btn : btnList) {
    buttonGroup->addButton(btn);
  }

  connect(buttonGroup, &QButtonGroup::buttonClicked, this, &Calculator::onButtonGroupClicked);
}

void Calculator::onButtonGroupClicked(const QAbstractButton* btn) {
  QString name = btn->text();

  if (name == "C") {
    _ui->lineEdit->clear();
    m_infix = "";
    _ui->lineEdit->insert("0");
  }
  else if (name == "CE") {
    _ui->lineEdit->clear();
    m_infix = "";
    _ui->lineEdit->insert("0");
  }
  else if (name == "Del") {
    _ui->lineEdit->setCursorPosition(_ui->lineEdit->cursorPosition() - 1);
    _ui->lineEdit->del();
    if (_ui->lineEdit->text().isEmpty())
      _ui->lineEdit->insert("0");
    m_infix.erase(m_infix.end() - 1);
  }
  else if (name == "=") {
    _ui->lineEdit->setText(QString("%1").arg(getResult()));
    m_equalIsPushed = true;
    m_powSymIsPushed = false;
    m_primarySymIsPushed = false;
  }
  else if (Tools::isPowSym(name)) {
    if (m_primarySymIsPushed) {
      m_infix.erase(m_infix.end() - 1);
    }
    if (_ui->lineEdit->text() == "0") {
      m_infix += "0";
    }
    m_primarySymIsPushed = false;
    m_equalIsPushed = false;
    m_powSymIsPushed = true;
    if (name == "1/x") {
      qsizetype index = m_infix.length();
      while (index--) {
        if (Tools::isPrimarySym(m_infix[index]) ||
          m_infix[index] == '^') {
          index++;
          const double val = m_infix.mid(index, -1).toDouble();
          name = QString("1÷%1").arg(val);
          break;
        }
        if (index == 0) {
          name = QString("1÷%1").arg(m_infix);
        }
      }
      m_infix.remove(index, m_infix.length() - index);
    }
    else if (name == "\342\210\232x")
      name = "^0.5";
    else if (name == "x\302\262")
      name = "^2";
    m_infix += name;
    _ui->expLineEdit->insert(name);
  }
  else if (Tools::isPrimarySym(name)) {
    if (m_primarySymIsPushed) {
      m_infix.erase(m_infix.end() - 1);
    }
    if (_ui->lineEdit->text() == "0") {
      m_infix += "0";
    }
    m_primarySymIsPushed = true;
    m_equalIsPushed = false;
    m_powSymIsPushed = false;
    m_infix += name;
    _ui->expLineEdit->insert(name);
  }
  else if (name >= "0" && name <= "9" ||
    name == ".") {
    if (((_ui->lineEdit->text() == "0" ||
        m_equalIsPushed) &&
      name == ".")) {
      name = "0.";
      _ui->lineEdit->clear();
    }
    else if (_ui->lineEdit->text() == "0" &&
      name != ".") {
      _ui->lineEdit->clear();
    }

    if (m_equalIsPushed) {
      _ui->lineEdit->clear();
      _ui->expLineEdit->clear();
      m_infix = "";
    }
    if (m_primarySymIsPushed) {
      _ui->lineEdit->clear();
    }
    if (m_primarySymIsPushed && name == ".") {
      name = "0.";
    }
    _ui->lineEdit->insert(name);

    m_infix += name;

    m_primarySymIsPushed = false;
    m_equalIsPushed = false;
    m_powSymIsPushed = false;
  }

  _ui->expLineEdit->setText(m_infix);
}

double Calculator::getResult() {
  const StdInfixGenerator stdInfixGenerator(m_infix);
  PostfixExprGenerator postfixExprGenerator(stdInfixGenerator);
  m_postfix = postfixExprGenerator.getPostfix();
  CalResult cal(m_postfix);
  for (const auto& tmp : m_postfix) {
    if (tmp[0] >= '0' && tmp[0] <= '9')
      cal.num(tmp);
    else if (tmp == "+")
      cal.add();
    else if (tmp == "-")
      cal.sub();
    else if (tmp == "×")
      cal.mul();
    else if (tmp == "÷")
      cal.div();
    else if (tmp == "%")
      cal.mod();
    else if (tmp == "^")
      cal.pow();
  } //end for

  while (!cal.isEmpty())
    cal.other();
  return cal.result();
}
