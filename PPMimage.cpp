// copyright, Patrick Marais
// Department of Computer Science
// University of Cape Town
// (c) 2025
//MOdified by Philasande Ngubo to cater for PPMimages

#include <iostream>
#include <string>
#include <fstream>

#include "PPMimage.h"
#include "PGMimage.h"

using namespace std;

void PPMimage::setImageData(unsigned char* data, int wd, int ht)
{
    if (data == nullptr || wd < 1 || ht < 1)
    {
        cerr << "setImageData() invalid data specified - aborted.\n";
        return;
    }
    //if (buffer) delete[] buffer;
    buffer = new unsigned char[wd * ht * 3]; // 3 channels for RGB
    width = wd; height = ht;
    for (size_t i = 0; i < wd * ht * 3; ++i) buffer[i] = data[i];
}

void PPMimage::read(const string& fileName)
{
    ifstream ifs(fileName, ios::binary);
    if (!ifs)
    {
        cerr << "Failed to open file for read: " << fileName << endl;
        return;
    }
    string line;
    ifs >> line >> ws;
    if (line != "P6")
    {
        cerr << "Malformed PPM file - magic is: " << line << endl;
        return;
    }
    while (getline(ifs, line))
    {
        if (line[0] != '#') break;
    }
    istringstream iss(line);
    iss >> width >> height;

    if (!iss)
    {
        cerr << "Header not correct - unexpected image sizes found: " << line << endl;
        return;
    }
    int maxChan = 0;
    ifs >> maxChan >> ws;
    if (maxChan != 255)
    {
        cerr << "Max color level incorrect - found: " << maxChan << endl;
    }

    buffer = new unsigned char[width * height * 3]; // 3 channels for RGB
    ifs.read(reinterpret_cast<char*>(buffer), width * height * 3);

    if (!ifs)
    {
        cerr << "Failed to read binary block - read\n";
    }

    ifs.close();
}

void PPMimage::write(const string& fileName)
{
    if (buffer == nullptr || width< 1 || height < 1)
    {
        cerr << "Invalid data for PPM write to " << fileName << endl;
        return;
    }
    ofstream ofs(fileName, ios::binary);
    if (!ofs)
    {
        cerr << "Unable to open PPM output file " << fileName << endl;
        return;
    }

    ofs << "P6\n#File produced by P Marais\n" << width << " " << height << endl << 255 << endl;
    ofs.write(reinterpret_cast<char*>(buffer), width * height * 3);
    if (!ofs)
    {
        cerr << "Error writing binary block of PPM.\n";
    }

    ofs.close();
}

/*int main(){
    PPMimage image;
    image.read("Mxo.ppm");
    int wd, ht;
    image.getDims(wd,ht);
    std::cout<<"Width :"<<wd<<" , Height:"<<ht<<". \n";

    unsigned char * buffer = const_cast<unsigned char *>(image.getBuffer());
    image.setImageData( buffer,320,320);
    image.write("inja_mfethu.ppm");

    unsigned char * OutPut = new unsigned char[wd*ht];
    int index = -1;
    for (int i = 0; i< ht*wd; i++){
        int Intensity = static_cast<int> (static_cast<float>(  0.299*int(buffer[++index]) +  0.587*int(buffer[++index]) +  0.114*int(buffer[++index])));
        OutPut[i] = char(Intensity);
    }

    PGMimage pimage;
    pimage.setImageData( OutPut,320,320);
    pimage.write("Nguuu.pgm");
    return 0;
}*/