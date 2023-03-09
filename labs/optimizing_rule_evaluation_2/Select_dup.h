#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Select_dup
{
public:
  string m_name_of_variable;
  vector<int> m_columns_of_variables_of_duplicates;
  Select_dup(string & name_of_variable, vector<int> & columns_of_variables):
  m_name_of_variable(name_of_variable),
  m_columns_of_variables_of_duplicates(columns_of_variables){}
  ~Select_dup(){}
private:
};
