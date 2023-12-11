#include<iostream>
#include<algorithm>
#include <fstream>
#include<vector>
#include<climits>
#include<cmath>

using namespace std;
vector<vector<int>> equi_freq_binning(vector<int>data, int n_bin){
    double n = ceil((double)data.size()/(double)n_bin);
    vector<vector<int>>bins;
    for(int i = 0; i<n_bin; i++){
        vector<int>bin;
        for(int j=i*n; j<(i+1)*n; j++){
            if(j >= data.size()) break;
            bin.push_back(data[j]);
        }
        bins.push_back(bin);
    }
    return bins;
}

vector<vector<int>> equiwidth(vector<int>data, int n_bin){
     int n = data.size();
     int maxi = *max_element(data.begin(), data.end());    
     int mini = *min_element(data.begin(), data.end());

     int bin_width = (maxi-mini)/n_bin;
       vector<int> arr;
     for(int i = 0 ; i< n_bin+1; i++){
        arr.push_back(mini + i*bin_width); //shows the bin boundries
     }  

     vector<vector<int>>bins;
     for(int i = 0; i<n_bin;i++){
        vector<int>bin;
        for(int j:data){
            if(j >= arr[i] && j<arr[i+1]){
                bin.push_back(j);
            }
         
        }
        bins.push_back(bin);
     }  
     bins[n_bin-1].push_back(data[n-1]);
     return bins;
}

void writeCSV(string filename, vector<vector<int>>data){
    ofstream output(filename);
    for(int i = 0; i<data.size(); i++){
        output << "BIN"<<i+1<< "-";
        vector<int>bin = data[i];
        for(int num : bin){
            output << num << ",";
        }
        output << "\n";
    }
    output.close();
}

int main(){
    vector<int>data;
    int value;

    ifstream input("data.csv");

    while(input >> value){
        data.push_back(value);
    }
    sort(data.begin(), data.end());
    int method, n_bin;
    cout<<"Choose binning method"<< endl;
    cout<<"1. Equal freq. binning"<< endl;
    cout<<"2. Equal width binning"<< endl;

    cout << "Enter method no."<< endl;
    cin >> method;

    cout << "Enter no. of bins" << endl;
    cin >> n_bin;

    if(method == 1){
        vector<vector<int>> freqBins = equi_freq_binning(data,n_bin);
        writeCSV("output_equifreq.csv",freqBins);
    }
    else if (method == 2)
    {
    vector<vector<int>> widthBins = equiwidth(data, n_bin);
    writeCSV("output_equiwidth.csv", widthBins);
    }
    else
   {
    cout << "Invalid method choice." << endl;
   }

    return 0;

}