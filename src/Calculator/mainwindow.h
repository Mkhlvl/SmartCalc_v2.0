#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QMainWindow>
#include <QString>
#include <QVector>

#include "credit.h"
#include "graph.h"
#include "my_smartcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class Form;
}  // namespace Ui
QT_END_NAMESPACE

namespace my {

class Form : public QWidget {
  Q_OBJECT

 public:
  explicit Form(QWidget *parent = nullptr);
  ~Form();

 private slots:
  void on_pushButton_OK_clicked();

 private:
  Ui::Form *ui;

 signals:
  void signalForm(QString);
};

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  std::string GetInputString(QString string) const;
  ~View();

 private:
  Ui::MainWindow *ui;
  Form *form_{nullptr};
  Graph *graph_{nullptr};
  Credit *credit_{nullptr};

  ControllerSmartCalc *controller_;

  void SetResult(double result) const;

 private slots:
  void digits();
  void on_pushButton_dot_clicked();
  void operations();
  void x_x();
  void on_pushButton_del_clicked();
  void on_pushButton_clear_last_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_credit_clicked();

 public slots:
  void slotForm(QString value_x);

 signals:
  void sendData(VectorXY, QString);
};

}  // namespace my

#endif  // MAINWINDOW_H
