#include "myopenglwidget.h"

namespace  s21 {

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

MyOpenGLWidget::~MyOpenGLWidget() {}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyOpenGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(xRot, 1.0, 0.0, 0.0);
  glRotatef(yRot, 0.0, 1.0, 0.0);
  glRotatef(zRot, 0.0, 0.0, 1.0);

  if (!data_.vertexes.empty() && !data_.facets.empty()) {
    glVertexPointer(3, GL_FLOAT, 0, &data_.vertexes[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_LINES, data_.f_count, GL_UNSIGNED_INT, &data_.facets[0]);
    glDrawArrays(GL_POINTS, 0, data_.v_count / 3);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* mo) { isClicking = true; }

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent* mo) { isClicking = false; }

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* mo) {
  mDelta = mo->pos() - mPos;
  mPos = mo->pos();
  if (isClicking) {
    xRot += 1 / M_PI * mDelta.y();
    yRot += 1 / M_PI * mDelta.x();
  }
  update();
  mDelta = QPoint();
}

void MyOpenGLWidget::DataObj(Data data) {
  data_ = data;
}

}
