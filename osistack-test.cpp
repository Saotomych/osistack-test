/*
 * osistack-test.cpp
 *
 *  Created on: 9 марта 2016 г.
 *      Author: alex
 */


#include "osistack-test.h"

const quint8 OsiStackTest::s_mmsInitRequestPDU[] = {
			0xa8, 0x26,  0x80, 0x03, 0x00,  0xfd,
			0xe8,  0x81, 0x01, 0x06,  0x82, 0x01, 0x06,  0x83, 0x01, 0x06,  0xa4, 0x16,
			0x80, 0x01, 0x01,  0x81, 0x03, 0x05,  0xf1, 0x00,  0x82, 0x0c, 0x03,  0xee,
			0x08, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01,  0xef, 0x18
};

const quint8 OsiStackTest::s_testData[] = {
			0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f,  0x00,  0x01,  0x02,  0x03,  0x04,  0x05,
			0x06,  0x07,  0x08,  0x09,  0x0a,  0x0b,  0x0c,  0x0d,
			0x0e,  0x0f
};

void OsiStackTest::startServer()
{
	OsiStackTest* pTest = OsiStackTest::getMainTest();

	pTest->checkServerConnected = false;
	pTest->checkServerErrorConnected = false;
	pTest->checkServerErrorTransfer = false;
	pTest->checkIllegalArg = false;
	pTest->checkIllegalClassMbr = false;

	// Create server and start listening
	qint32 port = 18982;
	pTest->pAcseAssociationListener = new CAcseAssociationListener;
	pTest->pServerAcse = new CServerAcseSap(port, 0, QHostAddress("127.0.0.1"), pTest->pAcseAssociationListener, CSocketFactory::getSocketFactory());
	pTest->pServerAcse->setMessageTimeout(500);
	pTest->pServerAcse->setMessageFragmentTimeout(500);
	pTest->pConnectionListener = pTest->pServerAcse->getConnectionListener();

	// server slots
	pTest->connect(pTest->pConnectionListener, SIGNAL(signalConnected(const CConnection*)), pTest, SLOT(slotServerClientConnected(const CConnection*)));
	pTest->connect(pTest->pConnectionListener, SIGNAL(signalDisconnected(const CConnection*)), pTest, SLOT(slotServerClientDisconnected(const CConnection*)));
	pTest->connect(pTest->pConnectionListener, SIGNAL(signalTSduReady(const CConnection*)), pTest, SLOT(slotServerTSduReady(const CConnection*)));
	pTest->connect(pTest->pConnectionListener, SIGNAL(signalCRReady(const CConnection*)), pTest, SLOT(slotServerCRReady(const CConnection*)));
	pTest->connect(pTest->pConnectionListener, SIGNAL(signalIOError(QString)), pTest, SLOT(slotServerIOError(QString)));

	// acse server slots
	pTest->connect(pTest->pAcseAssociationListener, SIGNAL(signalAcseConnected(CAcseAssociation*)), pTest, SLOT(slotAcseServerClientConnected(CAcseAssociation*)));
	pTest->connect(pTest->pAcseAssociationListener, SIGNAL(signalAcseDisconnected(CAcseAssociation*)), pTest, SLOT(slotAcseServerAssociationClosed(CAcseAssociation*)));
	pTest->connect(pTest->pAcseAssociationListener, SIGNAL(signalAcseTSduReady(CAcseAssociation*)), pTest, SLOT(slotAcseServerTSduReady(CAcseAssociation*)));
	pTest->connect(pTest->pAcseAssociationListener, SIGNAL(signalAcseCnReady(CAcseAssociation*)), pTest, SLOT(slotAcseServerCnReady(CAcseAssociation*)));
	pTest->connect(pTest->pAcseAssociationListener, SIGNAL(signalAcseIOError(QString)), pTest, SLOT(slotAcseServerIOError(QString)));

	pTest->pServerAcse->startListening();

}

