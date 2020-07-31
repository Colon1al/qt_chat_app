#include <QCoreApplication>
#include "Client.hpp"
#include <QTimer>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QString ipString;
	qDebug() << "Enter server ip address";
	qStdIn() >> ipString;

	qDebug() << "Enter server tcp port address";
	int port;
	qStdIn() >> port;

	qDebug() << "Enter your username";
	QString name;
	qStdIn() >> name;

	Client *client = new Client(QHostAddress(ipString),port);

	client->authorise(name);

	return app.exec();
}
