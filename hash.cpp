#include <iostream>
#include <functional>
#include "hash.h"
#include "common.h"

int quadProb(int i){
    int counter = 0; 
    i = i + counter * counter;
    counter++;  
    return i; 
}

int Hash::hashing(std::string key){
    std::size_t hashed = hashString(key);
    return (size_t) (hashed % tableSize);

}

void Hash::swapingHash(itemHash &a, itemHash &b){
    itemHash holder(a.keyHash, a.info, a.heapHere);
    itemHash temp;

    a.keyHash = b.keyHash;
    a.info = b.info;
    a.heapHere = b.heapHere;

    b.keyHash = holder.keyHash;
    b.info = holder.info;
    b.heapHere = holder.heapHere;
}

void Hash::swaping(item &a, item &b){
 
    item holder(a.key, a.freq, a.tieBreaker, a.heapIndex, a.hashPosition);
    
    int tempAHashIndex = a.hashPosition;
    int tempBHashIndex = b.hashPosition; 
    std::string holdHashKey = hashVec[a.hashPosition].keyHash;
    int holdHashHeap = hashVec[a.hashPosition].heapHere; 

    a.key = b.key;
    a.freq = b.freq;
    a.tieBreaker = b.tieBreaker;
    a.heapIndex = b.heapIndex;
    a.hashPosition = b.hashPosition;
    
    hashVec[tempAHashIndex].heapHere = hashVec[b.hashPosition].heapHere;  
    b.key = holder.key;
    b.freq = holder.freq;
    b.tieBreaker = holder.tieBreaker;
    b.heapIndex = holder.heapIndex;
    b.hashPosition = holder.hashPosition;

    hashVec[tempBHashIndex].heapHere = holdHashHeap;

}

void Hash::percolateUp(int i) {

    while(i > 0){
        if( (heapVec[i].freq < heapVec[i/2].freq) || ( heapVec[i].freq == heapVec[i/2].freq && heapVec[i].tieBreaker > heapVec[i/2].tieBreaker)){
            swaping(heapVec[i/2], heapVec[i]); 
        }
        i = i/2;
        //percolateUp(i);
    }
}

void Hash::percolateDown(int i) {

    int left = 2*i + 1 ;
    int right = 2*i + 2; 
 
    while(left < heapSize ){
        
        if ( (right < gHeapIndex) ) {
         
            if( right < gHeapIndex && ( (heapVec[right].freq < heapVec[left].freq) || ( heapVec[right].freq == heapVec[left].freq && heapVec[right].tieBreaker > heapVec[left].tieBreaker ) ) ){
                left++;
            }
        }

        if ( (heapVec[i].freq < heapVec[left].freq) || ( heapVec[i].freq == heapVec[left].freq) && heapVec[i].tieBreaker > heapVec[left].tieBreaker){        

        }

        if ( (heapVec[i].freq > heapVec[left].freq) || ( heapVec[i].freq == heapVec[left].freq) && heapVec[i].tieBreaker < heapVec[left].tieBreaker ){
             
            swaping(heapVec[left], heapVec[i]); 

        }
 
        i = left; 
        left = 2 * left  + 1; 
    }

}

void Hash::search(std::string parKey){
    bool found = false;
    int tablePosition = hashing(parKey);
    int tablePosition2 = tablePosition; 
    int counter = 0;
    int counter2 = 0; 

    if(gHeapIndex != 0){

        while(found == false && counter < tableSize/2){

            if(hashVec[tablePosition].info == EMPTY){

                break;
            }
            else if (hashVec[tablePosition].info == USING && hashVec[tablePosition].keyHash == parKey){

                heapVec[hashVec[tablePosition].heapHere].setFreq( (heapVec[hashVec[tablePosition].heapHere].getFreq() + 1) );

                int hold = hashVec[tablePosition].heapHere;
                percolateDown(hold);
                
                found = true;
            }
            else{
                ++counter;
                tablePosition = (tablePosition2 +  counter * counter) % tableSize;
            }
        }
    }        

    if (!found){

        if( gHeapIndex < heapVec.size()){
            
            heapVec.at(gHeapIndex) = item(parKey, 1, gTie, gHeapIndex, tablePosition2);

            
            if(hashVec[tablePosition2].info == EMPTY || hashVec[tablePosition2].info == DELETE){
                hashVec[tablePosition2].keyHash = parKey;
                hashVec[tablePosition2].info = USING;

                hashVec[tablePosition2].heapHere = gHeapIndex; 
            }
            
            else {

                tablePosition = tablePosition2; 
                while(counter2 < tableSize){
  
                    ++counter2; 
                    tablePosition = (tablePosition2 + counter2 * counter2) % tableSize;
                    
                    if(hashVec[tablePosition].info != USING){
                        hashVec[tablePosition].keyHash = parKey;
                        hashVec[tablePosition].info = USING;
                        hashVec[tablePosition].heapHere = gHeapIndex; 
                        heapVec[gHeapIndex].hashPosition = tablePosition; 
                    } 
                }
            }

            percolateUp(gHeapIndex);

            gHeapIndex++;
            ++gTie;
            
        }
        else if ( gHeapIndex > heapVec.size() - 1){

            heapVec[0].key = parKey;
            heapVec[0].setFreq(heapVec[0].freq + 1);
            heapVec[0].tieBreaker = gTie; 

            hashVec[heapVec[0].hashPosition].info = DELETE;            
            tablePosition = tablePosition2;
            if(hashVec[tablePosition].info == USING){

                while (counter2 < tableSize){  
                    ++counter2;          
                    tablePosition = (tablePosition2 + counter2 * counter2) % tableSize;
                    if(hashVec[tablePosition].info != USING){
                        break;
                    }
                }
            }

            hashVec[tablePosition].keyHash = parKey;        
            hashVec[tablePosition].info = USING;
            hashVec[tablePosition].heapHere = 0;
            heapVec[0].hashPosition = tablePosition; 
        
            percolateDown(0);
            ++gTie; 
        }        
    }
}
