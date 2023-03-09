#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <iomanip>
using namespace std;

class Tuple{
public:
  vector <string> m_related_objects;

  Tuple(vector <string> related_objects)
    : m_related_objects(related_objects) {}
  Tuple(const Tuple & copy_tuple)
  {
    m_related_objects = copy_tuple.m_related_objects;
  }
  bool operator<(const Tuple & to_compare) const
  {
    for (int i = 0; i < (int) m_related_objects.size(); i++) {
      if (m_related_objects[i] != to_compare.m_related_objects[i]) {
        return m_related_objects[i] < to_compare.m_related_objects[i];
      }
    }
    return false;
  }
  void toString(){
    for (auto i : m_related_objects) {
      cout << setw(4) << i;
    }
    cout << endl;
  }
  int find(string object_name){
    for (int i = 0; i < (int) m_related_objects.size(); i++) {
      if (m_related_objects[i] == object_name) {
        return i;
      }
    }
    return -1;
  }
  vector<string> get_tuple_objects(){
    return m_related_objects;
  }
private:
};

class Relation{
public:
  set <Tuple> m_tuples;
  vector <string> m_scheme;
  Relation(set<Tuple> & tuples, vector<string> & scheme)
    : m_tuples(tuples),
    m_scheme(scheme){}
  void toString(){
    for (auto i : m_scheme) {
      cout << setw(4) << i;
    }
    cout << endl << endl;
    for (auto i : m_tuples) {
      i.toString();
    }
  }
  Relation get_select(string selected_object, int select_identifier);

  Relation get_select(int identifier_1, int identifier_2);

  Relation get_project(vector<int> proj_indices){
    vector<string> new_scheme;
    for (int i : proj_indices) {
      new_scheme.push_back(m_scheme[i]);
    }
    set<Tuple> new_tuples;
    vector<string> new_objects;
    for (auto j : m_tuples) {
      for (int i : proj_indices) {
        new_objects.push_back(j.get_tuple_objects()[i]);
      }
      Tuple T(new_objects);
      // for (int i = 0; i < T.get_tuple_objects().size(); i++) {
      //   cout << T.get_tuple_objects()[i] << " ";
      // }
      // cout << endl;
      new_objects.clear();
      new_tuples.insert(T);
    }
    Relation projected_relation(new_tuples, new_scheme);
  //  projected_relation.toString();
    return projected_relation;
  }
  Relation get_rename(vector<string> new_scheme){
    Relation renamed_relation(m_tuples, new_scheme);
    return renamed_relation;
  }
private:
};
