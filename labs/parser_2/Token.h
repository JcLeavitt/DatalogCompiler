#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Token{
public:
  Token(string token_type)
  :m_token_type(token_type),
  m_token_value(),
  m_token_line_number(-1)
  {}
  Token(string token_type, string token_value, int token_line_number)
  :m_token_type(token_type),
  m_token_value(token_value),
  m_token_line_number(token_line_number)
  {}
    virtual ~Token(){}
  virtual string getType(){
    return m_token_type;
  }
  virtual string getValue(){
    return m_token_value;
  }
  virtual int getLineNumber(){
    return m_token_line_number;
  }
  virtual void ToString(){
      cout << "(" << m_token_type << "," << "\"" << m_token_value << "\"," << m_token_line_number << ")" << endl;
    return;
  }
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token)
  {
    if(input[0] == m_token_value[0]){
      found_token = new Token(m_token_type, m_token_value, current_line_number);
      return true;
    }
    return false;
  }

protected:
  string m_token_type;
  string m_token_value;
  int m_token_line_number;
};

class Period : public Token{
public:
  Period():Token("PERIOD"){m_token_value = ".";}
};

class Comma : public Token{
public:
  Comma() : Token("COMMA"){m_token_value = ",";}
};

class Question_Mark : public Token{
public:
  Question_Mark() : Token("Q_MARK"){m_token_value = "?";}
};

class Left_Parentheses : public Token{
public:
  Left_Parentheses() : Token("LEFT_PAREN"){m_token_value = "(";}
};

class Right_Parentheses : public Token{
public:
  Right_Parentheses() : Token("RIGHT_PAREN"){m_token_value = ")";}
};

class Colon_Dash : public Token{
public:
  Colon_Dash() : Token("COLON_DASH"){m_token_value = ":-";}
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    if(input[0]==':'){
      if (input[1] == '-') {
        found_token = new Token(m_token_type, m_token_value, current_line_number);
        return true;
      }
      return false;
    }
    return false;
  }
};

class Colon : public Token{
public:
  Colon() : Token("COLON"){m_token_value = ":";}
};

class Multiply : public Token{
public:
  Multiply() : Token("MULTIPLY"){m_token_value = "*";}
};

class Add : public Token{
public:
  Add() : Token("ADD"){m_token_value = "+";}
};

class Schemes : public Token{
public:
  Schemes() : Token("SCHEMES"){m_token_value = "Schemes";}
  bool extra_character_check(const char * input, int char_counter){
    if (isalpha(input[char_counter]) || isdigit(input[char_counter])) {
      return false;
    }
    return true;
  }
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    if (input[char_counter++] == 'S') {
      if (input[char_counter++] == 'c') {
        if (input[char_counter++] == 'h') {
          if (input[char_counter++] == 'e') {
            if (input[char_counter++] == 'm') {
              if (input[char_counter++] == 'e') {
                if (input[char_counter++] == 's') {
                  found_token = new Token(m_token_type, m_token_value, current_line_number);
                  return extra_character_check(input, char_counter);
                }
                return false;
              }
              return false;
            }
            return false;
          }
          return false;
        }
        return false;
      }
      return false;
    }
    return false;
  }
};

class Facts : public Token{
public:
  Facts() : Token("FACTS"){m_token_value = "Facts";}
  bool extra_character_check(const char * input, int char_counter){
    if (isalpha(input[char_counter]) || isdigit(input[char_counter])) {
      return false;
    }
    return true;
  }
 virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
   int char_counter = 0;
   if (input[char_counter++] == 'F') {
     if (input[char_counter++] == 'a') {
       if (input[char_counter++] == 'c') {
         if (input[char_counter++] == 't') {
           if (input[char_counter++] == 's') {
             found_token = new Token(m_token_type, m_token_value, current_line_number);
             return extra_character_check(input, char_counter);
           }
           return false;
         }
         return false;
       }
       return false;
     }
     return false;
   }
   return false;
  }
};

class Rules : public Token{
public:
  Rules() : Token("RULES"){m_token_value = "Rules";}
  bool extra_character_check(const char * input, int char_counter){
    if (isalpha(input[char_counter]) || isdigit(input[char_counter])) {
      return false;
    }
    return true;
  }
 virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
   int char_counter = 0;
   if (input[char_counter++] == 'R') {
     if (input[char_counter++] == 'u') {
       if (input[char_counter++] == 'l') {
         if (input[char_counter++] == 'e') {
           if (input[char_counter++] == 's') {
             found_token = new Token(m_token_type, m_token_value, current_line_number);
             return extra_character_check(input, char_counter);
           }
           return false;
         }
         return false;
       }
       return false;
     }
     return false;
   }
   return false;
  }
};

class Queries : public Token{
public:
  Queries() : Token("QUERIES"){m_token_value = "Queries";}
  bool extra_character_check(const char * input, int char_counter){
    if (isalpha(input[char_counter]) || isdigit(input[char_counter])) {
      return false;
    }
    return true;
  }
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    if (input[char_counter++] == 'Q') {
      if (input[char_counter++] == 'u') {
        if (input[char_counter++] == 'e') {
          if (input[char_counter++] == 'r') {
            if (input[char_counter++] == 'i') {
              if (input[char_counter++] == 'e') {
                if (input[char_counter++] == 's') {
                    found_token = new Token(m_token_type, m_token_value, current_line_number);
                    return extra_character_check(input,char_counter);
                }
                return false;
              }
              return false;
            }
            return false;
          }
          return false;
        }
        return false;
      }
      return false;
    }
    return false;
  }
};

