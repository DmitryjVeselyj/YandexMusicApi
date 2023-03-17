#ifndef CONVERTER_H
#define CONVERTER_H
#include "types.h"

template <typename T, typename U>
U Convert(const T &first) {
    return static_cast<U>(first);
}

template <>
inline int Convert<string, int>(const string &first) {
    return stoi(first);
}
#endif //  CONVERTER_H