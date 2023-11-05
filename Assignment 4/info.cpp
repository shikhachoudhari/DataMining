#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

using namespace std;

// Function to calculate entropy
double calculateEntropy(int positive, int negative)
{
    double total = positive + negative;
    double entropy = 0.0;

    if (total > 0)
    {
        double positiveProbability = positive / total;
        double negativeProbability = negative / total;

        if (positiveProbability > 0)
        {
            entropy -= positiveProbability * log2(positiveProbability);
        }

        if (negativeProbability > 0)
        {
            entropy -= negativeProbability * log2(negativeProbability);
        }
    }

    return entropy;
}

// Function to compute information gain
double computeInformationGain(map<string, int> &parentCounts, map<string, map<string, int>> &childCounts)
{
    // YES-> TRUE and NO->FALSE
    double positiveParent = parentCounts["Yes"];
    double negativeParent = parentCounts["No"];
    double totalParent = positiveParent + negativeParent;

    double parentEntropy = calculateEntropy(positiveParent, negativeParent);
    cout << "Parent Entropy: " << parentEntropy << "\n";

    double childEntropy = 0;

    for (auto it = childCounts.begin(); it != childCounts.end(); ++it)
    {
        string childName = it->first;
        double positiveChild = it->second["Yes"];
        double negativeChild = it->second["No"];
        double totalChild = positiveChild + negativeChild;

        double childEntropyPart = calculateEntropy(positiveChild, negativeChild);

        childEntropy += (totalChild / totalParent) * childEntropyPart;
    }

    cout << "Weighted Child Entropy: " << childEntropy << "\n";

    double informationGain = parentEntropy - childEntropy;
    cout << "Information Gain: " << informationGain << "\n";

    return informationGain;
}

int main()
{

    // get the input data set

    ifstream file("info-gain.csv");

    // variables to store attribute data and the categorical class: playtennis
    string line, day, outlook, temp, humidity, wind, playtennis, value;
    // parentCount-> to calculate main entrophy for the categorical class: playtennis

    map<string, int> parentCounts;
    map<string, map<string, int>> childCounts;

    if (!file.is_open())
    {
        cerr << "Error opening input file." << endl;
        return -1;
    }

    int i = 0;
    string childName;
    int choice;

    // reads data for a
    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playtennis, '.');
        // getline(str, value, ',');

        if (i == 0)
        {
            i++;
            cout << "Enter Child Column Number: ";
            cin >> choice;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Sorry this is not a valid attribute-> choose some other attribute" << endl;
            return -1;

        case 2:
            childName = outlook;
            break;

        case 3:
            childName = temp;
            break;

        case 4:
            childName = humidity;
            break;

        case 5:
            childName = wind;
            break;

        default:
            childName = value;
            break;
        }

        // now calculate the freq of categorical class and the freq of values for the chosen attribute
        parentCounts[playtennis]++;
        childCounts[childName][playtennis]++;
    }

    double informationGain = computeInformationGain(parentCounts, childCounts);

    cout << "Overall Information Gain: " << informationGain << "\n";

    file.close();

    return 0;
}