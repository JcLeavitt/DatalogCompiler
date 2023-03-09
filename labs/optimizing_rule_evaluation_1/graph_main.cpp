#include "graph.h"

void test1() //this test has all the rules dependent on themselves alone, there should be 5 SCC's all separate
{
  cout << "Test 1:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {a};
  vector<string> R1 = {b};
  vector<string> R2 = {c};
  vector<string> R3 = {d};
  vector<string> R4 = {e};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test2() //this tests symmetric relationships from a->b/b->a and d->e/e->d, there should be 3 SCC's, ab,c,de
{
  cout << "Test 2:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b};
  vector<string> R1 = {a};
  vector<string> R2 = {c};
  vector<string> R3 = {e};
  vector<string> R4 = {d};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test3() //this tests symmetry between a,b,and c where all of them are dependent on all the others, 3 SCC's: abc, d, e
{
  cout << "Test 3:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b,a};
  vector<string> R1 = {a,c};
  vector<string> R2 = {b,a};
  vector<string> R3 = {d};
  vector<string> R4 = {e};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test4() //this tests symmetry between a,b,and c where each is only dependent on one of the others, 3 SCC's:abd,d,e
{
  cout << "Test 4:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b};
  vector<string> R1 = {c};
  vector<string> R2 = {a};
  vector<string> R3 = {d};
  vector<string> R4 = {e};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test5() //this test symmetry between all the rules, 1 SCC:abcde
{
  cout << "Test 5:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b};
  vector<string> R1 = {c};
  vector<string> R2 = {d};
  vector<string> R3 = {e};
  vector<string> R4 = {a};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test6() //this tests that A is dependent on all other rules, but none of them on A, 5 SCC's:a,b,c,d,e
{
  cout << "Test 6:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b,c,d,e};
  vector<string> R1 = {b};
  vector<string> R2 = {c};
  vector<string> R3 = {d};
  vector<string> R4 = {e};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test7() //this tests when a is dependent on everything, and only c is dependent on a, 4 SCC's:ac,b,d,e
{
  cout << "Test 7:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b,c,d,e};
  vector<string> R1 = {b};
  vector<string> R2 = {a};
  vector<string> R3 = {d};
  vector<string> R4 = {e};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test8() //this tests when A is dependent on B multiple times, b dep. on a, 4 SCC's: ab,c,d,e
{
  cout << "Test 8:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b,b,b,a};
  vector<string> R1 = {b,a};
  vector<string> R2 = {c};
  vector<string> R3 = {d};
  vector<string> R4 = {e};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test9() //tests that all rules dependent on others, but not all on each other, 1 SCC: abcde
{
  cout << "Test 9:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {d,c,e};
  vector<string> R1 = {a,d};
  vector<string> R2 = {c,b};
  vector<string> R3 = {d,a,b};
  vector<string> R4 = {e,c,a};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}
void test10() //this tests when all rules are dependent on all other rules, 1 SCC: abcde
{
  cout << "Test 10:" << endl;
  graph g;
  string a = "A";
  string b = "B";
  string c = "C";
  string d = "D";
  string e = "E";
  vector<string> R0 = {b,c,d,e};
  vector<string> R1 = {a,c,d,e};
  vector<string> R2 = {a,b,d,e};
  vector<string> R3 = {a,b,c,e};
  vector<string> R4 = {a,b,c,d};
  // typedef pair<const Key, T>
  g.m_dependency_graph[a] = R0;
  g.m_dependency_graph[b] = R1;
  g.m_dependency_graph[c] = R2;
  g.m_dependency_graph[d] = R3;
  g.m_dependency_graph[e] = R4;
  g.m_original_DFS_markers[a] = false;
  g.m_original_DFS_markers[b] = false;
  g.m_original_DFS_markers[c] = false;
  g.m_original_DFS_markers[d] = false;
  g.m_original_DFS_markers[e] = false;
  cout << "Dependency graph: " << endl;
  g.toString(g.m_dependency_graph);
  cout << endl;
  g.reverse_edges_in_graph();
  g.strongly_connected_components();
  return;
}

int main(int argc, char * argv[])
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();

  // g.m_
  return 0;
}
