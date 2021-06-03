#include "include/widget/kanjiselector.h"
#include "ui_kanjiselector.h"
#include "include/db/databasemanager.h"

KanjiSelector::KanjiSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanjiSelector)
{
    ui->setupUi(this);
    clear();
}

KanjiSelector::~KanjiSelector()
{
    delete ui;
}

void KanjiSelector::clear(void)
{
    ui->kanjiTable->clear();

    QStringList header;
    header.append(tr("Character"));
    header.append(tr("Meaning"));
    header.append(tr("Internal Id"));

    ui->kanjiTable->setColumnCount(3);
    ui->kanjiTable->setRowCount(0);
    ui->kanjiTable->setHorizontalHeaderLabels(header);
}

void KanjiSelector::setCharsetList(const QList<Charset> &list)
{
    int total = list.count();
    int i = 0;

    qDebug() << "Building charset list";

    ui->charsetCombo->clear();

    for (i = total - 1; (i >= 0); i--)
    {
        ui->charsetCombo->addItem(list.at(i).getName(), list.at(i).getId());
    }
}

void KanjiSelector::fillCharacterTable(const Charset &charset)
{
    QList<Character> charList = DatabaseManager::getAllCharactersForCharset(charset);
    int charCount = charList.count();
    int i = 0;

    qDebug() << "Filling character table";

    clear();
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

    qDebug() << "Getting selected characters";

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

    qDebug() << "Hiding selected characters";

    for (i = 0; (i < total); i++)
    {
        if (items.at(i)->column() == 0)
        {
            ui->kanjiTable->hideRow(items.at(i)->row());
        }
    }
}

void KanjiSelector::hideCharacters(const QList<Character> &characters)
{
    int charactersCount = characters.count();
    int rowCount = ui->kanjiTable->rowCount();
    int i = 0;
    int j = 0;

    for (i = 0; (i < charactersCount); i++)
    {
        const Character characterToHide = characters.at(i);

        qDebug() << "Hiding character" << characters.at(i).getCharacter();

        for (j = 0; (j < rowCount); j++)
        {
            if (ui->kanjiTable->item(j, KANJISELECTOR_ID_ROW)->text().toInt() == characterToHide.getId())
            {
                ui->kanjiTable->hideRow(j);
                break;
            }
        }
    }
}

void KanjiSelector::unhideCharacters(const QList<Character> &list)
{
    int charactersCount = list.count();
    int rowCount = ui->kanjiTable->rowCount();
    int i = 0;
    int j = 0;

    for (i = 0; (i < charactersCount); i++)
    {
        const Character characterToHide = list.at(i);

        qDebug() << "Hiding character" << list.at(i).getCharacter();

        for (j = 0; (j < rowCount); j++)
        {
            if (ui->kanjiTable->item(j, KANJISELECTOR_ID_ROW)->text().toInt() == characterToHide.getId())
            {
                ui->kanjiTable->showRow(j);
                break;
            }
        }
    }
}

void KanjiSelector::on_charsetCombo_currentIndexChanged(int index)
{
    qDebug() << "Selected charset changed";

    if (index < 0)
    {
        return;
    }

    int charsetId = ui->charsetCombo->itemData(index).toInt();
    fillCharacterTable(DatabaseManager::getCharset(charsetId));
    emit charsetChanged();
}

void KanjiSelector::allowMultipleSelects(bool val)
{
    if (val)
    {
        ui->kanjiTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    }
    else
    {
        ui->kanjiTable->setSelectionMode(QAbstractItemView::SingleSelection);
    }
}

void KanjiSelector::selectAllCharacters(void)
{
    ui->kanjiTable->selectAll();
}

void KanjiSelector::unselect(void)
{
    ui->kanjiTable->clearSelection();
}

void KanjiSelector::on_kanjiTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    (void) currentRow;
    (void) currentColumn;
    (void) previousRow;
    (void) previousColumn;

    emit characterSelected();
}


void KanjiSelector::on_kanjiTable_cellClicked(int row, int column)
{
    (void) row;
    (void) column;

    emit
    characterSelected();
}

