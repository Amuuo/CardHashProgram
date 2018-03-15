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
void Set::addCard(Card* newCard)
{
	int   hashValue = hashFunction(newCard->getKey());
	Card* arrayPtr = hashTable[hashValue];


	std::cout << "\n\n\t> Attempting to insert "; newCard->printCard(); std::cout << "at [" << hashValue << "]:";

	if (arrayPtr == nullptr)
	{
		std::cout << "\n\t> hash slot is empty... ";
		hashTable[hashValue] = new Card(newCard);
		arrayPtr = hashTable[hashValue];
		std::cout << "\n\t    ==========================================================";
		std::cout << "\n\t    || UPDATED: hashTable[" << hashValue << "] -> " << bucketFront(arrayPtr);
		std::cout << "\n\t    ==========================================================";
		return;
	}
	std::cout << "\n\t> hashTable[" << hashValue << "] -> " << bucketFront(arrayPtr);

	while (arrayPtr != nullptr)
	{
		if (*arrayPtr == newCard)
		{
			std::cout << "\n     \n\t\tduplicate detected, deleting new card...("; arrayPtr->printCard(); std::cout << ")";
			std::cout << "\n\t       -----------------------------------------------------------";
			newCard->eraseCard();
			return;
		}
		else if (arrayPtr->getNextPtr() == nullptr)
		{
			std::cout << "\n\t> linking "; newCard->printCard();
			std::cout << "to "; arrayPtr->printCard();
			Card* arrayPtrNext = arrayPtr->getNextPtr();

			arrayPtrNext = new Card(newCard);
			arrayPtr->setNextPtr(arrayPtrNext);
			arrayPtrNext->setPrevPtr(arrayPtr);
			arrayPtrNext->setNextPtr(nullptr);
			std::cout << "\n\t    ==========================================================";
			std::cout << "\n\t    || UPDATED: hashTable[" << hashValue << "]: " << bucketEnd(arrayPtrNext);
			std::cout << "\n\t    ==========================================================";
			return;
		}
		else if (arrayPtr->getNextPtr() != nullptr)
		{
			arrayPtr = arrayPtr->getNextPtr();
		}
	}
}