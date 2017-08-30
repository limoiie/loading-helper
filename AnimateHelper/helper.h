#ifndef ANIMATEHELPER_HELPER_H
#define ANIMATEHELPER_HELPER_H

class QPainter;
class QRect;

class Helper {
public:
    static long const circle_len = 360*16;
    static double constexpr pi = 3.1415926535898;

    virtual long getPeriod() = 0;
    virtual void paint(QPainter& painter, QRect const& rect, long const elasped) = 0;

    virtual ~Helper() {}

    class Builder {
    public:
        virtual Helper *build() const = 0;
        virtual ~Builder() {}
    };
};

#endif // ANIMATEHELPER_HELPER_H
