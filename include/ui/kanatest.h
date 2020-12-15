#ifndef KANATEST_H
#define KANATEST_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class KanaTest; }
QT_END_NAMESPACE

class KanaTest : public QWidget
{
    Q_OBJECT
    public:
        explicit KanaTest(QWidget *parent = nullptr);

    signals:
        void backButtonClicked(void);

private slots:
        void on_kanatestbackbutton_clicked();

private:
        Ui::KanaTest *ui;
};

#endif // KANATEST_H
