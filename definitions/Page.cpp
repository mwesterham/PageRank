#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cstdio>

#include "Page.h"

using namespace std;

Page::Page(int id) {
  this->id = id;
}

void Page::addOutgoingEdge(Page* page)
{
  this->outgoingEdges.push_back(page);
}

void Page::addIncomingEdge(Page* page)
{
  this->incomingEdges.push_back(page);
}

int Page::getId() {
  return this->id;
}

vector<Page*> Page::getOutgoingEdges() {
  return this->outgoingEdges;
}

vector<Page*> Page::getIncomingEdges() {
  return this->incomingEdges;
}