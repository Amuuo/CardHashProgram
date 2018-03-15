#pragma once

const int TABLE_SIZE = 20;

class Set {
private:
	std::string       fileName;
	std::array<Card*, TABLE_SIZE> hashTable;
public:
	Set();
	int          hashFunction(int)   const;
	Card*        getHashTable(int)   const;
	std::string  bucketEnd(Card*) const;
	std::string  bucketFront(Card*) const;
	std::string  getFileName();
	void         setFileName(std::string);
	void         printHash(std::string);
	void         addCard(Card*);
};