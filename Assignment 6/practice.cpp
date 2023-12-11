#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

double findmedian({
 
    if(n%2){
        return data[n/2];
    }
    else {
        return (data[(n/2)-1]+data[n/2])/2;
    }
}



int main(){
    ifstream input("box_plot.csv");
    ofstream output("five_number_output.csv");

    vector <int> data;
   
    int val;
    while(input >> val){
        data.push_back(val);
    }

    sort(data.begin(), data.end());
  
    int n = data.size();
    double median = findmedian(data);
    double first_quartile = findq1();
    double third_quartile;
    if(n%2){
        third_quartile = findmedian(arr+(n/2+1), n);
    }
    else{
         third_quartile = findmedian(arr+(n/2), n);
    }

   cout<<median << "  " << first_quartile << "  " << third_quartile<<endl;
   input.close();
   output.close(); 

}