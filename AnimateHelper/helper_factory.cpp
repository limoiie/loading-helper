#include "helper_factory.h"
#include "helper_kind.h"

#include <thread>
#include <exception>
#include <string>

HelperFactory& HelperFactory::getInstance() {
    // note: this statement is thread-safe only under c++11
    static HelperFactory instance;
    return instance;
}

Helper* HelperFactory::getHelper(HelperKind i_kind) const {
    auto builder = m_factory.find(i_kind);
    if (m_factory.end() == builder) {
        std::string msg = "There is no builder for this kind \\ in helper factory.";
        throw std::runtime_error(msg);
    }

    return builder->second->build();
}

void HelperFactory::registerHelper(HelperKind i_kind, Helper::Builder *ip_builder) {
    if (m_factory.end() != m_factory.find(i_kind)) {
        std::string msg = "A helper builder for this kind \\ already exists in helper factory.";
        throw std::runtime_error(msg);
    }
    m_factory[i_kind] = ip_builder;
}
