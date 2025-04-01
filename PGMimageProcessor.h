#ifndef IMG_P
#define IMG_P

#include "PGMimage.h"
#include <memory>
#include <iterator>
#include <vector>
class PGMimageProcessor{
	
	private:
	 int width,height;
	 std::unique_ptr<std::vector<* ConnectedComponent> > connectedComponents = std::make_unique<std::vector<* ConnectedComponent>>();_;
	
	public:
	 PGMimageProcessor(int wdt, int ht) :width(wdt), height(ht){ }
	 PGMimageProcessor(PGMimageProcessor& other);
	 PGMimageProcessor(PGMimageProcessor&& other);
	 ~PGMimageProcessor(){}
	 
	 int extractComponents(unsigned char threshold, int minValidSize); 
	 int filterComponentsBySize(int minSize, int maxSize); 
	 bool writeComponents(const std::string& outFileName);
	 int getLargestSize(void) const; 
	 int getSmallestSize(void) const;
	 void printComponentData(const ConnectedComponent & theComponent) const; 	 
};

class ConnectedComponent{
	private:
	 int id;
	 std::vector<int> * pixels;
	
	public:
	 ConnectedComponent(int identity , std::vector<int>*&& pxls): id(identity), pixels(pxls){}
	 ConnectedComponent(ConnectedComponent& other);
	 ConnectedComponent(ConnectedComponent&& other);
	 ~ConnectedComponent(){}
	 
	 vector<int> *&& get();
};
#endif