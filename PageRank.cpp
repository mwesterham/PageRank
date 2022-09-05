#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <string.h>

#include "definitions/PageNetwork.h"

using namespace std;

/**
 * @brief Callback function called at the end of each iteration
 * @param iter the current iteration
 * @param weights the current page weights
 */
void printWeights(int iter, vector<PageNode*> weights) {
  cout << "Iteration " << iter << ":" << endl;
  for(PageNode* pn : weights)
    cout << "Page " << pn->page->getId() << " weight: " << pn->weight << endl;
  cout << endl;
}

int main() {
  // Obtain all the ids in this network from user input
  string ids;
  vector<int> idList;

  cout << "Enter a list of page ids seperated by commas, must be positive:" << endl;
  cin >> ids;

  stringstream ssIds(ids);

  for (int i; ssIds >> i;) {
    idList.push_back(i);
    if (ssIds.peek() == ',')
      ssIds.ignore();
  }

  cout << endl;

  // Get definition of page references
  // First number is the base page, all numbers following are that page's references
  cout << "Enter the adjacencies of each page (ex page 3 has page 1 and 2 as adjacency is 3,1,2):" << endl;
  cout << "When finished typing adjacencies, enter f to finish entering adjacencies" << endl;
  
  // Initialize the adjacency map with all the ids
  map<int, vector<int>> adjacencies;
  for (int i : idList) {
    vector<int> v;
    adjacencies[i] = v;
  }

  // Populate the adjacency map from user input
  string thisAdjecency;
  do {
    cin >> thisAdjecency;

    // First number is the base page
    stringstream ssAdj(thisAdjecency);
    int id;
    ssAdj >> id;
    if (ssAdj.peek() == ',')
      ssAdj.ignore();

    // All other numbers are the base page's adjacencies
    for (int i; ssAdj >> i;) {
      adjacencies[id].push_back(i);
      if (ssAdj.peek() == ',')
        ssAdj.ignore();
    }

  } while(thisAdjecency.compare("f") != 0);

  // Initialize all pages with ids
  map<int, Page*> pageMap;
  map<int, vector<int>>::iterator it1;
  for (it1 = adjacencies.begin(); it1 != adjacencies.end(); it1++)
    pageMap[it1->first] = new Page(it1->first);

  // Handle sinks, since we are using an algorithmic approach without matrices we do this manually
  // by linking each sink to all pages. This is technically done during the algorithm
  // but in this implementation it is done here instead
  map<int, Page*>::iterator it2;
  for (it2 = pageMap.begin(); it2 != pageMap.end(); it2++)
    if(adjacencies[it2->first].size() == 0)
      for(int id : idList)
        adjacencies[it2->first].push_back(id);

  // Populate adjacencies
  for (it2 = pageMap.begin(); it2 != pageMap.end(); it2++)
    for(int adjPageId : adjacencies[it2->first])
      pageMap[it2->first]->addPageReference(pageMap[adjPageId]);

  // Transform map to vector of pages
  vector<Page*> networkPages;
  transform(pageMap.begin(), pageMap.end(),
            back_inserter(networkPages),
            [](const pair<int, Page*> &p) {
                return p.second;
            });

  // Retrieve the number of iterations to run for
  cout << "Enter the number of iterations to run for: " << endl;
  int iterations;
  cin >> iterations;

  // Retrieve the damping factor
  cout << "Enter the damping factor to run with: " << endl;
  string dampingFactorStr;
  cin >> dampingFactorStr;
  double dampingFactor = stod(dampingFactorStr);

  // Define the page network, then rank all pages
  PageNetwork pageNetwork(networkPages);
  pageNetwork.rankPages(iterations, dampingFactor, printWeights);
}