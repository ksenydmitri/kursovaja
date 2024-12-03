#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "usermanager.h"

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr, UserManager *manager = nullptr);
    QString getUsername() const;
    QString getPassword() const;

signals:
    void loginSuccess(const User &user);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    UserManager &userManager;
    QString username;
    QString password;
};

#endif // LOGINWINDOW_H
