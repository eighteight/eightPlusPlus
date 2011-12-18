#ifndef SCHEMA_TYPE_HXX
#define SCHEMA_TYPE_HXX

#include <string>
#include <typeinfo>

std::string
schema_type (const std::type_info&);

// Return polymorphic type schema name in the form "namespace#name".
// If there is no entry for this type, then return empty string.
//
template <typename T>
inline std::string
schema_type (const T& x)
{
  return schema_type (typeid (x));
}

#endif // SCHEMA_TYPE_HXX
