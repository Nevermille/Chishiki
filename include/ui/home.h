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

    private:
        Ui::Home *ui;
};

#endif // HOME_H
