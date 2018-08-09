#include "timerwidget.h"

TimerWidget::TimerWidget(QWidget *parent)
    : QWidget(parent)
    , timer(new QTimer(this))
    , label(new QLabel(this))
    , button(new QPushButton("Start Timer", this))
{
    createLayout();
    createConnections();
}


void TimerWidget::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    QWidget* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(button.data());
    layout->addWidget(label.data());

    label->setFixedSize(100, 25);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: rgb(255, 0, 0); font: 18pt 'Times';");

    layout->addWidget(spacer);

    setLayout(layout);
}

void TimerWidget::createConnections()
{
    connect(button.data(), &QPushButton::released, [this]()
    {
        timer->start(1000);
        T = QTime::currentTime();
        ssT = T.hour()*60*60 + T.minute()*60 + T.second();
    });

    connect(timer.data(), &QTimer::timeout, [this]()
    {
        QTime div = QTime::currentTime();
        int ssD = div.hour()*60*60 + div.minute()*60 + div.second();
        int res = ssD-ssT;

        res = 15*60 - res;

        int H = res / 3600;

        int M = (res-(H*3600)) / 60;

        int S = res-(H*3600)-(M*60);

        label->setText(QString::number(H)+":"+QString::number(M)+":"+QString::number(S));
    });
}
