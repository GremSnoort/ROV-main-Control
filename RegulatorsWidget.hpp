#ifndef REGULATORSWIDGET_HPP
#define REGULATORSWIDGET_HPP

#include <QCheckBox>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QRegExpValidator>

class RegulatorsWidget : public QWidget {
    Q_OBJECT
public:
    explicit RegulatorsWidget(QWidget* parent = nullptr);

signals:

public slots:
private:
    void createConnections();
    void createLayout();
    void readCoeffs();
    void updateCoeffs();

    QScopedPointer<QCheckBox> m_depthRegulator;
    QScopedPointer<QCheckBox> m_yawRegulator;

    QScopedPointer<QLabel> m_depth_coef_label;
    QScopedPointer<QLabel> m_yaw_coef_label;

    QScopedPointer<QLineEdit> m_depth_coef_value;
    QScopedPointer<QLineEdit> m_yaw_coef_value;

};

#endif // REGULATORSWIDGET_HPP
