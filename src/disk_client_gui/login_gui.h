#ifndef LOGIN_GUI_H
#define LOGIN_GUI_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class LoginGUI;
}

class LoginGUI : public QDialog
{
    Q_OBJECT

public:
    explicit LoginGUI(QDialog*parent = 0);
    ~LoginGUI();

    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
public slots:
    void set_style();

    void Login();

private:
    Ui::LoginGUI*ui;
};

#endif // LOGIN_GUI_H
