#include "old_main.h"
#include "analyzer.h"
#include "Database.h"
#include <sstream>

// void test1(Relation & abcd){ //rename a relation from "abcd" to "dabc"
//   vector<string> rename_scheme;
//   rename_scheme.push_back("d");
//   rename_scheme.push_back("a");
//   rename_scheme.push_back("b");
//   rename_scheme.push_back("c");
//   Relation abcd1 = abcd.get_rename(rename_scheme);
//   cout << "rename a relation from \"abcd\" to \"dabc\". The schema should change, but the tuples should all remain the same.\n";
//   abcd1.toString();
//   cout << "Passed" << endl << endl;
// }
// void test2(Relation & abcd){ //project an "abcd" schema relation on "c" and "a" or (2,0)
//   vector<int> project_columns;
//   project_columns.push_back(2);
//   project_columns.push_back(0);
//   Relation abcd1 = abcd.get_project(project_columns);
//   cout << "project an \"abcd\" schema relation on \"c\" and \"a\" or (2,0).\nThe schema should change to \"ca\", and the remaining tuples should be (a,c)-->(3,1),(7,5),(11,9),(15,13), and (19,17).\n";
//   abcd1.toString();
//   cout << "Passed" << endl << endl;
// }
// void test3(Relation & abcd){ //select an "abcd" schema on "c" and "15", or ("15",2)
//   Relation abcd1 = abcd.get_select("15", 2);
//   cout << "select an \"abcd\" schema relation on \"c\" and \"15\" or (\"15\",2).\nThe schema should remain \"abcd\", and the only tuple remaining should be (13,14,15,16).\n";
//   abcd1.toString();
//   cout << "Passed" << endl << endl;
// }
// void test4(Relation & abc){ //select an "abc" schema on "b" and "c" or (1,2)
//   Relation abc1 = abc.get_select(1,2);
//   cout << "select an \"abc\" schema relation on \"b\" and \"c\" or (1,2).\nThe schema should remain \"abc\", and tuples (0-0-0),(0-1-1),(1-0-0), and (1-1-1) should remain.\n";
//   abc1.toString();
//   cout << "Passed" << endl << endl;
// }
// void test5(Relation & abc){ //select an "abc" schema on "a" and "b" or (0,1) then again on "a" and "1" or ("1",0)
//   Relation abc1 = abc.get_select(0,1);
//   Relation abc2 = abc1.get_select("1",0);
//   cout << "select an \"abc\" schema relation on \"a\" and \"b\" or (0,1).\nThen select again on the resulting relaion with \"a\" and \"1\" or (\"1\",0).\nThe schema should remain \"abc\", and tuples (1-1-0) and (1-1-1) should remain.\n";
//   abc2.toString();
//   cout << "Passed" << endl << endl;
// }
// void test6(Relation & abc){ //project an "abc" schema on "a" and "b" or (0,1) then select on "a" and "b" or (0,1)
//   vector<int> project_columns;
//   project_columns.push_back(0);
//   project_columns.push_back(1);
//   Relation abc1 = abc.get_project(project_columns);
//   Relation abc2 = abc1.get_select(0,1);
//   cout << "project an \"abc\" schema relation on \"a\" and \"b\" or (0,1).\nThen select on \"a\" and \"b\" or (\"0\",1).\nThe schema should change to \"ab\", and the remaining tuples should be (0-0) and (1-1).\n";
//   abc2.toString();
//   cout << "Passed" << endl << endl;
// }
// void test7(Relation & abc){ //project an "abc" schema on "a" and "b" or (0,1) then select on "a" and "0" or ("0",0)
//   vector<int> project_columns;
//   project_columns.push_back(0);
//   project_columns.push_back(1);
//   Relation abc1 = abc.get_project(project_columns);
//   Relation abc2 = abc1.get_select("0",0);
//   cout << "project an \"abc\" schema relation on \"a\" and \"b\" or (0,1).\nThen select on \"a\" and \"0\" or (\"0\",0).\nThe schema should change to \"ab\", and the remaining tuples should be (0-0) and (0-1).\n";
//   abc2.toString();
//   cout << "Passed" << endl << endl;
// }
// void test8(Relation & abc){ //select an "abc" schema on "b" and "c" or (1,2) then project on "b" or (1)
//   vector<int> project_columns;
//   //project_columns.push_back(0);
//   project_columns.push_back(1);
//   Relation abc1 = abc.get_select(1,2);
//   Relation abc2 = abc1.get_project(project_columns);
//   cout << "select an \"abc\" schema relation on \"b\" and \"c\" or (1,2).\nThen project on \"b\" (1).\nThe schema should change to \"b\", and the remaining tuples should be (0) and (1).\n";
//   abc2.toString();
//   cout << "Passed" << endl << endl;
// }
// void test9(Relation & abc){ //select an "abc" schema on "b" and "0" or ("0",1) then project on "c" and "a" or (2,0)
// vector<int> project_columns;
// project_columns.push_back(0);
// project_columns.push_back(2);
// Relation abc1 = abc.get_select("0",1);
// Relation abc2 = abc1.get_project(project_columns);
// cout << "select an \"abc\" schema relation on \"b\" and \"0\" or (\"0\",1).\nThen project on \"a\" and \"c\" (0,2).\nThe schema should change to \"ac\", and the remaining tuples should be (0-0),(0-1),(1-0), and (1-1).\n";
// abc2.toString();
// cout << "Passed" << endl << endl;
// }
// void test10(Relation & abc){ //rename an "abc" schema to "xyz" then select on "x" and "z" or (0,2) then select on "x" and "y" or (0,1)
//   vector<string> xyz_scheme;
//   xyz_scheme.push_back("x");
//   xyz_scheme.push_back("y");
//   xyz_scheme.push_back("z");
//   vector<int> project_columns;
//   //project_columns.push_back(0);
//   project_columns.push_back(1);
//   Relation abc0 = abc.get_rename(xyz_scheme);
//   Relation abc1 = abc0.get_select(0,2);
//   Relation abc2 = abc1.get_select(0,1);
//   cout << "rename an \"abc\" schema to \"xyz\" then select on \"x\" and \"z\" or (\"0\",2).\nThen select on \"x\" and \"y\" or (0,1).\nThe schema should remain \"abc\", and the remaining tuples should be (0-0-0) and (1-1-1).\n";
//   abc2.toString();
//   cout << "Passed" << endl << endl;
// }

