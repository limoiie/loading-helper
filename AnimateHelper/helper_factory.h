#ifndef ANIMATEHELPER_HELPER_factory_H
#define ANIMATEHELPER_HELPER_factory_H

#include "helper.h"
#include "helper_kind.h"

#include <QRect>
#include <map>

class HelperFactory {
public:
    static HelperFactory& getInstance();
    void registerHelper(HelperKind i_kind, Helper::Builder *ip_builder);
    Helper* getHelper(HelperKind i_kind) const;

private:
    HelperFactory() {}
    std::map<HelperKind, Helper::Builder *> m_factory;
};

#endif // ANIMATEHELPER_HELPER_H
