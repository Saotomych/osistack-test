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
	checkServerConnected = false;
	checkServerErrorConnected = false;
	checkServerErrorTransfer = false;
	checkIllegalArg = false;
	checkIllegalClassMbr = false;

	// Create server and start listening
	qint32 port = 18982;
	pAcseAssociationListener = new CAcseAssociationListener;
	pServerAcse = new CServerAcseSap(port, 0, QHostAddress("127.0.0.1"), pAcseAssociationListener, CSocketFactory::getSocketFactory());
	pServerAcse->setMessageTimeout(500);
	pServerAcse->setMessageFragmentTimeout(500);
	pConnectionListener = pServerAcse->getConnectionListener();

	// server slots
	connect(pConnectionListener, SIGNAL(signalConnected(const CConnection*)), this, SLOT(slotServerClientConnected(const CConnection*)));
	connect(pConnectionListener, SIGNAL(signalDisconnected(const CConnection*)), this, SLOT(slotServerClientDisconnected(const CConnection*)));
	connect(pConnectionListener, SIGNAL(signalTSduReady(const CConnection*)), this, SLOT(slotServerTSduReady(const CConnection*)));
	connect(pConnectionListener, SIGNAL(signalCRReady(const CConnection*)), this, SLOT(slotServerCRReady(const CConnection*)));
	connect(pConnectionListener, SIGNAL(signalIOError(QString)), this, SLOT(slotServerIOError(QString)));

	// acse server slots
	connect(pAcseAssociationListener, SIGNAL(signalAcseConnected(CAcseAssociation*)), this, SLOT(slotAcseServerClientConnected(CAcseAssociation*)));
	connect(pAcseAssociationListener, SIGNAL(signalAcseDisconnected(CAcseAssociation*)), this, SLOT(slotAcseServerAssociationClosed(CAcseAssociation*)));
	connect(pAcseAssociationListener, SIGNAL(signalAcseTSduReady(CAcseAssociation*)), this, SLOT(slotAcseServerTSduReady(CAcseAssociation*)));
	connect(pAcseAssociationListener, SIGNAL(signalAcseCnReady(CAcseAssociation*)), this, SLOT(slotAcseServerCnReady(CAcseAssociation*)));
	connect(pAcseAssociationListener, SIGNAL(signalAcseIOError(QString)), this, SLOT(slotAcseServerIOError(QString)));

	pServerAcse->startListening();

}

