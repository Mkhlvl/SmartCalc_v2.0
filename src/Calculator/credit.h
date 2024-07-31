#ifndef CREDIT_H
#define CREDIT_H

#include <QDoubleValidator>
#include <QTableWidget>
#include <QWidget>

#include "my_smartcalc.h"

namespace Ui {
class Credit;
class Differ;
class Annuietet;
}  // namespace Ui

namespace my {

class Differ : public QWidget {
  Q_OBJECT

 public:
  explicit Differ(QWidget *parent = nullptr);
  ~Differ();

 private:
  Ui::Differ *ui;

 public slots:
  void recieveCredit(std::vector<double> result_);
};

class Annuietet : public QWidget {
  Q_OBJECT

 public:
  explicit Annuietet(QWidget *parent = nullptr);
  ~Annuietet();

 private:
  Ui::Annuietet *ui;

 public slots:
  void recieveCredit(std::vector<double> result_);
};

class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  double GetInput(double input) const;
  ~Credit();

 private:
  Ui::Credit *ui;
  Annuietet *annuietet_{nullptr};
  Differ *differ_{nullptr};
  ControllerBankCalc *controller_;
  std::vector<double> result_;
  void SetCreditResult(std::vector<double> result);

 private slots:
  void on_pushButton_OK_clicked();

 signals:
  void sendCredit(std::vector<double> result_);
};

}  // namespace my
#endif  // CREDIT_H
