 #ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QDebug>
#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include <QVector>
#include <QSslSocket>
#include <QSslKey>
#include <QSslCertificate>
#include <QFile>

class Server  : public QTcpServer
{
public:
	Server(QHostAddress ip, int port,QString certificateString, QString privateKeyString);
	~Server();

	void initServer();
	void checkForMessages();
	void disconnected(QTcpSocket* socket);
public slots:
	void handleNewConnection();
	void readData();
	void authClient();
	void encrypted();
	void Errors(const QList<QSslError> & errors);
private:
	QHostAddress m_ip = QHostAddress::Any;
	int m_port = 33333;
	QMap<QString,QTcpSocket*> m_users;
	QVector<QString> m_buffer;
	QTcpSocket* tmpSocket;
	void sendMessage(QTcpSocket* user,QString message);

	QSslKey key;
	QSslCertificate cert;

protected:
	void incomingConnection(qintptr socketDescriptor) override;
};




#endif //SERVER_HPP