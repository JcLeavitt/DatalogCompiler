#include "Relation.h"

Relation Relation::get_select(string selected_object, int select_identifier)
{
  set<Tuple> new_tuples;
  //cout << "string and int" << endl;
  for (auto i : m_tuples)
  {
    if (i[select_identifier] == selected_object)
    {
      Tuple T(i);
      new_tuples.insert(T);
    }
  }
  Relation selected_relation(m_name,new_tuples, m_scheme);
  return selected_relation;
}
Relation Relation::get_select(vector<int> identifiers)
{
  set<Tuple> new_tuples;
  //cout << "int and int" << endl;
  for (auto i : m_tuples)
  {
    bool is_equal = true;
    int j = 0;
    if (check_for_all_equal_column_values(i,j,identifiers,is_equal)) {
      Tuple T(i);
      new_tuples.insert(T);
    }
  }
  Relation selected_relation(m_name,new_tuples, m_scheme);
  return selected_relation;
}
