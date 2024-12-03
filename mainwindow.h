#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "basewidget.h"
#include "usermanager.h"
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void switchWidget(BaseWidget *currentWidget, BaseWidget *newWidget);
    void setWidgetBackground(BaseWidget *widget, const QString &imagePath);

    QStackedWidget *stackedWidget;
    MenuWidget *menuWidget;
    GameWidget *gameWidget;
    SettingsWidget *settingsWidget;
    GameOverWidget *gameOverWidget;
    UserManager userManager;
    User currentUser;
    QString gameBackgroundPath;
    QTimer *restoreTimer; // Новый таймер для восстановления попыток

private slots:
    void onLoginSuccess(const User &user);
    void showGameOverWidget();
    void logoutUser();

    void onAvatarChanged(const QString &filePath);
    void onBackgroundChanged(const QString &filePath);
    void onMusicChanged(const QString &filePath);
    void onDifficultyChanged(const QString &difficulty);
    void restoreAttempt();
};

#endif // MAINWINDOW_H
