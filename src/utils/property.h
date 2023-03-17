#ifndef PROPERTY_H
#define PROPERTY_H

#include "types.h"



template <typename Class, typename T>
struct Property {
    using Type =  T;
    constexpr Property(T Class::*aMember, const char *aName) : member{aMember}, name{aName} {}

    T Class::*member;
    const char *name;
};



template <typename... Properties>
constexpr auto makePropertiesTuple(const Properties &&...args) {
    auto properties = std::make_tuple(args...);
    return properties;
}

#endif // PROPERTY_H