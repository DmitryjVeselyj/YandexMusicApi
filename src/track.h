#ifndef TRACK_H
#define TRACK_H
#include "client.h"
#include "types.h"
#include "errors.h"
#include "jsonSerDer.h"
#include <fstream>
#include <iostream>
class Track : public AddJsonSerDer<Track> {
private:
    
    Client client;
    
    cpr::Url buildDirectLink(cpr::Url downloadInfoUrl);
    constexpr static auto getProperties();
public:
    int trackId;
    int albumId;

    string timestamp;
    json fullInfo;
    json downloadInfo;
    Track(const Client &client);
    Track(const Client &client, const json& data);
    Track(const Client &client, int trackId);
    json getFullInfo();
    json getDownloadInfo();
    void download(string filename, string codec = "mp3", int bitrate = 320);
    json toJson() const;
    friend std::ostream& operator<<(std::ostream& os, const Track& tr);
   
    
};

#endif // TRACK_H
