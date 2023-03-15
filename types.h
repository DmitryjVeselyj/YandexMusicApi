#ifndef TYPES_H
#define TYPES_H
#include <cpr/cpr.h>
#include <future>
#include <nlohmann/json.hpp>
#include <stdlib.h>
#include <string>
#include <vector>

using string = std::string;
using json = nlohmann::json;
using json_list = std::vector<json>;
using future_json = cpr::AsyncWrapper<json, false>;
using future_json_list = std::vector<future_json>;
#endif // TYPES_H
