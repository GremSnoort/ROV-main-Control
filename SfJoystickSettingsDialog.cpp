#include "SfJoystickSettingsDialog.hpp"
#include <QDebug>
#include <QLabel>
#include <QObject>
#include <QVBoxLayout>

SfJoystickSettingsDialog::SfJoystickSettingsDialog(QWidget* parent)
    : QDialog(parent)
    , m_settings(new QSettings("RovSettings.ini", QSettings::IniFormat))
    , m_wAxisList(new QComboBox(this))
    , m_xAxisList(new QComboBox(this))
    , m_yAxisList(new QComboBox(this))
    , m_zAxisList(new QComboBox(this))
    , m_servoXList(new QComboBox(this))
    , m_servoYList(new QComboBox(this))
    , m_openManipulatorList(new QComboBox(this))
    , m_closeManipulatorList(new QComboBox(this))
    , m_rotateManipulatorList(new QComboBox(this))

    , m_LL_box(new QComboBox(this))
    , m_LR_box(new QComboBox(this))
    , m_RL_box(new QComboBox(this))
    , m_RR_box(new QComboBox(this))

    , m_wAxisInv(new QCheckBox(this))
    , m_xAxisInv(new QCheckBox(this))
    , m_yAxisInv(new QCheckBox(this))
    , m_zAxisInv(new QCheckBox(this))
    , m_servoXInv(new QCheckBox(this))
    , m_servoYInv(new QCheckBox(this))
    , m_manipulatorInv(new QCheckBox(this))

{
    readSettings();
    createLayout();
    createConnections();
}

sf::Joystick::Axis SfJoystickSettingsDialog::wAxis()
{
    return m_wAxis;
}

bool SfJoystickSettingsDialog::isWInvese()
{
    return m_isWInv;
}

void SfJoystickSettingsDialog::setWAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickAxisW", static_cast<int>(axis));
    m_settings->setValue("JoystickAxisWIsInv", inverse);
    m_wAxis = axis;
    m_isWInv = inverse;
    m_settings->endGroup();
}

sf::Joystick::Axis SfJoystickSettingsDialog::xAxis()
{
    return m_xAxis;
}

bool SfJoystickSettingsDialog::isXInvese()
{
    return m_isXInv;
}

void SfJoystickSettingsDialog::setXAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickAxisX", static_cast<int>(axis));
    m_settings->setValue("JoystickAxisXIsInv", inverse);

    m_xAxis = axis;
    m_isXInv = inverse;
    m_settings->endGroup();
}

sf::Joystick::Axis SfJoystickSettingsDialog::yAxis()
{
    return m_yAxis;
}

bool SfJoystickSettingsDialog::isYInvese()
{
    return m_isYInv;
}

void SfJoystickSettingsDialog::setYAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickAxisY", static_cast<int>(axis));
    m_settings->setValue("JoystickAxisYIsInv", inverse);

    m_yAxis = axis;
    m_isYInv = inverse;
    m_settings->endGroup();
}

sf::Joystick::Axis SfJoystickSettingsDialog::zAxis()
{
    return m_zAxis;
}

bool SfJoystickSettingsDialog::isZInvese()
{
    return m_isZInv;
}

void SfJoystickSettingsDialog::setZAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickAxisZ", static_cast<int>(axis));
    m_settings->setValue("JoystickAxisZIsInv", inverse);
    m_zAxis = axis;
    m_isZInv = inverse;
    m_settings->endGroup();
}

sf::Joystick::Axis SfJoystickSettingsDialog::servoXAxis()
{
    return m_servoXAxis;
}

bool SfJoystickSettingsDialog::isServoXInvese()
{
    return m_isServoXInv;
}

void SfJoystickSettingsDialog::setServoXAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickServoXAxis", static_cast<int>(axis));
    m_settings->setValue("JoystickServoXAxisInv", inverse);
    m_servoXAxis = axis;
    m_isServoXInv = inverse;
    m_settings->endGroup();
}

sf::Joystick::Axis SfJoystickSettingsDialog::servoYAxis()
{
    return m_servoYAxis;
}

bool SfJoystickSettingsDialog::isServoYInvese()
{
    return m_isServoYInv;
}

