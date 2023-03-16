#include "client.h"
#include "track.h"
#include "types.h"
#include <iostream>
#include <stdlib.h>

#include "property.h"
#include <iostream>
#include <stdarg.h>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>

struct AddJsonSerDer {

    template <template <class...> class Pack, class... T, class U>
    void JsonValueToClass(const Pack<T...> &prop, const json &data, U classThis) {
        
        if (data.contains(prop.name)) {
            classThis->*prop.member = data[prop.name];
        }
    }

    template <template <class...> class Pack, class... T, class U>
    void ClassValueToJson(const Pack<T...> &prop, json& jsonClass, U classThis) {
        jsonClass[prop.name] = classThis->*prop.member;
    }

    template<typename... Ts, class U>
    json toJson(std::tuple<Ts...> properties, U toJsonClassThis){
        json jsonClass;
        
        std::apply([&toJsonClassThis, &jsonClass, this](auto &&...args) { ((ClassValueToJson(args, jsonClass, toJsonClassThis)), ...); }, properties);
        return jsonClass;

    }
    template<typename... Ts, class U>
    void deJson(const json &data, std::tuple<Ts...> properties, U deJsonClassThis) {
        std::apply([&data,  &deJsonClassThis, this](auto &&...args) { (JsonValueToClass(args, data, deJsonClassThis), ...); }, properties);
    }
};

class User : public AddJsonSerDer {
public:
    std::string username;
    int info;

public:
    auto getProperties() {
        return makePropertiesTuple(Property<User, std::string>{&User::username, "username"},
                                   Property<User, int>{&User::info, "info"});
    }

    User(const json &data) {
        deJson(data, getProperties(), this);
    }
};

int main() {
    json value;

    value["info"] = 1;
    value["username"] = "Стартуем";
    User u(value);

    std::cout << u.toJson(u.getProperties(), &u);
    return 0;
}

// const std::string TOKEN = std::getenv("YANDEX_TOKEN");

// int main(int argc, char *argv[]) {

//     Client client(TOKEN, "ru");
//     client.initAccount();
//     json tracks = client.userLikesTracks();
//     std::cout << tracks["result"]["library"]["tracks"][0];
//     string trackId = tracks["result"]["library"]["tracks"][1]["id"];

//     Track track(client, std::stoi(trackId));
//     track.download("/home/user/Документы/Visual Studio Code Projects/YandexMusicApi/hto.mp3");
//     return 0;
// }
