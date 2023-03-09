#include <queue>
#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
  queue <int> s;
  for (int i = 0; i < 10; i++) {
    s.push(i);
  }
  queue <int> a;
  while (!s.empty()) {
    a.push(s.front());
    s.pop();
  }
  while (!a.empty()) {
    cout << a.front() << endl;
    a.pop();
  }
}
