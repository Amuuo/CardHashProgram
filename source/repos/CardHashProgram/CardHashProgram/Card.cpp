#include"Main.h"

Card::Card() : face(), suit(), nextCard(nullptr), prevCard(nullptr) {}
Card::Card(std::string(face), std::string(suit)) : nextCard(nullptr), prevCard(nullptr) {}
/*
=================================================================
COPY CONSTRUCTORS
=================================================================
*/
Card::Card(Card& c1) : face(c1.getFace()),  suit(c1.getSuit()),  nextCard(nullptr), prevCard(nullptr) {}
Card::Card(Card* c1) : face(c1->getFace()), suit(c1->getSuit()), nextCard(nullptr), prevCard(nullptr) {}
/*
=================================================================
DESTRUCTORS
=================================================================
*/
Card::~Card() { std::cout << "\nDestroying Card... (" << face << " of " << suit << ")"; }
/*
=================================================================
OPERATOR OVERLOADS
=================================================================
*/
bool  Card::operator== (Card* c2)
{
	if (c2 == this)
	{
		std::cout << "\nThis is the same memory address for " << face << " of " << suit;
	}
	return ((this->face == c2->getFace()) && (this->suit == c2->getSuit()));
}
Card* Card::operator= (Card* rhs) { return rhs; }
Card  Card::operator= (Card& rhs)
{
	this->face     = rhs.getFace();
	this->suit     = rhs.getSuit();
	this->nextCard = rhs.getNextPtr();
	this->prevCard = rhs.getPrevPtr();
	return *this;
}
/*
=================================================================
GETTERS
=================================================================
*/
std::string Card::getFace()    const { return face;     }
std::string Card::getSuit()    const { return suit;     }
Card*       Card::getNextPtr()       { return nextCard; }
Card*       Card::getPrevPtr()       { return prevCard; }
/*
=================================================================
SETTERS
=================================================================
*/
void  Card::setFace    (std::string f    ) { face = f;               }
void  Card::setSuit    (std::string s    ) { suit = s;               }
void  Card::setNextPtr (Card* tmpNextCard) { nextCard = tmpNextCard; }
void  Card::setPrevPtr (Card* tmpPrevCard) { prevCard = tmpPrevCard; }
void  Card::setPrevPtr (int i            ) { prevCard = nullptr;     }

void Card::printCard() const { std::cout << face << " of " << suit << " "; return; }
/*
=================================================================
FUNCTION.   : getKey
PARAMETERS  : n/a
RETURN TYPE : int
DESCRIPTION : returns sum of ASCII values of the card's face and suit
=================================================================
*/
int Card::getKey()
{
	int key = 0;
	for (int i : face) key += i;
	for (int i : suit) key += i;
	return key;
}
/*
=================================================================
FUNCTION.   : eraseCard
PARAMETERS  : n/a
RETURN TYPE : void
DESCRIPTION : erase card from linked list
=================================================================
*/
void Card::eraseCard()
{
	if ((this->nextCard == nullptr) && (this->prevCard == nullptr))
	{
		delete this;
		return;
	}
	else if (this->nextCard != nullptr)
	{
		if (this->prevCard != nullptr)
		{
			(this->nextCard)->setPrevPtr(this->prevCard);
			delete this;
			return;
		}
		else
		{
			(this->prevCard)->setPrevPtr(nullptr);
			delete this;
			return;
		}
	}
	else if (this->prevCard != nullptr)
	{
		(this->prevCard)->setNextPtr(nullptr);
		delete this;
		return;
	}
}