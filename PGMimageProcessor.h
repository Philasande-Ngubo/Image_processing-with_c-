#ifndef IMG_P
#define IMG_P

#include "PGMimage.h"

class PGMimageProcessor :public PGMimage{
	public:
	 PGMimageProcessor(){}
	 PGMimageProcessor(PGMimageProcessor& other);
	 PGMimageProcessor(PGMimageProcessor&& other);
	 
	 int extractComponents(unsigned char threshold, int minValidSize); 
	 int filterComponentsBySize(int minSize, int maxSize); 
	 bool writeComponents(const std::string & outFileName);
	 int getLargestSize(void) const; 
	 int getSmallestSize(void) const;
	 void printComponentData(const ConnectedComponent & theComponent) const; 
	 
	 
};
#endif