int main(int argc, char * argv[]){
  DatalogProgram * initial_program = main_parser(argv[1]);
  vector<Relation> relations_to_query_with;
  Database master(initial_program,relations_to_query_with);
  master.create_starting_relations();
  master.start_queries();
  master.toString();
  //master.check_stuff();
  vector<string> tuples;
  set<Tuple> all_tuples;
  //master.~Database();
  // for (int i = 1; i < 21; i++) {
  //   stringstream ss;
  //   ss << i;
  //   string str = ss.str();
  //   tuples.push_back(str);
  //   if ((i%4) == 0) {
  //     Tuple a(tuples);
  //     all_tuples.insert(a);
  //     tuples.clear();
  //   }
  // }
  // vector<string> scheme;
  // scheme.push_back("a");
  // scheme.push_back("b");
  // scheme.push_back("c");
  // scheme.push_back("d");
  //
  // Relation abcd(all_tuples, scheme);
  //
  // vector<string> abc_scheme;
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // abc_scheme.push_back("c");
  // vector<string> abc_objects;
  // set<Tuple> abc_tuples;
  // abc_objects.push_back("0");
  // abc_objects.push_back("0");
  // abc_objects.push_back("0");
  // Tuple t0(abc_objects);
  // abc_tuples.insert(t0);
  // abc_objects.clear();
  // abc_objects.push_back("0");
  // abc_objects.push_back("0");
  // abc_objects.push_back("1");
  // Tuple t1(abc_objects);
  // abc_tuples.insert(t1);
  // abc_objects.clear();
  // abc_objects.push_back("0");
  // abc_objects.push_back("1");
  // abc_objects.push_back("0");
  // Tuple t2(abc_objects);
  // abc_tuples.insert(t2);
  // abc_objects.clear();
  // abc_objects.push_back("0");
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // Tuple t3(abc_objects);
  // abc_tuples.insert(t3);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("0");
  // abc_objects.push_back("0");
  // Tuple t4(abc_objects);
  // abc_tuples.insert(t4);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("0");
  // abc_objects.push_back("1");
  // Tuple t5(abc_objects);
  // abc_tuples.insert(t5);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_objects.push_back("0");
  // Tuple t6(abc_objects);
  // abc_tuples.insert(t6);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // Tuple t7(abc_objects);
  // abc_tuples.insert(t7);
  // abc_objects.clear();
  // Relation abc(abc_tuples,abc_scheme);
  // //cout << "Selected on columns: " << identifier_1 << " and " << identifier_2 << endl;
  // cout << "Tests 1-3 will be run on the following relation: " << endl;
  // abcd.toString();
  // cout << endl << "Test1" << endl;
  // test1(abcd);
  // cout << "Test2" << endl;
  // test2(abcd);
  // cout << "Test3" << endl;
  // test3(abcd);
  // cout << "Tests 4-10 will be run on the following relation: " << endl;
  // abc.toString();
  // cout << endl << "Test4" << endl;
  // test4(abc);
  // cout << "Test5" << endl;
  // test5(abc);
  // cout << "Test6" << endl;
  // test6(abc);
  // cout << "Test7" << endl;
  // test7(abc);
  // cout << "Test8" << endl;
  // test8(abc);
  // cout << "Test9" << endl;
  // test9(abc);
  // cout << "Test10" << endl;
  // test10(abc);



  return 0;
}
