#pragma once
#include <string>
#include <vector>
#include "meta.hh"
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

// copy josn string to struct.
template <typename D> void Copy(D &destination, std::string &source) {}
// copy struct to json string
template <typename S> void Copy(std::string &destination, S &source) {}
}; // namespace icurve

// clang-format off
#define _COPYPP_META_DATA std::vector<icurve::_copypp_raw_meta> _data; bool _is_prepare = false;

// 1. 写入_copypp_raw_meta
// 2. 写入_set,_get
// 3. 设置_prepareFields
// 4. 设置_setField
#define COPYPP_FIELDS_INTRUSIVE(...) \
    _COPYPP_META_DATA  \
    _COPYPP_META_SETGET(__VA_ARGS__)  \
    _COPYPP_META_PREPARED(__VA_ARGS__)  \
    _COPYPP_META_SETFIELD(__VA_ARGS__)  \
    //

// #define COPYPP_EXPAND(x) x

#define COPYPP_FIELDS_NON_INTRUSIVE(D, S, ...)  \
    template<> void icurve::copy(D &destination, S &source) {  \
        _COPYPP_PASTE(__VA_ARGS__)  \
    } \
    // 非侵入式
// clang-format on