#include "mainwindow.h"

#include <QMessageBox>

#include "ui_form.h"
#include "ui_mainwindow.h"

namespace my {

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
  ui->lineEdit->setValidator(new QDoubleValidator(-10, 10, 8));
}

void Form::on_pushButton_OK_clicked() {
  QString string = ui->lineEdit->text();
  if (string == "") return;
  emit signalForm(ui->lineEdit->text());
}

Form::~Form() { delete ui; }

View::View(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(new ControllerSmartCalc) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(x_x()));
  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operations()));
}

void View::operations() {
  QPushButton *button = (QPushButton *)sender();
  if ((ui->display_main->toPlainText().contains('>'))) {
    ui->display_main->setText(button->text());
  } else {
    ui->display_main->setText(ui->display_main->toPlainText() + button->text());
  }
}

void View::x_x() {
  QPushButton *button = (QPushButton *)sender();
  QString str = (ui->display_main->toPlainText());
  int count = str.size();
  if (str[count - 1] == '>') {
    ui->display_main->setText(button->text());
  } else {
    ui->display_main->setText(ui->display_main->toPlainText() + button->text());
  }
}

void View::digits() {
  QPushButton *button = (QPushButton *)sender();
  if ((ui->display_main->toPlainText().contains('>'))) {
    ui->display_main->setText(button->text());
  } else {
    ui->display_main->setText(ui->display_main->toPlainText() + button->text());
  }
}

void View::on_pushButton_dot_clicked() {
  QString str = (ui->display_main->toPlainText());
  int count = str.size();
  if (str[count - 1] == '>') {
    ui->display_main->setText(".");
  } else if (str[count - 1] != '.') {
    ui->display_main->setText(ui->display_main->toPlainText() + ".");
  }
}

void View::on_pushButton_del_clicked() { ui->display_main->setText(">"); }

void View::on_pushButton_equal_clicked() {
  QString string = (ui->display_main->toPlainText());
  if (string == ">") {
    return;
  } else {
    if (graph_) graph_->close();
    if (credit_) credit_->close();
    if ((ui->display_main->toPlainText().contains('x'))) {
      if (form_) {
        delete form_;
        form_ = nullptr;
      }
      form_ = new Form;
      form_->setWindowTitle("Введите значение х:");
      form_->show();
      connect(form_, &Form::signalForm, this, &View::slotForm);
    } else {
      try {
        controller_->CalculateExpression(GetInputString(string), "");
        SetResult(controller_->GetExpressionResult());
      } catch (const std::exception &ex) {
        QMessageBox::critical(this, "Error ", ex.what());
        ui->display_main->setText(">");
      }
    }
  }
}

std::string View::GetInputString(QString string) const {
  return string.toStdString();
}

void View::SetResult(double result) const {
  ui->display_main->setText(QString::number(result, 'g', 15));
}

void View::slotForm(QString value_x) {
  QString string = ui->display_main->toPlainText();
  try {
    controller_->CalculateExpression(GetInputString(string),
                                     GetInputString(value_x));

    SetResult(controller_->GetExpressionResult());
  } catch (const std::exception &ex) {
    QMessageBox::critical(this, "Error ", ex.what());
    ui->display_main->setText(">");
  }
}

void View::on_pushButton_graph_clicked() {
  if (credit_) credit_->close();
  if (form_) form_->close();
  QString string = (ui->display_main->toPlainText());
  if (string == ">") return;

  if (graph_) {
    delete graph_;
    graph_ = nullptr;
  }
  try {
    controller_->CalculateGraph(GetInputString(string), "", "");
    graph_ = new Graph;
    graph_->setWindowTitle("График " + string);
    connect(this, SIGNAL(sendData(VectorXY, QString)), graph_,
            SLOT(recieveData(VectorXY, QString)));
    emit sendData(controller_->GetGraphResult(), string);
    graph_->show();
  } catch (const std::exception &ex) {
    QMessageBox::critical(this, "Error ", ex.what());
  }
}

void View::on_pushButton_clear_last_clicked() {
  QString str = (ui->display_main->toPlainText());
  str.chop(1);
  if (!(ui->display_main->toPlainText().contains('>'))) {
    ui->display_main->setText(str);
  }
}

void View::on_pushButton_credit_clicked() {
  if (graph_) graph_->close();
  if (form_) form_->close();
  if (credit_) {
    delete credit_;
    credit_ = nullptr;
  }
  credit_ = new Credit;
  credit_->setWindowTitle("Кредитный калькулятор");
  credit_->show();
}

View::~View() {
  if (form_) delete form_;
  if (graph_) delete graph_;
  if (credit_) delete credit_;
  delete ui;
}

}  // namespace my
