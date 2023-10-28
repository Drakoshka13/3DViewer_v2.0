#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

// #include <GL/gl.h>
// #include <GL/glu.h>
#include <glu.h>

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>

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
    bool circle{0};
    bool disable_p{0};
    double size_l{1};
    double size_p{1};
  };
  Setting &SetObj() { return obj; }

 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
//  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 private:
  Setting obj;
  float xRot, yRot, zRot;
  QPoint mPos, mDelta;
  bool isClicking;
  void PaintObj();
  void ProjectionCenter();
  void ProjectionParallel();
};

}  // namespace s21

#endif  // MYOPENGLWIDGET_H
