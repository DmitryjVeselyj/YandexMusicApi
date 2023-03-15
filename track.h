#ifndef TRACK_H
#define TRACK_H
#include "client.h"
#include "types.h"

class Track {
private:
    int trackId;
    Client client;
    json fullInfo;
    json downloadInfo;
    cpr::Url buildDirectLink(cpr::Url downloadInfoUrl);

public:
    Track(const Client &client);
    Track(const Client &client, int trackId);
    json getFullInfo();
    json getDownloadInfo();
    void download(string filename, string codec = "mp3", int bitrate = 320);

    int getTrackId() const;
    void setTrackId(int newTrackId);
};

#endif // TRACK_H
