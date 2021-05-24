#include "include/widget/kanjiviewer.h"
#include "ui_kanjiviewer.h"

KanjiViewer::KanjiViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KanjiViewer)
{
    ui->setupUi(this);
}

KanjiViewer::~KanjiViewer()
{
    delete ui;
}
