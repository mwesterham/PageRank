build: PageRank.o Page.o PageNetwork.o
	g++ -std=c++11 PageRank.o Page.o PageNetwork.o -o executable.out

PageRank.o: PageRank.cpp
	g++ -std=c++11 -c PageRank.cpp
	
Page.o: definitions/Page.cpp definitions/Page.h
	g++ -std=c++11 -c definitions/Page.cpp
	
PageNetwork.o: definitions/PageNetwork.cpp definitions/PageNetwork.h
	g++ -std=c++11 -c definitions/PageNetwork.cpp

clean:
	rm *.o