/*----------------------------------------------------------------------
-- SOURCE FILE:	TcpServer.cpp	- Listens for incoming tcp connections
--								
-- PROGRAM:		ComAudio
--
-- FUNCTIONS:
--					TcpServer(QObject* parent)
--					~TcpServer()
--					void startListening(short port)
--
-- DATE:		April 16, 2018
--
-- DESIGNER:	Delan Elliot
--
-- PROGRAMMER:	Delan Elliot
--
-- NOTES:
-- Tcp Server that listens for incoming connections on a user specified port
--
----------------------------------------------------------------------*/

#include "TcpServer.h"

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	TcpServer
--
--	DATE:		Apr. 14, 2018
--
--	DESIGNER:	D. Elliot
--
--	PROGRAMMER:	D. Elliot
--
--	INTERFACE:	TcpServer(QObject *parent)
--					QObject *parent: Pointer to the QT parent object
--	RETURNS:
--
--	NOTES:
--	Class constructor
--
--	Initializes QTcpServer parent object
-----------------------------------------------------------------------------------------*/
TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent)
{
}

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	~TcpServer
--
--	DATE:		Apr. 14, 2018
--
--	DESIGNER:	D. Elliot
--
--	PROGRAMMER:	D. Elliot
--
--	INTERFACE:	TcpServer::~TcpServer()
--	RETURNS:
--
--	NOTES:
--	Class destructor
-----------------------------------------------------------------------------------------*/
TcpServer::~TcpServer()
{
}

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	startListening
--
--	DATE:		Apr. 14, 2018
--
--	DESIGNER:	D. Elliot
--
--	PROGRAMMER:	D. Elliot
--
--	INTERFACE:	void TcpServer::startListening(short port)
--					short port: port number to listen on
--	RETURNS: void
--
--	NOTES:
--	Starts listening on the specified port number
-----------------------------------------------------------------------------------------*/
void TcpServer::startListening(short port)
{
	listen(QHostAddress::AnyIPv4, port);
}




