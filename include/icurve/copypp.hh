#pragma once
#if _MSC_VER && _MSVC_LANG < 201402L
#error "minimun c++ version is c++14."
#elif __cplusplus < 201402L
#error "minimun c++ version is c++14."
#endif

#define COPYPP_VERSION 000200

#include <string>
#include <vector>
#include "meta.hh"
#ifdef NLOHMANN_DEFINE_TYPE_INTRUSIVE // 如果引入了nlohamnn_json
// clang-format off
#define _COPYPP_NLOHMANN_JSON_FROM(v1) if (nlohmann_json_j.contains(#v1)) nlohmann_json_j.at(#v1).get_to(nlohmann_json_t.v1);
#define _COPYPP_JSON(Type, ...) \
    friend void to_json(nlohmann::json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    friend void from_json(const nlohmann::json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(_COPYPP_NLOHMANN_JSON_FROM, __VA_ARGS__)) }
// clang-format on
#else
#define _COPYPP_JSON(...)
#endif

namespace icurve {

class _copypp_raw_meta {
public:
    std::string field_type = "";
    std::string field_name = "";
    size_t field_size = 0;
    void *p_value = nullptr;

public:
    _copypp_raw_meta(std::string field_type, std::string field_name,
                     size_t field_size, void *p_value)
        : field_type(field_type), field_name(field_name),
          field_size(field_size), p_value(p_value) {}
};

template <typename D, typename S> void copy(D &destination, S &source) {
    source._prepareFields();
    destination._prepareFields();
    for (auto dest : destination._data) {
        for (auto sour : source._data) {
            if (sour.field_name == dest.field_name &&
                sour.field_type == dest.field_type &&
                sour.field_size == dest.field_size) {
                destination._setField(dest.field_name, sour.p_value);
                break;
            }
        }
    }
}

#ifdef NLOHMANN_DEFINE_TYPE_INTRUSIVE
// copy josn string to struct.
template <typename D> void copy(D &destination, std::string &source) {
    nlohmann::json tmp = nlohmann::json::parse(source);
    destination = tmp;
}
// copy struct to json string
template <typename S> void copy(std::string &destination, S &source) {
    nlohmann::json tmp = source;
    destination = tmp.dump();
}
#endif
}; // namespace icurve

// clang-format off
#define _COPYPP_META_DATA std::vector<icurve::_copypp_raw_meta> _data; bool _is_prepare = false;

// 1. 写入_copypp_raw_meta
// 3. 设置_prepareFields
// 4. 设置_setField
#define COPYPP_FIELDS_INTRUSIVE(TYPE, ...) \
    _COPYPP_META_DATA  \
    _COPYPP_META_PREPARED(__VA_ARGS__)  \
    _COPYPP_META_SETFIELD(__VA_ARGS__)  \
    _COPYPP_JSON(TYPE, __VA_ARGS__)  \
    //

#define COPYPP_FIELDS_NON_INTRUSIVE(D, S, ...)  \
    template<> void icurve::copy(D &destination, S &source) {  \
        _COPYPP_META_PASTE(__VA_ARGS__)  \
    } \
    // 非侵入式
// clang-format on