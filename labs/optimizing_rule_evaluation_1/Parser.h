#pragma once
#include <vector>
#include <string>
#include <set>
#include "Token.h"
#include "Relation.h"
using namespace std;
class SFRQ {
public:
  vector<vector<string>> m_individual_schemes;
  vector<set<Tuple>> m_tuples_based_on_scheme;
  vector<string> m_individual_queries;
  SFRQ(){}
  virtual ~SFRQ(){}
  virtual void toString(){}
  virtual string get_SFRQ_Type(){return "";}
  // virtual vector<vector<string>> get_Vector(){}
  // virtual vector<set<Tuple>> get_Vector(){}

private:
};
class schemes : public SFRQ {
public:
  vector <Token *> m_scheme_tokens;
  schemes(vector <Token *> & scheme_tokens):SFRQ(){m_scheme_tokens = scheme_tokens;}
  virtual ~schemes(){}
  // vector<vector<string>> get_Vector()
  // {
  //   return m_individual_schemes;
  // }
  virtual string get_SFRQ_Type(){
    return "SCHEMES";
  }
  void get_scheme_vectors()
  {
    vector<string> temp_scheme_hold;
    string current_token_value;
    for (auto i : m_scheme_tokens) {
      if ((i->getType() == "ID")) {
        temp_scheme_hold.push_back(i->getValue());
      }
      if (i->getType() == "RIGHT_PAREN") {
        m_individual_schemes.push_back(temp_scheme_hold);
        temp_scheme_hold.clear();
      }
    }
    // for (auto i : m_individual_schemes) {
    //   for (auto j : i) {
    //     cout << j << " ";
    //   }
    //   cout << endl;
    // }
  }
  virtual void toString(){
    int scheme_counter = 0;
    for (int i = 0; i < (int) m_scheme_tokens.size(); i++) {
      if (m_scheme_tokens[i]->getType() == "RIGHT_PAREN") {
        scheme_counter++;
      }
    }
    cout << "Schemes(" << scheme_counter << "):" << endl << "  ";
    for (int i = 0; i < (int) m_scheme_tokens.size(); i++) {
      cout << m_scheme_tokens[i]->getValue();
      if (m_scheme_tokens[i]->getType() == "RIGHT_PAREN") {
        cout << endl;
        if (i < (int) m_scheme_tokens.size() - 1) {
          cout << "  ";
        }
      }
    }
    //cout << endl;
  }
};
class facts : public SFRQ {
public:
  vector<Token *> m_fact_tokens;
  facts(vector<Token *> & fact_tokens):SFRQ(){m_fact_tokens = fact_tokens;}
  virtual ~facts(){}
  // vector<set<Tuple>> get_Vector()
  // {
  //   return m_tuples_based_on_scheme;
  // }
  bool verify_existance(Tuple & T, set<Tuple> & collect_tuples_with_same_scheme)
  {
    for(auto & j : m_tuples_based_on_scheme)
    {
      if (T[0] == j.begin()->at(0))
      {
        j.insert(T);
        T.clear();
        return true;
      }
    }
    return false;
  }
  void add_to_sets(Token * & i, set<Tuple> & collect_tuples_with_same_scheme, Tuple & T)
  {
    // cout << "right paren" << endl;
    if (m_tuples_based_on_scheme.empty())
    {
      // cout << "empty vector of sets" << endl;
      if (collect_tuples_with_same_scheme.empty())
      {
        // cout << "empty set" << endl;
        collect_tuples_with_same_scheme.insert(T);
        m_tuples_based_on_scheme.push_back(collect_tuples_with_same_scheme);
        T.clear();
      }
      else if (T[0] == collect_tuples_with_same_scheme.begin()->at(0))
      {
        // cout << "not empty set and scheme_names match" << endl;
        collect_tuples_with_same_scheme.insert(T);
        //m_tuples_based_on_scheme.push_back(collect_tuples_with_same_scheme);
        T.clear();
      }
      else
      {
        // cout << "not empty set and scheme_names do not match" << endl;
        //m_tuples_based_on_scheme.push_back(collect_tuples_with_same_scheme);
        collect_tuples_with_same_scheme.clear();
        collect_tuples_with_same_scheme.insert(T);
        m_tuples_based_on_scheme.push_back(collect_tuples_with_same_scheme);
        T.clear();
      }
    }
    else
    {
      // cout << "not empty vector and not empty set" << endl;
      if (verify_existance(T,collect_tuples_with_same_scheme))
      {
        // cout << "set existed in vector and tuple was inserted" << endl;
      }
      else
      {
        //cout << "set did not exist in vector so we made one and inserted it with the tuple" << endl;
        //m_tuples_based_on_scheme.push_back(collect_tuples_with_same_scheme);
        collect_tuples_with_same_scheme.clear();
        collect_tuples_with_same_scheme.insert(T);
        m_tuples_based_on_scheme.push_back(collect_tuples_with_same_scheme);
        T.clear();
      }
    }
  }
  void get_all_tuples()
  {
    set<Tuple> collect_tuples_with_same_scheme;
    Tuple T;
    for(auto i : m_fact_tokens)
    {
      if (i->getType() == "RIGHT_PAREN") {
        add_to_sets(i,collect_tuples_with_same_scheme,T);
      }
      else if (i->getType() == "ID") {
        T.push_back(i->getValue());
      }
      else if (i->getType() == "STRING") {
        T.push_back(i->getValue());
      }
    }
    // for (auto i : m_tuples_based_on_scheme)
    // {
    //   for (auto j : i)
    //   {
    //     for (auto k : j.m_related_objects)
    //     {
    //       cout << k << " ";
    //     }
    //     cout << endl;
    //   }
    // }
  }
  virtual string get_SFRQ_Type(){
    return "FACTS";
  }
  virtual void toString(){
    int fact_counter = 0;
    for (int i = 0; i < (int) m_fact_tokens.size(); i++) {
      if (m_fact_tokens[i]->getType() == "PERIOD") {
        fact_counter++;
      }
    }
    cout << "Facts(" << fact_counter << "):" << endl;
    if (fact_counter != 0) {
      cout << "  ";
    }
    for (int i = 0; i < (int) m_fact_tokens.size(); i++) {
      cout << m_fact_tokens[i]->getValue();
      if (m_fact_tokens[i]->getType() == "PERIOD") {
        cout << endl;
        if (i < (int) m_fact_tokens.size() - 1) {
          cout << "  ";
        }
      }
    }
    //cout << endl;
  }
};
class Parameter{
public:
  vector<Token *> m_parameter_tokens;
  Parameter(){}
  virtual ~Parameter()
  {
    // for(auto i : m_parameter_tokens)
    // {
    //   // delete i;
    // }
    // m_parameter_tokens.clear();
  }
  virtual void toString(){}
};
class ID_Parameter : public Parameter{
public:
  Token * m_id;
  ID_Parameter(Token * & id){m_id = id;}
  virtual ~ID_Parameter()
  {
    // delete m_id;
  }
  virtual void toString(){
    cout << m_id->getValue();
  }
};
class STRING_Parameter : public Parameter{
public:
  Token * m_string;
  STRING_Parameter(Token * & string){m_string = string;}
  virtual ~STRING_Parameter()
  {
    // delete m_string;
  }
  virtual void toString(){
    cout << m_string->getValue();
  }
};
class Expression_Parameter : public Parameter{
public:
  Token * m_left_paren;
  Token * m_right_paren;
  Parameter * m_left_parameter;
  Parameter * m_right_parameter;
  Token * m_my_operator;
  Expression_Parameter(Token * & left_paren,Parameter * & left_parameter, Token * & my_operator,Parameter * & right_parameter,Token * & right_paren)
  {m_left_paren = left_paren,
  m_left_parameter = left_parameter,
  m_my_operator = my_operator,
  m_right_parameter = right_parameter,
  m_right_paren = right_paren;}
  virtual ~Expression_Parameter()
  {
    // delete m_left_paren;
    // delete m_right_paren;
    // delete m_left_parameter;
    // delete m_right_parameter;
    // delete m_my_operator;
  }
  virtual void toString(){
    cout << m_left_paren->getValue();
    m_left_parameter->toString();
    cout << m_my_operator->getValue();
    m_right_parameter->toString();
    cout << m_right_paren->getValue();
  }
};
class Predicate{
public:
  vector<Token *> m_predicate_tokens;
  //vector<Token *> m_parameter_tokens;
  vector<string> m_current_predicate;
  vector<vector<string>> m_all_predicates;
  vector<Parameter *> m_all_parameters;
  vector<string> m_str_predicate;
  Predicate(vector<Token *> & predicate_tokens){m_predicate_tokens = predicate_tokens;}
  virtual ~Predicate()
  {
    // for(auto i : m_predicate_tokens)
    // {
    //   delete i;
    // }
    // m_predicate_tokens.clear();
    for(auto j : m_all_parameters)
    {
      delete j;
    }
    m_all_parameters.clear();
  }
  void fill_str_predicate()
  {
    for(auto i : m_predicate_tokens)
    {
      if (i->getType() == "ID" || i->getType() == "STRING") {
        m_str_predicate.push_back(i->getValue());
      }
    }
    return;
  }
  void check_predicate_start(int & i){
    if (m_predicate_tokens[i]->getType() == "ID" && m_predicate_tokens[i+1]->getType() == "LEFT_PAREN") {
      if ((int) m_all_predicates.empty()) {
        m_current_predicate.push_back(m_predicate_tokens[i]->getValue());
      }
      else
      {
        m_all_predicates.push_back(m_current_predicate);
        m_current_predicate.clear();
        m_current_predicate.push_back(m_predicate_tokens[i]->getValue());
      }
      i++;
      i++;
      return;
    }
    return;
  }
  int check_null_l_r(Parameter * & to_check, int & i){
    //cout << "check_null_l_r " << m_predicate_tokens[i]->getValue() << endl;
    if(to_check != NULL && (m_predicate_tokens[i]->getType() == "ADD" || m_predicate_tokens[i]->getType() == "MULTIPLY")){
      //cout << m_predicate_tokens[i-1]->getValue() << " left parameter " << endl;
      return 1;
    }
    else if(to_check != NULL && (m_predicate_tokens[i]->getType() == "RIGHT_PAREN")){
      //cout << m_predicate_tokens[i]->getValue() << " right parameter " << i << endl;
      return 2;
    }
    return 0;
  }
  Parameter * get_ID(int & i){
    if (m_predicate_tokens[i]->getType() == "ID") {
      Parameter * p_id = new ID_Parameter(m_predicate_tokens[i]);
      i++;
      return p_id;
    }
    return NULL;
  }
  Parameter * get_STRING(int & i){
    if (m_predicate_tokens[i]->getType() == "STRING") {
      Parameter * p_string = new STRING_Parameter(m_predicate_tokens[i]);
      i++;
      return p_string;
    }
    return NULL;
  }
  Parameter * get_Expression(int & i){
    if (m_predicate_tokens[i]->getType() == "LEFT_PAREN") {
      Token * left_paren = m_predicate_tokens[i];
      //cout << endl << m_predicate_tokens[i]->getType() << " left paren " << i << endl;
      i++;
      Parameter * left_parameter = NULL;
      Parameter * right_parameter = NULL;
      Token * my_operator = NULL;
      Token * right_paren = NULL;
      Parameter * check_expression = get_Expression(i);
      if (check_null_l_r(check_expression,i) == 1) {
        //cout << endl << "left get expression" << endl;
        left_parameter = check_expression;
        my_operator = m_predicate_tokens[i];
        i++;
      }
      check_expression = get_Expression(i);
      if (check_null_l_r(check_expression,i) == 2) {
        //cout << "right get expression" << endl;
        right_parameter = check_expression;
        right_paren = m_predicate_tokens[i];
        Parameter * p_expression = new Expression_Parameter(left_paren, left_parameter, my_operator, right_parameter, right_paren);
        i++;
        return p_expression;
      }
      Parameter * check_id = get_ID(i);
      if (check_null_l_r(check_id,i) == 1) {
        //cout << "left get id" << endl;
        left_parameter = check_id;
        my_operator = m_predicate_tokens[i];
        i++;
        //cout << m_predicate_tokens[i]->getValue() << endl;
      }
      check_id = get_ID(i);
      if (check_null_l_r(check_id,i) == 2) {
        //cout << "right get id" << endl;
        right_parameter = check_id;
        right_paren = m_predicate_tokens[i];
        Parameter * p_expression = new Expression_Parameter(left_paren, left_parameter, my_operator, right_parameter, right_paren);
        i++;
        return p_expression;
      }
      //string call get_string
      Parameter * check_string = get_STRING(i);
      if (check_null_l_r(check_string,i) == 1) {
        //cout << "left get string" << endl;
        left_parameter = check_string;
        my_operator = m_predicate_tokens[i];
        i++;
      }
      check_string = get_STRING(i);
      if (check_null_l_r(check_string,i) == 2) {
        //cout << "right get string" << endl;
        right_parameter = check_string;
        right_paren = m_predicate_tokens[i];
        Parameter * p_expression = new Expression_Parameter(left_paren, left_parameter, my_operator, right_parameter, right_paren);
        i++;
        return p_expression;
      }
      //expression--call a get_expression function
    }
    return NULL;
  }
  void get_Parameters(){
    for (int i = 0; i < (int) m_predicate_tokens.size(); i++) {
      check_predicate_start(i);
      //id-call get_id
      Parameter * check_expression = get_Expression(i);
      if (check_expression != NULL) {
        m_all_parameters.push_back(check_expression);
      }
      Parameter * check_id = get_ID(i);
      if (check_id != NULL) {
        m_all_parameters.push_back(check_id);
      }
      //string call get_string
      Parameter * check_string = get_STRING(i);
      if (check_string != NULL) {
        m_all_parameters.push_back(check_string);
      }
      //expression--call a get_expression function
    }
  }
  void toString(){
    for (int i = 0; i < (int) m_predicate_tokens.size(); i++) {
      if (i == 2) {
        break;
      }
      cout << m_predicate_tokens[i]->getValue();
    }
    for (int i = 0; i < (int) m_all_parameters.size(); i++) {
      m_all_parameters[i]->toString();
      if (i != ((int) m_all_parameters.size() - 1)) {
        cout << ",";
      }
    }
    cout << ")";
  }
};
class rules : public SFRQ {
public:
  vector<Token *> m_rule_tokens;
  vector<Predicate *> m_all_predicates;
  vector<Token *> m_predicate_tokens;
  vector<string> m_head_predicate;
  vector<vector<string>> m_body_predicates;
  //int m_rule_counter = 0;
  rules(vector<Token *> & rule_tokens):SFRQ(){m_rule_tokens = rule_tokens;}
  virtual ~rules()
  {
    // for(auto i : m_rule_tokens)
    // {
    //   delete i;
    // }
    // for(auto j : m_all_predicates)
    // {
    //   delete j;
    // }
    // for(auto k : m_predicate_tokens)
    // {
    //   delete k;
    // }
    // m_rule_tokens.clear();
    m_all_predicates.clear();
    // m_predicate_tokens.clear();
  }
  virtual string get_SFRQ_Type(){
    return "RULES";
  }
  bool check_end_Predicate(int i){
    if (m_rule_tokens[i]->getType() == "COMMA" && m_rule_tokens[i+1]->getType() == "ID" && m_rule_tokens[i+2]->getType() == "LEFT_PAREN") {
      return true;
    }
    return false;
  }
  bool string_or_id(const int & i)
  {
    if (m_rule_tokens[i]->getType() == "STRING" || m_rule_tokens[i]->getType() == "ID")
    {
      return true;
    }
    return false;
  }
  void get_Predicates(){
  //  ID LEFT_PAREN parameter parameterList RIGHT_PAREN

    if ((int) m_rule_tokens.size() == 0) {
      return;
    }
    //m_rule_counter++;
    int i = 0;
    // i++;
    vector<string> current_head_predicate;
    for (; m_rule_tokens[i]->getType() != "COLON_DASH"; i++)
    {
      if (string_or_id(i))
      {
        m_head_predicate.push_back(m_rule_tokens[i]->getValue());
      }
    }
    // m_head_predicate.push_back(current_head_predicate);
    // current_head_predicate.clear();
    // i++;
    for (; i < (int) m_rule_tokens.size(); i++) {
      if ((i+2) == (int) m_rule_tokens.size()) {
        m_predicate_tokens.push_back(m_rule_tokens[i]);
        m_predicate_tokens.push_back(m_rule_tokens[i+1]);
        Predicate * p = new Predicate(m_predicate_tokens);
        p->fill_str_predicate();
        m_body_predicates.push_back(p->m_str_predicate);
        p->get_Parameters();
        m_all_predicates.push_back(p);
        m_predicate_tokens.clear();
        break;
      }
      else if (check_end_Predicate(i)) {
        Predicate * p = new Predicate(m_predicate_tokens);
        p->fill_str_predicate();
        m_body_predicates.push_back(p->m_str_predicate);
        p->get_Parameters();
      //  m_all_predicates.push_back(p);
        int j = (int) m_predicate_tokens.size();
        for (int k = 0; k < j; k++) {
          m_predicate_tokens.pop_back();
        }
        m_all_predicates.push_back(p);
        //comma creates new predicate, period means end of predicates in general
      }
      else{
        m_predicate_tokens.push_back(m_rule_tokens[i]);
      }
    }
  }
  int avoid_begin(int i){
    if (i == 0) {
      i++;
    }
    return i;
  }
  virtual void toString(){
    // if (rule_counter != 0) {
    //   cout << "  ";
    // }
    if ((int) m_rule_tokens.size() == 0) {
      return;
    }
    cout << "  ";
    for (int i = 0; i < (int) m_rule_tokens.size(); i++) {
      cout << m_rule_tokens[i]->getValue();
      if ((m_rule_tokens[i+1]->getType() == "COLON_DASH")) {
        cout << " " << m_rule_tokens[i+1]->getValue() << " ";
        i++;
        break;
      }
    }
    for (int j = 0; j < (int) m_all_predicates.size() ; j++) {
      m_all_predicates[j]->toString();
      if (j != ((int) m_all_predicates.size() - 1)) {
        cout << ",";
      }
    }
    cout <<"." << endl;
    //cout << endl;
  }
};
class queries : public SFRQ {
public:
  vector<Token *> m_query_tokens;
  vector<Predicate *> m_all_query_predicates;
  vector<Token *> m_query_predicate;
  queries(vector<Token *> & query_tokens):SFRQ(){m_query_tokens = query_tokens;}
  virtual ~queries()
  {
    // for(auto i : m_query_tokens)
    // {
    //   delete i;
    // }
    for(auto j : m_all_query_predicates)
    {
      delete j;
    }
    // for(auto k : m_query_predicate)
    // {
    //   delete k;
    // }
    // m_query_predicate.clear();
    // m_query_tokens.clear();
    m_all_query_predicates.clear();
  }
  void get_query_vectors()
  {
    vector<string> temp_query_hold;
    string current_token_value;
    for (auto & i : m_query_tokens)
    {
      if ((i->getType() == "ID") || (i->getType() == "STRING"))
      {
        temp_query_hold.push_back(i->getValue());
      }
      if (i->getType() == "RIGHT_PAREN")
      {
        m_individual_queries = temp_query_hold;
        temp_query_hold.clear();
      }
    }
  }
  virtual string get_SFRQ_Type(){
    return "QUERIES";
  }
  void get_Predicates(){
  //  ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    //m_rule_counter++;
    int i = 0;
    for (; i < (int) m_query_tokens.size(); i++) {
      if (m_query_tokens[i]->getType() == "Q_MARK") {
        Predicate * p = new Predicate(m_query_predicate);
        p->get_Parameters();
      //  m_all_predicates.push_back(p);
        m_all_query_predicates.push_back(p);
        i++;
        break;
        //comma creates new predicate, period means end of predicates in general
      }
      else{
        m_query_predicate.push_back(m_query_tokens[i]);
      }
    }
  }
  virtual void toString(){
    for (int i = 0; i < (int) m_all_query_predicates.size(); i++) {
      if (i < (int) m_all_query_predicates.size()) {
        cout << "  ";
      }
      //cout << m_query_tokens[0]->getValue() << m_query_tokens[1]->getValue();
      m_all_query_predicates[i]->toString();
      cout << "?" << endl;
    }
  }
};

