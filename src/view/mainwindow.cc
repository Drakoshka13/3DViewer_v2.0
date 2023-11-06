#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(ControllerViewer *controller_viewer, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_viewer_(controller_viewer) {
  ui->setupUi(this);
  setFixedSize(1450, 900);
  frame_count_ = 0;
  timer_ = new QTimer(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_open_file_clicked() {
  QString fileDialog = QFileDialog::getOpenFileName(
      this, "Выберите файл", QCoreApplication::applicationDirPath(),
      "Файлы OBJ (*.obj)");
  if (fileDialog != "") {
    controller_viewer_->Parser(fileDialog.toStdString());
      if(controller_viewer_->GetData().v_count > 0){
        ui->spin_box_move_x->setValue(0.0);
        ui->spin_box_move_y->setValue(0.0);
        ui->spin_box_move_z->setValue(0.0);
        ui->spin_box_x_rot->setValue(0.0);
        ui->spin_box_y_rot->setValue(0.0);
        ui->spin_box_z_rot->setValue(0.0);
        ui->spin_box_scale->setValue(1.0);
        ui->open_gl_widget->SetObj().data = controller_viewer_->GetData();
        ui->name_file->setText(QFileInfo(fileDialog).fileName());
        ui->path_file->setText(QFileInfo(fileDialog).filePath());
        ui->num_of_vertices->setText(
            QString::number(controller_viewer_->GetData().v_count/3));
        ui->num_of_edges->setText(
            QString::number(controller_viewer_->GetData().f_count/2));
    }
  }
}

void MainWindow::on_parallel_radio_toggled() {
  if (ui->central_radio->isChecked() == true) {
    ui->central_radio->setChecked(false);
    ui->open_gl_widget->SetObj().parallel = true;
    ui->open_gl_widget->SetObj().central = false;
  } else {
    ui->parallel_radio->setChecked(true);
  }
}

void MainWindow::on_central_radio_toggled() {
  if (ui->parallel_radio->isChecked() == true) {
    ui->parallel_radio->setChecked(false);
    ui->open_gl_widget->SetObj().parallel = false;
    ui->open_gl_widget->SetObj().central = true;
  } else {
    ui->central_radio->setChecked(true);
  }
}

void MainWindow::on_line_toggled() {
  if (ui->dash_line->isChecked() == true ||
      ui->disable_line->isChecked() == true) {
    ui->dash_line->setChecked(false);
    ui->disable_line->setChecked(false);
    ui->open_gl_widget->SetObj().dash = false;
    ui->open_gl_widget->SetObj().disable_line = false;
  } else {
    ui->line->setChecked(true);
  }
}

void MainWindow::on_dash_line_toggled() {
  if (ui->line->isChecked() == true || ui->disable_line->isChecked() == true) {
    ui->line->setChecked(false);
    ui->disable_line->setChecked(false);
    ui->open_gl_widget->SetObj().dash = true;
    ui->open_gl_widget->SetObj().disable_line = false;
  } else {
    ui->dash_line->setChecked(true);
  }
}

void MainWindow::on_disable_line_toggled() {
  if (ui->line->isChecked() == true || ui->dash_line->isChecked() == true) {
    ui->line->setChecked(false);
    ui->dash_line->setChecked(false);
    ui->open_gl_widget->SetObj().dash = false;
    ui->open_gl_widget->SetObj().disable_line = true;
  } else {
    ui->disable_line->setChecked(true);
  }
}

void MainWindow::on_square_toggled() {
  if (ui->circle->isChecked() == true ||
      ui->disable_vertex->isChecked() == true) {
    ui->circle->setChecked(false);
    ui->disable_vertex->setChecked(false);
    ui->open_gl_widget->SetObj().circle = false;
    ui->open_gl_widget->SetObj().disable_points = false;
  } else {
    ui->square->setChecked(true);
  }
}

void MainWindow::on_circle_toggled() {
  if (ui->square->isChecked() == true ||
      ui->disable_vertex->isChecked() == true) {
    ui->square->setChecked(false);
    ui->disable_vertex->setChecked(false);
    ui->open_gl_widget->SetObj().circle = true;
    ui->open_gl_widget->SetObj().disable_points = false;
  } else {
    ui->circle->setChecked(true);
  }
}

void MainWindow::on_disable_vertex_toggled() {
  if (ui->square->isChecked() == true || ui->circle->isChecked() == true) {
    ui->square->setChecked(false);
    ui->circle->setChecked(false);
    ui->open_gl_widget->SetObj().circle = false;
    ui->open_gl_widget->SetObj().disable_points = true;
  } else {
    ui->disable_vertex->setChecked(true);
  }
}

void MainWindow::on_size_p_valueChanged(double arg1) {
  ui->open_gl_widget->SetObj().size_p = arg1;
}

void MainWindow::on_size_l_valueChanged(double arg1) {
  ui->open_gl_widget->SetObj().size_l = arg1;
}

void MainWindow::on_save_clicked() {
  QSettings settings("s21", "3D_viewer");
  settings.setValue("parallel", ui->open_gl_widget->GetObj().parallel);
  settings.setValue("central", ui->open_gl_widget->GetObj().central);
  settings.setValue("dash", ui->open_gl_widget->GetObj().dash);
  settings.setValue("disable_line", ui->open_gl_widget->GetObj().disable_line);
  settings.setValue("disable_points", ui->open_gl_widget->GetObj().disable_points);
  settings.setValue("circle", ui->open_gl_widget->GetObj().circle);
  settings.setValue("size_l", ui->open_gl_widget->GetObj().size_l);
  settings.setValue("size_p", ui->open_gl_widget->GetObj().size_p);
  settings.setValue("main_color", ui->open_gl_widget->GetObj().main_color_);
  settings.setValue("line_color", ui->open_gl_widget->GetObj().line_color_);
  settings.setValue("vertex_color", ui->open_gl_widget->GetObj().vertex_color_);
}

void MainWindow::on_load_clicked() {
  QSettings settings("s21", "3D_viewer");
  ui->open_gl_widget->SetObj().parallel =
      settings.value("parallel", true).toBool();
  ui->open_gl_widget->SetObj().central =
      settings.value("central", false).toBool();
  if (ui->open_gl_widget->GetObj().parallel == true) {
    ui->parallel_radio->setChecked(true);
  } else {
    ui->central_radio->setChecked(true);
  }

  ui->open_gl_widget->SetObj().dash = settings.value("dash", false).toBool();
  ui->open_gl_widget->SetObj().disable_line =
      settings.value("disable_line", false).toBool();
  if (ui->open_gl_widget->GetObj().dash == true) {
    ui->dash_line->setChecked(true);
  } else if (ui->open_gl_widget->GetObj().disable_line == true) {
    ui->disable_line->setChecked(true);
  } else {
    ui->line->setChecked(true);
  }

  ui->open_gl_widget->SetObj().circle = settings.value("circle", false).toBool();
  ui->open_gl_widget->SetObj().disable_points =
      settings.value("disable_points", false).toBool();
  if (ui->open_gl_widget->GetObj().circle == true) {
    ui->circle->setChecked(true);
  } else if (ui->open_gl_widget->GetObj().disable_points == true) {
    ui->disable_vertex->setChecked(true);
  } else {
    ui->square->setChecked(true);
  }

  ui->open_gl_widget->SetObj().size_l = settings.value("size_l", 0.0).toDouble();
  ui->size_l->setValue(ui->open_gl_widget->GetObj().size_l);
  ui->open_gl_widget->SetObj().size_p = settings.value("size_p", 0.0).toDouble();
  ui->size_p->setValue(ui->open_gl_widget->GetObj().size_p);

  ui->open_gl_widget->SetObj().main_color_ =
      settings.value("main_color", QColor(50, 50, 50, 0)).value<QColor>();
  ui->open_gl_widget->SetObj().line_color_ =
      settings.value("line_color", QColor(255, 0, 0, 0)).value<QColor>();
  ui->open_gl_widget->SetObj().vertex_color_ =
      settings.value("vertex_color", QColor(255, 0, 0, 0)).value<QColor>();
}

void MainWindow::on_spin_box_scale_valueChanged(double arg1) {
  ui->spin_box_scale->setMinimum(0.1);
  double s = arg1 / ui->open_gl_widget->num_last_scale;
  controller_viewer_->ChangeScale(s, s, s);
  ui->open_gl_widget->num_last_scale = arg1;
  ui->open_gl_widget->SetObj().data = controller_viewer_->GetData();
  ui->open_gl_widget->update();
}

void MainWindow::on_spin_box_move_x_valueChanged(double x) {
  double scale_factor = x - ui->open_gl_widget->num_last_x_move;
  controller_viewer_->ChangeX(scale_factor*ui->open_gl_widget->GetObj().data.max_coord);
  ui->open_gl_widget->num_last_x_move = x;
  ui->open_gl_widget->SetObj().data = controller_viewer_->GetData();
  ui->open_gl_widget->update();
}

void MainWindow::on_spin_box_move_y_valueChanged(double y) {
  double scale_factor = y - ui->open_gl_widget->num_last_y_move;
  controller_viewer_->ChangeY(scale_factor*ui->open_gl_widget->GetObj().data.max_coord);
  ui->open_gl_widget->num_last_y_move = y;
  ui->open_gl_widget->SetObj().data = controller_viewer_->GetData();
  ui->open_gl_widget->update();
}

void MainWindow::on_spin_box_move_z_valueChanged(double z) {
  double scale_factor = z - ui->open_gl_widget->num_last_z_move;
  controller_viewer_->ChangeZ(scale_factor*ui->open_gl_widget->GetObj().data.max_coord);
  ui->open_gl_widget->num_last_z_move = z;
  ui->open_gl_widget->SetObj().data = controller_viewer_->GetData();
  ui->open_gl_widget->update();
}

void MainWindow::on_spin_box_x_rot_valueChanged(int arg1) {
  if (arg1 >= 360) {
    ui->spin_box_x_rot->setValue(0);
  } else if (arg1 <= -1) {
    ui->spin_box_x_rot->setValue(359);
  } else {
    controller_viewer_->RotateOX(arg1 - ui->open_gl_widget->num_last_x_rot);
    ui->open_gl_widget->num_last_x_rot = arg1;
    QObject::connect(ui->spin_box_x_rot, SIGNAL(valueChanged(int)),
                     ui->dial_x_rot, SLOT(setValue(int)));
  }
  ui->open_gl_widget->update();
}

void MainWindow::on_dial_x_rot_valueChanged(int value) {
  ui->open_gl_widget->xRot = value;
  QObject::connect(ui->dial_x_rot, SIGNAL(valueChanged(int)), ui->spin_box_x_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_spin_box_y_rot_valueChanged(int arg1) {
  if (arg1 >= 360) {
    ui->spin_box_y_rot->setValue(0);
  } else if (arg1 <= -1) {
    ui->spin_box_y_rot->setValue(359);
  } else {
    controller_viewer_->RotateOY(arg1 - ui->open_gl_widget->num_last_y_rot);
    ui->open_gl_widget->num_last_y_rot = arg1;
  }
  QObject::connect(ui->spin_box_y_rot, SIGNAL(valueChanged(int)), ui->dial_y_rot,
                   SLOT(setValue(int)));
  ui->open_gl_widget->update();
}

void MainWindow::on_dial_y_rot_valueChanged(int value) {
  ui->open_gl_widget->yRot = value;
  QObject::connect(ui->dial_y_rot, SIGNAL(valueChanged(int)), ui->spin_box_y_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_spin_box_z_rot_valueChanged(int arg1) {
  if (arg1 >= 360) {
    ui->spin_box_z_rot->setValue(0);
  } else if (arg1 <= -1) {
    ui->spin_box_z_rot->setValue(359);
  } else {
    controller_viewer_->RotateOZ(arg1 - ui->open_gl_widget->num_last_z_rot);
    ui->open_gl_widget->num_last_z_rot = arg1;
  }
  QObject::connect(ui->spin_box_z_rot, SIGNAL(valueChanged(int)), ui->dial_z_rot,
                   SLOT(setValue(int)));
  ui->open_gl_widget->update();
}

void MainWindow::on_dial_z_rot_valueChanged(int value) {
  ui->open_gl_widget->zRot = value;
  QObject::connect(ui->dial_z_rot, SIGNAL(valueChanged(int)), ui->spin_box_z_rot,
                   SLOT(setValue(int)));
}

void MainWindow::on_exit_program_clicked() { QApplication::quit(); }

void MainWindow::on_color_point_clicked() {
  color_vertex_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_vertex_.isValid())
    ui->open_gl_widget->set_vertex_color(color_vertex_);
  ui->open_gl_widget->update();
}

void MainWindow::on_color_lines_clicked() {
  color_line_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_line_.isValid()) ui->open_gl_widget->set_line_color(color_line_);
  ui->open_gl_widget->update();
}

void MainWindow::on_color_background_clicked() {
  color_main_ = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color_main_.isValid()) ui->open_gl_widget->set_main_color(color_main_);
  ui->open_gl_widget->update();
}

void MainWindow::on_screenshot_clicked() {
  QString f_name = QFileDialog::getSaveFileName(
      this, "Save screenshot", "", "BMP Image (*.bmp);; JPEG Image (*.jpeg)");
  QImage img = ui->open_gl_widget->GetFrame();
  img.save(f_name);
}

void MainWindow::on_pb_gif_clicked() {
  gif_name_ =
      QFileDialog::getSaveFileName(this, "Save GIF", "", "Gif Files (*.gif)");
  if (gif_name_ != "") {
    ui->pb_gif->setText("▢");
    ui->pb_gif->setDisabled(true);
    frame_ = new QGifImage;
    frame_->setDefaultDelay(10);
    timer_->setInterval(100);
    timer_->start();
    connect(timer_, SIGNAL(timeout()), this, SLOT(SaveGIF()));
  }
}

void MainWindow::SaveGIF() {
  QImage img = ui->open_gl_widget->GetFrame();
  frame_->addFrame(img);
  if (frame_count_ == 50) {
    timer_->stop();
    frame_->save(gif_name_);
    frame_count_ = 0;
    delete frame_;
    delete timer_;
    ui->pb_gif->setEnabled(true);
    ui->pb_gif->setText("GIF ▶");
  }
  frame_count_++;
}

}  // namespace s21
