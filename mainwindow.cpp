#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_kanatestsection_clicked()
{
    ui->mainwidget->setCurrentWidget(ui->kanatest);
}


void MainWindow::on_kanatestbackbutton_clicked()
{
    ui->mainwidget->setCurrentWidget(ui->mainpage);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(ui->centralwidget);
}
