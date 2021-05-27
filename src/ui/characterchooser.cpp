#include "include/ui/characterchooser.h"
#include "ui_characterchooser.h"
#include "include/db/databasemanager.h"

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

void CharacterChooser::resetUi(void)
{
    QList<Charset> list;

    switch (listMode)
    {
        case KanaList:
            list = DatabaseManager::getCharsetRange(0, 99);
            ui->kanjiSelector->setCharsetList(list);
            break;

        default:
        case KanjiList:
            list = DatabaseManager::getCharsetRange(100, 299);
            ui->kanjiSelector->setCharsetList(list);
            break;
    }
}
