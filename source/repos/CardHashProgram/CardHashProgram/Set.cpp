#pragma once
#include"Main.h"

Set::Set() : hashTable() {}
/*
 _  _ _|_ _|_  _  ._ _
_> (/_ |_  |_ (/_ | _>
*/
std::string Set::getFileName() { return fileName; }
/*
 _   _ _|_ _|_  _  ._ _
(_| (/_ |_  |_ (/_ | _>
_|
*/
Card* Set::getHashTable(int i) const { return hashTable[i]; }
void  Set::setFileName(std::string file) { fileName = file; }
/*
                      _
|_       _ |   _ _|_ |_ ._   _|
|_) |_| (_ |< (/_ |_ |_ | | (_|

      DESCRIPTION : recursive function that takes the tail bucket link,
      and prints out links from head to tail
*/
std::string Set::bucketEnd(Card* endLink) const
{
      std::string s;

      if (endLink->getPrevPtr() == nullptr)
      {
            s = endLink->getFace() + " of " + endLink->getSuit() + " -> ";
            return s;
      }
      else
      {
            s = endLink->getFace() + " of " + endLink->getSuit() + " -> ";
            return bucketEnd(endLink->getPrevPtr()) + s;
      }
}
/*
                      _
|_       _ |   _ _|_ |_ ._ _  ._ _|_
|_) |_| (_ |< (/_ |_ |  | (_) | | |_

      DESCRIPTION : recursive function that takes the tail bucket link,
      and prints out links from head to tail
*/
std::string Set::bucketFront(Card* frontLink) const
{
      std::string s = frontLink->getFace() + " of " + frontLink->getSuit() + " -> ";
      if (frontLink->getNextPtr() == nullptr) return s;
      else { return s + bucketFront(frontLink->getNextPtr()); }
}

/*              _
|_   _.  _ |_  |_    ._   _ _|_ o  _  ._
| | (_| _> | | | |_| | | (_  |_ | (_) | |

      DESCRIPTION : takes key, runs through has function, and returns
      hash value*/

int Set::hashFunction(int key) const { return (key % TABLE_SIZE); }
/*

._  ._ o ._ _|_ |_|  _.  _ |_
|_) |  | | | |_ | | (_| _> | |
|
      DESCRIPTION : prints the entire Set hashTable with bucket links
*/
void Set::printHash(std::string graphic)
{
      Card* tmpPtr;

      std::cout << "\n\n";
      std::cout << graphic;

      for (int i = 0; i < TABLE_SIZE; i++)
      {
            tmpPtr = hashTable[i];
            if (tmpPtr == nullptr) std::cout << "\n\t " << "[" << i << "] -> NULL";
            else
            {
                  while (tmpPtr->getNextPtr() != nullptr)
                  {
                        tmpPtr = tmpPtr->getNextPtr();
                  }
                  std::cout << "\n\t [" << i << "] -> " << bucketEnd(tmpPtr);
            }
      }
}

/*
                   _
  _ |_   _   _ |  | \     ._
 (_ | | (/_ (_ |< |_/ |_| |_)
                          |
      DESCRIPTION : takes a newly created card pointer and probes Set
      hashTable for first available slot at the index
      corresponding to hashFunction */

bool Set::checkDup(Card* tmpHead, Card* newCard)
{
      if (tmpHead == nullptr) return false;
      else if (*tmpHead == newCard) return true;
      else     return checkDup(tmpHead->getNextPtr(), newCard);
      /*while (tmpHead != nullptr)
      {
      if (tmpHead == newCard) return true;
      tmpHead->setNextPtr(tmpHead->getNextPtr());
      }
      return false;*/

}
/*
  _
_|_ o ._   _| |   _.  _ _|_
 |  | | | (_| |_ (_| _>  |_

      DESCRIPTION : takes a newly created card pointer and probes Set
      hashTable for first available slot at the index
      corresponding to hashFunction
*/
Card* Set::findLast(Card* tmpHead)
{

      if (tmpHead->getNextPtr() == nullptr) return tmpHead;
      return findLast(tmpHead->getNextPtr());
}
/*
_
 _.  _|  _| /   _. ._ _|
(_| (_| (_| \_ (_| | (_|

      DESCRIPTION : takes a newly created card pointer and probes Set
      hashTable for first available slot at the index
      corresponding to hashFunction
*/
void Set::addCard(Card* newCard)
{
      int hashValue = hashFunction(newCard->getKey());

      if (hashTable[hashValue] == nullptr)
      {
            hashTable[hashValue] = new Card(*newCard);
            hashTable[hashValue]->setPrevPtr(nullptr);
            hashTable[hashValue]->setNextPtr(nullptr);
      }
      else if (!checkDup(hashTable[hashValue], newCard))
      {
            Card* arrayPtr = findLast(hashTable[hashValue]);
            arrayPtr->setNextPtr(new Card(*newCard));
            arrayPtr->getNextPtr()->setPrevPtr(arrayPtr);
            arrayPtr->getNextPtr()->setNextPtr(nullptr);
      }
      return;
}

