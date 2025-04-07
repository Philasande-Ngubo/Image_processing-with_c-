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

void PGMimageProcessor::iterative_bfs(unsigned char * threshold, int * visited, int index, int num_objects, int minSize){

	// Create a queue for BFS
    std::queue<int> q;
    q.push(index);  

    while (!q.empty()) {
        int current_index = q.front();  // Get the next pixel to process
        q.pop();  

        if (visited[current_index]) continue; 

        if ( int(threshold[current_index]) < minSize) {
            threshold[current_index] = 0;
            visited[current_index] = 1;
            continue;
        }

        // Mark this pixel as part of the current object
        threshold[current_index] = static_cast<unsigned char>(num_objects);
        visited[current_index] = 1;

        int y = current_index / width;
        int x = current_index % width;

        // Calculate neighbors (up, down, left, right)
        int up = (y - 1) * width + x;
        int down = (y + 1) * width + x;
        int before = current_index - 1;
        int after = current_index + 1;

        if (y > 0 && !visited[up]) {  // Not the top-most pixel
            q.push(up);
        }
        if (y < height - 1 && !visited[down]) {  // Not the down-most pixel
            q.push(down);
        }
        if (x > 0 && !visited[before]) {  // Not the left-most pixel
            q.push(before);
        }
        if (x < width - 1 && !visited[after]) {  // Not the right-most pixels
            q.push(after);
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
				iterative_bfs(threshold,visited,i,num_Objects,minValidSize);

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
	int max = 0;  //
	
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
	std::cout<< "Pixel \n"<<"  ID: "<<theComponent.id<< std::endl<<"  Number of pixels: "<<theComponent.get()->size()<<std::endl;
}



// -----------------------------------ConnectedComponent class -----------------------------------------------
std::vector<int> * ConnectedComponent::get() const{
	return pixels;
}
