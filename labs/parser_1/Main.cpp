#include "old_main.h"
#include "analyzer.h"

bool SCHEMES(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "SCHEMES") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool FACTS(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "FACTS") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool RULES(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "RULES") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool QUERIES(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "QUERIES") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool ID(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool LEFT_PAREN(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "LEFT_PAREN") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool RIGHT_PAREN(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "RIGHT_PAREN") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool COLON(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COLON") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool COLON_DASH(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COLON_DASH") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool PERIOD(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "PERIOD") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool COMMA(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COMMA") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool STRING(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "STRING") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool ADD(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ADD") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool MULTIPLY(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "MULTIPLY") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool Q_MARK(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "Q_MARK") {
    delete tokens_to_parse.front();
    tokens_to_parse.pop();
    return true;
  }
  return false;
}

bool stringList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COMMA") {
    return (COMMA(tokens_to_parse) && STRING(tokens_to_parse) && stringList(tokens_to_parse));
  }
  return true;
}

bool operator_token(queue <Token *> & tokens_to_parse){
  return (ADD(tokens_to_parse) || MULTIPLY(tokens_to_parse));
}

bool parameter(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "LEFT_PAREN") { //This if statement essentially calls the "expression" function.
    return (LEFT_PAREN(tokens_to_parse) && parameter(tokens_to_parse) && operator_token(tokens_to_parse) && parameter(tokens_to_parse) && RIGHT_PAREN(tokens_to_parse));
  }
  return (ID(tokens_to_parse) || STRING(tokens_to_parse));
}

bool parameterList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COMMA") {
    return (COMMA(tokens_to_parse) && parameter(tokens_to_parse) && parameterList(tokens_to_parse));
  }
  return true;
}

bool predicate(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (ID(tokens_to_parse) && LEFT_PAREN(tokens_to_parse) && parameter(tokens_to_parse) && parameterList(tokens_to_parse) && RIGHT_PAREN(tokens_to_parse));
  }
  return false;
}

bool query(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (predicate(tokens_to_parse) && Q_MARK(tokens_to_parse));
  }
  return false;
}

bool queryList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (query(tokens_to_parse) && queryList(tokens_to_parse));
  }
  return true;
}

bool predicateList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COMMA") {
    return (COMMA(tokens_to_parse) && predicate(tokens_to_parse) && predicateList(tokens_to_parse));
  }
  return true;
}

bool idList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "COMMA") {
    return (COMMA(tokens_to_parse) && ID(tokens_to_parse) && idList(tokens_to_parse));
  }
  return true;
}

bool headPredicate(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (ID(tokens_to_parse) && LEFT_PAREN(tokens_to_parse) && ID(tokens_to_parse) && idList(tokens_to_parse) && RIGHT_PAREN(tokens_to_parse));
  }
  return false;
}

bool rule(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (headPredicate(tokens_to_parse) && COLON_DASH(tokens_to_parse) && predicate(tokens_to_parse) && predicateList(tokens_to_parse) && PERIOD(tokens_to_parse));
  }
  return false;
}

bool ruleList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (rule(tokens_to_parse) && ruleList(tokens_to_parse));
  }
  return true;
}

bool fact(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (ID(tokens_to_parse) && LEFT_PAREN(tokens_to_parse) && STRING(tokens_to_parse) && stringList(tokens_to_parse) && RIGHT_PAREN(tokens_to_parse) && PERIOD(tokens_to_parse));
  }
  return false;
}

bool factList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (fact(tokens_to_parse) && factList(tokens_to_parse));
  }
  return true;
}

bool scheme(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (ID(tokens_to_parse) && LEFT_PAREN(tokens_to_parse) && ID(tokens_to_parse) && idList(tokens_to_parse) && RIGHT_PAREN(tokens_to_parse));
  }
  return false;
}

bool schemeList(queue <Token *> & tokens_to_parse){
  if (tokens_to_parse.front()->getType() == "ID") {
    return (scheme(tokens_to_parse) && schemeList(tokens_to_parse));
  }
  return true;
}

bool datalog_check_two(queue <Token *> & tokens_to_parse){
  return (RULES(tokens_to_parse) && COLON(tokens_to_parse) && ruleList(tokens_to_parse) && QUERIES(tokens_to_parse) && COLON(tokens_to_parse) && query(tokens_to_parse) && queryList(tokens_to_parse));
}

bool datalog_check_one(queue <Token *> & tokens_to_parse){
  return (SCHEMES(tokens_to_parse) && COLON(tokens_to_parse) && scheme(tokens_to_parse) && schemeList(tokens_to_parse) && FACTS(tokens_to_parse) && COLON(tokens_to_parse) && factList(tokens_to_parse));
}

bool datalogProgram(queue <Token *> & tokens_to_parse){
  return (datalog_check_one(tokens_to_parse) && datalog_check_two(tokens_to_parse));
}

int main(int argc, char * argv[])
{
  vector <Token *> tokens_from_analyzer =  analyzer_tokens(argv[1]);
  queue <Token *> token_queue;
  for (auto i : tokens_from_analyzer) {
    token_queue.push(i);
  }
  if (!datalogProgram(token_queue)) {
    cout << "Failure!" << endl;
    cout << "  ";
    token_queue.front()->ToString();
    return 0;
  }
  if (token_queue.front()->getType() == "EOF") {
    delete token_queue.front();
    token_queue.pop();
    cout << "Success!" << endl;
  }
  else if (!token_queue.empty()) {
    cout << "Failure!" << endl;
    cout << "  ";
    token_queue.front()->ToString();
    return 0;
  }

  return 0;
}
