#include"Main.h"

Set::Set() : hashTable() {}
/*
=================================================================
SETTERS
=================================================================
*/
std::string Set::getFileName() { return fileName; }
/*
=================================================================
GETTERS
=================================================================
*/
Card* Set::getHashTable(int i) const { return hashTable[i]; }
void  Set::setFileName(std::string file) { fileName = file; }
/*
/*
=================================================================
OPERATOR OVERLOADS
=================================================================
*/
/*
=================================================================
FUNCTION.   : bucketEnd
PARAMETERS  : CARD POINTER (tail bucket link)
RETURN TYPE : STRING
DESCRIPTION : recursive function that takes the tail bucket link,
and prints out links from head to tail
=================================================================
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
=================================================================
FUNCTION.   : bucketEnd
PARAMETERS  : CARD POINTER (tail bucket link)
RETURN TYPE : STRING
DESCRIPTION : recursive function that takes the tail bucket link,
and prints out links from head to tail
=================================================================
*/
std::string Set::bucketFront(Card* frontLink) const
{
	std::string s = frontLink->getFace() + " of " + frontLink->getSuit() + " -> ";
	if (frontLink->getNextPtr() == nullptr) return s;
	else { return s + bucketFront(frontLink->getNextPtr()); }
}
/*
=================================================================
FUNCTION.   : hashFunction
PARAMETERS  : Card hash key (INT)
RETURN TYPE : INT
DESCRIPTION : takes key, runs through has function, and returns
hash value
=================================================================
*/
int Set::hashFunction(int key) const { return (key % TABLE_SIZE); }
/*
=================================================================
FUNCTION.   : printHash
PARAMETERS  : n/a
RETURN TYPE : VOID
DESCRIPTION : prints the entire Set hashTable with bucket links
=================================================================
*/
void Set::printHash(std::string graphic)
{
	Card* tmpPtr;

	//std::cout << "\n-------------------------------------------------------------\n";
	std::cout << "\n\n";
	std::cout << graphic;
	//std::cout << "\n\t>>Printing Hash Table (created from " << fileName << ": \n";
	//std::cout << "\n\t[] - hash index, \n\t-> - bucket links\n";
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
	//std::cout << "\n\n-------------------------------------------------------------\n";
}
/*
=================================================================
FUNCTION.   : addCard
PARAMETERS  : CARD POINTER
RETURN TYPE : VOID
DESCRIPTION : takes a newly created card pointer and probes Set
hashTable for first available slot at the index
corresponding to hashFunction
=================================================================
*/
bool Set::checkDup(Card* tmpHead, Card* newCard)
{
      if       (tmpHead == nullptr) return false;
      else if  (*tmpHead == newCard) return true ;
      else     return checkDup(tmpHead->getNextPtr(), newCard);
      /*while (tmpHead != nullptr)
      {
            if (tmpHead == newCard) return true;
            tmpHead->setNextPtr(tmpHead->getNextPtr());
      }
      return false;*/
     
}
/*
=================================================================
FUNCTION.   : addCard
PARAMETERS  : CARD POINTER
RETURN TYPE : VOID
DESCRIPTION : takes a newly created card pointer and probes Set
hashTable for first available slot at the index
corresponding to hashFunction
=================================================================
*/
Card* Set::findLast(Card* tmpHead)
{

      if (tmpHead->getNextPtr() == nullptr) return tmpHead;
      return findLast(tmpHead->getNextPtr());
}
/*
=================================================================
FUNCTION.   : addCard
PARAMETERS  : CARD POINTER
RETURN TYPE : VOID
DESCRIPTION : takes a newly created card pointer and probes Set
hashTable for first available slot at the index
corresponding to hashFunction
=================================================================
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
      else
      {
            std::cout << "\ndeleting..."; 
            newCard->printCard();
            newCard;
      }
      return;
}

