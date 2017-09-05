#include "material_loading_helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QDebug>
#include <cmath>

MaterialLoadingHelper::MaterialLoadingHelper(long min_len,
                                             long max_len,
                                             long shift_period,
                                             long const_period,
                                             long speed,
                                             std::vector<QColor> color_list) :
    m_init_len(min_len),
    m_color_list(color_list)
{
    double const T1 = shift_period;
    double const T2 = const_period;
    double const H = T1 + T2;
    double const T = 2 * H;
    double const K = 2 * pi / T1 ;

    // Integral function of speed increasement
    // SpeedIncreasement(t) = 1 - cos(K * t), where t belongs [0, T1]
    // note: t must belong to [0, T1]
    auto f_integral_speed_incrsmnt = [K](double t, double a)->double {
        return a * t - a * sin(t * K) / K;
    };

    double const L = max_len;
    double const S = speed;
    double const A = L / f_integral_speed_incrsmnt(T1, 1);

    // Integral function of speed in one period.
    // Speed(t) = S + A - cos(t * K), where t belongs [0, T1]
    //          = S                 , where t belongs (T1, T]
    // note: t must belong to [0, T]
    auto f_integral_speed_in_one_period = [=](double t) {
        if (t <= T1)
            return f_integral_speed_incrsmnt(t, A) + t * S;
        return f_integral_speed_incrsmnt(T1, A) + t * S;
    };

    double const D = f_integral_speed_in_one_period(T);

    mf_integral_speed = [=](double t)->double {
        int const N = static_cast<int>(t/T);
        return D * N + f_integral_speed_in_one_period(t - N*T);
    };

    m_period = T;
    m_head_offset = mf_integral_speed(0);
    m_tail_offset = mf_integral_speed(H);
}

long MaterialLoadingHelper::getPeriod() const
{
    // todo
    return 0;
}

void MaterialLoadingHelper::paint(QPainter& painter, QRect const &rect, long const elasped) const
{
    painter.save();

    // todo: use color list
    painter.setBrush(QColor(0xFF1E88E5));
    painter.setPen(QColor(0xFFf44336));

    int tail = mf_integral_speed(elasped + m_period/2) - m_tail_offset;
    int span = mf_integral_speed(elasped) - m_head_offset - tail + m_init_len;

    painter.drawArc(rect, tail, span);

    painter.restore();
}

MaterialLoadingHelper::MaterialLoadingBuilder::MaterialLoadingBuilder() :
    m_clockwise(true),
    m_min_len(0),
    m_max_len(circle_len * 3/4),
    m_shift_period(1000),         // todo
    m_const_period(500),          // todo
    m_speed(2),
    m_color_list()                // todo
{
    // nothing to do
}

Helper *MaterialLoadingHelper::MaterialLoadingBuilder::build() const
{
    // todo: check if there are some field that are missing
    return new MaterialLoadingHelper(m_min_len,
                                     m_max_len,
                                     m_shift_period,
                                     m_const_period,
                                     m_speed,
                                     m_color_list);
}

MaterialLoadingHelper::MaterialLoadingBuilder*
MaterialLoadingHelper::MaterialLoadingBuilder::setClockwise(bool clockwise)
{
    this->m_clockwise = clockwise;
    return this;
}

MaterialLoadingHelper::MaterialLoadingBuilder*
MaterialLoadingHelper::MaterialLoadingBuilder::setMinLen(long val)
{
    // todo
    this->m_min_len = val;
    return this;
}

MaterialLoadingHelper::MaterialLoadingBuilder*
MaterialLoadingHelper::MaterialLoadingBuilder::setMaxLen(long val)
{
    // todo
    this->m_max_len = val;
    return this;
}

MaterialLoadingHelper::MaterialLoadingBuilder*
MaterialLoadingHelper::MaterialLoadingBuilder::setPeriod(long shift_period,
                                                         long const_period = -1)
{
    // todo
    this->m_shift_period = shift_period;
    this->m_const_period = const_period == - 1 ? shift_period : const_period;
    return this;
}

MaterialLoadingHelper::MaterialLoadingBuilder*
MaterialLoadingHelper::MaterialLoadingBuilder::setSpeed(long val)
{
    // todo
    this->m_speed = val;
    return this;
}

MaterialLoadingHelper::MaterialLoadingBuilder*
MaterialLoadingHelper::MaterialLoadingBuilder::setColorList(std::vector<QColor> val)
{
    // todo
    this->m_color_list = std::move(val);
    return this;
}