void SfJoystickSettingsDialog::setServoYAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickServoYAxis", static_cast<int>(axis));
    m_settings->setValue("JoystickServoYAxisInv", inverse);
    m_servoYAxis = axis;
    m_isServoYInv = inverse;
    m_settings->endGroup();
}

sf::Joystick::Axis SfJoystickSettingsDialog::manipulatorAxis()
{
    return m_manipulatorAxis;
}

bool SfJoystickSettingsDialog::isManipulatorInvese()
{
    return m_isManipulatorInv;
}

void SfJoystickSettingsDialog::setManipulatorAxis(sf::Joystick::Axis axis, bool inverse)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickManipulatorAxis", static_cast<int>(axis));
    m_settings->setValue("JoystickManipulatorAxisInv", inverse);
    m_manipulatorAxis = axis;
    m_isManipulatorInv = inverse;
    m_settings->endGroup();
}

int SfJoystickSettingsDialog::manipulatorOpenButton()
{
    return m_openButton;
}

void SfJoystickSettingsDialog::setOpenButton(int button)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickOpenButton", button);
    m_openButton = button;
    m_settings->endGroup();
}

int SfJoystickSettingsDialog::manipulatorCloseButton()
{
    return m_closeButton;
}

void SfJoystickSettingsDialog::setCloseButton(int button)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("JoystickCloseButton", button);
    m_closeButton = button;
    m_settings->endGroup();
}
//////////////////////////////////////////////////////////////
int SfJoystickSettingsDialog::seismMotorLeft_leftButton()
{
    return m_leftMotor_left;
}

void SfJoystickSettingsDialog::setLeft_leftButton(int button)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("LeftSeismLeftButton", button);
    m_leftMotor_left = button;
    m_settings->endGroup();
}

int SfJoystickSettingsDialog::seismMotorLeft_rightButton()
{
    return m_leftMotor_right;
}

void SfJoystickSettingsDialog::setLeft_rightButton(int button)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("LeftSeismRightButton", button);
    m_leftMotor_right = button;
    m_settings->endGroup();
}

int SfJoystickSettingsDialog::seismMotorRight_leftButton()
{
    return m_rightMotor_left;
}

void SfJoystickSettingsDialog::setRight_leftButton(int button)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("RightSeismLeftButton", button);
    m_rightMotor_left = button;
    m_settings->endGroup();
}

int SfJoystickSettingsDialog::seismMotorRight_rightButton()
{
    return m_rightMotor_right;
}

void SfJoystickSettingsDialog::setRight_rightButton(int button)
{
    m_settings->beginGroup("Joystick");
    m_settings->setValue("RightSeismRightButton", button);
    m_rightMotor_right = button;
    m_settings->endGroup();
}

/////////////////////////////////////////////////////////////

void SfJoystickSettingsDialog::readSettings()
{
    sf::Joystick::update();
    m_settings->beginGroup("Joystick");

    m_wAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickAxisW", static_cast<int>(sf::Joystick::Axis::R)).toInt());
    m_xAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickAxisX", static_cast<int>(sf::Joystick::Axis::X)).toInt());
    m_yAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickAxisY", static_cast<int>(sf::Joystick::Axis::Y)).toInt());
    m_zAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickAxisZ", static_cast<int>(sf::Joystick::Axis::Z)).toInt());
    m_servoXAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickServoXAxis", static_cast<int>(sf::Joystick::Axis::PovX)).toInt());
    m_servoYAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickServoYAxis", static_cast<int>(sf::Joystick::Axis::PovY)).toInt());
    m_manipulatorAxis = static_cast<sf::Joystick::Axis>(m_settings->value("JoystickManipulatorAxis", static_cast<int>(sf::Joystick::Axis::U)).toInt());

    m_isWInv = m_settings->value("JoystickAxisWIsInv", false).toBool();
    m_wAxisInv.data()->setChecked(m_isWInv);
    m_isXInv = m_settings->value("JoystickAxisXIsInv", false).toBool();
    m_xAxisInv.data()->setChecked(m_isXInv);
    m_isYInv = m_settings->value("JoystickAxisYIsInv", false).toBool();
    m_yAxisInv.data()->setChecked(m_isYInv);
    m_isZInv = m_settings->value("JoystickAxisZIsInv", false).toBool();
    m_zAxisInv.data()->setChecked(m_isZInv);
    m_isServoXInv = m_settings->value("JoystickServoXAxisInv", false).toBool();
    m_servoXInv.data()->setChecked(m_isServoXInv);
    m_isServoYInv = m_settings->value("JoystickServoYAxisInv", false).toBool();
    m_servoYInv.data()->setChecked(m_isServoYInv);
    m_isManipulatorInv = m_settings->value("JoystickManipulatorAxisInv", false).toBool();
    m_manipulatorInv->setChecked(m_isManipulatorInv);

    m_openButton = m_settings->value("JoystickOpenButton", 1).toInt();
    m_closeButton = m_settings->value("JoystickCloseButton", 0).toInt();

    m_leftMotor_left = m_settings->value("LeftSeismLeftButton", 0).toInt();
    m_leftMotor_right = m_settings->value("LeftSeismRightButton", 0).toInt();
    m_rightMotor_left = m_settings->value("RightSeismLeftButton", 0).toInt();
    m_rightMotor_right = m_settings->value("RightSeismRightButton", 0).toInt();

    m_settings->endGroup();
}

