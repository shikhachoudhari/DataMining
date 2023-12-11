#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<fstream>
#include<cmath>
// #include<climits>
using namespace std;

double find_entropy(double yes_cnt, double no_cnt){
    double entropy = 0.0;
    double total_cnt = yes_cnt + no_cnt;
    
    double yes_probability = yes_cnt/total_cnt;
    double no_probability = no_cnt/total_cnt;

   if(yes_probability > 0){ 
    entropy -= yes_probability * log2(yes_probability);
    }
   if(no_probability > 0){ 
    entropy -= no_probability * log2(no_probability);
    }
    return entropy;

}

double find_infogain(map<string, int> parentcount,map<string, map<string,int>>childcount){
    double yes_cnt = parentcount["Yes"]; 
    double no_cnt = parentcount["No"]; 

    double total_cnt = yes_cnt + no_cnt;

    double parentEntropy = find_entropy(yes_cnt, no_cnt);
      cout << " Parent Entropy- " << parentEntropy << endl;

    double childEntropy = 0.0;

    for(auto it : childcount){
        string value = it.first;

        double child_yes_cnt = it.second["Yes"];
        double child_no_cnt = it.second["No"];
        double child_total = child_yes_cnt + child_no_cnt;
        double child_probability = child_total/total_cnt;

        double child_part_entropy = find_entropy(child_yes_cnt, child_no_cnt);

        childEntropy += child_probability * child_part_entropy;
    }

     cout << "Entropy of selected attribute is " << childEntropy << endl;

     double infogain = parentEntropy - childEntropy;
     return infogain;
}

int main(){
    map<string, int> parentcount;
    map<string, map<string,int>>childcount;
    string line, day, outlook, temp,humidity,wind,playtennis;
    string childname;
    ifstream input("info-gain.csv");

    int choice;
    cout << "Enter for which attribute you want to proceed" << endl;
      cout<<"Press:"<<endl;
      cout<<"1-Outlook"<<endl;
      cout<<"2-temp"<<endl;
      cout<<"3-humidity"<<endl;
      cout<<"4-wind"<<endl;
      cin >> choice;

      while(getline(input,line)){
        stringstream str(line);
        getline(str,day,',');
        getline(str,outlook,',');
        getline(str,temp,',');
        getline(str,humidity,',');
        getline(str,wind,',');
        getline(str,playtennis,'.');

        switch(choice){
            case 1: 
                childname = outlook;
                break;
            case 2:
                childname = temp;
                break;

            case 3:
                childname = humidity;
                break;
            case 4:
                childname = wind;
                break;

            default:
                childname = outlook;
                break;
        }

        parentcount[playtennis]++;
        childcount[childname][playtennis]++;
      }

      double infogain = find_infogain(parentcount,childcount);
      cout << "The infogain of selected attribute is " << infogain;
      input.close();
      return 0;
    
}