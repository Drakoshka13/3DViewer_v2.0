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
  void on_save_clicked();
  void on_load_clicked();

  void on_SpinBox_Scale_valueChanged(double arg1);
  void on_SpinBox_moveX_valueChanged(double с);
  void on_SpinBox_moveY_valueChanged(double arg1);
  void on_SpinBox_moveZ_valueChanged(double arg1);
  void on_SpinBox_X_rot_valueChanged(int arg1);
  void on_dial_X_rot_valueChanged(int value);
  void on_SpinBox_Y_rot_valueChanged(int arg1);
  void on_dial_Y_rot_valueChanged(int value);
  void on_SpinBox_Z_rot_valueChanged(int arg1);
  void on_dial_Z_rot_valueChanged(int value);

  void on_exit_program_clicked();
  void on_color_point_clicked();
  void on_color_lines_clicked();
  void on_color_background_clicked();
  void on_pushButton_clicked();

  void on_pB_GIF_clicked();
  void SaveGIF();

private:
  Ui::MainWindow *ui;
  ControllerViewer *controller_viewer_;
  void SaveSetting();
  QColor color_main_, color_line_, color_vertex_;

  int frame_count_;
  QTimer *timer_;
  QGifImage *frame_;
  QString gif_name_;

};

}  // namespace s21

#endif  // MAINWINDOW_H
