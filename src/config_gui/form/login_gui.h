#ifndef LOGIN_GUI_H
#define LOGIN_GUI_H

#include <QDialog>

namespace Ui {
class LoginGUI;
}

class LoginGUI : public QDialog
{
    Q_OBJECT

public:
    explicit LoginGUI(QWidget *parent = nullptr);
    ~LoginGUI();

private:
    Ui::LoginGUI *ui;
};

#endif // LOGIN_GUI_H
