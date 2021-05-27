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

    ui->kanjiTable->setColumnCount(2);
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
        QTableWidgetItem *tableItem = new QTableWidgetItem();
        tableItem->setText(charList.at(i).getCharacter());

        ui->kanjiTable->setItem(i, 0, tableItem);
    }
}

void KanjiSelector::on_charsetCombo_currentIndexChanged(int index)
{
    if (index < 0) {
        return;
    }

    int charsetId = ui->charsetCombo->itemData(index).toInt();
    fillCharacterTable(DatabaseManager::getCharset(charsetId));
}

