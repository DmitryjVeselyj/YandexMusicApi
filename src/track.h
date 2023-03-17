#ifndef TRACK_H
#define TRACK_H
#include "client.h"
#include "types.h"
#include "errors.h"
#include "jsonSerDer.h"

class Track : public AddJsonSerDer<Track> {
private:
    
    Client client;
    
    cpr::Url buildDirectLink(cpr::Url downloadInfoUrl);

public:
    int trackId;
    int albumId;

    string timestamp;
    json fullInfo;
    json downloadInfo;
    Track(const Client &client);
    Track(const json& data);
    Track(const Client &client, int trackId);
    json getFullInfo();
    json getDownloadInfo();
    void download(string filename, string codec = "mp3", int bitrate = 320);
    json TOJSON();
    static constexpr auto getProperties() ;
        constexpr static auto prop = makePropertiesTuple(Property<Track, int>{&Track::trackId, "id", simpleType::INT}, 
                               Property<Track, int>{&Track::albumId, "albumId", simpleType::INT}, 
                               Property<Track, string>{&Track::timestamp, "timestamp", simpleType::STRING});
};

#endif // TRACK_H
