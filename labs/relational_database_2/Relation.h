#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <iomanip>
using namespace std;

class Tuple : public vector<string>{};

// class Tuple{
// public:
//   vector <string> m_related_objects;
//
//   Tuple(vector<string> & related_objects)
//     : m_related_objects(related_objects) {}
//   Tuple(const Tuple & copy_tuple)
//   {
//     m_related_objects = copy_tuple.m_related_objects;
//   }
//   virtual ~Tuple(){}
//   bool operator<(const Tuple & to_compare) const
//   {
//     for (int i = 0; i < (int) m_related_objects.size(); i++) {
//       if (m_related_objects[i] != to_compare.m_related_objects[i]) {
//         cout << "comparing: " << m_related_objects[i] << " " << to_compare.m_related_objects[i] << endl;
//         return m_related_objects[i] < to_compare.m_related_objects[i];
//       }
//     }
//     return false;
//   }
//   void toString(){
//     for (auto i : m_related_objects) {
//       cout << setw(12) << i;
//     }
//     cout << endl;
//   }
//   int find(string object_name){
//     for (int i = 0; i < (int) m_related_objects.size(); i++) {
//       if (m_related_objects[i] == object_name) {
//         return i;
//       }
//     }
//     return -1;
//   }
//   vector<string> get_tuple_objects(){
//     return m_related_objects;
//   }
// private:
// };

class Relation{
public:
  set <Tuple> m_tuples;
  vector <string> m_scheme;
  string m_name;
  Relation(string name,set<Tuple> & tuples, vector<string> & scheme)
    : m_tuples(tuples),
    m_scheme(scheme),
    m_name(name){}
  virtual ~Relation(){}
  void operator=(const Relation & to_set_equal)
  {
    m_tuples.clear();
    for(auto i : to_set_equal.m_tuples)
    {
      m_tuples.insert(i);
    }
    m_name = to_set_equal.m_name;
    m_scheme = to_set_equal.m_scheme;
  }
  bool check_first_query_indice_for_string(vector<string> & current_query)
  {
    if (*current_query[0].begin() == '\'') {
      return true;
    }
    return false;
  }
  bool check_for_all_string_literal_query(vector<string> current_query)
  {
    for(int i = 0; i < (int) current_query.size(); i++)
    {
      if (*current_query[i].begin() != '\'') {
        return false;
      }
    }
    return true;
  }
  void toString(vector<string> & current_query){
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
  bool check_for_all_equal_column_values(Tuple & to_check, int & identifiers_index, vector<int> & identifiers, bool & is_equal)
  {
    if ((identifiers_index == ((int)identifiers.size() - 1)) && is_equal) {
      return is_equal;
    }
    else
    {
      // cout << identifiers_index << " " << identifiers.at(identifiers_index) << " " << identifiers.at(identifiers_index+1) << endl;
      // cout << to_check[identifiers.at(identifiers_index)] << " " << to_check[identifiers.at(1+identifiers_index)] << endl;
      if (to_check[identifiers.at(identifiers_index)] != to_check[identifiers.at(identifiers_index+1)]) {
        // cout << "bad value" << endl;
        is_equal = false;
        return is_equal;
      }
      else
      {
        identifiers_index++;
        return check_for_all_equal_column_values(to_check,identifiers_index,identifiers,is_equal);
      }
    }
  }
  int find_scheme_column(string scheme_col_id)
  {
    for (int i=0; i<(int)m_scheme.size();i++) {
      if (scheme_col_id == m_scheme[i]) {
        return i;
      }
    }
    return -1;
  }
  Relation get_select(string selected_object, int select_identifier);

  Relation get_select(vector<int> identifiers);

  Relation get_project(vector<int> proj_indices){
    vector<string> new_scheme;
    for (int i : proj_indices) {
      new_scheme.push_back(m_scheme[i]);
    }
    set<Tuple> new_tuples;
    Tuple T;
    for (auto j : m_tuples) {
      for (int i : proj_indices) {
        T.push_back(j[i]);
      }

      // for (int i = 0; i < T.get_tuple_objects().size(); i++) {
      //   cout << T.get_tuple_objects()[i] << " ";
      // }
      // cout << endl;
      new_tuples.insert(T);
      T.clear();
    }
    Relation projected_relation(m_name,new_tuples, new_scheme);
  //  projected_relation.toString();
    return projected_relation;
  }
  Relation get_rename(vector<string> new_scheme){
    Relation renamed_relation(m_name,m_tuples, new_scheme);
    return renamed_relation;
  }
private:
};
