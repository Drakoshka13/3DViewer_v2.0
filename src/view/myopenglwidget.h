#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "../controller/controller_viewer.h"

namespace  s21 {

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  void DataObj(Data data);
  bool isClicking, radio;

 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 private:
  Data data_;
  float xRot, yRot, zRot;
  QPoint mPos, mDelta;
  void PaintModel();
  void ProjectionCenter();
  void ProjectionParallel();

};


}

#endif  // MYOPENGLWIDGET_H
