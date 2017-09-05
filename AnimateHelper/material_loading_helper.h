#ifndef ANIMATEHELPER_MATERIAL_LOADING_HELPER_H
#define ANIMATEHELPER_MATERIAL_LOADING_HELPER_H

#include "helper.h"

#include <QColor>
#include <vector>
#include <functional>

class MaterialLoadingHelper : public Helper {
public:
    class MaterialLoadingBuilder : public Helper::Builder {
    public:
        MaterialLoadingBuilder();
        Helper *build() const override;

        MaterialLoadingBuilder* setClockwise(bool clockwise);
        MaterialLoadingBuilder* setMinLen(long val);
        MaterialLoadingBuilder* setMaxLen(long val);
        MaterialLoadingBuilder* setPeriod(long shift_period, long const_period);
        MaterialLoadingBuilder* setSpeed(long val);
        MaterialLoadingBuilder* setColorList(std::vector<QColor> val);

    private:
        bool m_clockwise;
        long m_min_len;
        long m_max_len;
        long m_shift_period;
        long m_const_period;
        long m_speed;
        std::vector<QColor> m_color_list;
    };

    long getPeriod() const override;
    void paint(QPainter& painter, QRect const& event, long const elasped) const override;

private:
    long m_period;
    long m_init_len;
    long m_head_offset;
    long m_tail_offset;
    std::vector<QColor> m_color_list;
    std::function<double(double)> mf_integral_speed;

    MaterialLoadingHelper(long min_len,
                          long max_len,
                          long shift_period,
                          long const_period,
                          long speed,
                          std::vector<QColor> m_color_list);
};

// todo: register %MaterialLoadingHelper to %HelperFactory

#endif // ANIMATEHELPER_MATERIAL_LOADING_HELPER_H
