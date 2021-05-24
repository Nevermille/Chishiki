#include "include/ui/mainwindow.h"
#include "include/ui/characterchooser.h"
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

void MainWindow::on_actionBlank_triggered()
{

}

void MainWindow::on_home_kanaTestClicked()
{

}

void MainWindow::on_kanatest_backButtonClicked(void)
{

}

void MainWindow::on_home_kanjiTestClicked()
{
    CharacterChooser* cc = dynamic_cast<CharacterChooser*>(ui->uiStack->widget(1));

    if (cc) {
        cc->setActionMode(CharacterChooser::KanjiTest);
        cc->setListMode(CharacterChooser::KanjiList);
        ui->uiStack->setCurrentIndex(1);
    }
}

void MainWindow::on_characterchooser_returnToHome()
{
    ui->uiStack->setCurrentIndex(0);
}

