#include "include/widget/kanjiselector.h"
#include "ui_kanjiselector.h"

KanjiSelector::KanjiSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanjiSelector)
{
    ui->setupUi(this);
}

KanjiSelector::~KanjiSelector()
{
    delete ui;
}
