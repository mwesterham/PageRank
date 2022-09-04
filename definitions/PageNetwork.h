#include <vector>

#include "Page.h"

/**
 * @brief Describes the ranking of a page through a weight
 */
struct PageNode {
  double weight;
  Page* page;
};

class PageNetwork {
  public:
    /**
     * @brief Constructor, additionally sets an initial set of pages
     * @param pages the initial set of pages
     */
    PageNetwork(std::vector<Page*> pages);

    /**
     * @brief Adds a page to the page network
     * @param page to add to the network
     */
    void addPage(Page* page);

    /**
     * @brief Performs a page rank on the current pages in the network from scratch
     * @param iters the number of iterations to run the page rank algorithm
     * @param dampingFactor the damping factor to use in the ranking
     * @param funcCallback a callback function called after each iteration with the iteration and current weights as input
     */
    void rankPages(int iters, double dampingFactor, void (*funcCallback)(int, std::vector<PageNode*>));

  private:
    std::vector<Page*> pages;
    std::vector<PageNode*> pageWeights;

    /**
     * @brief Helper function for the page rank algorithm to update the weights by one iteration
     * @param dampingFactor the damping factor to use in the ranking
     * @return the new weights of the pages
     */
    std::vector<PageNode*> getNextWeights(double dampingFactor);

    /**
     * @brief Helper function for the page rank algorithm to get the PageNode associated with a specific Page
     * @param pSearch the page to search with
     * @return the page node that is associated with this page
     */
    PageNode* getPageNode(Page* pSearch);
};
