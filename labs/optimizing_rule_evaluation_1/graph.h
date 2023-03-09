#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
using namespace std;
class graph
{
public:
  // typedef pair<const string, vector<string>> m_ind_rule_dep;
  map<string,vector<string>> m_dependency_graph;
  map<string,vector<string>> m_reverse_graph;
  stack<string> m_DFS_on_reverse;
  stack<string> m_DFS_on_original;
  map<string,bool> m_reverse_DFS_markers;
  map<string,bool> m_original_DFS_markers;
  vector<vector<string>> m_strongly_connected_components;
  vector<string> m_current_scc;
  stack<string> m_temp_original_DFS;
  // void post_order_traversal()
  // {
  //   cout << "write post_order_traversal" << endl;
  //   return;
  // }
  // bool check_children_for_markers(vector<string> children)
  // {
  //   for(auto i : children)
  //   {
  //     if(!m_reverse_DFS_markers.find(i)->second)
  //     {
  //       return false;
  //     }
  //   }
  //   return true;
  // }
  void depth_first_search_reverse(const string & node)
  {
    // cout << "write depth_first_search" << endl;
    if(m_reverse_DFS_markers.find(node)->second == true);
    else
    {
      m_reverse_DFS_markers.find(node)->second = true;
      // if (m_reverse_graph.find(node)->second.empty()) {
      //   m_DFS_on_reverse.push(node);
      // }
      for(auto i : m_reverse_graph.find(node)->second)
      {
        if((m_reverse_DFS_markers.find(i)->second));
        else
        {
          depth_first_search_reverse(i);
        }
      }
      m_DFS_on_reverse.push(node);
    }
  }
  void depth_first_search_original(const string & node)
  {
    // cout << "write depth_first_search" << endl;
    if(m_original_DFS_markers.find(node)->second == true);
    else
    {
      m_original_DFS_markers.find(node)->second = true;
      // if (m_dependency_graph.find(node)->second.empty()) {
      //   m_DFS_on_original.push(node);
      // }
      for(auto i : m_dependency_graph.find(node)->second)
      {
        if(m_original_DFS_markers.find(i)->second);
        else
        {
          depth_first_search_original(i);
        }
      }
      m_DFS_on_original.push(node);
    }
  }
  void check_that_all_rules_are_in_reverse_graph()
  {
    vector<string> reverse_dependents;
    for(auto i : m_dependency_graph)
    {
      if (!m_reverse_graph.count(i.first))
      {
        m_reverse_graph[i.first] = reverse_dependents;
        m_reverse_DFS_markers[i.first] = false;
      }
    }
  }
  void reverse_edges_in_graph()
  {
    //cout << "write reverse_edges_in_graph" << endl;
    for(auto i : m_dependency_graph)
    {
      vector<string> reverse_dependents;
      // reverse_dependents.push_back(i.first);
      for(auto j : i.second)
      {
        if (m_reverse_graph.empty() || !m_reverse_graph.count(j)) {
          m_reverse_graph[j] = reverse_dependents;
          m_reverse_DFS_markers[j] = false;
          m_reverse_graph.find(j)->second.push_back(i.first);
        }
        else
        {
          m_reverse_graph.find(j)->second.push_back(i.first);
        }
      }
      // if (!m_reverse_graph.count(i.first))
      // {
      //   m_reverse_graph[i.first] = reverse_dependents;
      // }
    }
    check_that_all_rules_are_in_reverse_graph();
    cout << "Reverse graph: " << endl;
    toString(m_reverse_graph);
    cout << endl;
    return;
  }
  void print_scc()
  {
    for(auto i : m_strongly_connected_components)
    {
      cout << "The following are strongly connected components: ";
      for(auto j : i)
      {
        cout << j;
        if (j != i[i.size()-1]) {
          cout << " ";
        }
      }
      cout << endl;
    }
  }
  void strongly_connected_components()
  {
    // cout << "write strongly_connected_components" << endl;
    for(auto i : m_reverse_graph)
    {
      depth_first_search_reverse(i.first);
    }
    // print_DFS_stack(m_DFS_on_reverse);
    cout << "DFS on reverse graph: " << endl;
    while (!m_DFS_on_reverse.empty())
    {
      depth_first_search_original(m_DFS_on_reverse.top());
      cout << m_DFS_on_reverse.top() << endl;
      m_DFS_on_reverse.pop();
      if (!m_DFS_on_original.empty()) {
        while (!m_DFS_on_original.empty())
        {
          m_current_scc.push_back(m_DFS_on_original.top());
          m_temp_original_DFS.push(m_DFS_on_original.top());
          m_DFS_on_original.pop();
        }
        m_strongly_connected_components.push_back(m_current_scc);
        m_current_scc.clear();
      }
    }
    cout << endl;
    while (!m_temp_original_DFS.empty())
    {
      m_DFS_on_original.push(m_temp_original_DFS.top());
      m_temp_original_DFS.pop();
    }
    cout << "DFS on dependency graph: " << endl;
    while (!m_DFS_on_original.empty())
    {
        cout << m_DFS_on_original.top() << endl;
        m_DFS_on_original.pop();
    }
    cout << endl;
    print_scc();
    cout << endl;
    // do depth_first_search() on r0 in reverse graph
    // then do depth_first_search() starting from the last element in the stack from the previous DFS.
    // while computing the DFS the second time, all the nodes reachable from a specific rule are SCC's
    return;
  }
  void toString(map<string,vector<string>> current_graph)
  {
    for(auto i : current_graph)
    {
      cout << i.first << ": ";
      for(auto j: i.second)
      {
        cout << j;
        if (!(j == i.second[i.second.size() - 1])) {
          cout << ", ";
        }
      }
      cout << endl;
    }
  }
private:
};