void OsiStackTest::startClient()
{
	OsiStackTest* pTest = OsiStackTest::getMainTest();

	pTest->checkClientConnected = false;
	pTest->checkClientErrorConnected = false;
	pTest->checkClientErrorTransfer = false;

	// Create client and start connection
	pTest->pClientAcse = new CClientAcseSap(CSocketFactory::getSocketFactory());

	// client's error slots
	pTest->connect(pTest->pClientAcse->m_pClientTSap, SIGNAL(signalIllegalArgument(QString)), pTest, SLOT(slotIllegalArgument(QString)));
	pTest->connect(pTest->pClientAcse->m_pClientTSap, SIGNAL(signalConnectError(QString)), pTest, SLOT(slotConnectError(QString)));
	pTest->connect(pTest->pClientAcse->m_pClientTSap, SIGNAL(signalIllegalClassMember(QString)), pTest, SLOT(slotIllegalClassMember(QString)));

	pTest->pClientAcse->setMaxTPDUSizeParam(7);
	pTest->pClientAcse->setMessageTimeout(5000);
	pTest->pClientAcse->setMessageFragmentTimeout(5000);

	QHostAddress address("127.0.0.1");
	qint32 port = 18982;

	pTest->pConnection = pTest->pClientAcse->m_pClientTSap->createConnection(address, port);
	pTest->pAcseAssociation = pTest->pClientAcse->createAssociate(pTest->pConnection);

	// connection slots
	pTest->connect(pTest->pAcseAssociation, SIGNAL(signalAcseAssociationReady(CAcseAssociation*)), pTest, SLOT(slotAcseClientAssociationReady(CAcseAssociation*)));
	pTest->connect(pTest->pAcseAssociation, SIGNAL(signalAcseTSduReady(CAcseAssociation*)), pTest, SLOT(slotAcseClientTSduReady(CAcseAssociation*)));
	pTest->connect(pTest->pAcseAssociation, SIGNAL(signalAcseIOError(QString)), pTest, SLOT(slotAcseClientIOError(QString)));

	QByteArray arrApdu( (char*) s_mmsInitRequestPDU, sizeof(s_mmsInitRequestPDU)/sizeof(s_mmsInitRequestPDU[0]) );
	CBerByteArrayOutputStream apdu(arrApdu, 0);

	pTest->pClientAcse->startAssociation(pTest->pAcseAssociation, QString(""), apdu);

}

void OsiStackTest::sendTestData(CConnection* that)
{
	QByteArray qdata;
	qdata.reserve(sizeof(s_testData)/sizeof(s_testData[0]));
	for (char c: s_testData)
	{
		qdata.push_back(c);
	}

	that->send(qdata, (quint32)0, qdata.size());
}

void OsiStackTest::Test1::runTest()
{
	qDebug() << "Test1: Check connection";

	OsiStackTest* pTest = OsiStackTest::getMainTest();

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test1: checkClientConnected wrong", true, pTest->checkClientConnected);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test1: checkClientErrorConnected wrong", false, pTest->checkClientErrorConnected);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test1: checkServerConnected wrong", true, pTest->checkServerConnected);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test1: checkServerErrorConnected wrong", false, pTest->checkServerErrorConnected);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test1: checkIllegalArg wrong", false, pTest->checkIllegalArg);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test1: checkIllegalClassMbr wrong", false, pTest->checkIllegalClassMbr);
}

void OsiStackTest::Test2::runTest()
{
	qDebug() << "Test2: Check server side received data";

	OsiStackTest* pTest = OsiStackTest::getMainTest();

//	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test2: Server side has error transfer", false, pTest->checkServerErrorTransfer);
//
//	qint32 expectedSize = sizeof(s_testData)/sizeof(s_testData[0]);
//	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test2: Check server size of received data wrong", expectedSize, pTest->m_serverRcvData.size());
//
//	QByteArray::Iterator dataIt = pTest->m_serverRcvData.begin();
//	for (char c: s_testData)
//	{
//		CPPUNIT_ASSERT_EQUAL_MESSAGE("Test2: Check server side received data wrong", c, *dataIt);
//		dataIt++;
//	}

}

void OsiStackTest::Test3::runTest()
{
	qDebug() << "Test3: Check client side received data";

	OsiStackTest* pTest = OsiStackTest::getMainTest();

//	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test3: Client side has error transfer", false, pTest->checkClientErrorTransfer);
//
//	qint32 expectedSize = sizeof(s_testData)/sizeof(s_testData[0]);
//	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test3: Check client size of received data wrong", expectedSize, pTest->m_clientRcvData.size());
//
//	QByteArray::Iterator dataIt = pTest->m_clientRcvData.begin();
//	for (char c: s_testData)
//	{
//		CPPUNIT_ASSERT_EQUAL_MESSAGE("Test3: Check client side received data wrong", c, *dataIt);
//		dataIt++;
//	}

}

