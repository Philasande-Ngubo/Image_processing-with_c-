#ifndef IMG_P
#define IMG_P

#include "PGMimage.h"
#include <memory>
#include <iterator>
#include <vector>
#include <iostream>

class ConnectedComponent{
	private:
	 int id;
	 std::vector<int> * pixels = new std::vector<int>();
	
	public:
	 ConnectedComponent(int identity): id(identity){}
	 ConnectedComponent(int identity , std::vector<int> *&& pxls): id(identity), pixels(pxls){}
	 ~ConnectedComponent(){
		 //delete [] pixels;
	 }
	 void add(int pixel){ (*pixels).push_back(pixel);}
	 
	 std::vector<int> * get() const;
};

class PGMimageProcessor{
	
	private:
	 PGMimage image;
	 int width,height;
	 int getIndex(std::vector<std::vector<int>> * cons, int num);
	 void add(std::vector<std::vector<int>> * cons, int before, int up);
	 std::unique_ptr<std::vector< ConnectedComponent *> > connectedComponents = std::make_unique<std::vector< ConnectedComponent*>>();
	
	public:
	 PGMimageProcessor(int wdt, int ht) :width(wdt), height(ht){ }
	 PGMimageProcessor(const PGMimageProcessor& other);
	 PGMimageProcessor(PGMimageProcessor&& other);
	 ~PGMimageProcessor(){} //No need
	 
	 int extractComponents(unsigned char * threshold, int minValidSize); 
	 int filterComponentsBySize(int minSize, int maxSize); 
	 bool writeComponents(const std::string& outFileName);
	 int getLargestSize(void) const; 
	 int getSmallestSize(void) const;
	 void printComponentData(const ConnectedComponent & theComponent) const; 	 
};

#endif