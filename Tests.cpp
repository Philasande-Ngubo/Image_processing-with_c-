#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PGMimageProcessor.h"




int one =1;
int two =2;

TEST_CASE ("Test number of  Connected Component")
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

 TEST_CASE (" Connected Components")
 {
    PGMimage image;
    image.read("Chess_Colours.pgm");
    int wd,ht;
    image.getDims(wd,ht);

    PGMimageProcessor imageProcessor(wd,ht);
    imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()),171 );

    REQUIRE( imageProcessor.getLargestSize() == 7961);
    
 }

