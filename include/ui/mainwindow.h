#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define HOME_PAGE 0
#define CHARACTER_CHOOSER_PAGE 1
#define LIBRARY_PAGE 2

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void checkNavbarItem(QWidget* item);

    private slots:
        void on_testButton_clicked();
        void on_homeButton_clicked();
        void on_learnButton_clicked();
        void on_libraryButton_clicked();
        void on_resultButton_clicked();

        void on_actionAbout_Qt_triggered();

        void on_actionExit_triggered();

private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
