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
  void on_disable_vertex_toggled();
  void on_dash_line_toggled();
  void on_square_toggled();
  void on_circle_toggled();
  void on_size_p_valueChanged(double arg1);
  void on_size_l_valueChanged(double arg1);
  void on_save_clicked();
  void on_load_clicked();
  void on_spin_box_scale_valueChanged(double arg1);
  void on_spin_box_move_x_valueChanged(double с);
  void on_spin_box_move_y_valueChanged(double arg1);
  void on_spin_box_move_z_valueChanged(double z);
  void on_spin_box_x_rot_valueChanged(int arg1);
  void on_dial_x_rot_valueChanged(int value);
  void on_spin_box_y_rot_valueChanged(int arg1);
  void on_dial_y_rot_valueChanged(int value);
  void on_spin_box_z_rot_valueChanged(int arg1);
  void on_dial_z_rot_valueChanged(int value);
  void on_exit_program_clicked();
  void on_color_point_clicked();
  void on_color_lines_clicked();
  void on_color_background_clicked();
  void on_screenshot_clicked();
  void on_pb_gif_clicked();
  void SaveGIF();

 private:
  Ui::MainWindow *ui;
  ControllerViewer *controller_viewer_;
  QColor color_main_, color_line_, color_vertex_;
  int frame_count_;
  QTimer *timer_;
  QGifImage *frame_;
  QString gif_name_;
};

}  // namespace s21

#endif  // MAINWINDOW_H
