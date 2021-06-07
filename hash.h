#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector>
#include "common.h"

enum SlotInfo { USING, EMPTY, DELETE };
//struct item; 
struct itemHash; 



      struct item
      {
            std::string key;
            int freq;
            int tieBreaker;
            int heapIndex;
            //itemHash * hashPtr;
            int hashPosition;

            int getFreq() {return freq;}
            void setFreq(int i) { freq = i; }
            void updateFreq() {freq = freq++;} 

            item() : key(""), freq(), tieBreaker(0), hashPosition(0) {}
            
            item(std::string inKey, int inFreq, int inTie, int inHashPos): 
                     key(inKey), freq(inFreq), tieBreaker(inTie), hashPosition(inHashPos) {}
            
            item(std::string inKey, int inFreq, int inTie, int inIndex, int inHashPos): 
                     key(inKey), freq(inFreq), tieBreaker(inTie), heapIndex(inIndex), hashPosition(inHashPos) {}        
      };
      
      struct itemHash
      {
            std::string keyHash;
            SlotInfo info;
            //item * itemPtr;
            int heapHere; 

            itemHash(): keyHash(""), info(EMPTY), heapHere(0) {};
            itemHash(std::string inKey, SlotInfo i) : keyHash(inKey), info(i), heapHere(0) {}; 
            itemHash(std::string inKey, SlotInfo i, int inHeapH) : keyHash(inKey), info(i), heapHere(inHeapH) {}; 

      };     


class Hash {
    public: 
        
      int heapSize; //set heap size to argv[4]
      int tableSize; 
      std::hash<std::string> hashString;
      std::vector<itemHash> hashVec;
      std::vector<item> heapVec;


   //public:
      //struct itemHash; 
      //struct item;
      bool isPrime (int n) {
   if (n == 2 || n == 3)
      return true;
   if (n == 1 || n % 2 == 0)
      return false;
   for (int i = 3; i * i <= n; i += 2)
      if (n % i == 0)
         return false;
   return true;
}

int nextPrime(int n) {
   if (n <= 0)
      n == 3;
   if (n % 2 == 0)
      n++;
   for (; !isPrime( n ); n += 2);
      return n;
}


        Hash(int inHeap){
            heapSize = inHeap; 
            int twice = 2*inHeap;
            int theSize = nextPrime(twice);
            tableSize = theSize;
            
            hashVec.resize(theSize);
            heapVec.resize(inHeap);
        }

        void insert(std::string key);
        void remove(std::string key);
        void search(std::string key);
        int hashing(std::string key);
        void percolateUp(int i);
        void percolateDown(int i); 
        void print(item inKey);
        void swaping(item &a, item &b);
        void swapingHash(itemHash &a, itemHash &b); 
    
};

#endif