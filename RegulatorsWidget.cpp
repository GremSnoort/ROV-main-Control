#include "RegulatorsWidget.hpp"
#include "RovSingleton.hpp"

#include <QVBoxLayout>
#include <bitset>

RegulatorsWidget::RegulatorsWidget(QWidget* parent)
    : QWidget(parent)
    , m_depthRegulator(new QCheckBox("Глубина", this))
    , m_yawRegulator(new QCheckBox("Курс", this))

    , m_depth_coef_label(new QLabel("Коэффициент глубины: ", this))
    , m_yaw_coef_label(new QLabel("Коэффициент курса: ", this))

    , m_depth_coef_value(new QLineEdit(this))
    , m_yaw_coef_value(new QLineEdit(this))
{
    createLayout();
    createConnections();
    readCoeffs();
}

void RegulatorsWidget::readCoeffs()
{
    QFile file(QCoreApplication::applicationDirPath()+"/res/coefs.cfg");
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly))
        return;
    data = file.readAll();
    QList<QByteArray> fields = data.split(' ');
    if(fields.size()==2)
    {
        m_depth_coef_value->setText(fields.at(0));
        m_yaw_coef_value->setText(fields.at(1));

        RovSingleton::instance()->control().coef_depth = static_cast<quint32>(m_depth_coef_value->text().toInt());
        RovSingleton::instance()->control().coef_yaw = static_cast<quint32>(m_yaw_coef_value->text().toInt());
    }
}

void RegulatorsWidget::updateCoeffs()
{
    QFile file(QCoreApplication::applicationDirPath()+"/res/coefs.cfg");
    if (!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    out << m_depth_coef_value->text();
    out << " ";
    out << m_yaw_coef_value->text() << endl;
}

void RegulatorsWidget::createConnections()
{
    QObject::connect(m_depthRegulator.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        std::bitset<8> regulator = RovSingleton::instance()->control().regulators;
        regulator[0] = m_depthRegulator.data()->isChecked();
        RovSingleton::instance()->control().regulators = static_cast<quint8>(regulator.to_ulong());
    });

    QObject::connect(m_yawRegulator.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        std::bitset<8> regulator = RovSingleton::instance()->control().regulators;
        regulator[1] = m_yawRegulator.data()->isChecked();
        RovSingleton::instance()->control().regulators = static_cast<quint8>(regulator.to_ulong());
    });

    QObject::connect(m_depth_coef_value.data(), &QLineEdit::textEdited, [this](QString str) {
        int i = str.toUInt();
        RovSingleton::instance()->control().coef_depth = static_cast<quint32>(i);
        updateCoeffs();
    });
    QObject::connect(m_yaw_coef_value.data(), &QLineEdit::textEdited, [this](QString str) {
        int i = str.toUInt();
        RovSingleton::instance()->control().coef_yaw = static_cast<quint32>(i);
        updateCoeffs();
    });
}

void RegulatorsWidget::createLayout()
{
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(m_depthRegulator.data(), 0, 0);
    layout->addWidget(m_depth_coef_label.data(), 1, 0);
    layout->addWidget(m_depth_coef_value.data(), 2, 0);

    layout->addWidget(m_yawRegulator.data(), 0, 1);
    layout->addWidget(m_yaw_coef_label.data(), 1, 1);
    layout->addWidget(m_yaw_coef_value.data(), 2, 1);

    m_depth_coef_value->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));
    m_yaw_coef_value->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));

    setLayout(layout);
}
