#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(ControllerViewer *controller_viewer,
                      QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_open_file_clicked();
  void on_parallel_radio_toggled();
  void on_central_radio_toggled();
  void on_line_toggled();
  void on_disable_line_toggled();
  void on_dash_line_toggled();
  void on_square_toggled();
  void on_circle_toggled();
  void on_vertex_disable_toggled();
  void on_size_p_valueChanged(double arg1);

  void on_size_l_valueChanged(double arg1);

  void on_exit_program_clicked();

  void on_color_point_clicked();
  void on_color_lines_clicked();
  void on_color_background_clicked();

  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  ControllerViewer *controller_viewer_;
  QColor color_main_, color_line_, color_vertex_;
};

}  // namespace s21

#endif  // MAINWINDOW_H
