#include<bits/stdc++.h>
#include <cmath>
using namespace std;

vector<double>minmaxNormalization(const vector<double>data,double min, double max){
    double min_old = *min_element(data.begin(), data.end());
    double max_old = *max_element(data.begin(), data.end());

    vector<double> normalized_data;
    for(double val : data){
        double normalized_val = (val - min_old)/(max_old - min_old) * (max-min)+ min;
        normalized_data.push_back(normalized_val);
    }
    return normalized_data;
}
vector<double>zscoreNormalization(const vector<double>data){
    double mean = 0;
    for(double val : data){
        mean += val; 
    }
    mean /= data.size();

    double varience = 0;
    for(double val : data){
        varience += (val-mean) * (val-mean);
    }
    varience /= data.size();
    double std_dev = sqrt(varience);

    vector<double>normalized_data;
     for (double val : data) {
        double z_score = (val - mean) / std_dev;
        normalized_data.push_back(z_score);
    }
    
    return normalized_data;
    
}


int main(){
    ifstream input("data.csv");
    ofstream output("i1.csv");

    vector<double>data;
    double value;

    //input read karna hai aur ek array me store karna hai
    while(input >> value){
        data.push_back(value);
    }

    double min_new; double max_new;
    cout << "Enter the new range for min-max normalization" << endl;

    cin >> min_new >> max_new;
    vector<double>min_max_normalized = minmaxNormalization(data, min_new, max_new);
    vector<double>zScore_normalized = zscoreNormalization(data);

    output << "Min_Max normalization\n";
    for(double val : min_max_normalized){
        output<<val<<"\n";
    }
    output << "z score normalization\n";
    for(double val : zScore_normalized){
        output<<val<<"\n";
    }
    
    input.close();
    output.close();
    return 0;

}   