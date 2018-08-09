#pragma once

#include "Crc.hpp"
#include <QDataStream>
#include <QIODevice>
#include <QtCore>
#include <QList>

struct RovControl {
    qint8 axisX = 0; //! -100/100;
    qint8 axisY = 0; //! -100/100;
    qint8 axisZ = 0; //! -100/100;
    qint8 axisW = 0; //! -100/100;
    float desiredDepth = 0.0f;
    float desiredYaw = 0.0f;
    qint8 cameraRotation[2] = { 0, 0 };
    qint8 thrusterPower[6] = { 0, 0, 0, 0, 0, 0 };
    quint8 debugFlag = 0;
    qint8 manipulatorRotation = 0; //! -100/100
    qint8 manipulatorOpenClose = 0; //! -1 close/+1 open;
    quint8 regulators = 0; //! 1st bit - depth;
    quint32 coef_depth = 2;
    quint32 coef_yaw = 3;
    qint8 seism_motor_right = 0; //-1/1
    qint8 seism_motor_left = 0; //-1/1

    QByteArray toRangerControlMsg()
    {
        QByteArray ba;

        QDataStream in(&ba, QIODevice::WriteOnly);
        in.setFloatingPointPrecision(QDataStream::SinglePrecision);

        in << axisX;
        in << axisY;
        in << axisZ;
        in << axisW;
        in << debugFlag;
        for (qint8 t : thrusterPower) {
            in << t;
        }
        in << manipulatorRotation;
        for (qint8 c : cameraRotation) {
            in << c;
        }
        in << manipulatorOpenClose;
        in << regulators;
        in << desiredDepth;
        in << desiredYaw;
        in << coef_depth;
        in << coef_yaw;
        in << seism_motor_left;
        in << seism_motor_right;
        in << calculateCRC(ba.data(), ba.size());

        return ba;
    }
};
Q_DECLARE_METATYPE(RovControl)

struct RovTelimetry {
    enum class RovTelimetryErrorCode : int {
        NoError = 0,
        WrongCrc = 1,
        WrongDataSize = 2,
    };

    float depth = 0.0f;

    float pitch = 0.0f; //! -180/180;
    float yaw = 0.0f; //! 0 - 360;
    float roll = 0.0f; //! -180/180;
    float ammeter = 0.0f;
    float voltmeter = 0.0f;
    quint8 regulatorsFeedback = 0;
    qint8 manipulatorAngle = 0; //! ???
    qint8 manipulatorState = 0; //! -1 close/+1 open;

    qint8 size = 0;
    QList<qint8> WiFi_array;

    RovTelimetryErrorCode fromRangerTelimetryMsg(QByteArray& ba)
    {
        QDataStream out(&ba, QIODevice::ReadOnly);
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);

        out >> depth;
        out >> pitch;
        out >> roll;
        out >> yaw;
        out >> ammeter;
        out >> voltmeter;
        out >> regulatorsFeedback;
        out >> manipulatorAngle;
        out >> manipulatorState;

        out >> size;
        //out >> WiFi_array;
        for(int s = 0; s<size; s++)
        {
            qint8 tmp;
            out >> tmp;
            WiFi_array.append(tmp);
        }

        qint16 crc = 0;
        out >> crc;

        qint16 currentCrc = calculateCRC(ba.data(), ba.size() - 2);

        if (currentCrc != crc) {
            depth = 0.0f;
            pitch = 0.0f;
            yaw = 0.0f;
            roll = 0.0f;
            voltmeter = 0.0f;
            ammeter = 0.0f;
            regulatorsFeedback = 0;
            manipulatorAngle = 0;
            manipulatorState = 0;
            size = 0;
            WiFi_array.clear();
            return RovTelimetryErrorCode::WrongCrc;
        }

        return RovTelimetryErrorCode::NoError;
    }

    static QString fromErrorToString(RovTelimetryErrorCode ec)
    {
        QMap<RovTelimetryErrorCode, QString> ec2str;
        ec2str[RovTelimetryErrorCode::NoError] = "No error";
        ec2str[RovTelimetryErrorCode::WrongCrc] = "CRC missmatch";
        ec2str[RovTelimetryErrorCode::WrongDataSize] = "Wrong data size";

        return ec2str[ec];
    }
};
Q_DECLARE_METATYPE(RovTelimetry)