class ID : public Token{
public:
  ID() : Token("ID"){}
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    string token_value = "";
    if (isalpha(input[char_counter])) {
      token_value = input[char_counter];
      char_counter++;
      while (isalpha(input[char_counter]) | isdigit(input[char_counter])) {
        token_value += input[char_counter];
        char_counter++;
      }
      found_token = new Token(m_token_type, token_value, current_line_number);
      return true;
    }
    return false;
  }
};

class String : public Token{
public:
  String() : Token("STRING"){}
  bool apostrophe_checker(const char * input, int apostrophe_counter){
    if ((apostrophe_counter % 2) == 0) {
      return true;
    }
    return false;
  }
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    string token_value = "";
    int apostrophe_counter = 0;
    int starting_line_number = current_line_number;
    if (input[char_counter] == '\'') {
      token_value = input[char_counter];
      do {
        //cout << "string input_size " << input_size << endl;
        char_counter++;
        if (input_size-char_counter < 1) {
          found_token = new Token("UNDEFINED", token_value, starting_line_number);
          return true; //string reached EOF before the closing '\''...
        }
        if (input[char_counter] == '\n') {
          //token_value += input[char_counter];
          //cout << input[char_counter] << input[char_counter+1] <<input[char_counter+2]<< "STRING changing line number from " << current_line_number;
          current_line_number++;
          //cout << " to " << current_line_number << endl;
        }
        if ((input[char_counter] == '\'') && ((input[char_counter+1] == '\''))) {
          token_value += input[char_counter++];
          apostrophe_counter += 2;
        }
        else if (input[char_counter] == '\'') {
          apostrophe_counter++;
        }
        token_value += input[char_counter];
      } while (apostrophe_checker(input,apostrophe_counter));
      found_token = new Token(m_token_type, token_value, starting_line_number);
      return true;
    }
    return false;
  }
};

class Comment : public Token{
public:
  Comment() : Token("COMMENT"){}
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    string token_value = "";
    if (input[char_counter] == '#') {
      token_value += input[char_counter];
      char_counter++;
      if (input[char_counter] == '|') {
        return false;
      }
      while ((input[char_counter] != '\n') && char_counter != input_size) {
        token_value += input[char_counter];
        char_counter++;
      }
      found_token = new Token(m_token_type, token_value, current_line_number);
      return true;
    }
    return false;
  }
};



class Block_Comment : public Token{
public:
  Block_Comment() : Token("COMMENT"){}
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    string token_value = "";
    int starting_line_number = current_line_number;
    if (input[char_counter] == '#') {
      token_value += input[char_counter];
      char_counter++;
      if (input[char_counter] == '|') {
        token_value += input[char_counter];
        char_counter++;
        do {
          if ((input[char_counter] == '|') && (input[char_counter + 1] == '#')) {
            token_value += input[char_counter++];
            token_value += input[char_counter];
            found_token = new Token(m_token_type, token_value, starting_line_number);
            return true;
          }
          if (input[char_counter] == '\n') {
            //cout <<  input[char_counter] << input[char_counter+1] << input[char_counter+2] <<"BLOCK COMMENT changing line number from " << current_line_number;
            current_line_number++;
            //cout << " to " << current_line_number << endl;
          }
          token_value += input[char_counter];
          char_counter++;
          if (input_size-char_counter < 1) {
            found_token = new Token("UNDEFINED", token_value, starting_line_number);
            return true;
          }
        } while (char_counter != input_size);
        return false;
      }
      return false;
    }
    return false;
  }
};

// class MyEOF : public Token{
// public:
//   MyEOF() : Token("EOF"){m_token_value = "";}
//   virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
//     //cout << input[0] << endl << input_size << endl;
//     if (0 == input_size - 1) {
//       found_token = new Token(m_token_type, m_token_value, current_line_number);
//       return true;
//     }
//     return false;
//   }
// };

class Whitespace : public Token{
public:
  Whitespace() : Token("WHITESPACE"){}
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    int char_counter = 0;
    string token_value = "";
    int starting_line_number = current_line_number;
    if (input_size < 1){
      return false;
    }
    if (isspace(input[char_counter])) {
      while (isspace(input[char_counter])) {
        token_value += input[char_counter];
        if (input[char_counter] == '\n') {
          //cout << input[char_counter] << input[char_counter+1] <<input[char_counter+2]<<input[char_counter+3]<< "WHITESPACE changing line number from " << current_line_number;
          current_line_number++;
          //cout << " to " << current_line_number << endl;
        }
        char_counter++;
        if (input_size-char_counter < 1){
          break;
        }
      }
      //cout << "whitespace input size " << input_size << endl;
      found_token = new Token(m_token_type, token_value, starting_line_number);
      return true;
    }
    return false;
  }
};

class Undefined : public Token{
public:
  Undefined() : Token("UNDEFINED"){}
  virtual bool identify(const char * input, int input_size, int & current_line_number,Token * & found_token){
    string token_value(1,input[0]);
    if (token_value == "") {
      return false;
    }
    found_token = new Token(m_token_type, token_value, current_line_number);
    return true;
  }
};