// server slots
void OsiStackTest::slotServerClientConnected(const CConnection*)
{
	qDebug() << "OsiStackTest::slotServerClientConnected";

	checkServerConnected = true;
}

void OsiStackTest::slotServerClientDisconnected(const CConnection*)
{
	qDebug() << "OsiStackTest::slotServerClientDisconnected";

	checkServerConnected = false;
}

void OsiStackTest::slotServerTSduReady(const CConnection* that)
{

}

void OsiStackTest::slotServerCRReady(const CConnection*)
{
	qDebug() << "OsiStackTest::slotServerCRReady";

}

void OsiStackTest::slotServerIOError(QString str)
{
	qDebug() << "OsiStackTest::slotServerIOError: " << str;

	checkServerErrorTransfer = true;
}

// server acse level slots
void OsiStackTest::slotAcseServerClientConnected(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseServerAssociationClosed(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseServerCnReady(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseServerTSduReady(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseServerIOError(QString strErr)
{
	qDebug() << "OsiStackTest::slotAcseClientIOError: " << strErr;

}


// client slots
void OsiStackTest::slotConnectionReady(const CConnection* that)
{
	qDebug() << "OsiStackTest::slotConnectionReady";

	checkClientConnected = true;

	CConnection* myconn = const_cast<CConnection*>(that);

	OsiStackTest* pTest = OsiStackTest::getMainTest();

	pTest->sendTestData(myconn);
}

void OsiStackTest::slotConnectionClosed(const CConnection*)
{
	qDebug() << "OsiStackTest::slotConnectionClosed";

	checkClientConnected = false;
}

void OsiStackTest::slotClientTSduReady(const CConnection* that)
{

	if (checkClientConnected)
	{
		qDebug() << "OsiStackTest::slotClientTSduReady";

		QByteArray tempBuffer;
		if ( (const_cast<CConnection*>(that))->receive(tempBuffer) == true)
		{
			m_clientRcvData = tempBuffer;
		}
	}
}

void OsiStackTest::slotClientIOError(QString str)
{
	qDebug() << "OsiStackTest::slotClientIOError: " << str;

	checkClientErrorTransfer = true;
}

// client acse slots
void OsiStackTest::slotAcseClientAssociationReady(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseClientAssociationClosed(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseClientTSduReady(CAcseAssociation*)
{

}

void OsiStackTest::slotAcseClientIOError(QString strErr)
{
	qDebug() << "OsiStackTest::slotAcseClientIOError: " << strErr;

}


// Client Errors
void OsiStackTest::slotIllegalArgument(QString strErr)
{
	qDebug() << "OsiStackTest::slotIllegalArgument: " << strErr;

	checkIllegalArg = true;
}

void OsiStackTest::slotConnectError(QString strErr)
{
	qDebug() << "OsiStackTest::slotConnectError: " << strErr;

	checkClientErrorConnected = true;
}

void OsiStackTest::slotIllegalClassMember(QString strErr)
{
	qDebug() << "OsiStackTest::slotIllegalClassMember: " << strErr;

	checkIllegalClassMbr = true;
}

void OsiStackTest::prepare()
{

	test1 = new OsiStackTest::Test1("ACSE Association test");
	test2 = new OsiStackTest::Test2("ACSE Send test");
	test3 = new OsiStackTest::Test3("ACSE Receive test");

	CServer* srv = new CServer(this);
	CClient* clt = new CClient(this);

	srv->start();
	QThread::usleep(500);
	clt->start();

}

void OsiStackTest::run()
{
    // Do processing here

	CppUnit::TextTestRunner runner;
	runner.addTest(test1);
	runner.addTest(test2);
	runner.addTest(test3);

	runner.run();

	std::ofstream outFile("testResult.xml");
	CppUnit::XmlOutputter outputer(&runner.result(), outFile);
	outputer.write();

	emit finished();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OsiStackTest *test = OsiStackTest::getMainTest(&a);

    QObject::connect(test, SIGNAL(finished()), &a, SLOT(quit()));

    QTimer::singleShot(0, test, SLOT(prepare()));
    QTimer::singleShot(1000, test, SLOT(run()));

    return  a.exec();
}
