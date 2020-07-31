#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->loginWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}

void MainWindow::on_sendButton_clicked()
{
    if(client->socket->isValid())
    {
        ui->chatWindow->append("Me:" + ui->inputText->text());
        client->writeMessage(ui->inputText->text());
    }
}

void MainWindow::on_loginButton_clicked()
{
    client = new Client(QHostAddress(ui->serverText->text()),ui->portText->text().toInt());
    client->authorise(ui->nameText->text());
    ui->sendButton->setEnabled(true);
	QObject::connect(client,&Client::recieveMessage,this,&MainWindow::addNewLineToChatText);
    QObject::connect(client->socket,&QSslSocket::connected,[=]{
        ui->connectionInfoLabel->setText(
                    "Secured connection to "
                            + client->socket->peerAddress().toString() + ":"
                            + QString::number(client->socket->peerPort())
                            + " Username: " + ui->nameText->text()
                                ); });
    ui->loginWidget->hide();
}

void MainWindow::addNewLineToChatText(QString message)
{
	ui->chatWindow->append(message);
}

void MainWindow::on_actionLogin_triggered()
{
    ui->loginWidget->show();
}

void MainWindow::on_actionDisconnect_triggered()
{
    client->socket->disconnectFromHost();
    ui->sendButton->setEnabled(false);
    delete client;
}
