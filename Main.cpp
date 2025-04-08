// Philasande Ngubo (NGBPHI016)
// Date: 1/04/2024
// University of Cape Town
// (c) 2025

#include <iostream>
#include <string>
#include "PGMimageProcessor.h"
#include <algorithm>
#include <cctype>
#include <fstream>

#define process  imageProcessor.extractComponents( buffer ,Threshold );\
if ( Default_Minimum_Valid_Object_Size > 1){ imageProcessor.filterComponentsBySize(Default_Minimum_Valid_Object_Size, imageProcessor.getLargestSize());}\
if (MaxSize){ imageProcessor.filterComponentsBySize(MinSize,MaxSize);}\
if ( Output_File.size() > 4){ imageProcessor.writeComponents(Output_File);}\
if (shouldPrint){\
\
	for (auto itr = imageProcessor.connectedComponents->begin(); itr != imageProcessor.connectedComponents->end() ; ++itr){\
		imageProcessor.printComponentData( *(*itr) );\
		std::cout<<std::endl;\
	}\
} 0

// User arguements

int Default_Minimum_Valid_Object_Size =1;
int MinSize = 0;
int MaxSize = 0;
int Threshold = 0;
bool shouldPrint = false;
std::string Output_File = "";

bool isPGM(std::string file){ //Checks if file a pgm
	int size = file.size();

	if ( file.size() > 4){
		return file.substr(size-4,4) == ".pgm";
	}
	return false;
	
}

bool isPPM(std::string file){ //Checks if file a pgm
	int size = file.size();

	if ( file.size() > 4){
		return file.substr(size-4,4) == ".ppm";
	}
	return false;
	
}

bool fileExists(std::string file){ //Checks if file exists
    std::ifstream filea(file);
	return filea.good();

}

bool isValid(int charc, char ** charv){

	int m =0;
	int f =0;
	int t =0;
	int p =0;
	int o =0;

	for (int i =2 ; i < charc; ++i){ // check if no arguement is repeated and per arguement is the value correct
		std::string cur = charv[i];
		if ( cur == "-m"){
			m++;
			if (m >1){
				return false;
			}

			try{
				std::string next_item = charv[i+1];
				Default_Minimum_Valid_Object_Size = std::stoi(next_item);

			}
			catch (int i){ return false;}

		}

		if ( cur == "-f"){
			f++;
			if (f>1){
				return false;
			}

			try{
				std::string next_item = charv[i+1];
				std::string next_item_2 = charv[i+2];

				MinSize = std::stoi(next_item);
				MaxSize = std::stoi(next_item_2);
				if (MinSize > MaxSize){
					return false;
				}

			}
			catch (int i){ return false;}

		}

		if ( cur == "-t"){
			t++;
			if (t >1){
				return false;
			}
			try{
				std::string next_item = charv[i+1];
				Threshold = std::stoi(next_item);
				if (Threshold < 1){
					return false;
				}

			}
			catch (int i){ return false;}

		}

		if ( cur == "-p"){
			p++;
			shouldPrint = true;
			if (p>1){
				return false;
			}

		}

		if ( cur == "-o"){
			o++;
			if (o >1){
				return false;
			}

			try{
				Output_File = charv[i+1];
				if ( !isPGM(Output_File)){
					return false;
				}

			}
			catch (int i){ return false;}

		}
	}



	return true;
}

void run(int charc, char ** charv){

	bool valid_arguement=  isValid(charc, charv);

	if ( charc > 1){

		std::string input = charv[1];

		if (valid_arguement){
			if ( isPGM(input) || isPPM(input) ){

				if (fileExists(input)){

					if (Threshold > 0){

					int wd,ht;
					wd = 0;
					ht =0;
					unsigned char * buffer;
						
					if (isPGM(input)){
						PGMimage image;
						image.read(input);
						image.getDims(wd,ht);
						buffer = const_cast<unsigned char *>(image.getBuffer());
						PGMimageProcessor<PGMimage> imageProcessor(wd,ht);
						process;
					    

					}else{
						PPMimage image;
						image.read(input);
						image.getDims(wd,ht);
						buffer = const_cast<unsigned char *>(image.getBuffer());
						PGMimageProcessor<PPMimage> imageProcessor(wd,ht);
						process;
					}

					/*PGMimageProcessor<PGMimage> imageProcessor(wd,ht);
					imageProcessor.extractComponents( buffer ,Threshold );
					if ( Default_Minimum_Valid_Object_Size > 1){ imageProcessor.filterComponentsBySize(Default_Minimum_Valid_Object_Size, imageProcessor.getLargestSize());}
					if (MaxSize){ imageProcessor.filterComponentsBySize(MinSize,MaxSize);}
					if ( Output_File.size() > 4){ imageProcessor.writeComponents(Output_File);}
					if (shouldPrint){

						for (auto itr = imageProcessor.connectedComponents->begin(); itr != imageProcessor.connectedComponents->end() ; ++itr){
							imageProcessor.printComponentData( *(*itr) );
							std::cout<<std::endl;
						}
					}*/


					}else{
						std::cout<< "No threshold value provided  i.e  -t int"<<std::endl;
					}
				}
				else{
					std::cout<< "No such file "<< input<<"."<<std::endl;
				}

			}else{
				std::cout<< "Expected a pgm/ppm image as a first agurment but none was provided."<<std::endl;
			}
		}else{
			std::cout<< "Invalid Arguements."<<std::endl;
		}
	}
	else{
		std::cout<< "Expected arguments but none were provided."<<std::endl;
	}
}




int main(int charc, char ** charv){

	run(charc,charv);
	return 0;
}
