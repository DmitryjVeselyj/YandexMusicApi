cmake_minimum_required(VERSION 3.14)

project(YandexMusicApi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/src/utils
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/utils/*.h"
        "${PROJECT_SOURCE_DIR}/src/utils/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.h"
        )
add_executable(YandexMusicApi
  main.cpp
  ${all_SRCS}
#   src/types.h
#   src/client.cpp
#   src/client.h
#   src/request.cpp
#   src/request.h
#   utils/errors.h
#   src/track.cpp
#   src/track.h
)



add_subdirectory(deps/jsonlib)
target_link_libraries(YandexMusicApi PUBLIC nlohmann_json::nlohmann_json)

add_subdirectory(deps/cprlib)
target_link_libraries(YandexMusicApi PUBLIC cpr::cpr)



install(TARGETS YandexMusicApi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
