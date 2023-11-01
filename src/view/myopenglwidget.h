#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

//#include <GL/gl.h>
//#include <GL/glu.h>

#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>

#include "../controller/controller_viewer.h"

namespace s21 {

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  struct Setting {
    Data data{};
    bool parallel{1};
    bool central{0};
    bool dash{0};
    bool disable_line{0};
    bool disable_p{0};
    bool circle{0};
    double size_l{1};
    double size_p{1};
  };
  Setting &SetObj() { return obj; }
  Setting GetObj() { return obj; }
  void SaveSetting();
  void LoadSetting();

  double num_last_scale = 1.0;
  double num_last_x_move = 0.0, num_last_y_move = 0.0, num_last_z_move = 0.0;
  double num_last_x_rot = 0.0, num_last_y_rot = 0.0, num_last_z_rot = 0.0;

  double xRot, yRot, zRot;


 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 private:
  Setting obj;
  QPoint mPos, mDelta;
  bool isClicking;
  void PaintObj();
  void ProjectionCenter();
  void ProjectionParallel();

  QColor main_color_, line_color_, vertex_color_;
};

}  // namespace s21

#endif  // MYOPENGLWIDGET_H
