#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#define GL_SILENCE_DEPRECATION
// #include <GL/gl.h>
// #include <GL/glu.h>

#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

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

  void set_line_color(const QColor &color) noexcept;
  void set_vertex_color(const QColor &color) noexcept;
  void set_main_color(const QColor &color) noexcept;
  QImage GetFrame() noexcept;

 private slots:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 private:
  Setting obj;
  float xRot, yRot, zRot;
  QPoint mPos, mDelta;
  bool isClicking;
  void PaintObj();
  void ProjectionCenter();
  void ProjectionParallel();

  QColor main_color_, line_color_, vertex_color_;
};

}  // namespace s21

#endif  // MYOPENGLWIDGET_H
