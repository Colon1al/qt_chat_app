#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QDebug>
#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QSslSocket>
#include <QFile>
#include <QSslKey>
#include <QSslCertificate>
#include <QSslConfiguration>


class Client  : public QObject
{
	Q_OBJECT
public:
	QSslSocket *socket;

	Client(QHostAddress ip, int port);
	~Client();
	QSslKey key;
	QSslCertificate cert;
	void authorise(QString name);
	
	void writeMessage(QString message);
public slots:
	void recieveMessageSlot();
	void encrypted();
	void disconnected();
signals:
	void recieveMessage(QString message);
};




#endif //CLIENT_HPP