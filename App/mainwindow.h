#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Client/Client.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_sendButton_clicked();

    void on_loginButton_clicked();

	void addNewLineToChatText(QString message);

private slots:
    void on_actionLogin_triggered();

    void on_actionDisconnect_triggered();

private:
    Ui::MainWindow *ui;
	Client *client;
	
};
#endif // MAINWINDOW_H
