#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(ControllerViewer *controller_viewer, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_viewer_(controller_viewer) {
  ui->setupUi(this);
  setFixedSize(1450, 900);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_open_file_clicked() {
  QString fileDialog = QFileDialog::getOpenFileName(
      this, "Выберите файл", QCoreApplication::applicationDirPath(),
      "Файлы OBJ (*.obj)");
  if (fileDialog != "") {
    controller_viewer_->Parser(fileDialog.toStdString());
    ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
    ui->name_file->setText(QFileInfo(fileDialog).fileName());
    ui->path_file->setText(QFileInfo(fileDialog).filePath());
    ui->num_of_vertices->setText(
        QString::number(controller_viewer_->GetData().v_count));
    ui->num_of_facets->setText(
        QString::number(controller_viewer_->GetData().f_count));
  }
}

void MainWindow::on_parallel_radio_toggled() {
  if (ui->central_radio->isChecked() == true) {
    ui->central_radio->setChecked(false);
    ui->openGLWidget->SetObj().parallel = true;
    ui->openGLWidget->SetObj().central = false;
  } else {
    ui->parallel_radio->setChecked(true);
  }
}

void MainWindow::on_central_radio_toggled() {
  if (ui->parallel_radio->isChecked() == true) {
    ui->parallel_radio->setChecked(false);
    ui->openGLWidget->SetObj().parallel = false;
    ui->openGLWidget->SetObj().central = true;
  } else {
    ui->central_radio->setChecked(true);
  }
}

void MainWindow::on_line_toggled() {
  if (ui->dash_line->isChecked() == true ||
      ui->disable_line->isChecked() == true) {
    ui->dash_line->setChecked(false);
    ui->disable_line->setChecked(false);
    ui->openGLWidget->SetObj().dash = false;
    ui->openGLWidget->SetObj().disable_line = false;
  } else {
    ui->line->setChecked(true);
  }
}

void MainWindow::on_dash_line_toggled() {
  if (ui->line->isChecked() == true || ui->disable_line->isChecked() == true) {
    ui->line->setChecked(false);
    ui->disable_line->setChecked(false);
    ui->openGLWidget->SetObj().dash = true;
    ui->openGLWidget->SetObj().disable_line = false;
  } else {
    ui->dash_line->setChecked(true);
  }
}

void MainWindow::on_disable_line_toggled() {
  if (ui->line->isChecked() == true || ui->dash_line->isChecked() == true) {
    ui->line->setChecked(false);
    ui->dash_line->setChecked(false);
    ui->openGLWidget->SetObj().dash = false;
    ui->openGLWidget->SetObj().disable_line = true;
  } else {
    ui->disable_line->setChecked(true);
  }
}

void MainWindow::on_square_toggled() {
  if (ui->circle->isChecked() == true ||
      ui->vertex_disable->isChecked() == true) {
    ui->circle->setChecked(false);
    ui->vertex_disable->setChecked(false);
    ui->openGLWidget->SetObj().circle = false;
    ui->openGLWidget->SetObj().disable_p = false;
  } else {
    ui->square->setChecked(true);
  }
}

void MainWindow::on_circle_toggled() {
  if (ui->square->isChecked() == true ||
      ui->vertex_disable->isChecked() == true) {
    ui->square->setChecked(false);
    ui->vertex_disable->setChecked(false);
    ui->openGLWidget->SetObj().circle = true;
    ui->openGLWidget->SetObj().disable_p = false;
  } else {
    ui->circle->setChecked(true);
  }
}

void MainWindow::on_vertex_disable_toggled() {
  if (ui->square->isChecked() == true || ui->circle->isChecked() == true) {
    ui->square->setChecked(false);
    ui->circle->setChecked(false);
    ui->openGLWidget->SetObj().circle = false;
    ui->openGLWidget->SetObj().disable_p = true;
  } else {
    ui->vertex_disable->setChecked(true);
  }
}

void MainWindow::on_size_p_valueChanged(double arg1) {
  ui->openGLWidget->SetObj().size_p = arg1;
}

void MainWindow::on_size_l_valueChanged(double arg1) {
  ui->openGLWidget->SetObj().size_l = arg1;
}

void MainWindow::on_save_clicked() {
  QSettings settings("s21", "3D_viewer");
  settings.setValue("parallel", ui->openGLWidget->GetObj().parallel);
  settings.setValue("central", ui->openGLWidget->GetObj().central);
  settings.setValue("dash", ui->openGLWidget->GetObj().dash);
  settings.setValue("disable_line", ui->openGLWidget->GetObj().disable_line);
  settings.setValue("disable_p", ui->openGLWidget->GetObj().disable_p);
  settings.setValue("circle", ui->openGLWidget->GetObj().circle);
  settings.setValue("size_l", ui->openGLWidget->GetObj().size_l);
  settings.setValue("size_p", ui->openGLWidget->GetObj().size_p);
  settings.setValue("main_color", ui->openGLWidget->GetObj().main_color_);
  settings.setValue("line_color", ui->openGLWidget->GetObj().line_color_);
  settings.setValue("vertex_color", ui->openGLWidget->GetObj().vertex_color_);
}

