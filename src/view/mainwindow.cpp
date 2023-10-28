#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21{

MainWindow::MainWindow(ControllerViewer *controller_viewer, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), controller_viewer_(controller_viewer){
    ui->setupUi(this);
    setFixedSize(1450, 900);

}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_open_file_clicked() {
    QString fileDialog = QFileDialog::getOpenFileName(this, "Выберите файл",  QCoreApplication::applicationDirPath(), "Файлы OBJ (*.obj)");
    controller_viewer_->Parser(fileDialog.toStdString());
    ui->openGLWidget->SetObj().data = controller_viewer_->GetData();
    if (fileDialog != ""){
        ui->name_file->setText(QFileInfo(fileDialog).fileName());
        ui->path_file->setText(QFileInfo(fileDialog).filePath());
    }
    ui->num_of_vertices->setText(QString::number(controller_viewer_->GetData().v_count));
    ui->num_of_facets->setText(QString::number(controller_viewer_->GetData().f_count));
}


void MainWindow::on_parallel_radio_toggled(){
    if(ui->central_radio->isChecked() == true){
        ui->central_radio->setChecked(false);
        ui->openGLWidget->SetObj().parallel = true;
        ui->openGLWidget->SetObj().central = false;
    }else{
        ui->parallel_radio->setChecked(true);
    }
}


void MainWindow::on_central_radio_toggled(){
    if(ui->parallel_radio->isChecked() == true){
        ui->parallel_radio->setChecked(false);
        ui->openGLWidget->SetObj().parallel = false;
        ui->openGLWidget->SetObj().central = true;
    }else{
        ui->central_radio->setChecked(true);
    }
}


void MainWindow::on_line_toggled(){
    if(ui->dash_line->isChecked() == true || ui->disable_line->isChecked() == true){
        ui->dash_line->setChecked(false);
        ui->disable_line->setChecked(false);
        ui->openGLWidget->SetObj().dash = false;
        ui->openGLWidget->SetObj().disable_line = false;
    }else{
        ui->line->setChecked(true);
    }
}

void MainWindow::on_dash_line_toggled(){
    if(ui->line->isChecked() == true || ui->disable_line->isChecked() == true){
        ui->line->setChecked(false);
        ui->disable_line->setChecked(false);
        ui->openGLWidget->SetObj().dash = true;
        ui->openGLWidget->SetObj().disable_line = false;
    }else{
        ui->dash_line->setChecked(true);
    }
}


void MainWindow::on_disable_line_toggled(){
    if(ui->line->isChecked() == true || ui->dash_line->isChecked() == true){
        ui->line->setChecked(false);
        ui->dash_line->setChecked(false);
        ui->openGLWidget->SetObj().dash = false;
        ui->openGLWidget->SetObj().disable_line = true;
    }else{
        ui->disable_line->setChecked(true);
    }
}


void MainWindow::on_square_toggled(){
    if(ui->circle->isChecked() == true || ui->vertex_disable->isChecked() == true){
        ui->circle->setChecked(false);
        ui->vertex_disable->setChecked(false);
        ui->openGLWidget->SetObj().circle = false;
        ui->openGLWidget->SetObj().disable_p = false;
    }else{
        ui->square->setChecked(true);
    }
}


void MainWindow::on_circle_toggled(){
    if(ui->square->isChecked() == true || ui->vertex_disable->isChecked() == true){
        ui->square->setChecked(false);
        ui->vertex_disable->setChecked(false);
        ui->openGLWidget->SetObj().circle = true;
        ui->openGLWidget->SetObj().disable_p = false;
    }else{
        ui->circle->setChecked(true);
    }
}


void MainWindow::on_vertex_disable_toggled(){
    if(ui->square->isChecked() == true || ui->circle->isChecked() == true){
        ui->square->setChecked(false);
        ui->circle->setChecked(false);
        ui->openGLWidget->SetObj().circle = false;
        ui->openGLWidget->SetObj().disable_p = true;
    }else{
        ui->vertex_disable->setChecked(true);
    }
}


void MainWindow::on_size_p_valueChanged(double arg1){
    ui->openGLWidget->SetObj().size_p = arg1;
}


void MainWindow::on_size_l_valueChanged(double arg1){
    ui->openGLWidget->SetObj().size_l = arg1;
}






}

