#include "schema-type.hxx"

#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>
#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/tree/type-serializer-map.hxx>

using namespace std;
namespace tree = xsd::cxx::tree;

static const tree::type_serializer_plate<0, char> serializer_plate_init;

string
schema_type (const type_info& tid)
{
  typedef tree::type_serializer_map<char> type_map;

  type_map& tm (tree::type_serializer_map_instance<0, char> ());

  if (const type_map::type_info* ti = tm.find (tid))
  {
    const type_map::qualified_name& qn (ti->name ());

    if (qn.namespace_ ().empty ())
      return qn.name ();
    else
      return qn.namespace_ () + '#' + qn.name ();
  }
  else
    return "";
}
