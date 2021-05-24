#ifndef CHARACTERCHOOSER_H
#define CHARACTERCHOOSER_H

#include <QWidget>

namespace Ui {
class CharacterChooser;
}

class CharacterChooser : public QWidget
{
    Q_OBJECT

    signals:
        void returnToHome(void);

    public:
        static const int KanjiTest = 1;
        static const int KanaTest = 2;
        static const int KanjiLearn = 3;
        static const int KanaLearn = 4;

        static const int AllCharsList = 0;
        static const int KanjiList = 1;
        static const int KanaList = 2;

        explicit CharacterChooser(QWidget *parent = nullptr);
        ~CharacterChooser();

        void setListMode(int mode);
        void setActionMode(int mode);

private slots:
        void on_pushButton_clicked();

private:
        Ui::CharacterChooser *ui;
        int listMode;
        int actionMode;
};

#endif // CHARACTERCHOOSER_H
