#include "RovCameraWidget.hpp"

#include <QCameraInfo>
#include <QVBoxLayout>

RovCameraWidget::RovCameraWidget(QWidget* parent)
    : QStackedWidget(parent)
    , m_cameraView(new QCameraViewfinder(this))
    , m_cameraList(new QComboBox)
    , m_refreshButton(new QPushButton(tr("Обновить")))
{
    createCameraSelectionWidget();
    createCameraViewWidget();
    createConnections();
    setCurrentIndex(WidgetType::CameraSelectionWidget);
}

void RovCameraWidget::takeScreenshot()
{
    QPixmap pm = m_cameraView->grab(QRect(0, 0, m_cameraView->size().width(), m_cameraView->size().height()));
    pm.save("//DESKTOP-3I4GEIE/Users/Public/Pictures/screen"+QString::number(count)+".jpg", "JPG");
    count+=1;
}

void RovCameraWidget::startCapture()
{
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    if (availableCameras.empty()) {
        qWarning() << "Нет доступных камер!";
        return;
    }
    QCameraInfo cameraInfo = availableCameras.at(m_cameraList->currentIndex());

    m_camera.reset(new QCamera(cameraInfo));
    m_camera->setViewfinder(m_cameraView.data());
    m_camera->start();
    setCurrentIndex(WidgetType::CameraViewWidget);
}

void RovCameraWidget::stopCapture()
{
    if (!m_camera) {
        return;
    }

    m_camera->stop();
    setCurrentIndex(WidgetType::CameraSelectionWidget);
}

QCamera::Status RovCameraWidget::cameraStatus()
{
    if (m_camera) {
        return m_camera->status();
    }
    return QCamera::Status::UnavailableStatus;
}

void RovCameraWidget::createCameraSelectionWidget()
{
    QWidget* cameraWidget = new QWidget;

    QWidget* topSpacer = new QWidget;
    QWidget* bottomSpacer = new QWidget;
    QWidget* leftSpacer = new QWidget;
    QWidget* rightSpacer = new QWidget;

    topSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    leftSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* listLayout = new QHBoxLayout;

    listLayout->addWidget(leftSpacer);
    listLayout->addWidget(m_cameraList.data());
    listLayout->addWidget(m_refreshButton.data());
    listLayout->addWidget(rightSpacer);

    m_refreshButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_cameraList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo& cameraInfo : availableCameras) {
        m_cameraList->addItem(cameraInfo.description());
    }

    QVBoxLayout* cameraListLayout = new QVBoxLayout;
    cameraListLayout->addWidget(topSpacer);
    cameraListLayout->addLayout(listLayout);
    cameraListLayout->addWidget(bottomSpacer);
    cameraWidget->setLayout(cameraListLayout);
    addWidget(cameraWidget);
}

void RovCameraWidget::createCameraViewWidget()
{
    addWidget(m_cameraView.data());
}

void RovCameraWidget::createConnections()
{
    QObject::connect(m_refreshButton.data(), &QPushButton::pressed, [this]() {
        m_cameraList->clear();
        const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
        for (const QCameraInfo& cameraInfo : availableCameras) {
            m_cameraList->addItem(cameraInfo.description());
        }
    });
}
