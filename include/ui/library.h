#ifndef LIBRARY_H
#define LIBRARY_H

#include <QWidget>

namespace Ui {
class Library;
}

class Library : public QWidget
{
    Q_OBJECT

public:
    explicit Library(QWidget *parent = nullptr);
    ~Library();
    void resetUi(void);

private slots:
    void on_selector_characterSelected();

private:
    Ui::Library *ui;
};

#endif // LIBRARY_H
