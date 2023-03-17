#ifndef METAPROGRAMMINGSTUFF_H
#define METAPROGRAMMINGSTUFF_H

template <unsigned int index, typename... Tail>
struct getNthFromVariadicType;

template <unsigned int index, typename Head, typename... Tail>
struct getNthFromVariadicType<index, Head, Tail...>
    : getNthFromVariadicType<index - 1, Tail...> {};

template <typename Head, typename... Tail>
struct getNthFromVariadicType<0, Head, Tail...> {
    using type = Head;
};

#endif //  METAPROGRAMMINGSTUFF_H