#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "expression.h"
using namespace std;


// You will need to make changes to this file
int main () {

  vector <Expression*> expStack;
  string s;

  // Read and construct expression object
  while (cin >> s) {

    istringstream ss(s);
    int n;
    int len = expStack.size();

    if (ss >> n) {
        expStack.emplace_back(new LoneInt(n));
    }
    else if (s == "NEG" || s == "ABS") {
        if (len>0) {
            expStack.emplace_back(new UnaryExp(s, expStack.at(len-1)));
            expStack.erase(expStack.end()-2);
        }
    }
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
        if (len>1){
            expStack.emplace_back
                (new BinExp(s,expStack.at(len-2),expStack.at(len-1)));
            expStack.erase(expStack.end()-2);
            expStack.erase(expStack.end()-2);
        }
    }
    else if (s == "done") {
            expStack.at(0)->prettyprint();
            cout << endl;
            break;
    }
    else {
            expStack.emplace_back(new Variable(s));
    }

  }

  // Command interpreter
  while (cin >> s) {
    istringstream ss(s);
    int n;
    if (s == "eval") {
        try {
            cout<<expStack.at(0)->evaluate()<<endl;
        }
        catch(string s){
            cout << s << endl;
            if (s=="Floating point exception")
                return -1;
        }

    }
    else if (s == "set") {
        cin>>s;
        cin>>n;
        expStack.at(0)->set(s, n);
    }
    else if (s == "unset") {
        cin>>s;
        expStack.at(0)->unset(s);
    }
    else if (s == "print") {
            expStack.at(0)->prettyprint();
            cout << endl;
    }
  }

    for (int i=0; i<expStack.size();i++){
        delete expStack[i];
    }
}

