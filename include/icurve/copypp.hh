#pragma once
#if _MSC_VER && _MSVC_LANG < 201402L
#error "minimun c++ version is c++14."
#elif __cplusplus < 201402L
#error "minimun c++ version is c++14."
#endif

#define COPYPP_VERSION 000200

#include <string>
#include <vector>
#include <vector>
#if (_MSC_VER && _MSVC_LANG >= 201703L) || __cplusplus >= 202002L
#include <span>
#endif
#include "meta.hh"

#ifndef NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT
#define NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(...)
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

template <typename D, size_t L1, typename S, size_t L2>
void copy(std::array<D, L1> &destination, std::array<S, L2> &source) {
    size_t len = std::min(L1, L2);
    for (int i = 0; i < len; i++) {
        icurve::copy(destination[i], source[i]);
    }
}

#if (_MSC_VER && _MSVC_LANG >= 201703L) || __cplusplus >= 202002L
template <typename D, size_t L1, typename S, size_t L2>
void copy(std::span<D, L1> destination, std::span<S, L2> source) {
    size_t len = std::min(L1, L2);
    for (int i = 0; i < len; i++) {
        icurve::copy(destination[i], source[i]);
    }
}

template <typename D, typename S>
void copy(std::vector<D> &destination, std::vector<S> &source) {
    destination.clear();
    if (source.empty())
        return;
    for (auto &item : source) {
        D tmp;
        copy(tmp, item);
        destination.push_back(tmp);
    }
}
#endif

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
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TYPE, __VA_ARGS__)  \
    //

#define COPYPP_FIELDS_NON_INTRUSIVE(D, S, ...)  \
    template<> void icurve::copy(D &destination, S &source) {  \
        _COPYPP_META_PASTE(__VA_ARGS__)  \
    } \
    // 非侵入式
// clang-format on