void MainWindow::on_load_clicked() {
  QSettings settings("s21", "3D_viewer");
  ui->openGLWidget->SetObj().parallel =
      settings.value("parallel", true).toBool();
  ui->openGLWidget->SetObj().central =
      settings.value("central", false).toBool();
  if (ui->openGLWidget->GetObj().parallel == true) {
    ui->parallel_radio->setChecked(true);
  } else {
    ui->central_radio->setChecked(true);
  }

  ui->openGLWidget->SetObj().dash = settings.value("dash", false).toBool();
  ui->openGLWidget->SetObj().disable_line =
      settings.value("disable_line", false).toBool();
  if (ui->openGLWidget->GetObj().dash == true) {
    ui->dash_line->setChecked(true);
  } else if (ui->openGLWidget->GetObj().disable_line == true) {
    ui->disable_line->setChecked(true);
  } else {
    ui->line->setChecked(true);
  }

  ui->openGLWidget->SetObj().circle = settings.value("circle", false).toBool();
  ui->openGLWidget->SetObj().disable_p =
      settings.value("disable_p", false).toBool();
  if (ui->openGLWidget->GetObj().circle == true) {
    ui->circle->setChecked(true);
  } else if (ui->openGLWidget->GetObj().disable_p == true) {
    ui->vertex_disable->setChecked(true);
  } else {
    ui->square->setChecked(true);
  }

  ui->openGLWidget->SetObj().size_l = settings.value("size_l", 0.0).toDouble();
  ui->size_l->setValue(ui->openGLWidget->GetObj().size_l);
  ui->openGLWidget->SetObj().size_p = settings.value("size_p", 0.0).toDouble();
  ui->size_p->setValue(ui->openGLWidget->GetObj().size_p);

  ui->openGLWidget->SetObj().main_color_ =
      settings.value("main_color", QColor(50, 50, 50, 0)).value<QColor>();
  ui->openGLWidget->SetObj().line_color_ =
      settings.value("line_color", QColor(255, 0, 0, 0)).value<QColor>();
  ui->openGLWidget->SetObj().vertex_color_ =
      settings.value("vertex_color", QColor(255, 0, 0, 0)).value<QColor>();
}

void MainWindow::on_SpinBox_Scale_valueChanged(double arg1) {
  ui->SpinBox_Scale->setMinimum(0.1);
  double s = arg1 / ui->openGLWidget->num_last_scale;
  controller_viewer_->ChangeScale(s, s, s);
  ui->openGLWidget->num_last_scale = arg1;
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_moveX_valueChanged(double x) {
  controller_viewer_->ChangeX(x - ui->openGLWidget->num_last_x_move);
  ui->openGLWidget->num_last_x_move = x;
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_moveY_valueChanged(double arg1) {
  controller_viewer_->ChangeY(arg1 - ui->openGLWidget->num_last_y_move);
  ui->openGLWidget->num_last_y_move = arg1;
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_moveZ_valueChanged(double arg1) {
  controller_viewer_->ChangeZ(arg1 - ui->openGLWidget->num_last_z_move);
  ui->openGLWidget->num_last_z_move = arg1;
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_SpinBox_X_rot_valueChanged(int arg1) {
  ui->SpinBox_X_rot->setValue((360 + (arg1 % 360)) % 360);
  controller_viewer_->RotateOX(arg1 - ui->openGLWidget->num_last_x_rot);
  ui->openGLWidget->num_last_x_rot = arg1;
  QObject::connect(ui->SpinBox_X_rot, SIGNAL(valueChanged(int)), ui->dial_X_rot,
                   SLOT(setValue(int)));
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_dial_X_rot_valueChanged(int value) {
  ui->openGLWidget->xRot = value;
  QObject::connect(ui->dial_X_rot, SIGNAL(valueChanged(int)), ui->SpinBox_X_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_SpinBox_Y_rot_valueChanged(int arg1) {
  ui->SpinBox_Y_rot->setValue((360 + (arg1 % 360)) % 360);
  controller_viewer_->RotateOY(arg1 - ui->openGLWidget->num_last_y_rot);
  ui->openGLWidget->num_last_y_rot = arg1;
  QObject::connect(ui->SpinBox_Y_rot, SIGNAL(valueChanged(int)), ui->dial_Y_rot,
                   SLOT(setValue(int)));
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_dial_Y_rot_valueChanged(int value) {
  ui->openGLWidget->yRot = value;
  QObject::connect(ui->dial_Y_rot, SIGNAL(valueChanged(int)), ui->SpinBox_Y_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_SpinBox_Z_rot_valueChanged(int arg1) {
  ui->SpinBox_Z_rot->setValue((360 + (arg1 % 360)) % 360);
  controller_viewer_->RotateOZ(arg1 - ui->openGLWidget->num_last_z_rot);
  ui->openGLWidget->num_last_z_rot = arg1;
  QObject::connect(ui->SpinBox_Z_rot, SIGNAL(valueChanged(int)), ui->dial_Z_rot,
                   SLOT(setValue(int)));
  ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
  ui->openGLWidget->update();
}

void MainWindow::on_dial_Z_rot_valueChanged(int value) {
  ui->openGLWidget->zRot = value;
  QObject::connect(ui->dial_Z_rot, SIGNAL(valueChanged(int)), ui->SpinBox_Z_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_exit_program_clicked() { QApplication::quit(); }

void MainWindow::on_color_point_clicked() {
  color_vertex_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_vertex_.isValid())
    ui->openGLWidget->set_vertex_color(color_vertex_);
  ui->openGLWidget->update();
}

void MainWindow::on_color_lines_clicked() {
  color_line_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_line_.isValid()) ui->openGLWidget->set_line_color(color_line_);
  ui->openGLWidget->update();
}

void MainWindow::on_color_background_clicked() {
  color_main_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_main_.isValid()) ui->openGLWidget->set_main_color(color_main_);
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_clicked() {
  QString f_name = QFileDialog::getSaveFileName(
      this, "Save screenshot", "", "BMP Image (*.bmp);; JPEG Image (*.jpeg)");
  QImage img = ui->openGLWidget->GetFrame();
  img.save(f_name);
}

}  // namespace s21
