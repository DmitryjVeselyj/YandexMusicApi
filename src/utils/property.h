#ifndef PROPERTY_H
#define PROPERTY_H

#include "types.h"
#include <boost/type_index.hpp>

enum class simpleType{
    INT, 
    STRING
};


template <typename Class, typename T>
struct Property {
    
    constexpr Property(T Class::*aMember, const char *aName, simpleType stype) : member{aMember}, name{aName}, stype(stype) {}

    T Class::*member;
    const char *name;
    simpleType stype;
};

template <typename... Properties>
constexpr auto makePropertiesTuple(const Properties &&...args) {
    auto properties = std::make_tuple(args...);
    return properties;
}

#endif // PROPERTY_H