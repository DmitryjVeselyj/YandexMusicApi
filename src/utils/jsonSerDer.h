#ifndef JSON_SER_DER_H
#define JSON_SER_DER_H

#include "property.h"
#include "types.h"
#include <any>
#include <boost/type_index.hpp>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <type_traits>
#include <variant>
#include <vector>


template <class Cls>
struct AddJsonSerDer {

    template <template <class...> class Pack, class... T>
    void JsonValueToClass(const Pack<T...> &prop, const json &data) {

        if (data.contains(prop.name)) {
            //  static_cast<Cls *>(this)->*prop.member = reinterpret_cast<int>(data.at(prop.name));
            

        }
    }

    template <template <class...> class Pack, class... T>
    void ClassValueToJson(const Pack<T...> &prop, json &jsonClass) {
        jsonClass[prop.name] = static_cast<Cls *>(this)->*prop.member;
    }

    template <typename... Ts>
    json toJson(std::tuple<Ts...> properties) {
        json jsonClass;

        std::apply([&jsonClass, this](auto &&...args) { ((ClassValueToJson(args, jsonClass)), ...); }, properties);
        return jsonClass;
    }

    template <typename... Ts>
    void deJson(const json &data, std::tuple<Ts...> properties) {

        std::apply([&data, this](auto &&...args) { (JsonValueToClass(args, data), ...); }, properties);
    }
};
#endif //  JSON_SER_DER
