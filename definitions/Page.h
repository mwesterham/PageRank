#include <vector>

/**
 * @brief Represents a page in a page network
 */
class Page {
  public:
    /**
     * @brief Constructor to instantiate a Page object
     * @param id the integer id of this page
     */
    Page(int id);

    /**
     * @brief Declare this page references another page.
     * @param p the page that is being referenced by this current page
     * 
     * Updates both the referencer and the referencee
     */
    void addPageReference(Page* p) {
      this->addOutgoingEdge(p);
      p->addIncomingEdge(this);
    }
    
    /**
     * @brief Getter function to retrieve the Page's id
     */
    int getId();

    /**
     * @brief Getter function to retrieve the Page's outgoing edges
     * @return the vector that holds all outgoing edges
     */
    std::vector<Page*> getOutgoingEdges();

    /**
     * @brief Getter function to retrieve the Page's incoming edges
     * @return the vector that holds all incoming edges
     */
    std::vector<Page*> getIncomingEdges();

  private:
    int id;
    std::vector<Page*> outgoingEdges;
    std::vector<Page*> incomingEdges;

    /**
     * @brief Helper function to add a specified page to the list of outgoing edges
     * @param page the page to add the outgoing page list
     */
    void addOutgoingEdge(Page* page);

    /**
     * @brief Helper function to add a specified page to the list of incoming edges
     * @param page the page to add the incoming page list
     */
    void addIncomingEdge(Page* page);
};
