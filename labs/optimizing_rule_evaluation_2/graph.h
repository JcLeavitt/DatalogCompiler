#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include <set>
using namespace std;
class graph
{
public:
  // typedef pair<const string, vector<string>> m_ind_rule_dep;
  map<int,set<int>> m_dependency_graph;
  map<int,set<int>> m_reverse_graph;
  vector<int> m_DFS_on_reverse;
  vector<int> m_DFS_on_original;
  map<int,bool> m_reverse_DFS_markers;
  map<int,bool> m_original_DFS_markers;
  vector<vector<int>> m_strongly_connected_components;
  vector<int> m_current_scc;
  // stack<int> m_temp_original_DFS;
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
  void depth_first_search_reverse(const int & node)
  {
    // cout << "write depth_first_search" << endl;
    if(m_reverse_DFS_markers.find(node)->second == true);
    else
    {
      m_reverse_DFS_markers.find(node)->second = true;
      // if (m_reverse_graph.find(node)->second.empty()) {
      //   m_DFS_on_reverse.push(node);
      // }
      for(set<int>::iterator i = m_reverse_graph.find(node)->second.begin(); i != m_reverse_graph.find(node)->second.end(); i++)
      {
        if(m_reverse_DFS_markers.find(*(m_reverse_graph.find(node)->second.find((*i))))->second);
        else
        {
          depth_first_search_reverse(*(m_reverse_graph.find(node)->second.find(*i)));
        }
      }
      m_DFS_on_reverse.push_back(node);
    }
  }
  void depth_first_search_original(const int & node)
  {
    // cout << "write depth_first_search" << endl;
    if(m_original_DFS_markers.find(node)->second == true);
    else
    {
      m_original_DFS_markers.find(node)->second = true;
      // if (m_dependency_graph.find(node)->second.empty()) {
      //   m_DFS_on_original.push(node);
      // }
      for(set<int>::iterator i = m_dependency_graph.find(node)->second.begin(); i != m_dependency_graph.find(node)->second.end(); i++)
      {
        if(m_original_DFS_markers.find(*(m_dependency_graph.find(node)->second.find(*i)))->second);
        else
        {
          depth_first_search_original(*(m_dependency_graph.find(node)->second.find(*i)));
        }
      }
      m_DFS_on_original.push_back(node);
    }
  }
  void check_that_all_rules_are_in_reverse_graph()
  {
    set<int> reverse_dependents;
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
      set<int> reverse_dependents;
      // reverse_dependents.push_back(i.first);
      for(auto j : i.second)
      {
        if (m_reverse_graph.empty() || !m_reverse_graph.count(j)) {
          m_reverse_graph[j] = reverse_dependents;
          m_reverse_DFS_markers[j] = false;
          m_reverse_graph.find(j)->second.insert(i.first);
        }
        else
        {
          m_reverse_graph.find(j)->second.insert(i.first);
        }
      }
      // if (!m_reverse_graph.count(i.first))
      // {
      //   m_reverse_graph[i.first] = reverse_dependents;
      // }
    }
    check_that_all_rules_are_in_reverse_graph();
    // cout << "Reverse graph: " << endl;
    // toString(m_reverse_graph);
    // cout << endl;
    return;
  }
  // void print_scc()
  // {
  //   for(auto i : m_strongly_connected_components)
  //   {
  //     cout << "The following are strongly connected components: ";
  //     for(auto j : i)
  //     {
  //       cout << j;
  //       if (j != i[i.size()-1]) {
  //         cout << " ";
  //       }
  //     }
  //     cout << endl;
  //   }
  // }
  int get_dfs_indices(int  current_scc_indice)
  {
    for (int l = 0; l < (int) m_DFS_on_reverse.size() ; l++) {

      if (m_DFS_on_reverse[l] == current_scc_indice) {
        return l;
      }
    }
    return -1;
  }
  void strongly_connected_components()
  {
    // cout << "write strongly_connected_components" << endl;
    for(auto i : m_reverse_graph)
    {
      depth_first_search_reverse(i.first);
    }
    // print_DFS_stack(m_DFS_on_reverse);
    // cout << "DFS on reverse graph: " << endl;
    while (!m_DFS_on_reverse.empty())
    {
        depth_first_search_original(m_DFS_on_reverse.back());
        while (!m_DFS_on_original.empty())
        {
          m_current_scc.push_back(m_DFS_on_original.back());
          // m_temp_original_DFS.push(m_DFS_on_original.top());
          m_DFS_on_original.pop_back();
        }
        m_strongly_connected_components.push_back(m_current_scc);
        for (int i = 0; i < (int) m_current_scc.size(); i++) {
          int j = m_current_scc[i];
          int to_kill = get_dfs_indices(j);
          m_DFS_on_reverse.erase(m_DFS_on_reverse.begin()+to_kill);
        }
        m_current_scc.clear();
        // cout << m_DFS_on_reverse.top() << endl;
        // m_DFS_on_reverse.pop();
    }
    // cout << endl;
    // while (!m_temp_original_DFS.empty())
    // {
    //   m_DFS_on_original.push(m_temp_original_DFS.top());
    //   m_temp_original_DFS.pop();
    // }
    // cout << "DFS on dependency graph: " << endl;
    // while (!m_DFS_on_original.empty())
    // {
    //     cout << m_DFS_on_original.top() << endl;
    //     m_DFS_on_original.pop();
    // }
    // cout << endl;
    // print_scc();
    // cout << endl;
    // do depth_first_search() on r0 in reverse graph
    // then do depth_first_search() starting from the last element in the stack from the previous DFS.
    // while computing the DFS the second time, all the nodes reachable from a specific rule are SCC's
    return;
  }
  void toString(map<int,set<int>> current_graph)
  {
    cout << "Dependency Graph" << endl;
    for(auto i : current_graph)
    {
      cout << "R" << i.first << ":";
      for(set<int>::iterator j = i.second.begin(); j != i.second.end(); j++)
      {
        cout << "R" << *j;
        if (((++j) != (i).second.end())) {
          cout << ",";
          --j;
        }
        else --j;
      }
      cout << endl;
    }
    cout << endl;
  }
private:
};
