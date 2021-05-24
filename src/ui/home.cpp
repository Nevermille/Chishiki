#include "include/ui/home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home)
{
    ui->setupUi(this);
}

void Home::on_kanaTestButton_clicked()
{
    emit kanaTestClicked();
}

void Home::on_kanjiTestButton_clicked()
{
    emit kanjiTestClicked();
}

void Home::on_pushButton_clicked()
{
    QApplication::quit();
}

