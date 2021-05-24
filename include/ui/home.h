#ifndef HOME_H
#define HOME_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QWidget
{
    Q_OBJECT

    public:
        explicit Home(QWidget *parent = nullptr);

    signals:
        void kanaTestClicked(void);
        void kanjiTestClicked(void);

    private slots:
        void on_kanaTestButton_clicked();

        void on_kanjiTestButton_clicked();

        void on_pushButton_clicked();

    private:
        Ui::Home *ui;
};

#endif // HOME_H
