#include "credit.h"
#include "ui_annuietet.h"
#include "ui_credit.h"
#include "ui_differ.h"
#include <QMessageBox>

namespace my {
Differ::Differ(QWidget *parent) : QWidget(parent), ui(new Ui::Differ) {
  ui->setupUi(this);
}

void Differ::recieveCredit(std::vector<double> result_) {
  QString toStr;
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->setStyleSheet(
      "QTableView {selection-background-color: rgb(180, 61, 255);}");
  ui->tableWidget->setRowCount(result_[0] + 1);
  int count = 0;
  for (int i = 0; i <= result_[0]; i++) {
    for (int j = 0; j < 4; j++) {
      toStr = QString::number(result_[++count], 'd', 2);
      ui->tableWidget->setItem(i, j, new QTableWidgetItem(toStr));
    }
  }
  toStr = QString::number(result_[++count], 'd', 2);
  ui->lineEdit_platMax->setText(toStr);
  toStr = QString::number(result_[++count], 'd', 2);
  ui->lineEdit_platMin->setText(toStr);
  toStr = QString::number(result_[++count], 'd', 2);
  ui->lineEdit_overPlat->setText(toStr);
  toStr = QString::number(result_[++count], 'd', 2);
  ui->lineEdit_result->setText(toStr);
}

Differ::~Differ() { delete ui; }

Annuietet::Annuietet(QWidget *parent) : QWidget(parent), ui(new Ui::Annuietet) {
  ui->setupUi(this);
}

void Annuietet::recieveCredit(std::vector<double> result_) {
  QString toStr = QString::number(result_[0], 'd', 2);
  ui->lineEdit_platVmes->setText(toStr);
  toStr = QString::number(result_[1], 'd', 2);
  ui->lineEdit_overPlat->setText(toStr);
  toStr = QString::number(result_[2], 'd', 2);
  ui->lineEdit_result->setText(toStr);
}

Annuietet::~Annuietet() { delete ui; }

Credit::Credit(QWidget *parent)
    : QWidget(parent), ui(new Ui::Credit), controller_(new ControllerBankCalc) {
  ui->setupUi(this);
  ui->lineEdit_loan->setValidator(new QDoubleValidator(-10, 10, 2));
  ui->lineEdit_term->setValidator(new QDoubleValidator(-10, 10, 1));
  ui->lineEdit_rate->setValidator(new QDoubleValidator(-10, 10, 2));
  ui->radioButton_an->setChecked(true);
}

void Credit::on_pushButton_OK_clicked() {
  double loan = (ui->lineEdit_loan->text()).toDouble();
  double term = (ui->lineEdit_term->text()).toDouble();
  double rate = (ui->lineEdit_rate->text()).toDouble();

  if (ui->radioButton_an->isChecked()) {
    if (differ_)
      differ_->close();
    if (annuietet_) {
      delete annuietet_;
      annuietet_ = nullptr;
    }
    try {
      controller_->CalculateAnnuietet(GetInput(loan), GetInput(term),
                                      GetInput(rate));
      annuietet_ = new Annuietet;
      annuietet_->setWindowTitle("Калькулятор аннуитетных платежей");
      SetCreditResult(controller_->GetCreditResult());
      connect(this, SIGNAL(sendCredit(std::vector<double>)), annuietet_,
              SLOT(recieveCredit(std::vector<double>)));
      emit sendCredit(result_);
      annuietet_->show();
    } catch (const std::exception &ex) {
      QMessageBox::critical(this, "Error ", ex.what());
    }
  } else {
    if (annuietet_)
      annuietet_->close();
    if (differ_) {
      delete differ_;
      differ_ = nullptr;
    }
    try {
      controller_->CalculateDifferPayment(GetInput(loan), GetInput(term),
                                          GetInput(rate));
      differ_ = new Differ;
      differ_->setWindowTitle("Калькулятор дифференцированных платежей");
      SetCreditResult(controller_->GetCreditResult());
      connect(this, SIGNAL(sendCredit(std::vector<double>)), differ_,
              SLOT(recieveCredit(std::vector<double>)));
      emit sendCredit(result_);
      differ_->show();
    } catch (const std::exception &ex) {
      QMessageBox::critical(this, "Error ", ex.what());
    }
  }
}

void Credit::SetCreditResult(std::vector<double> result) { result_ = result; }

double Credit::GetInput(double input) const { return input; }

Credit::~Credit() {
  if (annuietet_) {
    delete annuietet_;
  }
  if (differ_) {
    delete differ_;
  }
  delete ui;
}

} // namespace my
