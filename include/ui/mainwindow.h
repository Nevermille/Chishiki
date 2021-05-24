#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_actionAbout_Qt_triggered();
        void on_actionAbout_Chishiki_triggered();
        void on_actionBlank_triggered();
        void on_home_kanaTestClicked();
        void on_kanatest_backButtonClicked();

        void on_home_kanjiTestClicked();

        void on_characterchooser_returnToHome();

private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
