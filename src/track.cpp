#include "track.h"
#include "request.h"
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cpr/parameters.h>
#include <fstream>
#include <iostream>
#include <typeinfo>

Track::Track(const Client &client) {
    this->client = client;
}

Track::Track(const Client &client, int trackId) {
    this->trackId = trackId;
    this->client = client;
}

json Track::getFullInfo() {
    cpr::Parameters params{{"track-ids", std::to_string(trackId)}};
    cpr::Url url(client.getApiUrl() + "/tracks/");
    cpr::Response response = Request::Post(url, client.getRequest().getHeaders(), params);
    return json::parse(response.text);
}

json Track::getDownloadInfo() {

    cpr::Url url(client.getApiUrl() + "/tracks/" + std::to_string(trackId) + "/download-info");
    cpr::Response response = Request::Get(url, client.getRequest().getHeaders());
    return json::parse(response.text);
}
void Track::download(string filename, string codec, int bitrate) {
    json downloadInfo = getDownloadInfo();
    cpr::Url downloadInfoUrl;

    for (auto it = downloadInfo["result"].begin(); it != downloadInfo["result"].end(); ++it) {

        if ((*it)["codec"] == codec && (*it)["bitrateInKbps"] == bitrate) {
            downloadInfoUrl = static_cast<cpr::Url>((*it)["downloadInfoUrl"]);
            cpr::Response result = Request::Get(buildDirectLink(downloadInfoUrl), client.getRequest().getHeaders());

            std::ofstream track(filename, std::ofstream::binary);
            if (!track.is_open()) {

                throw PathError();
            }
            track << result.text;
            track.close();
            return;
        }
    }
    throw BitrateError();
}

cpr::Url Track::buildDirectLink(cpr::Url downloadInfoUrl) {
    cpr::Response response = Request::Get(downloadInfoUrl, client.getRequest().getHeaders());

    std::stringstream stream(response.text);
    boost::property_tree::ptree propertyTree;
    boost::property_tree::read_xml(stream, propertyTree);

    string host = propertyTree.get_child("download-info").get_child("host").data();
    string sign = propertyTree.get_child("download-info").get_child("s").data();
    string ts = propertyTree.get_child("download-info").get_child("ts").data();
    string path = propertyTree.get_child("download-info").get_child("path").data();
    string directLink = "https://" + host + "/get-mp3/" + sign + "/" + ts + path;

    return cpr::Url(directLink);
}
constexpr auto Track::getProperties() {
    return makePropertiesTuple(Property<Track, int>{&Track::trackId, "id", simpleType::INT}, 
                               Property<Track, int>{&Track::albumId, "albumId", simpleType::INT}, 
                               Property<Track, string>{&Track::timestamp, "timestamp", simpleType::STRING});
}
json Track::TOJSON(){
    return toJson(getProperties());
}
Track::Track(const json &data) {
    deJson(data, getProperties());
}