void SfJoystickSettingsDialog::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    auto addToLayout = [](QComboBox* box, QString lName, QVBoxLayout* layout, QCheckBox* cbox) {
        QHBoxLayout* hLayout = new QHBoxLayout;
        QLabel* name = new QLabel(lName);
        hLayout->addWidget(name);
        hLayout->addWidget(box);
        hLayout->addWidget(cbox);
        layout->addLayout(hLayout);
    };

    auto addButtonsToLayout = [](QComboBox* box, QString lName, QVBoxLayout* layout) {
        QHBoxLayout* hLayout = new QHBoxLayout;
        QLabel* name = new QLabel(lName);
        hLayout->addWidget(name);
        hLayout->addWidget(box);
        layout->addLayout(hLayout);
    };

    auto createBox = [this](QComboBox* box) {
        for (size_t axis = 0; axis < sf::Joystick::AxisCount; ++axis) {
            box->addItem(QString("Ось #%1").arg(axis));
        }
    };

    auto createButtonBox = [this](QComboBox* box) {
        for (size_t buttons = 0; buttons < sf::Joystick::getButtonCount(0); ++buttons) {
            box->addItem(QString("Копка #%1").arg(buttons));
        }
    };

    createBox(m_wAxisList.data());
    createBox(m_xAxisList.data());
    createBox(m_yAxisList.data());
    createBox(m_zAxisList.data());
    createBox(m_servoXList.data());
    createBox(m_servoYList.data());
    createBox(m_rotateManipulatorList.data());
    createButtonBox(m_openManipulatorList.data());
    createButtonBox(m_closeManipulatorList.data());

    createButtonBox(m_LL_box.data());
    createButtonBox(m_LR_box.data());
    createButtonBox(m_RL_box.data());
    createButtonBox(m_RR_box.data());

    addToLayout(m_wAxisList.data(), QString(tr("Тяга на ось W:")), layout, m_wAxisInv.data());
    addToLayout(m_xAxisList.data(), QString(tr("Тяга на ось X:")), layout, m_xAxisInv.data());
    addToLayout(m_yAxisList.data(), QString(tr("Тяга на ось Y:")), layout, m_yAxisInv.data());
    addToLayout(m_zAxisList.data(), QString(tr("Тяга на ось Z:")), layout, m_zAxisInv.data());
    addToLayout(m_servoXList.data(), QString(tr("Тяга на сервопривод 1:")), layout, m_servoXInv.data());
    addToLayout(m_servoYList.data(), QString(tr("Тяга на сервопривод 2:")), layout, m_servoYInv.data());
    addToLayout(m_rotateManipulatorList.data(), QString(tr("Поворот манипулятора:")), layout, m_manipulatorInv.data());
    addButtonsToLayout(m_openManipulatorList.data(), QString(tr("Открыть манипулятор:")), layout);
    addButtonsToLayout(m_closeManipulatorList.data(), QString(tr("Закрыть манипулятор:")), layout);

    addButtonsToLayout(m_LL_box.data(), QString(tr("Левый SS <-:")), layout);
    addButtonsToLayout(m_LR_box.data(), QString(tr("Левый SS ->:")), layout);
    addButtonsToLayout(m_RL_box.data(), QString(tr("Правый SS <-:")), layout);
    addButtonsToLayout(m_RR_box.data(), QString(tr("Правый SS ->:")), layout);

    m_wAxisList.data()->setCurrentIndex(static_cast<int>(wAxis()));
    m_xAxisList.data()->setCurrentIndex(static_cast<int>(xAxis()));
    m_yAxisList.data()->setCurrentIndex(static_cast<int>(yAxis()));
    m_zAxisList.data()->setCurrentIndex(static_cast<int>(zAxis()));
    m_servoXList.data()->setCurrentIndex(static_cast<int>(servoXAxis()));
    m_servoYList.data()->setCurrentIndex(static_cast<int>(servoYAxis()));
    m_rotateManipulatorList.data()->setCurrentIndex(static_cast<int>(manipulatorAxis()));
    setLayout(layout);
}

