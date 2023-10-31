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
}

}  // namespace s21
