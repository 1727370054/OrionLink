#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class LoginUI;
}

class LoginUI : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUI(QDialog* parent = nullptr);
    ~LoginUI();
    
    void InitGUI();

private slots:
    void Login();

private:
    Ui::LoginUI *ui;
};

#endif // LOGINUI_H
