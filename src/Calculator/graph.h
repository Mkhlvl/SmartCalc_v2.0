#ifndef GRAPH_H
#define GRAPH_H

#include <QCloseEvent>
#include <QDebug>
#include <QDoubleValidator>
#include <QList>
#include <QVector>
#include <QWidget>

#include "my_smartcalc.h"

namespace Ui {
class Graph;
}
namespace my {
class Graph : public QWidget {
  Q_OBJECT

public:
  explicit Graph(QWidget *parent = nullptr);
  std::string GetInputString(QString string) const;
  ~Graph();

private:
  Ui::Graph *ui;
  ControllerSmartCalc *controller_;
  VectorXY graph_;
  QString function_graph_;
  double x_begin_ = -15, x_end_ = 15;
  void SetResult() const;
  void BuildGraph();

public slots:
  void recieveData(VectorXY, QString);

private slots:
  void on_pushButton_clicked();
};
} // namespace my
#endif // GRAPH_H
