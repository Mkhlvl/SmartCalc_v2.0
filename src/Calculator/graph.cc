#include "graph.h"

#include "ui_graph.h"

namespace my {
Graph::Graph(QWidget *parent)
    : QWidget(parent), ui(new Ui::Graph), controller_(new ControllerSmartCalc) {
  ui->setupUi(this);
  ui->lineEdit_xBegin->setValidator(new QDoubleValidator(-10, 10, 8));
  ui->lineEdit_xEnd->setValidator(new QDoubleValidator(-10, 10, 8));
}

void Graph::recieveData(VectorXY graph, QString function_graph) {
  graph_ = graph;
  function_graph_ = function_graph;
  BuildGraph();
}

void Graph::BuildGraph() {
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->xAxis->setRange(x_begin_, x_end_);
  ui->widget->yAxis->setRange(x_begin_, x_end_);
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  SetResult();
}

std::string Graph::GetInputString(QString string) const {
  return string.toStdString();
}

void Graph::SetResult() const {
  QVector<double> x(graph_.first.begin(), graph_.first.end());
  QVector<double> y(graph_.second.begin(), graph_.second.end());
  ui->widget->graph(0)->addData(x, y);
  ui->widget->graph(0)->setPen(QColor(Qt::magenta));
  ui->widget->replot();
}

void Graph::on_pushButton_clicked() {
  if (!(ui->lineEdit_xBegin->text().isEmpty() &&
        !(ui->lineEdit_xEnd->text().isEmpty()))) {
    ui->widget->clearGraphs();
    x_begin_ = (ui->lineEdit_xBegin->text()).toDouble();
    x_end_ = (ui->lineEdit_xEnd->text()).toDouble();
    controller_->CalculateGraph(GetInputString(function_graph_),
                                GetInputString(QString::number(x_begin_)),
                                GetInputString(QString::number(x_end_)));
    graph_ = controller_->GetGraphResult();
    BuildGraph();
  }
}

Graph::~Graph() { delete ui; }

}  // namespace my
