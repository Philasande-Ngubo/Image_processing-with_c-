// Philasande Ngubo (NGBPHI016)
// Date: 1/04/2024
// University of Cape Town
// (c) 2025

#include "PGMimageProcessor.h"
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>

#define print(x) std::cout<<x<<std::endl;
// -----------------------------------PGMimageProcessor class -----------------------------------------------

PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other){
	width = other.width;
	height = other.height;
	
	(*connectedComponents).clear();
	
	for (auto itr = (*other.connectedComponents).begin(); itr != (*other.connectedComponents).end(); ++itr){
		(*connectedComponents).push_back(*itr);
	}
	
}

PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& other){
	
	width = other.width;
	height = other.height;
	
	(*connectedComponents).clear();
	
	for (auto itr = (*other.connectedComponents).begin(); itr != (*other.connectedComponents).end(); ++itr){
		(*connectedComponents).push_back(*itr);
	}
	
	//now clean the other object 
	other.connectedComponents = nullptr;

}

void PGMimageProcessor::rercusive_bfs(unsigned char * threshold, int * visited, int index, int num_objects, int minSize){

	if ( ! visited[index]){

		if (int(threshold[index]) < minSize ){ //Base case
			threshold[index] = char(0);
			visited[index] = 1;
		}else{

			threshold[index] = char(num_objects);
			visited[index] = 1;

			int y = static_cast<int>( index/ width);
			int x = index % width;

			int up = (y -1)*width + x;
			int down = (y +1)*width + x;

			int before = index -1;
			int after = index +1;

			//edge cases
			if ( y != 0){rercusive_bfs(threshold,visited, up,num_objects,minSize);} // not top-most pixel
			if ( y < height){rercusive_bfs(threshold,visited, down,num_objects,minSize);} //not the bottom-most pixel

			if (x != 0){rercusive_bfs(threshold,visited, before,num_objects,minSize);} //not the left-most pixel
			if (x < width){rercusive_bfs(threshold,visited, after,num_objects,minSize);} //not the right-most pixel

		}



	}

}

int PGMimageProcessor::extractComponents(unsigned char * threshold, int minValidSize){
	int num_Objects = 0;
	
	int * visited = new int[width*height];
	for (int i = 0 ; i < width*height;++i){ visited[i] = 0;}

	for (int i = 0 ; i < width*height;++i){

		if ( ! visited[i]){

			if ( int(threshold[i]) < minValidSize ){
				threshold[i] = char(0);
				visited[i] = 1;

			}else{
				num_Objects++;
				rercusive_bfs(threshold,visited,i,num_Objects,minValidSize);

			}

		}

	}

	(*connectedComponents).clear();

	delete [] visited;
	for (int i = 0; i < num_Objects; ++i){
		(*connectedComponents).push_back( new ConnectedComponent(i));
	}
	
	for (int i = 0 ; i < height*width; ++i){

		if ( int(threshold[i]) > 0){
			(*connectedComponents).at(int(threshold[i]) -1)->add(i);
			
		}
	}
	
	return  (*connectedComponents).size();
}

int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
	
	auto filtered_items = (*connectedComponents).erase(
        std::remove_if(
            (*connectedComponents).begin(),
            (*connectedComponents).end(),
            [minSize,maxSize](ConnectedComponent* rejects) { return ! rejects->inRange(minSize,maxSize); } // Predicate
        ),
		(*connectedComponents).end()
    );
	return (*connectedComponents).size();
}

bool PGMimageProcessor::writeComponents(const std::string& outFileName){

	try{
		unsigned char * outPut = new unsigned char[height*width];
		for (int i = 0; i < height*width ; ++i){ outPut[i] = char(0);}
		for ( auto itr =(*connectedComponents).begin() ; itr != (*connectedComponents).end(); ++itr ){
		
			for ( auto j = (*itr)->get()->begin() ; j !=(*itr)->get()->end() ; ++j){
				outPut[*j] = char(255);
		}
	}
	
	image.setImageData(outPut,width,height);
	image.write(outFileName);
	}
	catch(int myNum){
		std::cout<<"Could'nt write image to "<< outFileName<<std::endl;
		return false;
	}
	
	std::cout<<"Succesfully written image to "<< outFileName<<std::endl;
	return true;
}

int PGMimageProcessor::getLargestSize(void) const{
	int max = 0;
	
	for ( auto itr = (*connectedComponents).begin() ; itr !=(*connectedComponents).end();++itr ){
		if ( (*itr)->get()->size() > max ){
			max = (*itr)->get()->size();
		}
	}
	return max;
}

int PGMimageProcessor::getSmallestSize(void) const{
	int min = INT_MAX;//largest int con
	
	for ( auto itr = (*connectedComponents).begin() ; itr !=(*connectedComponents).end();++itr ){
		if ( (*itr)->get()->size() < min ){
			min = (*itr)->get()->size();
		}
	}
	return min;
}

void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{
	std::cout<<"ID: "<<theComponent.id<<std::endl<<"Number of pixels: "<<theComponent.get()->size();
}



// -----------------------------------ConnectedComponent class -----------------------------------------------
std::vector<int> * ConnectedComponent::get() const{
	return pixels;
}