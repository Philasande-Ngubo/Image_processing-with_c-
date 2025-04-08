// Philasande Ngubo (NGBPHI016)
// Date: 1/04/2024
// University of Cape Town
// (c) 2025

#ifndef IMG_P
#define IMG_P

#include "PGMimage.h"
#include "PPMimage.h"
#include <memory>
#include <iterator>
#include <vector>
#include <iostream>
#include <type_traits>

class ConnectedComponent{
	private:
	 int id;
	 std::vector<int> * pixels = new std::vector<int>();
	
	public:
	 ConnectedComponent(int identity): id(identity){}
	 ConnectedComponent(int identity , std::vector<int> *&& pxls): id(identity), pixels(pxls){}
	 ~ConnectedComponent(){
		 delete [] pixels;
	 }
	 void add(int pixel){ (*pixels).push_back(pixel);}
	 std::vector<int> * get() const;
	 bool isEmpty(){ return ( pixels->size()==0 );}
	 bool inRange(int min, int max) const{ return ( min -1 < pixels->size()) && ( pixels->size() < max+1) ;} //inclusive
	 
	 template <typename T>
	 friend class PGMimageProcessor;

};

template <typename T>
class PGMimageProcessor{
	
	private:
	 PGMimage image;
	 int width,height;
	 void iterative_bfs(unsigned char * threshold, int * visited, int index, int num_objects, int minSize);
	 std::unique_ptr<std::vector< ConnectedComponent *> > connectedComponents = std::make_unique<std::vector< ConnectedComponent*>>();
	 bool isPGM() const{return std::is_same_v<T, PGMimage> ;}

	
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
	 
	 friend void run(int charc, char ** charv);
};

#endif