void OsiStackTest::startClient()
{
	checkClientConnected = false;
	checkClientErrorConnected = false;
	checkClientErrorTransfer = false;

	// Create client and start connection
	pClientAcse = new CClientAcseSap(CSocketFactory::getSocketFactory());

	// client's error slots
	connect(pClientAcse->m_pClientTSap, SIGNAL(signalIllegalArgument(QString)), this, SLOT(slotIllegalArgument(QString)));
	connect(pClientAcse->m_pClientTSap, SIGNAL(signalConnectError(QString)), this, SLOT(slotConnectError(QString)));
	connect(pClientAcse->m_pClientTSap, SIGNAL(signalIllegalClassMember(QString)), this, SLOT(slotIllegalClassMember(QString)));

	pClientAcse->setMaxTPDUSizeParam(7);
	pClientAcse->setMessageTimeout(5000);
	pClientAcse->setMessageFragmentTimeout(5000);

	QHostAddress address("127.0.0.1");
	qint32 port = 18982;

	pConnection = pClientAcse->m_pClientTSap->createConnection(address, port);

	if (pConnection)
		slotConnectionReady(pConnection);

	pClientAcseAssociation = pClientAcse->createAssociate(pConnection);

	// connection slots
	connect(pConnection, SIGNAL(signalTSduReady(const CConnection*)), this, SLOT(slotClientTSduReady(const CConnection*)));
	connect(pConnection, SIGNAL(signalConnectionReady(const CConnection*)), this, SLOT(slotConnectionReady(const CConnection*)));
	connect(pConnection, SIGNAL(signalConnectionClosed(const CConnection*)), this, SLOT(slotConnectionClosed(const CConnection*)));
	connect(pClientAcseAssociation, SIGNAL(signalAcseAssociationReady(CAcseAssociation*)), this, SLOT(slotAcseClientAssociationReady(CAcseAssociation*)));
	connect(pClientAcseAssociation, SIGNAL(signalAcseTSduReady(CAcseAssociation*)), this, SLOT(slotAcseClientTSduReady(CAcseAssociation*)));
	connect(pClientAcseAssociation, SIGNAL(signalAcseIOError(QString)), this, SLOT(slotAcseClientIOError(QString)));

	QByteArray arrApdu( (char*) s_mmsInitRequestPDU, sizeof(s_mmsInitRequestPDU)/sizeof(s_mmsInitRequestPDU[0]) );
	CBerByteArrayOutputStream apdu(arrApdu, 0);

	pClientAcse->startAssociation(pClientAcseAssociation, QString(""), apdu);

	// TODO Parse data without headers

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

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test2: Server side has error transfer", false, pTest->checkServerErrorTransfer);

	qint32 expectedSize = sizeof(s_testData)/sizeof(s_testData[0]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test2: Check server size of received data wrong", expectedSize, pTest->m_serverRcvData.size());

	QByteArray::Iterator dataIt = pTest->m_serverRcvData.begin();
	for (char c: s_testData)
	{
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Test2: Check server side received data wrong", c, *dataIt);
		dataIt++;
	}

}

void OsiStackTest::Test3::runTest()
{
	qDebug() << "Test3: Check client side received data";

	OsiStackTest* pTest = OsiStackTest::getMainTest();

	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test3: Client side has error transfer", false, pTest->checkClientErrorTransfer);

	qint32 expectedSize = sizeof(s_testData)/sizeof(s_testData[0]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Test3: Check client size of received data wrong", expectedSize, pTest->m_clientRcvData.size());

	QByteArray::Iterator dataIt = pTest->m_clientRcvData.begin();
	for (char c: s_testData)
	{
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Test3: Check client side received data wrong", c, *dataIt);
		dataIt++;
	}

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
	checkServerAcseAssociationReady = false;
}

void OsiStackTest::slotServerTSduReady(const CConnection* pconn)
{
	qDebug() << "OsiStackTest::slotServerTSduReady: checkClientConnected = " << checkClientConnected;

	if (checkServerConnected)
	{
		if ( (const_cast<CConnection*>(pconn))->receive(m_serverRcvData) == true)
		{
			// TSDU Ready
			qDebug() << "Server TSDU ready: " << m_serverRcvData.toHex();

			// ACSE connect procedure
			if (!checkServerAcseAssociationReady)
			{
				checkServerAcseAssociationReady = true;

				pServerAcseAssociation = pServerAcse->createNewAcseAssociation(const_cast<CConnection*>(pconn));

				QDataStream InputStream(&m_serverRcvData, QIODevice::ReadOnly);

				m_serverPayload = pServerAcseAssociation->listenForCn(InputStream);

				qDebug() << "OsiStackTest::slotServerTSduReady: Received Payload" << m_serverPayload.toHex();

				m_serverRcvData.clear();
			}
			else
			{
				pServerAcseAssociation->receive(m_serverRcvData);

				QByteArray arr((char*)s_testData, sizeof(s_testData));
				CBerByteArrayOutputStream oStream(arr, 0);

				pServerAcseAssociation->send(oStream);
			}
 		}
		else
		{
			qDebug() << "Server TSDU not ready yet: " << m_serverRcvData.toHex();
		}
	}

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
	qDebug() << "OsiStackTest::slotAcseServerClientConnected";

}

void OsiStackTest::slotAcseServerAssociationClosed(CAcseAssociation*)
{
	qDebug() << "OsiStackTest::slotAcseServerAssociationClosed";
}

void OsiStackTest::slotAcseServerCnReady(CAcseAssociation* acse)
{
	qDebug() << "OsiStackTest::slotAcseServerCnReady: payload = " << m_serverPayload.toHex();

	checkAcseCnReady = true;

	// Send answer to client
	CBerByteArrayOutputStream payload(m_serverPayload, 0);
	acse->accept(payload);
}

void OsiStackTest::slotAcseServerTSduReady(CAcseAssociation*)
{
}

void OsiStackTest::slotAcseServerIOError(QString strErr)
{
	qDebug() << "OsiStackTest::slotAcseClientIOError: " << strErr;

}

// client slots
void OsiStackTest::slotConnectionReady(const CConnection*)
{
	qDebug() << "OsiStackTest::slotConnectionReady";

	checkClientConnected = true;
}

void OsiStackTest::slotConnectionClosed(const CConnection*)
{
	qDebug() << "OsiStackTest::slotConnectionClosed";

	checkClientConnected = false;
}

void OsiStackTest::slotClientTSduReady(const CConnection* pconn)
{
	qDebug() << "OsiStackTest::slotClientTSduReady: checkServerConnected = " << checkServerConnected
			<< "; checkClientAcseAssociationReady = " << checkClientAcseAssociationReady;

	if (checkClientConnected)
	{
		if ( (const_cast<CConnection*>(pconn))->receive(m_clientRcvData) == true)
		{
			// TSDU Ready
			qDebug() << "Client TSDU ready: " << m_clientRcvData.toHex();

			QDataStream InputStream(&m_clientRcvData, QIODevice::ReadOnly);

			if (!checkClientAcseAssociationReady)
			{
				m_clientRcvData = pClientAcseAssociation->parseClientAnswer(InputStream, m_serverPayload.size());

				qDebug() << "OsiStackTest::slotClientTSduReady: Received Payload" << m_clientRcvData.toHex();

				m_clientRcvData.clear();

				checkClientAcseAssociationReady = true;

				QByteArray arr((char*)s_testData, sizeof(s_testData));
				CBerByteArrayOutputStream oStream(arr, 0);

				pClientAcseAssociation->send(oStream);
			}
			else
			{
				pClientAcseAssociation->receive(m_clientRcvData);
			}
 		}
		else
		{
			qDebug() << "Client TSDU not ready yet: " << m_clientRcvData.toHex();
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
	qDebug() << "OsiStackTest::slotAcseClientAssociationClosed";
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
