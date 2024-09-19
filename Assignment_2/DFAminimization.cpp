#include<bits/stdc++.h>
using namespace std;

void printDFA(vector<vector<int>>& table, vector<char>& alphabets){
	cout<<"  STATE        ";
    int noOfAlphabets = alphabets.size();
	for(int i=0;i<noOfAlphabets;i++){
		cout<<"|  "<<alphabets[i]<<"  ";
	}
	cout<<endl;

	for(int i=0;i<table.size();i++){
		cout<<"       "<<i<<"      ";
		for(int j=0;j<table[i].size();j++){
			cout<<" |  ";
			cout<<table[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool areEquivalent(int i, int j, const vector<vector<int>>& dfa, const vector<int>& partition, int alphabetSize) {
    for (int z = 0; z < alphabetSize; ++z) {
        if (partition[dfa[i][z]] != partition[dfa[j][z]]) {
            return false;
        }
    }
    return true;
}

vector<vector<int>> minimizeDFA(const vector<vector<int>>& dfa, const vector<int>& final_states, int noOfStates, int alphabetSize) {
    vector<int> partition(noOfStates, -1);
    set<int> final_set(final_states.begin(), final_states.end());

    // Initial partition: final and non-final states are grouped separately
    int accept_idx = *final_set.begin(), reject_idx = -1;
    for (int i : final_set) {
        partition[i] = accept_idx;
    }
    for (int i = 0; i < noOfStates; ++i) {
        if (partition[i] < 0) {
            if (reject_idx < 0) reject_idx = i;
            partition[i] = reject_idx;
        }
    }

    // Iterative refinement of partition
    while (true) {
        vector<int> new_partition(noOfStates, -1);
        int i = 0;
        while (i < noOfStates) {
            new_partition[i] = i;
            int i_next = noOfStates;
            for (int j = i + 1; j < noOfStates; ++j) {
                if (new_partition[j] >= 0) continue;
                if (partition[i] == partition[j] && areEquivalent(i, j, dfa, partition, alphabetSize)) {
                    new_partition[j] = i; 
                } else if (i_next == noOfStates) {
                    i_next = j; // Move to the first unmerged state
                }
            }
            i = i_next;
        }
        if (partition == new_partition) break;
        partition = new_partition;
    }

    // Create minimized DFA
    vector<vector<int>> minimizedDFA;
    map<int, int> state_map;
    int new_state = 0;

    for (int i = 0; i < noOfStates; ++i) {
        if (state_map.find(partition[i]) == state_map.end()) {
            state_map[partition[i]] = new_state++;
        }
    }

    for (auto it:state_map) {

        int i = it.first;
        //for state i
        vector<int> temp;
        for(int j=0;j<alphabetSize;j++){

            int old_dest = dfa[i][j];
            int new_dest = state_map[partition[old_dest]];
            temp.push_back(new_dest);
        }
        minimizedDFA.push_back(temp);
    }

    return minimizedDFA;
}


int main(){
    vector<vector<int>> dfa;
	int noOfStates,alphabetSize,noOfFinalStates;
	cout<<"Enter number of states in DFA : ";
	cin>>noOfStates;
	cout<<"Enter number of elements in alphabet : ";
	cin>>alphabetSize;

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

    for(int i=0;i<noOfStates;i++){
		cout << "FOR STATE q" << i << endl;
		vector<int> v(alphabetSize);
		for(int j=0;j<alphabetSize;j++){
			cout<<"Enter output state for input "<<alphabets[j]<<" : ";
			cin>>v[j];
		}
		dfa.push_back(v);
	}

    cout<<endl<<"GIVEN DFA :"<<endl;
	printDFA(dfa, alphabets);

    vector<vector<int>> minimizedDFA = minimizeDFA(dfa, final_states, noOfStates, alphabetSize);

    cout << endl << "MINIMIZED DFA:" << endl;
    printDFA(minimizedDFA, alphabets);

    return 0;
}