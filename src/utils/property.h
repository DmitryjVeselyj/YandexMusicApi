template <typename Class, typename T>
struct Property {
    constexpr Property(T Class::*aMember, const char *aName) : member{aMember}, name{aName} {}

    T Class::*member;
    const char *name;
};

template <typename... Properties>
constexpr auto makePropertiesTuple(const Properties&&... args) {
    auto properties = std::make_tuple(args...);
    return properties;
}