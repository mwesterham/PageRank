#include <iostream>
#include <vector>
#include <string.h>

#include "PageNetwork.h"

using namespace std;

void printWeights(int iter, vector<PageNode*> weights) {
  cout << "Iteration " << iter << ":" << endl;
  for(PageNode* pn : weights) {
    cout << "Page " << pn->page->getId() << " weight: " << pn->weight << endl;
  }
  cout << endl;
}

int main() {
  Page page1(1);
  Page page2(2);
  Page page3(3);
  Page page4(4);

  page1.addPageReference(&page2);
  page1.addPageReference(&page3);
  page2.addPageReference(&page3);
  page3.addPageReference(&page1);
  page3.addPageReference(&page3);

  vector<Page*> networkPages{ &page1, &page2, &page3, &page4 };
  PageNetwork pageNetwork(networkPages);
  pageNetwork.rankPages(30, 0.85, printWeights);
}