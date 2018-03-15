#pragma once

class Card {

private:

	std::string  face;
	std::string  suit;
	Card*        nextCard;
	Card*        prevCard;

public:

	Card();
	Card(std::string(face), std::string(suit));
	Card(Card&);
	Card(Card*);
	~Card();
	bool          operator==(Card*);
	Card*         operator=(Card*);
	Card          operator=(Card&);
	Card*         getNextPtr()const;
	Card*         getPrevPtr()const;
	std::string   getFace()const;
	std::string   getSuit()const;
	void          printCard()const;
	void          setFace(std::string);
	void          setSuit(std::string);
	void          setNextPtr(Card*);
	void          setPrevPtr(Card*);
	void          setPrevPtr(int);
	void          eraseCard();
	int           getKey();
};
