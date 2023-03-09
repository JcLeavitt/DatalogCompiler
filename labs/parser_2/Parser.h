#pragma once
#include <vector>
#include <string>
#include <set>
#include "Token.h"
using namespace std;
class SFRQ {
public:
  SFRQ(){}
  virtual void toString(){}
  virtual string get_SFRQ_Type(){return "";}
private:
};
class schemes : public SFRQ {
public:
  vector <Token *> m_scheme_tokens;
  schemes(vector <Token *> & scheme_tokens):SFRQ(){m_scheme_tokens = scheme_tokens;}
  virtual string get_SFRQ_Type(){
    return "SCHEMES";
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
  virtual void toString(){}
};
class ID_Parameter : public Parameter{
public:
  Token * m_id;
  ID_Parameter(Token * & id){m_id = id;}
  virtual void toString(){
    cout << m_id->getValue();
  }
};
class STRING_Parameter : public Parameter{
public:
  Token * m_string;
  STRING_Parameter(Token * & string){m_string = string;}
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
  vector<Parameter *> m_all_parameters;
  Predicate(vector<Token *> & predicate_tokens){m_predicate_tokens = predicate_tokens;}
  void check_predicate_start(int & i){
    if (m_predicate_tokens[i]->getType() == "ID" && m_predicate_tokens[i+1]->getType() == "LEFT_PAREN") {
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
  //int m_rule_counter = 0;
  rules(vector<Token *> & rule_tokens):SFRQ(){m_rule_tokens = rule_tokens;}
  virtual string get_SFRQ_Type(){
    return "RULES";
  }
  bool check_end_Predicate(int i){
    if (m_rule_tokens[i]->getType() == "COMMA" && m_rule_tokens[i+1]->getType() == "ID" && m_rule_tokens[i+2]->getType() == "LEFT_PAREN") {
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
    i++;
    for (; m_rule_tokens[i]->getType() != "COLON_DASH"; i++){}
    i++;
    for (; i < (int) m_rule_tokens.size(); i++) {
      if ((i+2) == (int) m_rule_tokens.size()) {
        m_predicate_tokens.push_back(m_rule_tokens[i]);
        m_predicate_tokens.push_back(m_rule_tokens[i+1]);
        Predicate * p = new Predicate(m_predicate_tokens);
        p->get_Parameters();
        m_all_predicates.push_back(p);
        break;
      }
      else if (check_end_Predicate(i)) {
        Predicate * p = new Predicate(m_predicate_tokens);
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
  // vector<Rule *> m_all_rules;
  DatalogProgram(vector<Token *> & all_tokens, vector<SFRQ *> & output)
  :m_all_tokens(all_tokens),
  m_output(output)
  {}
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
        m_output.push_back(q);
        m_query_counter++;
        int size = (int) m_query_tokens.size();
        for (int j = 0; j < size; j++) {
          m_query_tokens.pop_back();
        }
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
        m_rule_counter++;
        int size = (int) m_rule_tokens.size();
        for (int j = 0; j < size; j++) {
          m_rule_tokens.pop_back();
        }
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
    //cout << endl;
    i++;
    i++;
    get_queries(i);
  }
protected:
};
