#ifndef ANIMATEHELPER_HELPER_H
#define ANIMATEHELPER_HELPER_H

class QPainter;
class QRect;

/**
 * @brief The Helper class is the interface for animation helper class.
 * Each helper class should provide only two functions: getPeriod() for
 * returning the real period and paint(QPainter&,QRect const&,long const)
 * for painting the loading animation frame at elasped time point to the
 * given painter.
 *
 * You need to implement this interface, register the builder of imple-
 * mented class to HelperFactory, then you can get the helper instance
 * from the factory and use it in function paintEvent(QPaintEvent*) of
 * class QWidget by calling function paint(QPainter&,QRect const&,long const)
 */
class Helper {
public:
    /**
     * @brief circle_len 360" in QT-degree format
     */
    static long const circle_len = 360*16;

    /**
     * @brief pi Constant variable for pi
     */
    static double constexpr pi = 3.1415926535898;

    /**
     * @brief getPeriod Get the real period which is the minest period
     * after which the animation should return to the start status.
     * @return The real period you may need in case variable elasped
     * was overflowed.
     */
    virtual long getPeriod() const = 0;

    /**
     * @brief paint Paint the loading animation frame on the given %rect
     * with the given %painter at the given elasped time point. The helper
     * class will not manage frame frequency, it just paints the frame at
     * the given time point %elasped. So you will need to start a timer
     * in the other thread to notify widget to call paintEvent where this
     * %paint function will be called for paint animation frame.
     * @param painter Painter be used
     * @param rect Area to be paint on
     * @param elasped Time elasped.
     */
    virtual void paint(QPainter& painter, QRect const& rect, long const elasped) const = 0;

    virtual ~Helper() {}

    /**
     * @brief The Builder class takes care of tasks of producing helper. It
     * will check and calculate the arguments and create the instance of the
     * out-class.
     */
    class Builder {
    public:
        /**
         * @brief build Build the out-class -- Helper
         * @return The helper instance
         */
        virtual Helper *build() const = 0;
        virtual ~Builder() {}
    };
};

#endif // ANIMATEHELPER_HELPER_H
