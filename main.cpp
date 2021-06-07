#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "hash.h"
#include "common.h"

int gHeapIndex; 
int gTie;

int main(int argc, char *argv[]){

    std::ofstream outFile;
    std::ifstream inFile;
    std::string data = "";
    int hashTableSize = std::stoi(argv[3]);
    Hash mainHash(hashTableSize);       

    if (argc != 4) {
		std::cerr << "Error format: a.out inputFile outputFile K" << std::endl;
	} 
    else {

        inFile.open(argv[1]);
        outFile.open(argv[2]);
        gTie = 0;
        gHeapIndex = 0; 
        
        while(std::getline(inFile, data,',')){
            mainHash.search(data);
        }
        
        std::string output = "";
        for( const auto& x : mainHash.heapVec){
            output += x.key + ":" + std::to_string(x.freq) +  ",";
        }
        outFile << output;

        //go through; 
        /* if the value at in*/

        outFile.close();

    }
    return 0; 
}    