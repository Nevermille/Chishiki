#include "include/ui/mainwindow.h"
#include "include/ui/characterchooser.h"
#include "include/ui/about.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu* settingsMenu = new QMenu(this);
    settingsMenu->addAction(ui->actionAbout_Chishiki);
    settingsMenu->addAction(ui->actionAbout_Qt);
    settingsMenu->addAction(ui->actionExit);

    ui->settingButton->setMenu(settingsMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkNavbarItem(QWidget *item)
{
    if (item == ui->testButton) {
        ui->testButton->setChecked(true);
    } else {
        ui->testButton->setChecked(false);
    }

    if (item == ui->learnButton) {
        ui->learnButton->setChecked(true);
    } else {
        ui->learnButton->setChecked(false);
    }

    if (item == ui->resultButton) {
        ui->resultButton->setChecked(true);
    } else {
        ui->resultButton->setChecked(false);
    }

    if (item == ui->libraryButton) {
        ui->libraryButton->setChecked(true);
    } else {
        ui->libraryButton->setChecked(false);
    }
}

void MainWindow::on_testButton_clicked()
{
    checkNavbarItem(ui->testButton);
    ui->uiStack->setCurrentIndex(1);
}

void MainWindow::on_homeButton_clicked()
{
    checkNavbarItem(ui->homeButton);
    ui->uiStack->setCurrentIndex(0);
}


void MainWindow::on_learnButton_clicked()
{
    checkNavbarItem(ui->learnButton);
}


void MainWindow::on_libraryButton_clicked()
{
    checkNavbarItem(ui->libraryButton);
}


void MainWindow::on_resultButton_clicked()
{
    checkNavbarItem(ui->resultButton);
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

