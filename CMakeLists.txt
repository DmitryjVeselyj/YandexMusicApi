cmake_minimum_required(VERSION 3.14)

project(YMApi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(YMApi
  main.cpp
  types.h
  client.cpp
  client.h
  request.cpp
  request.h
  errors.h
  track.cpp
  track.h
)


add_subdirectory(deps/jsonlib)
target_link_libraries(YMApi PUBLIC nlohmann_json::nlohmann_json)

add_subdirectory(deps/cprlib)
target_link_libraries(YMApi PUBLIC cpr::cpr)


install(TARGETS YMApi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
