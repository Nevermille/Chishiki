#include "include/ui/library.h"
#include "include/db/databasemanager.h"
#include "ui_library.h"

Library::Library(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
}

Library::~Library()
{
    delete ui;
}

void Library::resetUi(void)
{
    ui->selector->setCharsetList(DatabaseManager::getCharsetRange(0, 9999));
    ui->selector->allowMultipleSelects(false);
}

void Library::on_selector_characterSelected()
{
    QList<Character> c = ui->selector->getSelectedCharacters();

    if (!c.count())
    {
        qDebug() << "Nothing selected";
        return;
    }

    ui->viewer->printCharacter(c.at(0));
}

