#include "Server.hpp"


void Server::initServer()
{
	
	if (!listen(m_ip,m_port))
	{
		qInfo() << "Unable to start the server: " << errorString();
		close();
		delete this;
	}
	qDebug() << "Server running on ip:" << serverAddress().toString() <<" port:"<< serverPort();
	connect(this, &QTcpServer::newConnection, this, &Server::handleNewConnection);
}

Server::Server(QHostAddress ip, int port,QString certificateString, QString privateKeyString)
{
	m_ip = ip;
	m_port = port;
	QFile keyFile(privateKeyString);
	keyFile.open(QIODevice::ReadOnly);
	key = QSslKey(keyFile.readAll(), QSsl::Rsa);
	keyFile.close();

	cert = QSslCertificate::fromPath(certificateString)[0];
	
}

void Server::handleNewConnection()
{
	qDebug() << "New connection approved and handled";
	tmpSocket = nextPendingConnection();
	connect(tmpSocket, &QTcpSocket::disconnected, this, [=]{ disconnected(tmpSocket); });
	connect(tmpSocket, &QTcpSocket::readyRead, this, &Server::authClient);	
}

void Server::encrypted()
{
	qDebug() << "Connection has been encrypted";
	
}

void Server::authClient()
{
	QString name = QString::fromStdString(tmpSocket->readAll().toStdString());
	m_users[name] = tmpSocket;
	qDebug() << name << " connected";
	disconnect(tmpSocket, &QTcpSocket::readyRead, this, &Server::authClient);
	connect(tmpSocket, &QTcpSocket::readyRead, this, &Server::checkForMessages);
}

void Server::checkForMessages()
{
	for (auto user = m_users.begin(); user != m_users.end();user++)
	{
		if(user.value()->bytesAvailable())
		{
			m_buffer.append(user.key()+ ": " + QString::fromStdString(user.value()->readAll().toStdString())+'\n');
			qDebug() <<m_buffer.last();
			for (auto u: m_users)
			{
				if(u!=*user)
				{
					sendMessage(u,m_buffer.last());
				}
			}
			
		}
	}

}

void Server::sendMessage(QTcpSocket* user,QString message)
{
	user->write(QByteArray::fromStdString(message.toStdString()));
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	qDebug() << "New unencrypted connection";

    QSslSocket *serverSocket = new QSslSocket;
    if (serverSocket->setSocketDescriptor(socketDescriptor)) 
	{
		serverSocket->setPrivateKey(key);
		serverSocket->setLocalCertificate(cert);
		serverSocket->setPeerVerifyMode(QSslSocket::VerifyNone);

        connect(serverSocket, &QSslSocket::encrypted, this, &Server::encrypted);
		connect(serverSocket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), this, &Server::Errors );
		
        serverSocket->startServerEncryption();
		addPendingConnection(serverSocket);
		
    } else {
		qDebug() << "Socket descriptor could not be set, connection not started";
        delete serverSocket;
    }
}

void Server::Errors(const QList<QSslError> & errors)
{
	for(auto& elem:errors)
	{
		qDebug() << elem;
	}
}

void Server::disconnected(QTcpSocket* socket)
{
	qDebug() <<"**--------**"
			<<"\nUser disconnected."
			<<"\nReason: " << socket->errorString()
			<<"\nAddress: " << socket->peerAddress()
			<<"\nPort: " << socket->peerPort()
			<<"\n**--------**" ;
}

Server::~Server()
{
	qDeleteAll(m_users);
	delete tmpSocket;
}