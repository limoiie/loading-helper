#include "widget.h"
#include "AnimateHelper/helper.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

Widget::Widget(Helper *helper, QWidget *parent) :
    QWidget(parent),
    m_helper(helper),
    m_elapsed(0)
{
    QTimer *p_timer = new QTimer(nullptr);
    connect(p_timer, &QTimer::timeout, this, &Widget::animate);
    p_timer->start(50);

    setFixedSize(200, 200);
}

Widget::~Widget()
{
    delete m_helper;
}

void Widget::animate() {
    m_elapsed += qobject_cast<QTimer*>(sender())->interval();
    update();
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = QRect(event->rect().x() + 30,
                       event->rect().y() + 30,
                       event->rect().width() - 60,
                       event->rect().height() - 60);

    m_helper->paint(painter, rect, m_elapsed);
    painter.end();
}
