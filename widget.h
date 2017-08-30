#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent = nullptr);
    ~Widget();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *m_helper;
    long m_elapsed;
};

#endif // WIDGET_H
