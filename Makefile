build: PageRank.o Page.o PageNetwork.o
	g++ -std=c++11 PageRank.o Page.o PageNetwork.o -o executable.out

PageRank.o: PageRank.cpp
	g++ -std=c++11 -c PageRank.cpp
	
Page.o: Page.cpp Page.h
	g++ -std=c++11 -c Page.cpp
	
PageNetwork.o: PageNetwork.cpp PageNetwork.h
	g++ -std=c++11 -c PageNetwork.cpp

clean:
	rm *.o