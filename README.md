PART 1                                                                           


To Compile the program:
    make  (Unix)

Arguements:1

<string filename>:
    (Compulsory)
    The first arguement should be the name of the input file
    from the order of arguements  does not matter:(strictly a PGM file) i.e: 

       findcomp InputFile.pgm <the rest of the other  arguements>

-t <int>:
    (Compulsory)
    additional to the inputfile  the threshold and is a compulsory arguement
    set the threshold for component detection (default=128, limit to [0. . . 255]) 
    e.g
    
    findcomp input.pgm -t 120
this will detect connectedComponents with pixels of values greater than 119

-m <int>: 
    (Optional)
    this is an optional arguement it sets the defaults number of pixels a connectedComponent should
    have to be considered. e.g

    findcomp input.pgm -t 120 -m 100
this will detect connectedComponents with pixels of values greater than 119 and more than 99 in number

-f <int min> <int max> :
    (Optional)
    This filters the connectedComponents to leave the ones with the number of pixels in the range
    (min-max) inclusive

     findcomp input.pgm -t 120 -f 1200 7000
   this will detect connectedComponents with pixels of values greater than 119 and between 1200 and 7000 in number

-p:
    (Optional)   
    print out all the component data (entries do not have to be sorted) as well as the total 
    component number and the sizes of the smallest and largest components.

-w <string filename(PGM)>:
    (optional):
    write out all retained components (as foreground/background pixels) to a new PGM file.  

-b <string filename<PPM>>:
    (optional)
    draws a thin red box around the extracted connectedComponents and saves the result
    to the specified output PPM file

Examples:

1.     findcomp Birds.pgm -t 100

2.     findcomp Birds.pgm -t 110 -m 2000
   this is the same as findcomp Birds.pgm -m 2000 -t 100 (The order of other components don't matter)

3.     findcomp Birds.pgm -t 180 -m 2000 -f 3000 7500

4.     findcomp Birds.pgm -t 120 -m 2000  -p -f 3000 7500

5.     findcomp Birds.pgm -p -t 145 -m 2000 -f 3000 7500 -w Birds_o.pgm

6.     findcomp Birds.pgm -p -t 145 -m 2000 -f 3000 7500 -w Birds_o.pgm -b results.ppm

NB: the order of the Arguements doesn't matter except the input name must be at the beginning



TESTING 


NB: The file test_file/Chess_Colours.pgm is used for testing and should therefore be not disturbed

To compile tests run:

    make test

To run 

    ./test

 FILES CO-OPERATION 


There PGMimage.h/cpp and PPMimage.h/cpp provides methods to work pgm with and ppm images respectively.
There is then the PGMimageProcessor.h/cpp which contains connectedComponents class and the PGMimageProcessor template class that are the ones 
responsible for extracting components from images. The Main.cpp contains the main method and the logic for the arguements extraction from the terminal
Additionally there is a Tests.cpp to test wether the program operates as it should with this class is a folder test_file which contains the Chess.pgm that
is used for the testing.

I have also added a few PPM and PGM images to use for tests
