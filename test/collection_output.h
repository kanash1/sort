#pragma once

#ifndef COLLECTION_OUTPUT_H
#define COLLECTION_OUTPUT_H

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <set>
#include <utility>
#include <map>

template<class Collection>
std::string join(const Collection& ñoll, char sep) {
    std::stringstream ss;
    bool is_first = true;
    for (const auto& elem : ñoll) {
        if (!is_first) {
            ss << sep;
        }
        is_first = false;
        ss << elem;
    }
    return ss.str();
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    return os << '[' << join(v, ',') << ']';
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& v) {
    return os << '[' << join(v, ',') << ']';
}

template<class T, size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<T, size>& a) {
    return os << '[' << join(a, ',') << ']';
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    return os << '{' << join(s, ',') << '}';
}

template<class K, class V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p) {
    return os << '(' << p.first << ',' << p.second << ')';
}

template<class K, class V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    return os << '{' << join(m, ',') << '}';
}

#endif // !COLLECTION_OUTPUT_H
