#include "client.h"
#include "track.h"
#include "types.h"
#include <stdlib.h>
#include <iostream>

const std::string TOKEN = std::getenv("YANDEX_TOKEN");

int main(int argc, char *argv[]) {

    Client client(TOKEN, "ru");
    client.initAccount();

    json tracks = client.userLikesTracks();
    json lastLikedTrack = tracks["result"]["library"]["tracks"][2];
    Track track(client, lastLikedTrack);

    std::cout << track << std::endl;

    track.download("/home/user/Документы/Visual Studio Code Projects/YandexMusicApi/hto.mp3");
    return 0;
}
