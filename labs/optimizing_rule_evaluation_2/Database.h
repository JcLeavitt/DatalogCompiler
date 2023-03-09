#include <iostream>
#include "Parser.h"
#include "Select_lit.h"
#include "Select_dup.h"
#include "Project.h"
#include "Rename.h"
#include "graph.h"
#include <algorithm>
using namespace std;

class Database
{
public:
  vector<Relation> m_all_relations;
  vector<Relation> m_all_finished_queries;
  DatalogProgram * m_my_program;
  vector<vector<Select_lit>> m_all_literal_selects;
  vector<vector<Select_dup>> m_all_duplicate_selects;
  vector<Project> m_columns_to_project;
  vector<Rename> m_new_scheme_name;
  vector<string> m_all_query_names;
  vector<vector<string>> m_stored_queries_in_order;
  graph m_master_dependency_graph;
  Database(DatalogProgram * my_program, vector<Relation> & all_relations):
  m_all_relations(all_relations),
  m_my_program(my_program){}
  ~Database()
  {
    delete m_my_program;
  }
  // void check_stuff()
  // {
  //   // cout << m_my_program->m_output[0]->m_tuples_based_on_scheme[0] << " "
  //   // << m_my_program->m_output[1]->m_individual_schemes[0] << endl;
  // }
  // void current_operations_to_perform()
  // {
  //   for(int i = 0; i < (int) m_all_literal_selects.size(); i++)
  //   {
  //     cout << "query " << i << endl;
  //     cout << "Select Literals" << endl;
  //     for(auto j : m_all_literal_selects[i])
  //     {
  //       cout << j.m_name_of_literal << " " << j.m_column_of_literal << endl;
  //     }
  //     cout << "Select duplicates" << endl;
  //     for(auto j : m_all_duplicate_selects[i])
  //     {
  //       cout << j.m_name_of_variable << " ";
  //       for(auto k : j.m_columns_of_variables_of_duplicates)
  //       {
  //         cout << k << " ";
  //       }
  //       cout << endl;
  //     }
  //     cout << endl << "project" << endl;
  //     for(auto j : m_columns_to_project[i])
  //     {
  //       cout << j << " ";
  //     }
  //     cout << endl << "rename" << endl;
  //     for(auto j : m_new_scheme_name[i])
  //     {
  //       cout << j << endl;
  //     }
  //   }
  // }
  vector<int> check_rule_exists(string & predicate_being_checked)
  {
    vector<int> all_matching_rules;
    for(int i = 0; i < (int) m_my_program->m_all_rules.size(); i++)
    {
      if(m_my_program->m_all_rules[i].m_head_predicate[0] == predicate_being_checked)
      {
        all_matching_rules.push_back(i);
      }
    }
    return all_matching_rules;
  }
  bool check_duplicate_dependency(int k, int current_rule_index)
  {
    for(auto i : m_master_dependency_graph.m_dependency_graph.find(current_rule_index)->second)
    {
      if (i == k)
      {
        return true;
      }
    }
    return false;
  }
  void add_dependents_to_graph(vector<int> & rule_indices, int i)
  {
    for(auto k : rule_indices)
    {
      if (!rule_indices.empty() && !check_duplicate_dependency(k,i))
      {
        m_master_dependency_graph.m_dependency_graph.find(i)->second.insert(k);
      }
    }
  }
  void make_dependency_graph()
  {
    set<int> original_dependents;
    for(int i = 0; i < (int) m_my_program->m_all_rules.size(); i++)
    {
      m_master_dependency_graph.m_dependency_graph[i] = original_dependents;
      m_master_dependency_graph.m_original_DFS_markers[i] = false;
    }
    for(int i = 0; i < (int) m_my_program->m_all_rules.size(); i++)
    {
      for(int j = 0; j < (int) m_my_program->m_all_rules[i].m_body_predicates.size(); j++)
      {
        vector<int> rule_indices = check_rule_exists(m_my_program->m_all_rules[i].m_body_predicates[j][0]);
        add_dependents_to_graph(rule_indices,i);
      }
    }
    m_master_dependency_graph.toString(m_master_dependency_graph.m_dependency_graph);
    m_master_dependency_graph.reverse_edges_in_graph();
    m_master_dependency_graph.strongly_connected_components();
  }
  // void make_dependency_graph()
  // {
  //   cout<< "making dependency graph" << endl;
  //   vector<string> original_dependents;
  //   for(auto i : m_my_program->m_all_rules)
  //   {
  //     for(auto j : i.m_body_predicates)
  //     {
  //       original_dependents.push_back(j[0]);
  //     }
  //     m_master_dependency_graph.m_dependency_graph[i.m_head_predicate[0]] = original_dependents;
  //     original_dependents.clear();
  //   }
  //   m_master_dependency_graph.toString(m_master_dependency_graph.m_dependency_graph);
  //   m_master_dependency_graph.reverse_edges_in_graph();
  //   m_master_dependency_graph.strongly_connected_components();
  // }
  void to_rename(Relation & to_operate, int all_big_vector_index)
  {
    Relation R = to_operate;
    if (m_new_scheme_name[all_big_vector_index].empty()) {
      // cout << "empty scheme" << endl;
      m_all_finished_queries.push_back(R);
      return;
    }
    //rename from any variables/columns that were projected on
    R = R.get_rename(m_new_scheme_name[all_big_vector_index]);
    //m_new_scheme_name.clear();
    m_all_finished_queries.push_back(R);
    // R.toString();
    return;
  }
  void to_project(Relation & to_operate, int all_big_vector_index)
  {
    Relation R = to_operate;
    if (m_columns_to_project[all_big_vector_index].empty()) {
      // cout << "empty" << endl;
      to_rename(R,all_big_vector_index);
      return;
    }
    //project on the first column from each select_dup variable and then on any non-duplicate variables
    R = R.get_project(m_columns_to_project[all_big_vector_index]);
    //m_columns_to_project.clear();
    // R.toString();
    to_rename(R,all_big_vector_index);
  }
  void select_duplicates(Relation & to_operate, int all_big_vector_index)
  {
    Relation R = to_operate;
    //do all duplicate selects then return the finished Relation.
    for(auto & i : m_all_duplicate_selects[all_big_vector_index])
    {
      if ((int) i.m_columns_of_variables_of_duplicates.size()<2){}
      else
      {
        R = R.get_select(i.m_columns_of_variables_of_duplicates);
      }
      // R.toString();
    }
    to_project(R,all_big_vector_index);
    return;
  }
  void select_literals(Relation & to_operate, int all_big_vector_index)
  {
    Relation R = to_operate;
    if(m_all_literal_selects[all_big_vector_index].empty())
    {
      select_duplicates(R,all_big_vector_index);
      return;
    }
    //do all literal selects then return the finished Relation.
    for(auto & i : m_all_literal_selects[all_big_vector_index])
    {
      Relation R1 = R.get_select(i.m_name_of_literal,i.m_column_of_literal);
      R = R1;
      //cout << i.m_name_of_literal << " " << i.m_column_of_literal << endl;
      //R.toString();
    }
    select_duplicates(R,all_big_vector_index);
    return;
  }
  bool find_all_instances_of_variable(vector<int> & cols_for_dup_select, string & variable_name,vector<string> & current_query)
  {
    bool more_than_one = false;
    for(int i=0;i<(int)current_query.size();i++)
    {
      if (current_query[i] == variable_name) {
        cols_for_dup_select.push_back(i);
        if ((int)cols_for_dup_select.size() > 1) {
          more_than_one = true;
        }
      }
    }
    return more_than_one;
  }
  bool check_for_existing_dup_sel_vars(string & var_name,vector<Select_dup> & dup_sels)
  {
    for(auto & i : dup_sels)
    {
      if (i.m_name_of_variable == var_name) {
        return true;
      }
    }
    return false;
  }
  void parse_query_for_operations(vector<string> & current_query)
  {
    vector<Select_lit> lit_sels;
    vector<Select_dup> dup_sels;
    Project all_ind_proj_cols;
    Rename all_ind_rename_schemes;
    vector<int> cols_for_dup_select;
    int col_for_lit_select;
    string name_of_literal;
    string name_of_variable;
    m_all_query_names.push_back(current_query[0]);
    current_query.erase(current_query.begin());
    for(int i=0; i<(int)current_query.size(); i++)
    {
      if (*current_query[i].begin() == '\'') {
        col_for_lit_select = i;
        name_of_literal = current_query[i];
        Select_lit Sl1(name_of_literal,col_for_lit_select);
        lit_sels.push_back(Sl1);
      }
      else
      {
        name_of_variable = current_query[i];
        if(find_all_instances_of_variable(cols_for_dup_select,name_of_variable, current_query))
        {
          if (dup_sels.empty()) {
            Select_dup Sd1(name_of_variable,cols_for_dup_select);
            all_ind_proj_cols.push_back(i);
            all_ind_rename_schemes.push_back(current_query[i]);
            dup_sels.push_back(Sd1);
          }
          else
          {
            if (!check_for_existing_dup_sel_vars(name_of_variable,dup_sels)) {
              Select_dup Sd1(name_of_variable,cols_for_dup_select);
              all_ind_proj_cols.push_back(i);
              all_ind_rename_schemes.push_back(current_query[i]);
              dup_sels.push_back(Sd1);
            }
          }
        }
        else
        {
          all_ind_proj_cols.push_back(i);
          all_ind_rename_schemes.push_back(current_query[i]);
        }
      }
      cols_for_dup_select.clear();
    }
    m_all_literal_selects.push_back(lit_sels);
    m_all_duplicate_selects.push_back(dup_sels);
    m_columns_to_project.push_back(all_ind_proj_cols);
    m_new_scheme_name.push_back(all_ind_rename_schemes);
  }
  Relation get_matching_relation(string & relation_name)
  {
    for(auto i : m_all_relations)
    {
      if (i.m_name == relation_name) {
        return i;
      }
    }
    return Relation();
  }
  bool check_for_existing_dup_sel_vars(string & var_name,vector<string> & dup_sels)
  {
    for(auto & i : dup_sels)
    {
      if (i == var_name) {
        return true;
      }
    }
    return false;
  }
  Relation parse_predicate_for_operations(vector<string> & current_predicate) //still needs work *******
  {
    Project all_ind_proj_cols;
    Rename all_ind_rename_schemes;
    vector<int> cols_for_dup_select;
    int col_for_lit_select;
    string name_of_literal;
    string name_of_variable;
    // m_all_predicate_names.push_back(current_query[0]);
    string predicate_name = current_predicate[0];
    current_predicate.erase(current_predicate.begin());
    vector<string> dup_sels_vars;
    Relation R = get_matching_relation(predicate_name);
    R.m_scheme = current_predicate;
    for(int i=0; i<(int)current_predicate.size(); i++)
    {
      if (*current_predicate[i].begin() == '\'') {
        col_for_lit_select = i;
        name_of_literal = current_predicate[i];
        R = R.get_select(name_of_literal,col_for_lit_select);
      }
      else
      {
        name_of_variable = current_predicate[i];
        if(find_all_instances_of_variable(cols_for_dup_select,name_of_variable, current_predicate))
        {
          if (!check_for_existing_dup_sel_vars(name_of_variable,dup_sels_vars)) {
            R = R.get_select(cols_for_dup_select);
            cols_for_dup_select.clear();
            all_ind_proj_cols.push_back(i);
            all_ind_rename_schemes.push_back(current_predicate[i]);
          }
        }
        else
        {
          cols_for_dup_select.clear();
          dup_sels_vars.push_back(name_of_variable);
          all_ind_proj_cols.push_back(i);
          all_ind_rename_schemes.push_back(current_predicate[i]);
        }
      }
    }
    R = R.get_project(all_ind_proj_cols);
    R = R.get_rename(all_ind_rename_schemes);
    return R;
  }
  vector<int> get_proj_cols(vector<string> & head_predicate_scheme, vector<string> & evaluate_rule_scheme)
  {
    vector<int> cols_to_project_on;
    for (auto j : head_predicate_scheme) {
      for(int k = 0; k < (int) evaluate_rule_scheme.size(); k++)
      {
        if (j == evaluate_rule_scheme[k]) {
          cols_to_project_on.push_back(k);
        }
      }
    }
    return cols_to_project_on;
  }
  void union_rule_relations_to_existing_relations(Relation & R,bool & a_relation_has_changed)
  {
    for(auto & i : m_all_relations)
    {
      if ((R.m_name == i.m_name) && (R.m_scheme.size() == i.m_scheme.size())) {
        Relation before_union_relation = i;
        i = i.get_union(R);
        a_relation_has_changed = !(before_union_relation == i);
      }
    }
  }
  // void evaluate_rules()
  // {
  //   bool a_relation_has_changed;
  //   bool no_relations_changed;
  //
  //   int number_of_iterations = 0;
  //   do {
  //     no_relations_changed = true;
  //     for(auto i : m_my_program->m_all_rules)
  //     {
  //       vector<Relation> temp_predicates;
  //       for(auto j : i.m_body_predicates)
  //       {
  //         //run query on i and add resulting relation to temp_predicates.
  //         Relation R = parse_predicate_for_operations(j);
  //         temp_predicates.push_back(R);
  //       }
  //       Relation R = temp_predicates[0];
  //       for (int k = 1; k < (int) temp_predicates.size(); k++)
  //       {
  //         R = R.get_natural_join(temp_predicates[k]);
  //       }
  //       // cout << "hi" << endl;
  //       R.m_name = i.m_head_predicate[0];
  //       i.m_head_predicate.erase(i.m_head_predicate.begin());
  //       vector<int> cols_to_project_on = get_proj_cols(i.m_head_predicate,R.m_scheme);
  //       R = R.get_project(cols_to_project_on);
  //       union_rule_relations_to_existing_relations(R,a_relation_has_changed);
  //       if (a_relation_has_changed) {
  //         no_relations_changed = false;
  //       }
  //       // R.toString();
  //       //project R on variables from headPredicate that have the same name
  //       //call function that will check through m_all_relations and union R to any that have the same name.
  //     }
  //     number_of_iterations++;
  //   } while(!no_relations_changed);
  //   cout << "Schemes populated after " << number_of_iterations << " passes through the Rules." << endl;
  // }
  void print_current_scc(vector<int> & current_scc)
  {
    for (int i = 0; i < (int) current_scc.size(); i++) {
      cout << "R" << current_scc[i];
      if (i < (int) current_scc.size()-1) {
        cout << ",";
      }
    }
  }
  void evaluate_trivial_rule(int i, bool a_relation_has_changed)
  {
    vector<Relation> temp_predicates;
    for(auto j : m_my_program->m_all_rules[i].m_body_predicates)
    {
      //run query on i and add resulting relation to temp_predicates.
      Relation R = parse_predicate_for_operations(j);
      temp_predicates.push_back(R);
    }
    Relation R = temp_predicates[0];
    for (int k = 1; k < (int) temp_predicates.size(); k++)
    {
      R = R.get_natural_join(temp_predicates[k]);
    }
    // cout << "hi" << endl;
    R.m_name = m_my_program->m_all_rules[i].m_head_predicate[0];
    vector<string> temp_head_pred = m_my_program->m_all_rules[i].m_head_predicate;
    temp_head_pred.erase(temp_head_pred.begin());
    vector<int> cols_to_project_on = get_proj_cols(temp_head_pred,R.m_scheme);
    R = R.get_project(cols_to_project_on);
    union_rule_relations_to_existing_relations(R,a_relation_has_changed);
  }
  bool check_dependent_on_self(int rule_to_check)
  {
    for(auto i : m_master_dependency_graph.m_dependency_graph.find(rule_to_check)->second)
    {
      if (i == rule_to_check) {
        return true;
      }
    }
    return false;
  }
  void evaluate_rules(vector<int> & current_scc)
  {
    bool a_relation_has_changed;
    bool no_relations_changed;
    // make_dependency_graph();
    int number_of_iterations = 0;
    if ((int) current_scc.size() == 1 && !check_dependent_on_self(current_scc[0]))
    {
      evaluate_trivial_rule(current_scc[0],a_relation_has_changed);
      number_of_iterations++;
    }
    else
    {
      do {
        no_relations_changed = true;
        for(auto i : current_scc) //m_my_program->m_all_rules
        {
            vector<Relation> temp_predicates;
            for(auto j : m_my_program->m_all_rules[i].m_body_predicates)
            {
              //run query on i and add resulting relation to temp_predicates.
              Relation R = parse_predicate_for_operations(j);
              temp_predicates.push_back(R);
            }
            Relation R = temp_predicates[0];
            for (int k = 1; k < (int) temp_predicates.size(); k++)
            {
              R = R.get_natural_join(temp_predicates[k]);
            }
            // cout << "hi" << endl;
            R.m_name = m_my_program->m_all_rules[i].m_head_predicate[0];
            vector<string> temp_head_pred = m_my_program->m_all_rules[i].m_head_predicate;
            temp_head_pred.erase(temp_head_pred.begin());
            vector<int> cols_to_project_on = get_proj_cols(temp_head_pred,R.m_scheme);
            R = R.get_project(cols_to_project_on);
            union_rule_relations_to_existing_relations(R,a_relation_has_changed);
            if (a_relation_has_changed) {
              no_relations_changed = false;
            }
            // R.toString();
            //project R on variables from headPredicate that have the same name
            //call function that will check through m_all_relations and union R to any that have the same name.
        }
        number_of_iterations++;
      } while(!no_relations_changed);
    }
    cout << number_of_iterations << " passes: ";
    print_current_scc(current_scc);
    cout << endl;
  }
  void start_evaluating_rules()
  {
    make_dependency_graph();

    cout << "Rule Evaluation" << endl;
    for(auto i : m_master_dependency_graph.m_strongly_connected_components)
    {
      sort(i.begin(),i.end());
      evaluate_rules(i);
    }
    cout << endl;
  }
  bool check_if_scheme_exists(int i)
  {
    for(auto j : m_all_relations)
    {
      if (j.m_name == m_all_query_names[i]) {
        return true;
      }
    }
    return false;
  }
  void run_query()
  {
    // cout << all_queries.size() << " all_queries.size()" << endl;
    // cout << m_all_query_names.size() << " m_all_query_names.size()" << endl;
    for(int j=0; j < (int)m_all_query_names.size();j++)
    {
      if (!check_if_scheme_exists(j)) {
        string name = "null";
        set<Tuple> empty;
        Relation R(name,empty,m_stored_queries_in_order[j]);
        m_all_finished_queries.push_back(R);
      }
      else
      {
        for(auto & k : m_all_relations)
        {
          if ((k.m_name == m_all_query_names[j]) && (k.m_scheme.size() == (m_stored_queries_in_order[j].size() - 1))) {
            select_literals(k,j);
          }
        }
      }
    }
    return;
  }
  void start_queries()
  {
    cout << "Query Evaluation" << endl;
    for (auto & i : m_my_program->m_output) {
      if (i->get_SFRQ_Type() == "QUERIES") {
        m_stored_queries_in_order.push_back(i->m_individual_queries);
        parse_query_for_operations(i->m_individual_queries);
      }
    }
    // current_operations_to_perform();
    run_query();
  }
  void get_rid_of_garbage(set<Tuple> & i,set<Tuple> & new_set)
  {
    Tuple T1;
    for (auto & l : i) {
      for (int k = 1; k < (int)l.size(); k++) {
        T1.push_back(l.at(k));
      }
      // i.erase(l);
      new_set.insert(T1);
      T1.clear();
    }
    // i.clear();
    return;
  }
  void create_starting_relations()
  {

    for (auto & j : m_my_program->m_output[0]->m_individual_schemes)
    {
      string name = j[0];
      set<Tuple> new_set;
      j.erase(j.begin());
      Relation R(name,new_set,j);
      for (auto & i : m_my_program->m_output[1]->m_tuples_based_on_scheme)
      {
        if (i.begin()->at(0) == name) {
          get_rid_of_garbage(i,R.m_tuples);
        }
      }
      m_all_relations.push_back(R);
    }
    // i.clear();
  }
  void print_out_initial_query(int i)
  {
    cout << m_stored_queries_in_order[i].at(0) << "(";
    for(int j = 1; j < (int) m_stored_queries_in_order[i].size(); j++)
    {
      cout << m_stored_queries_in_order[i].at(j);
      if (j < (int) m_stored_queries_in_order[i].size() - 1) {
        cout << ",";
      }
    }
    cout << ")?";
  }
  // bool check_for_equal_schemes(vector<string> scheme_to_check, int & index, vector<string> & initial_scheme, bool & is_equal)
  // {
  //   if ((index == ((int)initial_scheme.size())) && is_equal) {
  //     return is_equal;
  //   }
  //   else
  //   {
  //     // cout << identifiers_index << " " << identifiers.at(identifiers_index) << " " << identifiers.at(identifiers_index+1) << endl;
  //     // cout << to_check[identifiers.at(identifiers_index)] << " " << to_check[identifiers.at(1+identifiers_index)] << endl;
  //     if (scheme_to_check[index] != initial_scheme[index]) {
  //       // cout << "bad value" << endl;
  //       is_equal = false;
  //       return is_equal;
  //     }
  //     else
  //     {
  //       index++;
  //       return check_for_equal_schemes(scheme_to_check,index,initial_scheme,is_equal);
  //     }
  //   }
  // }
  // bool check_all_relations_for_bad_schemes(int & i)
  // {
  //   bool all_not_equal = true;
  //   for(auto l : m_all_relations)
  //   {
  //     bool is_equal = true;
  //     int k = 0;
  //     if (check_for_equal_schemes(m_all_finished_queries[i].m_scheme,k,l.m_scheme,is_equal)) {
  //       all_not_equal = false;
  //       return all_not_equal;
  //     }
  //   }
  //   return all_not_equal;
  // }
  void toString()
  {
    // cout << m_all_finished_queries.size() << " m_all_finished_queries.size()"<< endl;
    // cout << m_all_query_names.size() << " m_all_query_names.size()"<< endl;
    // cout << m_all_relations.size() << " m_all_relations.size()"<< endl;
    // cout << "Dependency Graph" << endl;
    // m_master_dependency_graph.toString(m_master_dependency_graph.m_dependency_graph);
    for(int i = 0; i < (int) m_all_finished_queries.size(); i++)
    {
      //print out the actual query
      print_out_initial_query(i);
      //print out if there is a tuple(s) for which the query is true, print out Yes, and how many
      if (!m_all_finished_queries[i].m_tuples.empty()) {
        cout << " Yes(" << m_all_finished_queries[i].m_tuples.size() << ")" << endl;
        m_all_finished_queries[i].toString(m_stored_queries_in_order[i]);
      }
      else
      {
        cout << " No" << endl;
      }
      //if there is a variable/ID involved with a true query, print out the variable=the string for which it is true, indented
    }
  }
private:
};
