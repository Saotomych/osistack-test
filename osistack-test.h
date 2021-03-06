/*
 * osistack-test.h
 *
 *  Created on: 9 марта 2016 г.
 *      Author: alex
 */

#ifndef OSISTACK_TEST_H_
#define OSISTACK_TEST_H_

#define UNITTEST

#include <QCoreApplication>
#include <QTimer>
#include <QEventLoop>
#include <QVector>

#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/XmlOutputterHook.h>
#include <cppunit/XmlOutputter.h>

#include "servertsap.h"
#include "clienttsap.h"
#include "connection.h"
#include "connectionlistener.h"
#include "socketfactory.h"

#include "AcseAssociation.h"
#include "ClientAcseSap.h"
#include "ServerAcseSap.h"

class OsiStackTest: public QObject
{

	Q_OBJECT

	OsiStackTest(QObject *parent = 0) :
		QObject(parent),
		pServerAcse(nullptr),
		pClientAcse(nullptr),
		pConnection(nullptr),
		pClientAcseAssociation(nullptr),
		pServerAcseAssociation(nullptr),
		checkClientConnected(false),
		checkClientErrorConnected(false),
		checkClientErrorTransfer(false),
		checkServerErrorTransfer(false),
		checkServerConnected(false),
		checkServerErrorConnected(false),
		checkIllegalArg(false),
		checkIllegalClassMbr(false),
		checkClientAcseAssociationReady(false),
		checkServerAcseAssociationReady(false),
		checkAcseIOError(false),
		test1(nullptr),
		test2(nullptr),
		test3(nullptr)
	{}

public:

	CServerAcseSap* pServerAcse;
	CClientAcseSap* pClientAcse;
	CConnection* pConnection;
	CAcseAssociation* pClientAcseAssociation;
	CAcseAssociation* pServerAcseAssociation;

	CBerOctetString whatIsString;

	// Checks for transport level
	bool checkClientConnected;
	bool checkClientErrorConnected;
	bool checkClientErrorTransfer;
	bool checkServerErrorTransfer;
	bool checkServerConnected;
	bool checkServerErrorConnected;
	bool checkIllegalArg;
	bool checkIllegalClassMbr;

	// Check for presentation level
	bool checkClientAcseAssociationReady;
	bool checkServerAcseAssociationReady;
	bool checkAcseIOError;

	QByteArray m_serverRcvData;
	QByteArray m_serverPayload;
	QByteArray m_clientRcvData;

	static const quint8 s_mmsInitRequestPDU[];
	static const quint8 s_testData[];

	static OsiStackTest* getMainTest(QObject *parent = 0) {
		static OsiStackTest* pthis = nullptr;
		if (pthis == nullptr)
		{
			if (parent)
				pthis = new OsiStackTest(parent);
			else
				throw std::invalid_argument("OsiStackTest* getMainTest: QObject is nullptr when singletone constructed");
		}
		return pthis;
	}

	// Start of server and client in QThreads
	class CServer: public QThread
	{
		OsiStackTest* m_test;

	public:
		CServer(OsiStackTest *test): m_test(test) {}

		void run()
		{
		    QObject::connect(m_test, SIGNAL(finished()), this, SLOT(quit()));

		    m_test->startServer();

			this->exec();
		}
	};

	class CClient: public QThread
	{
		OsiStackTest* m_test;

	public:
		CClient(OsiStackTest *test): m_test(test){}

		void run()
		{
		    QObject::connect(m_test, SIGNAL(finished()), this, SLOT(quit()));

		    m_test->startClient();

			this->exec();
		}
	};

	// Test Classes
	/*
	 *  Class tests creation of connection client-server
	 */
	class Test1:public CppUnit::TestCase
	{
	public:
		Test1(const std::string str): TestCase(str) {}
		void runTest();
	};

	/*
	 *  Class tests data sending from client to server
	 */
	class Test2:public CppUnit::TestCase
	{
	public:
		Test2(const std::string str): TestCase(str) {}
		void runTest();
	};

	/*
	 *  Class tests data receiving from server to client
	 */
	class Test3:public CppUnit::TestCase
	{
	public:
		Test3(const std::string str): TestCase(str) {}
		void runTest();
	};

	Test1*	test1;
	Test2*	test2;
	Test3*	test3;

public slots:

	// server transport level slots
	void slotServerClientConnected(const CConnection* pconn);
	void slotServerClientDisconnected(const CConnection*);
	void slotServerTSduReady(const CConnection*);
	void slotServerCRReady(const CConnection*);
	void slotServerIOError(QString str);

	// client slots
	void slotConnectionReady(const CConnection* that);
	void slotConnectionClosed(const CConnection* that);
	void slotClientTSduReady(const CConnection* that);
	void slotClientIOError(QString str);

	// Client Errors
	void slotIllegalArgument(QString strErr);
	void slotConnectError(QString strErr);
	void slotIllegalClassMember(QString strErr);

    void prepare();
    void run();
	void startServer();
	void startClient();

	void sendTestData(CConnection* that);

signals:
    void finished();
};


#endif /* OSISTACK_TEST_H_ */
