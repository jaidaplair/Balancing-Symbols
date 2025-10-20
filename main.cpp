#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StringNode {
private:
  char elem;
  StringNode *next;

  friend class StringLinkedList;
};

class StringLinkedList {
public:
  StringLinkedList() : head(NULL) {} 
// Constructor to initialize head
  bool empty() const { return head == NULL; }
  const char &front() const { return head->elem; }
  void addFront(const char &e) {
    StringNode *v = new StringNode;
    v->elem = e;
    v->next = head;
    head = v;
  }
  void removeFront() {
    if (!empty()) {
      StringNode *old = head;
      head = old->next;
      delete old;
    }
  }

  string Balanced(string symbols);

private:
  StringNode *head;
};

string StringLinkedList::Balanced(string symbols) {
  StringLinkedList stack;

  for (int j = 0; j < symbols.length(); j++) {
    char ch = symbols[j];

    if (ch == '(' || ch == '[') {
      stack.addFront(ch);
    } else if (ch == ')' || ch == ']') {
      if (stack.empty())
        return "ERROR";

      char top = stack.front();
      if ((ch == ')' && top != '(') || (ch == ']' && top != '[')) {
        return "ERROR";
      }

      stack.removeFront();
    }
  }

  if (!stack.empty())
    return "ERROR";

  return "LEGAL";
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  ifstream inFile(argv[1]);
  if (!inFile) {
    cout << "Error: Cannot open file." << endl;
    return 1;
  }

  StringLinkedList stack;
  string symbols;
  while (getline(inFile, symbols)) {
    if (!symbols.empty()) {
      cout << symbols << " --> " << stack.Balanced(symbols) << endl;
    }
  }

  return 0;
}
