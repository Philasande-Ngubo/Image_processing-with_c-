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
template <class T>
PGMimageProcessor<T>::PGMimageProcessor(const PGMimageProcessor& other){
	width = other.width;
	height = other.height;
	
	(*connectedComponents).clear();
	
	for (auto itr = (*other.connectedComponents).begin(); itr != (*other.connectedComponents).end(); ++itr){
		(*connectedComponents).push_back(*itr);
	}
	
}

template <typename T>
PGMimageProcessor<T>::PGMimageProcessor(PGMimageProcessor&& other){
	
	width = other.width;
	height = other.height;
	
	(*connectedComponents).clear();
	
	for (auto itr = (*other.connectedComponents).begin(); itr != (*other.connectedComponents).end(); ++itr){
		(*connectedComponents).push_back(*itr);
	}
	
	//now clean the other object 
	other.connectedComponents = nullptr;

}

template <typename T>
void PGMimageProcessor<T>::iterative_bfs(unsigned char * threshold, int * visited, int index, int num_objects, int minSize){

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

template <typename T>
int PGMimageProcessor<T>::extractComponents(unsigned char * threshol, int minValidSize){
	int num_Objects = 0;
	unsigned char * threshold;

	if (isPGM()){
		threshold = threshol;
		curFile = new unsigned char[width*height];
		for (int i = 0; i< height*width; i++){curFile[i] = threshol[i];}
	}
	else{
		curFile = threshol; // is a ppm image construct an intensity buffer
		threshold = new unsigned char[height*width];
		int index = -1;
    	for (int i = 0; i< height*width; i++){
        	int Intensity = static_cast<int> (static_cast<float>(  0.299*int(threshol[++index]) +  0.587*int(threshol[++index]) +  0.114*int(threshol[++index])));
        	threshold[i] = char(Intensity);
    	}
	}

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

template <typename T>
int PGMimageProcessor<T>::filterComponentsBySize(int minSize, int maxSize){
	
	auto filtered_items = (*connectedComponents).erase( // erase idioms
        std::remove_if(
            (*connectedComponents).begin(),
            (*connectedComponents).end(),
            [minSize,maxSize](ConnectedComponent* rejects) { return ! rejects->inRange(minSize,maxSize); } // predicate
        ),
		(*connectedComponents).end()
    );
	return (*connectedComponents).size();
}

template <typename T>
bool PGMimageProcessor<T>::writeComponents(const std::string& outFileName){

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

template <typename T>
int PGMimageProcessor<T>::getLargestSize(void) const{
	int max = 0;  //
	
	for ( auto itr = (*connectedComponents).begin() ; itr !=(*connectedComponents).end();++itr ){
		if ( (*itr)->get()->size() > max ){
			max = (*itr)->get()->size();
		}
	}
	return max;
}

template <typename T>
int PGMimageProcessor<T>::getSmallestSize(void) const{
	int min = INT_MAX;//largest int con
	
	for ( auto itr = (*connectedComponents).begin() ; itr !=(*connectedComponents).end();++itr ){
		if ( (*itr)->get()->size() < min ){
			min = (*itr)->get()->size();
		}
	}
	return min;
}

template <typename T>
void PGMimageProcessor<T>::printComponentData(const ConnectedComponent & theComponent) const{
	std::cout<< "Pixel \n"<<"  ID: "<<theComponent.id<< std::endl<<"  Number of pixels: "<<theComponent.get()->size()<<std::endl;
}

template <typename T>
void PGMimageProcessor<T>::highlightComponents(std::string name) const{
	unsigned char * output;
	if(isPGM() ){
		output = new unsigned char[height*width*3];
	
		for ( int i = 0 ; i < height*width ; ++i){
			output[i*3] = curFile[i];
			output[i*3+1] = curFile[i];
			output[i*3+2] = curFile[i];

		}
	}
	else{
		output = curFile;
	}

	for ( auto itr =(*connectedComponents).begin() ; itr != (*connectedComponents).end(); ++itr ){ // draw rectangles for all the recorded components
		
		(*itr)->setMargins(width,height);
		drawRectangle( (*itr)->leftmost, (*itr)->rightmost,(*itr)->upmost, (*itr)->downmost  ,output);
	}

	PPMimage ppmimage;
	ppmimage.setImageData(output,width,height);
	ppmimage.write(name);
	if(isPGM() ){delete [] output;} //free the custom ppm from the pgm as no class is responsible for it
}

template <typename T>
void PGMimageProcessor<T>::drawRectangle(int leftmost, int rightmost, int upmost,int downmost, unsigned char * pixies) const {

	int line_width = (rightmost % width) - (leftmost % width);
	int line_height =(downmost /width) - (upmost/width);

	int topleft = ( upmost/width -2)*width + ( leftmost% width);
	int bottomleft = ( downmost/width -2)*width + ( leftmost% width);
	int topright = ( upmost/width -2)*width + ( rightmost% width);

	for (int i = topleft; i < topleft+line_width ; ++i){ //draw the top horizontal line
		if (i < 0){break;}
		pixies[i*3] = char(255);
		pixies[i*3 + 1] = char(0);
		pixies[i*3 + 2] = char(0);

		for (int j = 1 ; j < 2; ++j ){//thickness
			int index = (( i/ width) -j) * width + (i % width);
			if (index < 0){break;}
			pixies[index*3] = char(255);
			pixies[index*3 + 1] = char(0);
			pixies[index*3 + 2] = char(0);
		}

	}

	for (int i = bottomleft ; i < bottomleft+ line_width ; ++i){ //draw the bottom horizontal line
		if (i > height *width){break;}
		pixies[i*3] = char(255);
		pixies[i*3 + 1] = char(0);
		pixies[i*3 + 2] = char(0);

		for (int j = 1 ; j < 2; ++j ){//thickness
			int index = (( i/ width) +j) * width + (i % width);
			if (index > height *width ){break;}
			pixies[index*3] = char(255);
			pixies[index*3 + 1] = char(0);
			pixies[index*3 + 2] = char(0);
		}
	}

	for (int i = topleft; i < topleft + line_height* width; i+=width){ //draw the left vertical line

		pixies[i*3] = char(255);
		pixies[i*3 + 1] = char(0);
		pixies[i*3 + 2] = char(0);

		for (int j = 1 ; j < 2; ++j ){ //thickness
			int index = i -j;
			if ( i/width > index){break;}
			pixies[index*3] = char(255);
			pixies[index*3 + 1] = char(0);
			pixies[index*3 + 2] = char(0);

		}

	}

	for (int i = topright; i < topright + line_height* width; i+=width){ //draw the right vertical line

		pixies[i*3] = char(255);
		pixies[i*3 + 1] = char(0);
		pixies[i*3 + 2] = char(0);

		for (int j = 1 ; j < 2; ++j ){ //thickness
			int index = i +j;
			if ( i/width > index){break;}
			pixies[index*3] = char(255);
			pixies[index*3 + 1] = char(0);
			pixies[index*3 + 2] = char(0);

		}

	}

}

template class PGMimageProcessor<PGMimage>;
template class PGMimageProcessor<PPMimage>;

// -----------------------------------ConnectedComponent class -----------------------------------------------


ConnectedComponent::ConnectedComponent( ConnectedComponent & other): id(id), leftmost(leftmost), rightmost(rightmost), upmost(upmost), downmost(downmost){
	pixels->clear();
	for ( auto itr = pixels->begin(); itr != pixels->end(); ++itr){
		pixels->push_back(*itr);
	}
}

ConnectedComponent::ConnectedComponent( ConnectedComponent && other): id(id), leftmost(leftmost), rightmost(rightmost), upmost(upmost), downmost(downmost){
	pixels->clear();
	for ( auto itr = other.pixels->begin(); itr != other.pixels->end(); ++itr){
		pixels->push_back(*itr);
	}
	other.pixels->clear();
	pixels = nullptr;

}

std::vector<int> * ConnectedComponent::get() const{
	return pixels;
}

void ConnectedComponent::setMargins(int width, int height){
	leftmost = -1;rightmost =-1;
	upmost =-1;downmost =-1;

	if ( pixels->size() ==0){return;}

	leftmost = pixels->at(0);
	rightmost = leftmost;
	upmost = leftmost;
	downmost = upmost;

	for ( auto itr = pixels->begin(); itr != pixels->end(); ++itr){
		int pos = * itr;
		if ( (leftmost % width ) > (pos % width)  ){leftmost =pos;}   //Recording the edges
		if ( (rightmost % width ) < (pos % width)  ){rightmost =pos;}
		if ( (upmost /width ) > (pos / width)  ){upmost =pos;}
		if ( (downmost /width ) < (pos / width)  ){downmost =pos;}
	}

}