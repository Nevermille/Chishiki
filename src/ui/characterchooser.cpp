#include "include/ui/characterchooser.h"
#include "ui_characterchooser.h"

CharacterChooser::CharacterChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterChooser)
{
    ui->setupUi(this);
}

CharacterChooser::~CharacterChooser()
{
    delete ui;
}

void CharacterChooser::setListMode(int mode)
{
    listMode = mode;
}

void CharacterChooser::setActionMode(int mode)
{
    actionMode = mode;
}

void CharacterChooser::on_pushButton_clicked()
{
    emit returnToHome();
}

