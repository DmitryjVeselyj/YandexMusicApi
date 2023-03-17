#include "client.h"
#include "track.h"
#include "types.h"
#include <iostream>
#include <stdlib.h>

#include "property.h"
#include <tuple>
#include <type_traits>
#include <variant>
#include "jsonSerDer.h"
#include <boost/log/trivial.hpp>


const std::string TOKEN = std::getenv("YANDEX_TOKEN");

int main(int argc, char *argv[]) {

    Client client(TOKEN, "ru");
    client.initAccount();
    json tracks = client.userLikesTracks();

    json lastLikedTrack = json(tracks["result"]["library"]["tracks"][0]);
    // string trackId = tracks["result"]["library"]["tracks"][1]["id"];

    Track track(lastLikedTrack);
    std::cout << track.albumId<<std::endl;
    std::cout << track.trackId<<std::endl;
    std::cout << track.timestamp<<std::endl;

  
    std::cout << track.toJson(track.prop);
    
    // std::cout << track.toJson(track.getProperties());
    // track.download("/home/user/Документы/Visual Studio Code Projects/YandexMusicApi/hto.mp3");
    return 0;
}
