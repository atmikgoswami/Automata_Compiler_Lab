#include <bits/stdc++.h>
using namespace std;

void printFA(vector<vector<vector<int>>> &transitionTable, vector<char> &alphabets, bool isNFA) {
  cout << "  STATE  |  ";
  int noOfAlphabets = alphabets.size();
  for (int i = 0; i < noOfAlphabets; i++){
    cout << alphabets[i] << "    |    ";
  }
  if(isNFA) cout << "ε\n";
  
  int n = (isNFA)?transitionTable.size():transitionTable.size()-1;
  for (int i = 0; i < n; i++){
    cout << "   q" << i << "    |   ";
    for (int j = 0; j < transitionTable[i].size(); j++){
      cout << "[";
      for (int k = 0; k < transitionTable[i][j].size(); k++){
        cout << transitionTable[i][j][k];
        if (k != transitionTable[i][j].size() - 1){
          cout << ", ";
        }
      }
      cout << "]  |  ";
    }
    cout << endl;
  }
}

int main() {

  int noOfStates, alphabetSize;
  cout << "Enter total number of states in the FA :\n";
  cin >> noOfStates;
  cout << "Enter number of alphabets :\n";
  cin >> alphabetSize;

  cout << "Enter the alphabets one after another :\n";
  vector<char> alphabets(alphabetSize);
  for (int i = 0; i < alphabetSize; i++){
    cin >> alphabets[i];
  }

  vector<vector<vector<int>>> transitionTable;
  bool isNFA = false;

  for (int i = 0; i < noOfStates; i++){
    cout << "FOR STATE q" << i << endl;
    vector<vector<int>> temp;

    int noOfOutputStates, outputState;
    for (int j = 0; j < alphabetSize; j++){
      vector<int> t;
      cout << "Enter number of output states for input " << alphabets[j]<< " :\n";
      cin >> noOfOutputStates;
      if(noOfOutputStates){
        if(noOfOutputStates > 1) isNFA = true;
        cout << "Enter output states for input " << alphabets[j] << " :\n";
        for (int k = 0; k < noOfOutputStates; k++){
          cin >> outputState;
          t.push_back(outputState);
        }
      }
      temp.push_back(t);
    }
    vector<int> t;
    cout << "Enter number of output states for input ε :" << endl;
    cin >> noOfOutputStates;
    if(noOfOutputStates){
      isNFA = true;
      cout << "Enter output states for input ε :\n";
      for (int k = 0; k < noOfOutputStates; k++){
        cin >> outputState;
        t.push_back(outputState);
      }
    }
    temp.push_back(t);
    transitionTable.push_back(temp);
  }

  if(isNFA) cout<<"The automata is a NFA"<<endl;
  else cout<<"The automata is a DFA"<<endl;
  cout << "***************TRANSITION TABLE FOR FA***************" << endl;
  printFA(transitionTable, alphabets, isNFA);
  cout << endl<< endl;

}