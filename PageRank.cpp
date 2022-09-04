#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <string.h>

#include "definitions/PageNetwork.h"

using namespace std;

void printWeights(int iter, vector<PageNode*> weights) {
  cout << "Iteration " << iter << ":" << endl;
  for(PageNode* pn : weights) {
    cout << "Page " << pn->page->getId() << " weight: " << pn->weight << endl;
  }
  cout << endl;
}

void printAdjacencyMap(map<int, vector<int>> adjacencies) {
  map<int, vector<int>>::iterator it;
  for (it = adjacencies.begin(); it != adjacencies.end(); it++) {
    cout << it->first << ':'<< endl;
    for(int i : it->second) {
      cout << i << " ";
    }
    cout << endl;
  }
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

  string thisAdjecency;
  do {
    cin >> thisAdjecency;

    stringstream ssAdj(thisAdjecency);
    int id;
    ssAdj >> id;
    if (ssAdj.peek() == ',')
      ssAdj.ignore();

    for (int i; ssAdj >> i;) {
      adjacencies[id].push_back(i);
      if (ssAdj.peek() == ',')
        ssAdj.ignore();
    }

  } while(thisAdjecency.compare("f") != 0);

  // printAdjacencyMap(adjacencies);

  // Initialize all pages with ids
  map<int, Page*> pageMap;
  map<int, vector<int>>::iterator it1;
  for (it1 = adjacencies.begin(); it1 != adjacencies.end(); it1++)
    pageMap[it1->first] = new Page(it1->first);

  // Populate adjacencies
  map<int, Page*>::iterator it2;
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

  Page page1(1);
  Page page2(2);
  Page page3(3);
  Page page4(4);

  page1.addPageReference(&page2);
  page1.addPageReference(&page3);
  page2.addPageReference(&page3);
  page3.addPageReference(&page1);
  page3.addPageReference(&page3);

  // vector<Page*> networkPages{ &page1, &page2, &page3, &page4 };
  PageNetwork pageNetwork(networkPages);
  pageNetwork.rankPages(30, 0.85, printWeights);
}