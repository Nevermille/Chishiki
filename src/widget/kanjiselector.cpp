#include "include/widget/kanjiselector.h"
#include "ui_kanjiselector.h"
#include "include/db/databasemanager.h"

KanjiSelector::KanjiSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanjiSelector)
{
    ui->setupUi(this);

    QStringList header;
    header.append(tr("Character"));
    header.append(tr("Meaning"));
    header.append(tr("Internal Id"));

    ui->kanjiTable->setColumnCount(3);
    ui->kanjiTable->setHorizontalHeaderLabels(header);
}

KanjiSelector::~KanjiSelector()
{
    delete ui;
}

void KanjiSelector::setCharsetList(QList<Charset> &list)
{
    int total = list.count();
    int i = 0;

    ui->charsetCombo->clear();

    for (i = 0; (i < total); i++)
    {
        ui->charsetCombo->addItem(list.at(i).getName(), list.at(i).getId());
    }
}

void KanjiSelector::fillCharacterTable(const Charset &charset)
{
    QList<Character> charList = DatabaseManager::getAllCharactersForCharset(charset);
    int charCount = charList.count();
    int i = 0;

    ui->kanjiTable->setRowCount(charCount);

    for (i = 0; (i < charCount); i++)
    {
        QTableWidgetItem *tableCharacterItem = new QTableWidgetItem();
        tableCharacterItem->setText(charList.at(i).getCharacter());

        QTableWidgetItem *tableIdItem = new QTableWidgetItem();
        tableIdItem->setText(QString::number(charList.at(i).getId()));

        ui->kanjiTable->setItem(i, KANJISELECTOR_CHARACTER_ROW, tableCharacterItem);
        ui->kanjiTable->setItem(i, KANJISELECTOR_ID_ROW, tableIdItem);
    }
}

QList<Character> KanjiSelector::getSelectedCharacters(void)
{
    QList<QTableWidgetItem*> items = ui->kanjiTable->selectedItems();
    QList<Character> result;

    int total = items.count();
    int i = 0;

    for (i = 0; (i < total); i++)
    {
        if (items.at(i)->column() == KANJISELECTOR_ID_ROW)
        {
            result.append(DatabaseManager::getCharacter(items.at(i)->text().toInt()));
        }
    }

    return result;
}

void KanjiSelector::hideSelectedCharacters(void)
{
    QList<QTableWidgetItem*> items = ui->kanjiTable->selectedItems();

    int total = items.count();
    int i = 0;

    for (i = 0; (i < total); i++)
    {
        if (items.at(i)->column() == 0)
        {
            ui->kanjiTable->hideRow(items.at(i)->row());
        }
    }
}

void KanjiSelector::on_charsetCombo_currentIndexChanged(int index)
{
    if (index < 0)
    {
        return;
    }

    int charsetId = ui->charsetCombo->itemData(index).toInt();
    fillCharacterTable(DatabaseManager::getCharset(charsetId));
}
