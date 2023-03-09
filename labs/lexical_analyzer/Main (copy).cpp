#include "Token.h"
#include <vector>
#include <ctype.h>

Token * get_next_token(const char * file, int remaining_character_count, vector<Token *> & token_list, int & current_line_number){
  Token * found_token = NULL;
  //cout << file[0] << endl;
  for (auto i : token_list) {
    //cout << i->getType() << endl;
    if (i->identify(file, remaining_character_count, current_line_number, found_token)) {
      return found_token;
    }
  }
  return found_token;
}


void analyzer(const string & file, vector<Token *> & priority_token_list, vector<Token *> & found_tokens){
  int current_line_number = 1;
  int character_counter = 0;
  const int input_length = (int) file.size() - 1;
  while (character_counter < (input_length)) {
    //cout << file.size() - character_counter << endl;
    Token * found_token = get_next_token(&file[character_counter], (input_length - character_counter), priority_token_list, current_line_number);
    // if (found_token == NULL) {
    //   cout << "null token found" << endl;
    //   break;
    // }
    // else {
    //   found_token->ToString();
    // }
    //cout << character_counter << " " << input_length - character_counter << " = remaining characters." << endl;
    character_counter += (found_token->getValue().size());
    if (found_token->getType() != "WHITESPACE") {
      found_tokens.push_back(found_token);
    }
    else {
      delete found_token;
    }
  }
  found_tokens.push_back(new Token("EOF","",current_line_number));
}

void initialize_priority_token_list(vector <Token *> & priority_token_list){
  priority_token_list.push_back(new Comma());
  priority_token_list.push_back(new Period());
  priority_token_list.push_back(new Question_Mark());
  priority_token_list.push_back(new Left_Parentheses());
  priority_token_list.push_back(new Right_Parentheses());
  priority_token_list.push_back(new Multiply());
  priority_token_list.push_back(new Add());
  priority_token_list.push_back(new Colon_Dash());
  priority_token_list.push_back(new Colon());
  priority_token_list.push_back(new Queries());
  priority_token_list.push_back(new Schemes());
  priority_token_list.push_back(new Facts());
  priority_token_list.push_back(new Rules());
  priority_token_list.push_back(new ID());
  priority_token_list.push_back(new String());
  priority_token_list.push_back(new Block_Comment());
  priority_token_list.push_back(new Comment());
  priority_token_list.push_back(new Whitespace());
  //priority_token_list.push_back(new MyEOF());
  priority_token_list.push_back(new Undefined());
}

void print_tokens(vector <Token *> & found_tokens){
  for (auto i : found_tokens) {
    i->ToString();
  }
  cout << "Total Tokens = " << found_tokens.size() << endl;
}

int main(int argc, char * argv[]){
  vector <Token *> token_list;
  vector <Token *> found_tokens;
  ifstream in(argv[1]);
  string file((istreambuf_iterator<char>(in)),(istreambuf_iterator<char>()));
  //cout << file.size() << endl;
  initialize_priority_token_list(token_list);
  analyzer(file, token_list, found_tokens);
  print_tokens(found_tokens);
  for (auto j : found_tokens) {
    delete j;
  }
  for (auto j : token_list) {
    delete j;
  }


  // for (auto c:line) {
  //   //pass the string line into all of the individual boolean functions so that each function can check the input.ds
  // }
  return 0;
}
