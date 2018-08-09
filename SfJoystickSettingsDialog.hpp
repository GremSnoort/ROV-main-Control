#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QSettings>
#include <QWidget>
#include <SFML/Window.hpp>

class SfJoystickSettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SfJoystickSettingsDialog(QWidget* parent = nullptr);
    sf::Joystick::Axis wAxis();
    bool isWInvese();
    void setWAxis(sf::Joystick::Axis axis, bool inverse);

    sf::Joystick::Axis xAxis();
    bool isXInvese();
    void setXAxis(sf::Joystick::Axis axis, bool inverse);

    sf::Joystick::Axis yAxis();
    bool isYInvese();
    void setYAxis(sf::Joystick::Axis axis, bool inverse);

    sf::Joystick::Axis zAxis();
    bool isZInvese();
    void setZAxis(sf::Joystick::Axis axis, bool inverse);

    sf::Joystick::Axis servoXAxis();
    bool isServoXInvese();
    void setServoXAxis(sf::Joystick::Axis axis, bool inverse);

    sf::Joystick::Axis servoYAxis();
    bool isServoYInvese();
    void setServoYAxis(sf::Joystick::Axis axis, bool inverse);

    sf::Joystick::Axis manipulatorAxis();
    bool isManipulatorInvese();
    void setManipulatorAxis(sf::Joystick::Axis axis, bool inverse);

    int manipulatorOpenButton();
    void setOpenButton(int button);

    int manipulatorCloseButton();
    void setCloseButton(int button);

    int seismMotorLeft_leftButton();
    void setLeft_leftButton(int button);
    int seismMotorLeft_rightButton();
    void setLeft_rightButton(int button);

    int seismMotorRight_leftButton();
    void setRight_leftButton(int button);
    int seismMotorRight_rightButton();
    void setRight_rightButton(int button);

signals:

private:
    void readSettings();
    void createLayout();
    void createConnections();

    QScopedPointer<QSettings> m_settings;

    QScopedPointer<QComboBox> m_wAxisList;
    QScopedPointer<QComboBox> m_xAxisList;
    QScopedPointer<QComboBox> m_yAxisList;
    QScopedPointer<QComboBox> m_zAxisList;
    QScopedPointer<QComboBox> m_servoXList;
    QScopedPointer<QComboBox> m_servoYList;
    QScopedPointer<QComboBox> m_openManipulatorList;
    QScopedPointer<QComboBox> m_closeManipulatorList;
    QScopedPointer<QComboBox> m_rotateManipulatorList;

    QScopedPointer<QComboBox> m_LL_box;
    QScopedPointer<QComboBox> m_LR_box;
    QScopedPointer<QComboBox> m_RL_box;
    QScopedPointer<QComboBox> m_RR_box;

    QScopedPointer<QCheckBox> m_wAxisInv;
    QScopedPointer<QCheckBox> m_xAxisInv;
    QScopedPointer<QCheckBox> m_yAxisInv;
    QScopedPointer<QCheckBox> m_zAxisInv;
    QScopedPointer<QCheckBox> m_servoXInv;
    QScopedPointer<QCheckBox> m_servoYInv;
    QScopedPointer<QCheckBox> m_manipulatorInv;

    sf::Joystick::Axis m_xAxis;
    sf::Joystick::Axis m_yAxis;
    sf::Joystick::Axis m_zAxis;
    sf::Joystick::Axis m_wAxis;
    sf::Joystick::Axis m_servoXAxis;
    sf::Joystick::Axis m_servoYAxis;
    sf::Joystick::Axis m_manipulatorAxis;

    int m_openButton;
    int m_closeButton;

    int m_leftMotor_left;
    int m_leftMotor_right;
    int m_rightMotor_left;
    int m_rightMotor_right;

    bool m_isXInv = false;
    bool m_isYInv = false;
    bool m_isZInv = false;
    bool m_isWInv = false;
    bool m_isServoXInv = false;
    bool m_isServoYInv = false;
    bool m_isManipulatorInv = false;
};