void SfJoystickSettingsDialog::createConnections()
{
    QObject::connect(m_wAxisList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setWAxis(static_cast<sf::Joystick::Axis>(index), m_wAxisInv.data()->isChecked());
    });

    QObject::connect(m_xAxisList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setXAxis(static_cast<sf::Joystick::Axis>(index), m_xAxisInv.data()->isChecked());
    });

    QObject::connect(m_yAxisList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setYAxis(static_cast<sf::Joystick::Axis>(index), m_yAxisInv.data()->isChecked());
    });

    QObject::connect(m_zAxisList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setZAxis(static_cast<sf::Joystick::Axis>(index), m_zAxisInv.data()->isChecked());
    });

    QObject::connect(m_servoXList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setServoXAxis(static_cast<sf::Joystick::Axis>(index), m_servoXInv.data()->isChecked());
    });

    QObject::connect(m_servoYList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setServoYAxis(static_cast<sf::Joystick::Axis>(index), m_servoYInv.data()->isChecked());
    });
    //!
    QObject::connect(m_rotateManipulatorList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setManipulatorAxis(static_cast<sf::Joystick::Axis>(index), m_manipulatorInv.data()->isChecked());
    });

    QObject::connect(m_openManipulatorList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setOpenButton(index);
    });

    QObject::connect(m_closeManipulatorList.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setCloseButton(index);
    });

    ///////////////
    QObject::connect(m_LL_box.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setLeft_leftButton(index);
    });
    QObject::connect(m_LR_box.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setLeft_rightButton(index);
    });
    QObject::connect(m_RL_box.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setRight_leftButton(index);
    });
    QObject::connect(m_RR_box.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        this->setRight_rightButton(index);
    });
    ///////////////

    QObject::connect(m_wAxisInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setWAxis(static_cast<sf::Joystick::Axis>(m_wAxisList.data()->currentIndex()), m_wAxisInv.data()->isChecked());
    });

    QObject::connect(m_xAxisInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setXAxis(static_cast<sf::Joystick::Axis>(m_xAxisList.data()->currentIndex()), m_xAxisInv.data()->isChecked());
    });

    QObject::connect(m_yAxisInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setYAxis(static_cast<sf::Joystick::Axis>(m_yAxisList.data()->currentIndex()), m_yAxisInv.data()->isChecked());
    });

    QObject::connect(m_zAxisInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setZAxis(static_cast<sf::Joystick::Axis>(m_zAxisList.data()->currentIndex()), m_zAxisInv.data()->isChecked());
    });

    QObject::connect(m_servoXInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setZAxis(static_cast<sf::Joystick::Axis>(m_servoXList.data()->currentIndex()), m_servoXInv.data()->isChecked());
    });

    QObject::connect(m_servoYInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setZAxis(static_cast<sf::Joystick::Axis>(m_servoYList.data()->currentIndex()), m_servoYInv.data()->isChecked());
    });

    QObject::connect(m_manipulatorInv.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        this->setManipulatorAxis(static_cast<sf::Joystick::Axis>(m_rotateManipulatorList.data()->currentIndex()), m_manipulatorInv.data()->isChecked());
    });
}
