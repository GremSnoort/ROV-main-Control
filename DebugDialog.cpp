#include "DebugDialog.hpp"
#include "RovSingleton.hpp"
#include <QVBoxLayout>

DebugDialog::DebugDialog(QWidget* parent)
    : QDialog(parent)
    , m_isDebug(new QCheckBox("Отладка", this))
    , m_thrusterOneSlider(new QSlider(Qt::Horizontal, this))
    , m_thrusterTwoSlider(new QSlider(Qt::Horizontal, this))
    , m_thrusterThreeSlider(new QSlider(Qt::Horizontal, this))
    , m_thrusterFourSlider(new QSlider(Qt::Horizontal, this))
    , m_thrusterFiveSlider(new QSlider(Qt::Horizontal, this))
    , m_thrusterSixSlider(new QSlider(Qt::Horizontal, this))
    , m_thrusterOneLabel(new QLabel(tr("Движитель 1: 0"), this))
    , m_thrusterTwoLabel(new QLabel(tr("Движитель 2: 0"), this))
    , m_thrusterThreeLabel(new QLabel(tr("Движитель 3: 0"), this))
    , m_thrusterFourLabel(new QLabel(tr("Движитель 4: 0"), this))
    , m_thrusterFiveLabel(new QLabel(tr("Движитель 5: 0"), this))
    , m_thrusterSixLabel(new QLabel(tr("Движитель 6: 0"), this))

{
    setMinimumSize(240, 240);

    m_thrusterOneSlider.data()->setRange(-100, 100);
    m_thrusterOneSlider.data()->setValue(0);
    m_thrusterTwoSlider.data()->setRange(-100, 100);
    m_thrusterTwoSlider.data()->setValue(0);
    m_thrusterThreeSlider.data()->setRange(-100, 100);
    m_thrusterThreeSlider.data()->setValue(0);
    m_thrusterFourSlider.data()->setRange(-100, 100);
    m_thrusterFourSlider.data()->setValue(0);
    m_thrusterFiveSlider.data()->setRange(-100, 100);
    m_thrusterFiveSlider.data()->setValue(0);
    m_thrusterSixSlider.data()->setRange(-100, 100);
    m_thrusterSixSlider.data()->setValue(0);

    m_thrusterOneSlider.data()->setEnabled(false);
    m_thrusterTwoSlider.data()->setEnabled(false);
    m_thrusterThreeSlider.data()->setEnabled(false);
    m_thrusterFourSlider.data()->setEnabled(false);
    m_thrusterFiveSlider.data()->setEnabled(false);
    m_thrusterSixSlider.data()->setEnabled(false);

    startTimer(90);

    createLayout();
    createConnections();
}

void DebugDialog::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    if (!m_isDebug.data()->isChecked()) {
        return;
    }
    RovControl& rc = RovSingleton::instance()->control();

    rc.thrusterPower[0] = m_thrusterOneSlider.data()->value();
    m_thrusterOneLabel.data()->setText(QString(tr("Движитель 1: %1")).arg(rc.thrusterPower[0]));

    rc.thrusterPower[1] = m_thrusterTwoSlider.data()->value();
    m_thrusterTwoLabel.data()->setText(QString(tr("Движитель 2: %1")).arg(rc.thrusterPower[1]));

    rc.thrusterPower[2] = m_thrusterThreeSlider.data()->value();
    m_thrusterThreeLabel.data()->setText(QString(tr("Движитель 3: %1")).arg(rc.thrusterPower[2]));

    rc.thrusterPower[3] = m_thrusterFourSlider.data()->value();
    m_thrusterFourLabel.data()->setText(QString(tr("Движитель 4: %1")).arg(rc.thrusterPower[3]));

    rc.thrusterPower[4] = m_thrusterFiveSlider.data()->value();
    m_thrusterFiveLabel.data()->setText(QString(tr("Движитель 5: %1")).arg(rc.thrusterPower[4]));

    rc.thrusterPower[5] = m_thrusterSixSlider.data()->value();
    m_thrusterSixLabel.data()->setText(QString(tr("Движитель 6: %1")).arg(rc.thrusterPower[5]));
}

void DebugDialog::createConnections()
{
    QObject::connect(m_isDebug.data(), &QCheckBox::stateChanged, [this](int index) {
        Q_UNUSED(index)
        if (m_isDebug.data()->isChecked()) {
            RovSingleton::instance()->control().debugFlag = true;
            m_thrusterOneSlider.data()->setEnabled(true);
            m_thrusterTwoSlider.data()->setEnabled(true);
            m_thrusterThreeSlider.data()->setEnabled(true);
            m_thrusterFourSlider.data()->setEnabled(true);
            m_thrusterFiveSlider.data()->setEnabled(true);
            m_thrusterSixSlider.data()->setEnabled(true);

        } else {
            RovSingleton::instance()->control().debugFlag = false;
            m_thrusterOneSlider.data()->setEnabled(false);
            m_thrusterTwoSlider.data()->setEnabled(false);
            m_thrusterThreeSlider.data()->setEnabled(false);
            m_thrusterFourSlider.data()->setEnabled(false);
            m_thrusterFiveSlider.data()->setEnabled(false);
            m_thrusterSixSlider.data()->setEnabled(false);
        }
    });
}

void DebugDialog::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;

    auto addToLayout = [](QSlider* slider, QLabel* label, QVBoxLayout* layout) {
        QVBoxLayout* hLayout = new QVBoxLayout;
        hLayout->addWidget(label);
        hLayout->addWidget(slider);
        layout->addLayout(hLayout);
    };

    addToLayout(m_thrusterOneSlider.data(), m_thrusterOneLabel.data(), layout);
    addToLayout(m_thrusterTwoSlider.data(), m_thrusterTwoLabel.data(), layout);
    addToLayout(m_thrusterThreeSlider.data(), m_thrusterThreeLabel.data(), layout);
    addToLayout(m_thrusterFourSlider.data(), m_thrusterFourLabel.data(), layout);
    addToLayout(m_thrusterFiveSlider.data(), m_thrusterFiveLabel.data(), layout);
    addToLayout(m_thrusterSixSlider.data(), m_thrusterSixLabel.data(), layout);
    layout->addWidget(m_isDebug.data());

    setLayout(layout);
}
