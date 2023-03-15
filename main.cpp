#include "client.h"
#include "track.h"
#include <iostream>
#include <stdlib.h>
const std::string TOKEN = std::getenv("YANDEX_TOKEN");

int main(int argc, char *argv[]) {

    Client client(TOKEN, "ru");
    client.initAccount();
    json tracks = client.userLikesTracks();
    std::cout << tracks["result"]["library"]["tracks"][0];
    string trackId = tracks["result"]["library"]["tracks"][1]["id"];
    Track track(client, std::stoi(trackId));
    track.download("/home/user/YMApi/hto.mp3");
    return 0;
}
