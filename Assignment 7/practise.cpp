#include <bits/stdc++.h>

using namespace std;

double minfreq;
vector<set<string>>datatable;
set<string>products;
map<string, int> freq;

vector<string>wordsof(string str){
    vector<string> tmpset;
    string tmp = "";
    int i = 0;
    while (str[i])
    {
        if (isalnum(str[i]))
            tmp += str[i];
        else
        {
            if (tmp.size() > 0)
                tmpset.push_back(tmp);
            tmp = "";
        }
        i++;
    }

    if (tmp.size() > 0)
       {
        tmpset.push_back(tmp);
       }

    return tmpset;
}

string combine(vector<string> &arr, int miss){
    //The combine function is designed to create a string by combining elements from a vector of strings (arr) while skipping an element at a specified index (miss).
    string str;
    for(int i = 0; i<arr.size(); i++){
        if(i != miss){
            str += arr[i]+ " ";
        }
    }
        str = str.substr(0,str.size()-1); //removes the last space character from the string
        return str;
}

set<string> apriori_gen(set<string>&sets, int k){
    set<string> set2; //this will store the combined set

    for(set<string>:: iterator it1 = sets.begin();it1 != sets.end(); it1++){
            set<string>::iterator it2 = it1;
            it2++;
            for(; it2 != sets.end(); it2++){
                vector<string>v1=wordsof(*it1);
                vector<string>v2=wordsof(*it2);

                bool alleq = true;
                for(int i = 0; i<k-1; i++){
                    if(v1[i] != v2[i]){
                        alleq = false;  //matlab yaha dono itemset ke starting same nai hai isliye unko aage merger nai hongae
                    }
                }
                v1.push_back(v2[k-1]);

                if(v1[v1.size()-1] < v1[v1.size()-1]){
                    swap(v1[v1.size()-1],v1[v1.size()-2]);
                }

                for(int i = 0; i<v1.size() && alleq;i++){
                    string tmp = combine(v1,i);  //by skipping we are checking ki el element skip karne ke bad jo string bani hai vo hamare set me present thi ki nai agar nai hogi to uska superset banake bhi koi matlab nai hoga
                    if(sets.find(tmp) == sets.end()){
                        alleq = false;
                    }
                }

                if(alleq){  //agar mil gaya to hum aage proceed kar sakte hai aur v1 me jo set hai vo hamara new combination hoga
                    set2.insert(combine(v1,-1));
                }
            }
    }
    return set2;
}

int main(){
    ifstream input("item_set_input.csv");
    string line;
    cout << "Enter the minimum frequency:";
    cin >> minfreq;

    while(getline(input, line)){
        set<string>tempset;
        stringstream str(line);
        string item;
       while( getline(str,item,',')){
            tempset.insert(item);
       }

       datatable.push_back(tempset);

       for(auto it:tempset){
        products.insert(it);
        freq[it]+=1;
       }     
    }
    
    input.close();

    cout << "No. of transactions= "<<datatable.size() << endl;
    cout << "Entered min frequency = "<<minfreq << endl; 

    for(auto it: freq){    //removing the infrequent items from the product set
        if(it.second < minfreq){
            products.erase(it.first);
        }
    }

    int pass = 1;

    cout << "\nFrequent "<<pass++ << "-item set: \n";
    for(set<string>::iterator it = products.begin(); it != products.end(); it++){
        cout << "{" << *it <<"}  "<< freq[*it] << endl;
    }
   
    set<string> prev = products;

    int i = 2;

    while(i){
        set<string> curr = apriori_gen(prev, i-1);  //Generate the candidate itemsets of size i

        if(curr.size() < 1){
            break;
        }

        for(set<string>:: iterator it = curr.begin(); it != curr.end(); it++){
            vector<string> arr = wordsof(*it);

            int tot = 0;  //it counts the frequency of itemset in the given transactions in the input
            for(int j = 0; j<datatable.size(); j++){
                bool present = true;

                for(int k = 0; k<arr.size()&&present; k++){
                        if(datatable[j].find(arr[k]) == datatable[j].end()){
                            present = false;
                        }
                }
                if(present){tot++;}
            }
            if(tot >= minfreq){
                freq[*it] = tot;
            }
            else{
                curr.erase(*it);
            }


        }
        if(curr.size() == 0){
            break;
        }

        cout << "\n\nFrequent " << pass++ << "-itemset: \n";
        for(set<string>::iterator it = curr.begin(); it != curr.end(); it++){
            cout << "{" << *it << "}" << freq[*it] << endl;
        }
        prev = curr;
        i++;
   
    }

    ofstream output("item_set_output.csv");
    for(auto it = prev.begin(); it != prev.end(); it++){
        output << "{" << *it << "}" << endl;
    }

    return 0;
}