// Philasande Ngubo (NGBPHI016)
// Date: 04/04/2024
// University of Cape Town
// (c) 2025
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PGMimageProcessor.h"
#include <fstream>
#include <cstdio>

bool fileExists(std::string file){ //Checks if file exists
   std::ifstream filea(file);
  return filea.good();

}

TEST_CASE ("Test number of  Connected Component(Extracted components)")
 {
    PGMimage image;
    image.read("Chess_Colours.pgm");
    int wd,ht;
    image.getDims(wd,ht);

    PGMimageProcessor imageProcessor(wd,ht);
    REQUIRE( imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()),171 ) == 6);
    
 }


TEST_CASE ("MinSize Connected Component")
 {
    PGMimage image;
    image.read("Chess_Colours.pgm");
    int wd,ht;
    image.getDims(wd,ht);

    PGMimageProcessor imageProcessor(wd,ht);
    imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()),171 );

    REQUIRE( imageProcessor.getSmallestSize() == 4301);
    
 }

 TEST_CASE ("MaxSize Connected Components")
 {
    PGMimage image;
    image.read("Chess_Colours.pgm");
    int wd,ht;
    image.getDims(wd,ht);

    PGMimageProcessor imageProcessor(wd,ht);
    imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()),171 );

    REQUIRE( imageProcessor.getLargestSize() == 7961);
    
 }

 TEST_CASE ("Test for filterComponentsBySize")
 {
    PGMimage image;
    image.read("Chess_Colours.pgm");
    int wd,ht;
    image.getDims(wd,ht);

    PGMimageProcessor imageProcessor(wd,ht);
    imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()),171 );

    REQUIRE( imageProcessor.getSmallestSize() == 4301); //Before extracting
    REQUIRE( imageProcessor.getLargestSize() == 7961);

    REQUIRE(imageProcessor.filterComponentsBySize(7000,7961) == 3 );
   
    REQUIRE( imageProcessor.getSmallestSize() == 7055); //after extracting
    REQUIRE( imageProcessor.getLargestSize() == 7961);

    
 }

 TEST_CASE ("Test for writeComponents1")
 {
    
    PGMimage image;
    image.read("Chess_Colours.pgm");
    int wd,ht;
    image.getDims(wd,ht);

    PGMimageProcessor imageProcessor(wd,ht);
    imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()),171 );

    std::string filename ="cbnbvbcvbfbvfvbdjfdjfdkfdf.pgm";

    if (fileExists(filename)){remove("cbnbvbcvbfbvfvbdjfdjfdkfdf.pgm");}

    REQUIRE( imageProcessor.writeComponents(filename)); //Before exctracting
    REQUIRE( fileExists(filename));

    if (fileExists(filename)){remove("cbnbvbcvbfbvfvbdjfdjfdkfdf.pgm");}
 }

