#include "include/ui/characterchooser.h"
#include "ui_characterchooser.h"
#include "include/db/databasemanager.h"

CharacterChooser::CharacterChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterChooser)
{
    ui->setupUi(this);

    QStringList header;
    header.append(tr("Character"));
    header.append(tr("Meaning"));
    header.append(tr("Internal Id"));

    ui->selectedList->setColumnCount(3);
    ui->selectedList->setHorizontalHeaderLabels(header);
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

void CharacterChooser::on_addOneCharButton_clicked()
{
    QList<Character> selectedCharacters = ui->kanjiSelector->getSelectedCharacters();
    ui->kanjiSelector->hideSelectedCharacters();
    addToSelectedList(selectedCharacters);
}

void CharacterChooser::addToSelectedList(const QList<Character> &characters)
{
    int total = characters.count();
    int i = 0;

    for (i = 0; (i < total); i++)
    {
        int currentRowId = ui->selectedList->rowCount();
        QTableWidgetItem* characterItem = new QTableWidgetItem();
        characterItem->setText(characters.at(i).getCharacter());

        QTableWidgetItem* idItem = new QTableWidgetItem();
        idItem->setText(QString::number(characters.at(i).getId()));

        ui->selectedList->insertRow(currentRowId);
        ui->selectedList->setItem(currentRowId, CHARACTERCHOOSER_CHARACTER_ROW, characterItem);
        ui->selectedList->setItem(currentRowId, CHARACTERCHOOSER_ID_ROW, idItem);
    }
}
