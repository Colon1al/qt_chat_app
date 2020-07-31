#include <QCoreApplication>
#include "Server.hpp"
#include <QCommandLineParser>
#include <QCommandLineOption>



int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	QCommandLineParser argParser;
    argParser.addHelpOption();
    argParser.setApplicationDescription("\nSimple tcp chat server using TLS 1.3 ");

	QCommandLineOption serverIP("ip", "Server IP address.", "ip",""); 
	QCommandLineOption serverPORT("port", "Server tcp port.", "port",""); 
	QCommandLineOption serverCertificate("cert", "Absolute path to server's certificate for TLC 1.3.", "cert path","");
	QCommandLineOption serverPrivateKey("key", "Absolute path to certificate's private key for TLC 1.3.", "key path","");

	argParser.addOption(serverIP); 
    argParser.addOption(serverPORT);
    argParser.addOption(serverCertificate);  
	argParser.addOption(serverPrivateKey);   
 

	if (argc == 1)
        {
            argParser.showHelp();
            app.quit();
        }

	argParser.process(app);

	QString ipString = argParser.value(serverIP.names()[0]);
	qint16 port = argParser.value(serverPORT.names()[0]).toShort();
	QString certificatePathString =  argParser.value(serverCertificate.names()[0]);
	QString privateKeyPathString =  argParser.value(serverPrivateKey.names()[0]);

	Server *server = new Server(QHostAddress(ipString),port,certificatePathString,privateKeyPathString);

	server->initServer();

	return app.exec();
}