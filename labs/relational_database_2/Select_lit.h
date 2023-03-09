#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Select_lit
{
public:
  string m_name_of_literal;
  int m_column_of_literal;
  Select_lit(string & name_of_literal, int column_of_literal):
  m_name_of_literal(name_of_literal),
  m_column_of_literal(column_of_literal){}
  ~Select_lit(){}
private:
};
