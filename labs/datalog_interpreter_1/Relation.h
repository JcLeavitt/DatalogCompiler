#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <iomanip>
using namespace std;

class Tuple : public vector<string>{};


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
  void toString();

  void toString(vector<string> & current_query);

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
  vector<string> make_matching_scheme(  Relation & to_cross_with)
  {
    vector<string> resulting_scheme;
    for(auto i : m_scheme)
    {
      resulting_scheme.push_back(i);
    }
    for(auto j : to_cross_with.m_scheme)
    {
      resulting_scheme.push_back(j);
    }
    return resulting_scheme;
  }
  Relation get_cross_p(  Relation & to_cross_with)//works!!!
  {
    set<Tuple> cross_p_of_two_relations;
    for(auto i : m_tuples)
    {
      Tuple existing_relations_tuples;
      for(auto k : to_cross_with.m_tuples)
      {
        for(auto j : i)
        {
          existing_relations_tuples.push_back(j);
        }
        for(auto l : k)
        {
          existing_relations_tuples.push_back(l);
        }
        cross_p_of_two_relations.insert(existing_relations_tuples);
        existing_relations_tuples.clear();
      }
    }
    vector<string> new_scheme = make_matching_scheme(to_cross_with);
    return Relation(m_name,cross_p_of_two_relations,new_scheme);
  }
  void get_matching_scheme_columns(  vector<string> & scheme_of_to_join, vector<int> & current_relation_columns, vector<int> & to_join_columns)
  {
    for(int i = 0; i < (int) m_scheme.size(); i++)
    {
      for(int j = 0; j < (int) scheme_of_to_join.size(); j++)
      {
        if (m_scheme[i] == scheme_of_to_join[j]) {
          current_relation_columns.push_back(i);
          to_join_columns.push_back(j);
        }
      }
    }
    return;
  }
  void combine_tuples(Tuple & combo,   Tuple & current_relation_tuple,   Tuple & to_join_tuple,   vector<int> & to_join_matched_cols)
  {
    for(auto i : current_relation_tuple)
    {
      combo.push_back(i);
    }
    for (int j = 0; j < (int) to_join_tuple.size(); j++) {
      bool no_matching_cols = true;
      for(auto k : to_join_matched_cols)
      {
        if (j == k) {
          no_matching_cols = false;
        }
      }
      if (no_matching_cols) {
        combo.push_back(to_join_tuple[j]);
      }
    }
    return;
  }
  vector<string> combine_schemes(  vector<string> & to_join_scheme,   vector<int> & to_join_matched_cols)
  {
    vector<string> combo;
    for(auto i : m_scheme)
    {
      combo.push_back(i);
    }
    for (int j = 0; j < (int) to_join_scheme.size(); j++) {
      bool no_matching_cols = true;
      for(auto k : to_join_matched_cols)
      {
        if (j == k) {
          no_matching_cols = false;
        }
      }
      if (no_matching_cols) {
        combo.push_back(to_join_scheme[j]);
      }
    }
    return combo;
  }
  Relation get_natural_join(  Relation & to_join_with)
  {
    //needs to check first to see if any elements of the current relation's scheme and to_join_with's scheme match
    //if so, then loop through the tuples of the current relation checking the matching scheme columns with those of the
    //to_join_with relation. if the tuples have a matching value, combine those two tuples into one and add it into a new set
    //for the new relation.
    //if there are no matching scheme elements, do the cross product of the two relations.
    //if there are matching scheme elements, but no matching tuple values, then the relsulting relation should be empty.
    vector<int> current_relation_columns;
    vector<int> to_join_columns;
    set<Tuple> joined_tuples;
    vector<string> new_scheme;
    get_matching_scheme_columns(to_join_with.m_scheme,current_relation_columns,to_join_columns);
    if (((int) current_relation_columns.size() == 0) && ((int) to_join_columns.size() == 0)) {
      return get_cross_p(to_join_with);
    }
    else
    {
      vector<string> new_scheme = combine_schemes(to_join_with.m_scheme,to_join_columns);
      for(auto i : m_tuples)
      {
        for(auto j : to_join_with.m_tuples)
        {
          Tuple combo;
          bool matching_cols = true;
          for(int h = 0; h < (int) current_relation_columns.size(); h++)
          {
            if (i[current_relation_columns[h]] != j[to_join_columns[h]]) //this is not adequately checking for mutiple column natural joins.
            {
              matching_cols = false;
            }
          }
          if (matching_cols) {
            combine_tuples(combo,i,j,to_join_columns);
            joined_tuples.insert(combo);
          }
        }
      }
      return Relation(m_name,joined_tuples,new_scheme);
    }
  }
  Relation get_union(Relation & to_union_with) //works!!!
  {
    //so long as the schemes match between the current relation and to_union_with, then add all the tuples from both relations
    //to a new set for the new relation.
    set<Tuple> new_set;
    for(auto i : m_tuples)
    {
      new_set.insert(i);
    }
    for(auto j : to_union_with.m_tuples)
    {
      new_set.insert(j);
    }
    return Relation(m_name,new_set,m_scheme);
  }
private:
};



//
// class Relation{
// public:
//   set <Tuple> m_tuples;
//   vector <string> m_scheme;
//   Relation(set<Tuple> & tuples, vector<string> & scheme)
//     : m_tuples(tuples),
//     m_scheme(scheme){}
//   void toString(){
//     for (auto i : m_scheme) {
//       cout << setw(4) << i;
//     }
//     cout << endl << endl;
//     for (auto i : m_tuples) {
//       i.toString();
//     }
//   }
//   Relation get_select(string selected_object, int select_identifier);
//
//   Relation get_select(int identifier_1, int identifier_2);
//
//   Relation get_project(vector<int> proj_indices){
//     vector<string> new_scheme;
//     for (int i : proj_indices) {
//       new_scheme.push_back(m_scheme[i]);
//     }
//     set<Tuple> new_tuples;
//     vector<string> new_objects;
//     for (auto j : m_tuples) {
//       for (int i : proj_indices) {
//         new_objects.push_back(j.get_tuple_objects()[i]);
//       }
//       Tuple T(new_objects);
//       // for (int i = 0; i < T.get_tuple_objects().size(); i++) {
//       //   cout << T.get_tuple_objects()[i] << " ";
//       // }
//       // cout << endl;
//       new_objects.clear();
//       new_tuples.insert(T);
//     }
//     Relation projected_relation(new_tuples, new_scheme);
//   //  projected_relation.toString();
//     return projected_relation;
//   }
//   Relation get_rename(vector<string> new_scheme){
//     Relation renamed_relation(m_tuples, new_scheme);
//     return renamed_relation;
//   }
// private:
// };
