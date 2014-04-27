#pragma once


namespace lumina {

/**
 * @brief Function object to compare two objects with memcmp
 * @details Compares to arbitrary objects with the C function memcmp. It's an
 *          synthetic sort, since it does not make sense in most cases. It 
 *          can be used as compare object for container like std::map.
 * 
 * @tparam T Type of the objects
 */
template <typename T>
struct LSynthMemSorter {
  bool operator()(const T& x, const T& y) const {
    return memcmp(&x, &y, sizeof(T)) < 0;
  }
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};

};