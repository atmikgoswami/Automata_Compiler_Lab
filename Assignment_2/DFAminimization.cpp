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

vector<vector<int>> minimizeDFA(const vector<vector<int>>& dfa, const vector<int>& final_states, int noOfStates, int alphabetSize) {
    vector<int> isFinal(noOfStates, 0);
    for (int fs : final_states) isFinal[fs] = 1;

    set<int> F, NF; 
    for (int i = 0; i < noOfStates; i++) {
        if (isFinal[i]) F.insert(i);
        else NF.insert(i);
    }

    set<set<int>> partitions = {F, NF};

    queue<set<int>> partitionQueue;
    partitionQueue.push(F);
    partitionQueue.push(NF);

    while (!partitionQueue.empty()) {
        set<int> currentPartition = partitionQueue.front();
        partitionQueue.pop();

        for (int symbol = 0; symbol < alphabetSize; symbol++) {

            map<int, set<int>> transitionGroups;
            for (int state : currentPartition) {
                int nextState = dfa[state][symbol];
                for (const auto& partition : partitions) {
                    if (partition.count(nextState)) {
                        transitionGroups[nextState].insert(state);
                        break;
                    }
                }
            }

            for (const auto& partition : partitions) {
                set<int> intersect, difference;
                set_intersection(partition.begin(), partition.end(),
                                 transitionGroups.begin()->second.begin(),
                                 transitionGroups.begin()->second.end(),
                                 inserter(intersect, intersect.begin()));
                set_difference(partition.begin(), partition.end(),
                               transitionGroups.begin()->second.begin(),
                               transitionGroups.begin()->second.end(),
                               inserter(difference, difference.begin()));

                if (!intersect.empty() && !difference.empty()) {
                    partitions.erase(partition);
                    partitions.insert(intersect);
                    partitions.insert(difference);

                    if (intersect.size() < difference.size()) {
                        partitionQueue.push(intersect);
                    } else {
                        partitionQueue.push(difference);
                    }
                    break; 
                }
            }
        }
    }

    map<int, int> stateMapping; 
    int newStateIndex = 0;

    for (const auto& partition : partitions) {
        for (int state : partition) {
            stateMapping[state] = newStateIndex;
        }
        newStateIndex++;
    }

    vector<vector<int>> minimizedDFA(newStateIndex, vector<int>(alphabetSize));

    for (int i = 0; i < noOfStates; i++) {
        for (int symbol = 0; symbol < alphabetSize; symbol++) {
            minimizedDFA[stateMapping[i]][symbol] = stateMapping[dfa[i][symbol]];
        }
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