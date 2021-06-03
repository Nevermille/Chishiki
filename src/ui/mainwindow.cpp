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
    CharacterChooser* cc = dynamic_cast<CharacterChooser*>(ui->uiStack->widget(CHARACTER_CHOOSER_PAGE));

    checkNavbarItem(ui->testButton);

    cc->setActionMode(CharacterChooser::KanjiTest);
    cc->setListMode(CharacterChooser::KanjiList);
    cc->resetUi();

    ui->uiStack->setCurrentIndex(CHARACTER_CHOOSER_PAGE);
}

void MainWindow::on_homeButton_clicked()
{
    checkNavbarItem(ui->homeButton);
    ui->uiStack->setCurrentIndex(HOME_PAGE);
}


void MainWindow::on_learnButton_clicked()
{
    checkNavbarItem(ui->learnButton);
}


void MainWindow::on_libraryButton_clicked()
{
    Library* l = dynamic_cast<Library*>(ui->uiStack->widget(LIBRARY_PAGE));

    checkNavbarItem(ui->libraryButton);

    l->resetUi();

    ui->uiStack->setCurrentIndex(LIBRARY_PAGE);
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

