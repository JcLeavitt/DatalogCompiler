#include "old_main.h"
#include "analyzer.h"
#include "Database.h"
#include <sstream>

// void test1( Relation & abc1, Relation & abc2){ //union two different relations with scheme "abc"
//   Relation R = abc1.get_union(abc2);
//   cout << "union two different relations with scheme \"abc\"";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test2( Relation & abc1, Relation & def){ //natural join on schemes "abc" and "def" test cross product, same col width
//   Relation R = abc1.get_natural_join(def);
//   cout << "natural join on schemes \"abc\" and \"def\" test cross product with same col width schemes." << endl;
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test3( Relation & abc1,  Relation & aef1){ //natural join on scheme "abc" and "aef" where none of the values of 'a' in the first scheme should match
// //those of 'a' in the second scheme so we get back an empty relation.
//   Relation R = abc1.get_natural_join(aef1);
//   cout << "natural join on scheme \"abc\" and \"aef\" where none of the values of \'a\' in the first scheme should match those of \'a\' in the second scheme so we get back an empty relation.\n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test4( Relation & abc1, Relation & aef2){ //natural join on scheme "abc" and "aef" where 'a' in both schemes should match at least one tuple
//   Relation R = abc1.get_natural_join(aef2);
//   cout << "natural join on scheme \"abc\" and \"aef\" where \'a\' in both schemes should match at least one tuple\n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test5(  Relation & abc3,   Relation & eaf){ //natural join on scheme "abc" and "eaf" where 'a' in both schemes will match more than one tuple
// //this is testing natural join on the same variable in different columns of each scheme.
//   Relation R = abc3.get_natural_join(eaf);
//   cout << "natural join on scheme \"abc\" and \"eaf\" where \'a\' in both schemes will match more than one tuple.\n This is testing natural join on the same variable in different columns of each scheme.\n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test6(  Relation & abc1,   Relation abd){ //natural join on scheme "abc" and "abd" where at least one tuple matches, checks natural join on two columns
//   Relation R = abc1.get_natural_join(abd);
//   cout << "Natural join on scheme \"abc\" and \"abd\" where at least one tuple matches.\n Checks natural join on two columns\n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test7(  Relation & abc1,  Relation & abc3){ //natural join on scheme "abc" and "abc" where at least one tuple matches checks natural join on all columns at once
//   Relation R = abc1.get_natural_join(abc3);
//   cout << "natural join on scheme \"abc\" and \"abc\" where at least one tuple matches checks natural join on all columns at once\n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test8(  Relation & abc1,  Relation & abc2){ //natural join on "abc" and "abc" where none of the tuples match, should return an empty relation
//   Relation R = abc1.get_natural_join(abc2);
//   cout << "natural join on \"abc\" and \"abc\" where none of the tuples match, should return an empty relation. \n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test9(  Relation & abcde,   Relation & ab){ //natural join on "abcde" and "ab", where at least one tuple matches, testing natural join on diff scheme sizes
//   Relation R = abcde.get_natural_join(ab);
//   cout << "natural join on \"abcde\" and \"ab\", where at least one tuple matches, testing natural join on diff scheme sizes. \n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }
// void test10(  Relation & fg,   Relation & abcde){ //natural join on "fg" and "abcde" tests cross product part of natural join on diff size schemes
//   Relation R = fg.get_natural_join(abcde);
//   cout << "natural join on \"fg\" and \"abcde\" tests cross product part of natural join on diff size schemes. \n";
//   cout << endl;
//   R.toString();
//   cout << "Passed" << endl << endl;
// }

int main(int argc, char * argv[]){
  // vector<string> tuples;
  // set<Tuple> all_tuples;

  DatalogProgram * initial_program = main_parser(argv[1]);
  vector<Relation> relations_to_query_with;
  Database master(initial_program,relations_to_query_with);
  master.create_starting_relations();
  master.evaluate_rules();
  master.start_queries();
  master.toString();

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

  // Relation abcd(all_tuples, scheme);

  // vector<string> abc_scheme;
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // abc_scheme.push_back("c");
  // Tuple abc_objects;
  // set<Tuple> abc_tuples;
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("2");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // Relation abc1("hi",abc_tuples,abc_scheme);
  // abc_tuples.clear();
  // abc_scheme.clear();
  //
  // abc_objects.push_back("2");
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("1");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // abc_scheme.push_back("c");
  // Relation abc2("hi",abc_tuples,abc_scheme);
  // abc_tuples.clear();
  // abc_scheme.clear();
  //
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // abc_scheme.push_back("d");
  // Relation abd("hi",abc_tuples,abc_scheme);
  // abc_tuples.clear();
  // abc_scheme.clear();
  //
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // abc_scheme.push_back("c");
  // Relation abc3("hi",abc_tuples,abc_scheme);
  // abc_tuples.clear();
  // abc_scheme.clear();
  //
  //
  // abc_scheme.push_back("d");
  // abc_scheme.push_back("e");
  // abc_scheme.push_back("f");
  // abc_objects.push_back("1");
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("1");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // Relation def("hi2",abc_tuples,abc_scheme);
  // abc_scheme.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("e");
  // abc_scheme.push_back("f");
  // Relation aef2("hi2",abc_tuples,abc_scheme);
  // abc_tuples.clear();
  // abc_scheme.clear();
  //
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.clear();
  // abc_scheme.push_back("e");
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("f");
  // Relation eaf("hi2",abc_tuples,abc_scheme);
  // abc_scheme.clear();
  // abc_tuples.clear();
  //
  // abc_objects.push_back("4");
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("1");
  // abc_objects.push_back("1");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("4");
  // abc_objects.push_back("1");
  // abc_objects.push_back("3");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("e");
  // abc_scheme.push_back("f");
  // Relation aef1("hi2",abc_tuples,abc_scheme);
  // abc_objects.clear();
  // abc_tuples.clear();
  // abc_scheme.clear();
  //
  //
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("4");
  // abc_objects.push_back("5");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("2");
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("4");
  // abc_objects.push_back("5");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("4");
  // abc_objects.push_back("5");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("4");
  // abc_objects.push_back("2");
  // abc_objects.push_back("3");
  // abc_objects.push_back("4");
  // abc_objects.push_back("5");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // abc_scheme.push_back("c");
  // abc_scheme.push_back("d");
  // abc_scheme.push_back("e");
  // Relation abcde("hi2",abc_tuples,abc_scheme);
  // abc_scheme.clear();
  // abc_tuples.clear();
  //
  // abc_objects.push_back("1");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_objects.push_back("3");
  // abc_objects.push_back("2");
  // abc_tuples.insert(abc_objects);
  // abc_objects.clear();
  // abc_scheme.push_back("a");
  // abc_scheme.push_back("b");
  // Relation ab("hi2",abc_tuples,abc_scheme);
  // abc_scheme.clear();
  // abc_scheme.push_back("f");
  // abc_scheme.push_back("g");
  // Relation fg("hi2",abc_tuples,abc_scheme);
  // abc_tuples.clear();
  //
  // cout << "Test 1 will be run on the following relations: " << endl;
  // cout << endl;
  // abc1.toString();
  // cout << endl;
  // abc2.toString();
  // cout << endl << "Test1" << endl;
  // test1(abc1,abc2);
  //
  // cout << "Test 2 will be run on the following relations: " << endl << endl;
  // abc1.toString();
  // cout << endl;
  // def.toString();
  // cout << endl << "Test2" << endl;
  // test2(abc1,def);
  //
  // cout << "Test 3 will be run on the following relations: " << endl;
  // cout << endl;
  // abc1.toString();
  // cout << endl;
  // aef1.toString();
  // cout << endl << "Test3" << endl;
  // test3(abc1,aef1);
  //
  // cout << "Test 4 will be run on the following relations: " << endl;
  // cout << endl;
  // abc1.toString();
  // cout << endl;
  // aef2.toString();
  // cout << endl << "Test4" << endl;
  // test4(abc1,aef2);
  //
  // cout << "Test 5 will be run on the following relations: " << endl;
  // cout << endl;
  // abc3.toString();
  // cout << endl;
  // eaf.toString();
  // cout << endl << "Test5" << endl;
  // test5(abc3,eaf);
  //
  // cout << "Test 6 will be run on the following relations: " << endl;
  // cout << endl;
  // abc1.toString();
  // cout << endl;
  // abd.toString();
  // cout << endl << "Test6" << endl;
  // test6(abc1,abd);
  //
  // cout << "Test 7 will be run on the following relations: " << endl;
  // cout << endl;
  // abc1.toString();
  // cout << endl;
  // abc3.toString();
  // cout << endl << "Test7" << endl;
  // test7(abc1,abc3);
  //
  // cout << "Test 8 will be run on the following relations: " << endl;
  // cout << endl;
  // abc1.toString();
  // cout << endl;
  // abc2.toString();
  // cout << endl << "Test8" << endl;
  // test8(abc1,abc2);
  //
  // cout << "Test 9 will be run on the following relations: " << endl;
  // cout << endl;
  // abcde.toString();
  // cout << endl;
  // ab.toString();
  // cout << endl << "Test9" << endl;
  // test9(abcde,ab);
  //
  // cout << "Test 10 will be run on the following relations: " << endl;
  // cout << endl;
  // abcde.toString();
  // cout << endl;
  // fg.toString();
  // cout << endl << "Test10" << endl;
  // test10(fg,abcde);


  return 0;
}
