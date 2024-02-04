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

    void LoginPage();

    void RegisterPage();

    void Register();

    void GetCode();

    void UpdateButton(); // 新增的用于更新按钮状态的槽
private:
    Ui::LoginGUI*ui;

    QTimer* countdown_timer_; // 新增的计时器
    int remaining_time_;      // 倒计时剩余时间
};

#endif // LOGIN_GUI_H
