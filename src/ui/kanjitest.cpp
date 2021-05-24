#include "include/ui/kanjitest.h"
#include "ui_kanjitest.h"

KanjiTest::KanjiTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanjiTest)
{
    ui->setupUi(this);
}

KanjiTest::~KanjiTest()
{
    delete ui;
}
