#include <algorithm>
#include <iostream>

#include "PageNetwork.h"

using namespace std;

PageNetwork::PageNetwork(vector<Page*> pages) {
  this->pages = pages;
}

void PageNetwork::addPage(Page* page) {
  this->pages.push_back(page);
}

void PageNetwork::rankPages(int iters, double dampingFactor, void (*funcCallback)(int, vector<PageNode*>)) {
  // Initialize the page weights to 1/n where n is the number of pages in the network
  this->pageWeights.clear();
  int numPages = this->pages.size();
  for(Page* p : this->pages) {
    PageNode* pn = new PageNode{ 1.0 / numPages, p};
    this->pageWeights.push_back(pn);
  }

  // Do callback with 0 iterations
  funcCallback(0, this->pageWeights);

  // Run the algorithm
  for(int i = 0; i < iters; i++) {
    this->pageWeights = this->getNextWeights(dampingFactor);
    funcCallback(i+1, this->pageWeights);
  }
}

vector<PageNode*> PageNetwork::getNextWeights(double dampingFactor) {
  // Forward declaration for new weights
  vector<PageNode*> newWeights;

  // Calculate the weights of each page node in the next iteration
  for(PageNode* pn : this->pageWeights) {
    // Calculate the new weight of this individual page node
    double newWeight = 0;
    for(Page* pEdge : pn->page->getIncomingEdges()) {
      PageNode* pnEdge = this->getPageNode(pEdge);
      double pnEdgePriorWeight = pnEdge->weight;
      int pnEdgeOutgoingCount = pnEdge->page->getOutgoingEdges().size();
      newWeight += pnEdgePriorWeight * 1.0 / pnEdgeOutgoingCount;
    }

    // Dampening
    double initialWeight = 1.0 / this->pages.size();
    newWeight = (1 - dampingFactor) * initialWeight + dampingFactor * newWeight;
    // newWeight = (1 - dampingFactor) + dampingFactor * newWeight; // Alternative damping calculation

    // Add the new page node with the new weight to the list of new weights
    PageNode* pn_next = new PageNode{newWeight, pn->page};
    newWeights.push_back(pn_next);
  }

  return newWeights;
}


PageNode* PageNetwork::getPageNode(Page* pSearch) {
  for(PageNode* pn: this->pageWeights) {
    if(pn->page == pSearch)
      return pn;
  }
  __throw_runtime_error("Could not find page " + pSearch->getId());
}