// copyright, Patrick Marais
// Department of Computer Science
// University of Cape Town
// (c) 2025

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef _PPMI_H
#define _PPMI_H

class PPMimage {
private:
    unsigned char* buffer;
    int width, height;
public:
    // alway create an empty PGMimage, then call read() or setImageData() to fill it.
    PPMimage() : buffer(nullptr), width(0), height(0) {}
   ~PPMimage() { if (buffer) delete[] buffer; }

    // getters
    const unsigned char* getBuffer(void) const
    {
        return buffer;
    }

    void getDims(int& wd, int& ht) const
    {
        wd = width; ht = height;
    }

    // set Image data from existing sized buffer (1D flattened array)
    void setImageData(unsigned char* data, int wd, int ht);

    // read and write PGM images
    void read(const std::string& fileName);
    void write(const std::string& fileName);
	
};

#endif
