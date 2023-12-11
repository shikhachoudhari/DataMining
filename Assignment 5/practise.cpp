#include <bits/stdc++.h>
using namespace std;
struct CellData{
    int tweight;
    int dweight;
    int cnt;
};

map<string, map<string,CellData>>celldata;
map<string, int>row_total;
map<string, int>col_total;

void readcsv(string filename){
    string line;
    ifstream input(filename);
    int i = 0;

    while(getline(input, line)){
        stringstream str(line);

        if(i == 0){
            i++;
            continue;
        }

        string row, col, count;
        getline(str,row,',');
        getline(str,col,',');
        getline(str,count,',');

        int value = stoi(count);

        row_total[row] += value;
        col_total[col] += value;

        celldata[row][col].cnt += value;

    }
}

void writecsv(string filename){
    ofstream output(filename);

    output << "Column\\Row, Count, T-weight, D-Weight, Count, T-weight, D-Weight,Count, T-weight, D-Weight"<< endl;

    int total1 = 0;
    for(auto it : row_total){
        total1 += it.second;
    }

    for(auto it : row_total){
        string row = it.first;
        output << row <<",";
        for(auto i : col_total){
            string col = i.first;
            CellData cell = celldata[row][col];

            output << cell.cnt << ",";
            output << ((float)cell.cnt/row_total[row]) * 100 << "%,";
            output << ((float)cell.cnt/i.second) * 100 << "%,";
        }
        cout << row_total[row] <<  total1<< endl;

        output << row_total[row] << ","<<"100%,"<<row_total[row]*100/total1<<"%" << endl;
    }

    output << "Total,";
    int total = 0;
    for(auto it : col_total){
        total += it.second;
    }
    for(auto it : col_total){
        output << it.second << ",";
        output << ((float)it.second/total) * 100 << "%,";
        output << "100%,";
    }
    cout << total << endl;
    output << total << "," << "100%, 100%" << endl;
}

int main(){
    string filename = "tdinput.csv";
    readcsv(filename);
    writecsv("output.csv");

}
