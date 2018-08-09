#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QScopedPointer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>

class TimerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimerWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    QTime T;
    int ssT;

    void createConnections();

    void createLayout();

    QScopedPointer<QTimer> timer;
    QScopedPointer<QLabel> label;
    QScopedPointer<QPushButton> button;
};

#endif // TIMERWIDGET_H
