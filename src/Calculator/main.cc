#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale::English);
  QApplication a(argc, argv);
  my::View *view = new my::View;
  view->setAttribute(Qt::WA_DeleteOnClose);
  view->show();
  return a.exec();
}
