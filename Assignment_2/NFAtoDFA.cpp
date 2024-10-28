#include <bits/stdc++.h>
using namespace std;

void printNFA(vector<vector<vector<int>>> &transitionTable, vector<char> &alphabets) {
    cout << "  STATE  |  ";
    int noOfAlphabets = alphabets.size();
    for (int i = 0; i < noOfAlphabets; i++){
        cout << alphabets[i] << "    |    ";
    }
    cout << "ε\n";

    for (int i = 0; i < transitionTable.size(); i++){
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

void printDFA(vector<vector<int>> &states, vector<vector<vector<int>>> &dfa, vector<char> &alphabets, int noOfStates) {
    cout << "  STATE  |  ";
    int noOfAlphabets = alphabets.size();
    for (int i = 0; i < noOfAlphabets; i++){
        cout << alphabets[i] << "    |    ";
    }
    cout << endl;

    for (int i = 0; i < states.size(); i++){
        cout << "{ ";
        for (int h = 0; h < states[i].size(); h++)
            cout << "q" << states[i][h] << " ";
        if (states[i].empty()){
            cout << "q"<<noOfStates<<" ";
        }
        cout << "} ";
        for (int j = 0; j < dfa[i].size(); j++){
            cout << " | ";
            for (int k = 0; k < dfa[i][j].size(); k++){
                cout << dfa[i][j][k] << " ";
            }
            if (dfa[i][j].empty()){
                cout << noOfStates;
            }
        }
        cout << endl;
    }
}

vector<int> closure(int s, vector<vector<vector<int>>> &v) {
    vector<int> t;      
    set<int> visited;   
    queue<int> q;

    t.push_back(s);
    visited.insert(s);
    q.push(s);

    while (!q.empty()) {
        int f = q.front();
        q.pop();

        for (int y : v[f][v[f].size() - 1]) { 
            if (visited.find(y) == visited.end()) { 
                t.push_back(y);
                visited.insert(y);
                q.push(y); 
            }
        }
    }

    sort(t.begin(), t.end());
    return t;
}


int main() {

    int noOfStates, alphabetSize;
    cout << "Enter total number of states in NFA :\n";
    cin >> noOfStates;
    cout << "Enter number of alphabets :\n";
    cin >> alphabetSize;

    cout << "Enter the alphabets one after another :\n";
    vector<char> alphabets(alphabetSize);
    for (int i = 0; i < alphabetSize; i++){
        cin >> alphabets[i];
    }

    vector<vector<vector<int>>> transitionTable;

    for (int i = 0; i < noOfStates; i++){
        cout << "FOR STATE q" << i << endl;
        vector<vector<int>> temp;

        int noOfOutputStates, outputState;
        for (int j = 0; j < alphabetSize; j++){
            vector<int> t;
            cout << "Enter number of output states for input " << alphabets[j]<< " :\n";
            cin >> noOfOutputStates;
            if(noOfOutputStates){
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
            cout << "Enter output states for input ε :\n";
            for (int k = 0; k < noOfOutputStates; k++){
                cin >> outputState;
                t.push_back(outputState);
            }
        }
        temp.push_back(t);
        transitionTable.push_back(temp);
    }
    cout << "***************TRANSITION TABLE FOR NFA***************" << endl;
    printNFA(transitionTable, alphabets);
    cout << endl<< endl;

    cout << "***************TRANSITION TABLE FOR DFA***************" << endl;

    vector<vector<vector<int>>> dfa;
    vector<vector<int>> states;

    states.push_back(closure(0, transitionTable));
    queue<vector<int>> q;
    q.push(states[0]);
    while (!q.empty()){
        vector<int> f = q.front();
        q.pop();
        vector<vector<int>> v;
        for (int i = 0; i < alphabetSize; i++){
            vector<int> t;
            set<int> s;
            for (int j = 0; j < f.size(); j++){
                for (int k = 0; k < transitionTable[f[j]][i].size(); k++){
                    vector<int> cl = closure(transitionTable[f[j]][i][k], transitionTable);
                    for (int h = 0; h < cl.size(); h++){
                        if (s.find(cl[h]) == s.end())
                        s.insert(cl[h]);
                    }
                }
            }
            for (set<int>::iterator u = s.begin(); u != s.end(); u++)
                t.push_back(*u);
            v.push_back(t);
            if (find(states.begin(), states.end(), t) == states.end()){
                states.push_back(t);
                q.push(t);
            }
        }
        dfa.push_back(v);
    }
    printDFA(states, dfa, alphabets, noOfStates);

    return 0;
}
