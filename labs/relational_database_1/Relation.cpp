#include "Relation.h"

Relation Relation::get_select(string selected_object, int select_identifier)
{
  set<Tuple> new_tuples;
  //cout << "string and int" << endl;
  for (auto i : m_tuples)
  {
    if (i.get_tuple_objects()[select_identifier] == selected_object)
    {
      Tuple T(i.get_tuple_objects());
      new_tuples.insert(T);
    }
  }
  Relation selected_relation(new_tuples, m_scheme);
  return selected_relation;
}
Relation Relation::get_select(int identifier_1, int identifier_2)
{
  set<Tuple> new_tuples;
  //cout << "int and int" << endl;
  for (auto i : m_tuples)
  {
    if (i.get_tuple_objects()[identifier_1] == i.get_tuple_objects()[identifier_2])
    {
      Tuple T(i.get_tuple_objects());
      new_tuples.insert(T);
    }
  }
  Relation selected_relation(new_tuples, m_scheme);
  return selected_relation;
}
