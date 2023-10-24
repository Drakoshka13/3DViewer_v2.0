#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21{

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(ControllerViewer *controller_viewer, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::MainWindow *ui;
  ControllerViewer *controller_viewer_;
};

}

#endif  // MAINWINDOW_H
