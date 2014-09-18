#include <QtCore/QCoreApplication>
#include "hstcppollcomm.h"
#include "EmoHandler.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv); //QObject::startTimer: Timers can only be used with threads started with QThread

    HsTcpPollComm hsTcpPollComm;
	EmoHandler emoHandler;
	//emoHandler.setHsTcpPollComm(&hsTcpPollComm); //as duas threads Emo e Hs tem o mesmo valor da hsTcpPollComm
	
	hsTcpPollComm.emoHandler = &emoHandler;

	try {
		//Inicia tentativa de conexao com emotiv
		if (emoHandler.emoConnect() != 1){
		throw std::exception("Emotiv Connection failed.");
		}

		// Inicia tentativa de conexao com o systembox   
		hsTcpPollComm.tcpConnect("10.1.7.37");
	}//end try
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "Press any key to exit..." << std::endl;
		if (getchar()){
			exit(0);
		}
	}

	return app.exec();
}
