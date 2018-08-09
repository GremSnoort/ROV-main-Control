#include "RovSingleton.hpp"

#include <QDebug>
#include <QTimer>

RovSingleton::~RovSingleton() {}

RovSingleton* RovSingleton::instance()
{
    return Singleton<RovSingleton>::instance(RovSingleton::createInstance);
}

RovTelimetry& RovSingleton::telimetry() { return m_telimetry; }

RovControl& RovSingleton::control() { return m_controlData; }

void RovSingleton::setTransmit(bool transmit) { m_isTransmit = transmit; }

void RovSingleton::setTransmitTime(int time)
{
    m_transmitTimer->start(time);
}

void RovSingleton::setThrustScaleFactor(float scale)
{
    m_scaleFactor = scale;
}

RovSingleton::RovSingleton(QObject* parent)
    : m_transmitTimer(new QTimer(this))
    , m_udpConnection(new RovUdpConnection(this))

{
    Q_UNUSED(parent)
    m_transmitTimer->start(100);
    createConnections();
}

RovSingleton* RovSingleton::createInstance()
{
    return new RovSingleton();
}

void RovSingleton::createConnections()
{
    QObject::connect(m_udpConnection.data(), &RovUdpConnection::dataReceived,
        [this](QByteArray datagram) {
            RovTelimetry::RovTelimetryErrorCode ec = m_telimetry.fromRangerTelimetryMsg(datagram);
            if (ec != RovTelimetry::RovTelimetryErrorCode::NoError) {
                qInfo() << RovTelimetry::fromErrorToString(ec);
                return;
            }
            emit telimetryUpdated();
        });

    QObject::connect(m_transmitTimer.data(), &QTimer::timeout, [this]() {
        if (m_isTransmit) {
            m_controlData.axisW *= m_scaleFactor;
            m_controlData.axisX *= m_scaleFactor;
            m_controlData.axisZ *= m_scaleFactor;
            m_controlData.axisY *= m_scaleFactor;

            /*qDebug() << "desiredDepth: " << m_controlData.desiredDepth;
            qDebug() << "desiredYaw: " << m_controlData.desiredYaw;
            qDebug() << "debugFlag: " << m_controlData.debugFlag;
            qDebug() << "regulators 0: " << m_controlData.regulators;
            //qDebug() << "regulators 1: " << m_controlData.regulators[1];
            qDebug() << "coefDepth: " << m_controlData.coef_depth;
            qDebug() << "coefYaw: " << m_controlData.coef_yaw;*/

            m_udpConnection->transmitDatagram(m_controlData.toRangerControlMsg());
        }
    });
}
