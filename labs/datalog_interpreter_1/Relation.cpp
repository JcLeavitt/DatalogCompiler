#include "Relation.h"
#include <iomanip>

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

void Relation::toString()
{
    for (auto i : m_scheme) {
      cout << setw(10) << i;
    }
    cout << endl << endl;
    for (auto i : m_tuples) {
      for(auto j : i)
      {
        cout << setw(10) << j;
      }
      cout << endl;
    }
}

void Relation::toString(vector<string> & current_query)
{
  //cout << m_name << endl;
  current_query.erase(current_query.begin());
  for (auto i : m_tuples) {//for all the tuples
    bool no_string_in_query = false;
    if (m_tuples.empty()) {
      return;
    }
    if (!check_for_all_string_literal_query(current_query)) {
      cout << "  ";
      for(int j = 0; j < (int) m_scheme.size(); j++)
      {
        no_string_in_query = true;
        cout << m_scheme[j] << "=";
        cout << i[j];
        if (j < (int) m_scheme.size() - 1) {
          cout << ", ";
        }
      }
    }
    if (no_string_in_query) {
      cout << endl;
    }
  }
}
