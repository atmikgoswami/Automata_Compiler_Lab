#include<bits/stdc++.h>
using namespace std;

void printDFA(vector<vector<int>>& table, vector<char>& alphabets){
	cout<<"  STATE  ";
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

    cout<<endl<<"   GIVEN DFA :"<<endl;
	printDFA(dfa, alphabets);

    char ch;
    do{
		cout<<"Enter the string : ";
		string s;
		cin>>s;
		int curr=0,out;
		for(int i=0;i<s.length();i++){
			out=dfa[curr][s[i]-'a'];
			curr=out;
		}

        if(find(final_states.begin(),final_states.end(),out)!=final_states.end()){
			cout<<"String is accepted by the DFA at "<<out<<" state."<<endl;
		}else{
            cout<<"String is not accepted by the DFA."<<endl;
        }
        cout<<"Enter 'y' to continue : ";
        cin>>ch;
    }while(ch=='y');
    
    
    return 0;
}
