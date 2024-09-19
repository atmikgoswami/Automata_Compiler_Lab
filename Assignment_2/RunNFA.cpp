#include<bits/stdc++.h>
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

bool isAcceptedByNFA(vector<vector<vector<int>>> &transitionTable, vector<char> &alphabets, vector<int> &final_states, string &s, int startState) {
    int alphabetSize = alphabets.size();
    queue<pair<int, int>> q; 
    set<pair<int, int>> visited; 

    q.push({startState, 0}); 

    while (!q.empty()) {
        pair<int, int> currentPair = q.front();
        int currentState = currentPair.first;
        int idx = currentPair.second;
        q.pop();

        if (idx == s.size()) {
            if (find(final_states.begin(), final_states.end(), currentState) != final_states.end()) {
                return true;
            }
            continue;
        }

        visited.insert({currentState, idx});

        char symbol = s[idx];
        int symbolIndex = find(alphabets.begin(), alphabets.end(), symbol) - alphabets.begin();

        if (symbolIndex < alphabetSize) {
            for (int nextState : transitionTable[currentState][symbolIndex]) {
                if (visited.find({nextState, idx + 1}) == visited.end()) {
                    q.push({nextState, idx + 1});
                }
            }
        }

        for (int nextState : transitionTable[currentState][alphabetSize]) { 
            if (visited.find({nextState, idx}) == visited.end()) {
                q.push({nextState, idx}); 
            }
        }
    }

    return false; 
}

int main(){
    int noOfStates, alphabetSize, noOfFinalStates;
    cout << "Enter total number of states in NFA :\n";
    cin >> noOfStates;
    cout << "Enter number of alphabets :\n";
    cin >> alphabetSize;

    cout << "Enter the alphabets one after another :\n";
    vector<char> alphabets(alphabetSize);
    for (int i = 0; i < alphabetSize; i++){
        cin >> alphabets[i];
    }

    cout<<"Enter number of final states : ";
	cin>>noOfFinalStates;
	vector<int> final_states(noOfFinalStates);

	cout<<"Enter final state(s) : ";
	for(int i=0;i<noOfFinalStates;i++){
		cin>>final_states[i];
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

    char ch;
    do{
		cout<<"Enter the string : ";
		string s;
		cin>>s;
		
        bool accepted = isAcceptedByNFA(transitionTable, alphabets, final_states, s, 0);

        if (accepted) {
            cout << "The string is accepted by the NFA." << endl;
        } else {
            cout << "The string is rejected by the NFA." << endl;
        }


        cout<<"Enter 'y' to continue : ";
        cin>>ch;
    }while(ch=='y');
}