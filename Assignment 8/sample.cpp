#include <iostream>
#include <vector>

using namespace std;

// Function to print the frequent itemsets
void print_frequent_itemsets(vector<vector<int>> frequent_itemsets) {
  for (int i = 0; i < frequent_itemsets.size(); i++) {
    for (int j = 0; j < frequent_itemsets[i].size(); j++) {
      cout << frequent_itemsets[i][j] << " ";
    }
    cout << endl;
  }
}

// Function to generate the candidate itemsets of size k+1 from the frequent itemsets of size k
vector<vector<int>> generate_candidates(vector<vector<int>> frequent_itemsets, int k) {
  vector<vector<int>> candidate_itemsets;
  for (int i = 0; i < frequent_itemsets.size(); i++) {
    for (int j = i + 1; j < frequent_itemsets.size(); j++) {
      bool is_candidate = true;
      for (int l = 0; l < k; l++) {
        if (frequent_itemsets[i][l] != frequent_itemsets[j][l]) {
          is_candidate = false;
          break;
        }
      }
      if (is_candidate) {
        candidate_itemsets.push_back(frequent_itemsets[i]);
      }
    }
  }
  return candidate_itemsets;
}

// Function to check if the itemset is frequent
bool is_frequent(vector<int> itemset, vector<vector<int>> transactions, int min_support) {
  int support = 0;
  for (int i = 0; i < transactions.size(); i++) {
    bool is_subset = true;
    for (int j = 0; j < itemset.size(); j++) {
      if (find(transactions[i].begin(), transactions[i].end(), itemset[j]) == transactions[i].end()) {
        is_subset = false;
        break;
      }
    }
    if (is_subset) {
      support++;
    }
  }
  return support >= min_support;
}

// Function to apply the Apriori algorithm
void apriori(vector<vector<int>> transactions, int min_support) {
  // Initialize the frequent itemsets
  vector<vector<int>> frequent_itemsets;

  // Generate the candidate itemsets of size 1
  vector<vector<int>> candidate_itemsets = create_c1(transactions);

  // Iterate until no more frequent itemsets can be found
  while (candidate_itemsets.size() > 0) {

    // For each candidate itemset, check if it is frequent
    for (int i = 0; i < candidate_itemsets.size(); i++) {
      if (is_frequent(candidate_itemsets[i], transactions, min_support)) {
        frequent_itemsets.push_back(candidate_itemsets[i]);
      }
    }

    // Generate the candidate itemsets of size k+1 from the frequent itemsets of size k
    candidate_itemsets = generate_candidates(frequent_itemsets, frequent_itemsets.size() - 1);
  }

  // Print the frequent itemsets
  print_frequent_itemsets(frequent_itemsets);
}

// Main function
int main() {
  // Initialize the transactions
  vector<vector<int>> transactions = {{1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}};

  // Set the minimum support
  int min_support = 2;

  // Apply the Apriori algorithm
  apriori(transactions, min_support);

  return 0;
}