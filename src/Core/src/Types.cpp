#include "Types.h"

std::string to_string(const vec2 &v)
{
    std::string ret = "[";
    ret += std::to_string(v.x) + ",";
    ret += std::to_string(v.y);
    ret += "]";
    return ret;
}

std::string to_string(const vec3 &v)
{
    std::string ret = "[";
    ret += std::to_string(v.x) + ",";
    ret += std::to_string(v.y) + ",";
    ret += std::to_string(v.z);
    ret += "]";
    return ret;
}

std::string to_string(const vec4 &v)
{
    std::string ret = "[";
    ret += std::to_string(v.x) + ",";
    ret += std::to_string(v.y) + ",";
    ret += std::to_string(v.z) + ",";
    ret += std::to_string(v.w);
    ret += "]";
    return ret;
}

std::ostream &operator<<(std::ostream &os, const vec2 &v)
{
    return os << to_string(v);
}

std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    return os << to_string(v);
}

std::ostream &operator<<(std::ostream &os, const vec4 &v)
{
    return os << to_string(v);
}
