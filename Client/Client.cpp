#include "Client.hpp"



Client::Client(QHostAddress ip, int port)
{
	QFile keyFile("client.key");
	keyFile.open(QIODevice::ReadOnly);
	key = QSslKey(keyFile.readAll(), QSsl::Rsa);
	keyFile.close();

	QFile certFile("client.pem");
	certFile.open(QIODevice::ReadOnly);
	cert = QSslCertificate(certFile.readAll());
	certFile.close();
	
	
	socket = new QSslSocket(this);
	//socket->addCaCertificates(QSslCertificate::fromPath("domain.pem"));
	//socket->setLocalCertificate(cert);
	//socket->setPrivateKey(key);
	socket->setPeerVerifyMode(QSslSocket::VerifyPeer);
	
	connect(socket, &QSslSocket::encrypted, this, &Client::encrypted);
	connect(socket,QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),[=]{ qDebug() <<"SSL errors: "<< socket->sslHandshakeErrors(); socket->ignoreSslErrors();});
	connect(socket, &QSslSocket::readyRead, this, &Client::recieveMessageSlot);
	connect(socket, &QAbstractSocket::errorOccurred,[=]{qDebug() << socket->errorString();});
	connect(socket, &QSslSocket::disconnected, this, &Client::disconnected );

	socket->connectToHostEncrypted(ip.toString(),port);
}

void Client::authorise(QString name)
{
	socket->write(QByteArray::fromStdString(name.toStdString()));
}

void Client::recieveMessageSlot()
{
	QString message = QString::fromStdString(socket->readAll().toStdString());
	qDebug() << message;
	emit recieveMessage(message);
}

void Client::writeMessage(QString message)
{
	socket->write(QByteArray::fromStdString(message.toStdString()));
	qDebug() << socket->state();
}
void Client::encrypted()
{
	qDebug() << "Connection encrypted";
}

void Client::disconnected()
{
	qDebug() <<"**--------**"
			<< "\nServer disconnected"
			<<"\nReason: " << socket->errorString()
			<<"\nServer address: " << socket->peerAddress()
			<<"\nPort: " << socket->peerPort()
			<<"\n**--------**";
}


Client::~Client()
{
	delete socket;
}