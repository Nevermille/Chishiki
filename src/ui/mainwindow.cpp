#include "include/ui/mainwindow.h"
#include "include/ui/about.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Qt_triggered(void)
{
    QMessageBox::aboutQt(ui->centralwidget);
}

void MainWindow::on_actionAbout_Chishiki_triggered(void)
{
    About().exec();
}

void MainWindow::on_actionBlank_triggered(void)
{

}

void MainWindow::on_home_kanaTestClicked()
{
    ui->mainwidget->setCurrentWidget(ui->kanatest);
}

void MainWindow::on_kanatest_backButtonClicked()
{
    ui->mainwidget->setCurrentWidget(ui->home);
}