class DatalogProgram{
private:
  set<string> m_domain;
public:
  int m_rule_counter = 0;
  int m_query_counter = 0;
  vector<Token *> m_all_tokens;
  vector<SFRQ *> m_output;
  vector<Token *> m_scheme_tokens;
  vector<Token *> m_fact_tokens;
  vector<Token *> m_rule_tokens;
  vector<Token *> m_query_tokens;
  vector<rules> m_all_rules;
  // vector<Rule *> m_all_rules;
  DatalogProgram(vector<Token *> & all_tokens, vector<SFRQ *> & output)
  :m_all_tokens(all_tokens),
  m_output(output)
  {}
  virtual ~DatalogProgram()
  {
    for(auto i : m_all_tokens)
    {
      delete i;
    }
    m_all_tokens.clear();
    for(auto j : m_output)
    {
      delete j;
    }
    m_output.clear();
  }
  void toString(){
    bool query_first = false;
    bool rule_first = false;
    for (int i = 0; i < (int) m_output.size(); i++) {
      if ((m_output[i]->get_SFRQ_Type() == "RULES") && !rule_first) {
        cout << "Rules(" << m_rule_counter << "):" << endl;
        rule_first = true;
      }
      if ((m_output[i]->get_SFRQ_Type() == "QUERIES") && !query_first) {
        cout << "Queries(" << m_query_counter << "):" << endl;
        query_first = true;
      }
      m_output[i]->toString();
    }
    cout << "Domain(" << (int) m_domain.size() << "):" << endl;
    for (auto j: m_domain) {
      cout << "  " << j << endl;
    }
  }
  bool check_strings(string & to_check, int iterator){
    string STRING = "STRING";
    if ((to_check == STRING) && !m_domain.count((m_all_tokens[iterator]->getValue()))) {
      return true;
    }
    return false;
  }
  void get_queries(int & i){
    for (; m_all_tokens[i]->getType() != "EOF"; i++) {
      if (m_all_tokens[i]->getType() == "Q_MARK") {
        m_query_tokens.push_back(m_all_tokens[i]);
        queries * q = new queries(m_query_tokens);
        q->get_Predicates();
        q->get_query_vectors();
        m_output.push_back(q);
        m_query_counter++;
        //int size = (int) m_query_tokens.size();
        m_query_tokens.clear();
      }
      else{
        m_query_tokens.push_back(m_all_tokens[i]);
      }
    }
  }
  void get_SFRQ(){
    int i=0;
    i++;
    i++;
    for (; m_all_tokens[i]->getType() != "FACTS"; i++) {
      m_scheme_tokens.push_back(m_all_tokens[i]);
    }
    schemes * s = new schemes(m_scheme_tokens);
    s->get_scheme_vectors();
    m_output.push_back(s);
    i++;
    i++;
    for (; m_all_tokens[i]->getType() != "RULES"; i++) {
      string to_check = m_all_tokens[i]->getType();
      //cout << to_check << " " << STRING << endl;
      if  (check_strings(to_check,i)) {
        m_domain.insert(m_all_tokens[i]->getValue());
      }
      m_fact_tokens.push_back(m_all_tokens[i]);
    }
    facts * f = new facts(m_fact_tokens);
    f->get_all_tuples();
    m_output.push_back(f);
    i++;
    i++;
    //cout << endl << "Passed Tokens" << endl;
    for (; m_all_tokens[i]->getType() != "QUERIES"; i++) {
    //  cout << m_all_tokens[i]->getValue() << "PT";
      if (m_all_tokens[i]->getType() == "PERIOD") {
        rules * r = new rules(m_rule_tokens);
        r->get_Predicates();
        m_output.push_back(r);
        m_all_rules.push_back(*r);
        m_rule_counter++;
      //int size = (int) m_rule_tokens.size();
        m_rule_tokens.clear();
        //delete m_all_tokens[i];
        //i++;
      }
      else{
        m_rule_tokens.push_back(m_all_tokens[i]);
      //  cout << endl << "Rule Tokens" << endl;
      //  cout << endl;
      }
    }
    rules * r = new rules(m_rule_tokens);
    r->get_Predicates();
    m_output.push_back(r);
    // m_all_rules.push_back(*r);
    //cout << endl;
    i++;
    i++;
    get_queries(i);
  }
protected:
};
