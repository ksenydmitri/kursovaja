#include "loginwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent, UserManager *manager)
    : QDialog(parent), userManager(*manager) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Имя пользователя");
    layout->addWidget(usernameLineEdit);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Пароль");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLineEdit);

    loginButton = new QPushButton("Войти", this);
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    layout->addWidget(loginButton);

    registerButton = new QPushButton("Зарегистрироваться", this);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterButtonClicked);
    layout->addWidget(registerButton);

    setLayout(layout);
    setWindowTitle("Вход");
}

QString LoginWindow::getUsername() const {
    return username;
}

QString LoginWindow::getPassword() const {
    return password;
}

void LoginWindow::onLoginButtonClicked() {
    username = usernameLineEdit->text();
    password = passwordLineEdit->text();
    if (userManager.authenticate(username, password)) {
        User user = userManager.getUser(username);
        emit loginSuccess(user);
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль");
    }
}

void LoginWindow::onRegisterButtonClicked() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString avatarPath = "default_avatar.jpg";
    QString backgroundPath = "default_background.jpg";
    if (userManager.addUser(username, password, avatarPath, backgroundPath)) {
        QMessageBox::information(this, "Успех", "Пользователь зарегистрирован");
    } else {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким именем уже существует");
    }
}

