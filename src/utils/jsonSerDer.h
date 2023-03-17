#ifndef JSON_SER_DER_H
#define JSON_SER_DER_H

#include "converter.h"
#include "metaprogrammingStuff.h"
#include "property.h"
#include "types.h"

template <class Cls>
struct AddJsonSerDer {

    template <template <class...> class Pack, typename... T>
    void JsonValueToClass(const Pack<T...> &prop, const json &data) {

        if (data.contains(prop.name)) {
            Cls *cls = static_cast<Cls *>(this);
            // cls->*prop.member = Convert<string,typename getNthFromVariadicType<1, T...>::type> (data[prop.name]);
            cls->*prop.member = Convert<string, typename Pack<T...>::Type>(data[prop.name]);
        }
    }

    template <template <class...> class Pack, class... T>
    void ClassValueToJson(const Pack<T...> &prop, json &jsonClass) const {
        jsonClass[prop.name] = static_cast<const Cls *>(this)->*prop.member;
    }

    template <typename... Ts>
    json toJson(std::tuple<Ts...> properties) const {
        json jsonClass;

        std::apply([&jsonClass, this](auto &&...args) { ((ClassValueToJson(args, jsonClass)), ...); }, properties);
        return jsonClass;
    }

    template <typename... Ts>
    void deJson(const json &data, std::tuple<Ts...> properties) {

        std::apply([&data, this](auto &&...args) { (JsonValueToClass(args, data), ...); }, properties);
    }
};
#endif //  JSON_SER_DER_H
