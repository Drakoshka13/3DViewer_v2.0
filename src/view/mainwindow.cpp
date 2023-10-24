#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21{

MainWindow::MainWindow(ControllerViewer *controller_viewer, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), controller_viewer_(controller_viewer){
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
    QString fileDialog = QFileDialog::getOpenFileName(this,
    QDir::homePath());
    controller_viewer_->Parser(fileDialog.toStdString());
    ui->openGLWidget->DataObj(controller_viewer_->GetData());
}

}

