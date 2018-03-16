#include"Main.h"


/*
          ___
|\/|  /\   |  |\ |
|  | /--\ _|_ | \|
*/
int main()
{
	std::vector<Set>    cardSet;
	int            menuSelection;

	while (1)
	{
		menuSelection = titleScreen();
		switch (menuSelection)
		{
		case   1: setImport(cardSet); break;
		case   2: setUnion(cardSet); break;
		case   3: setIntersection(cardSet); break;
		case   4: setDifference(cardSet); break;
		case   5: searchCards(cardSet); break;
		case   6: printSetHash(cardSet); break;
		case   7: printSetList(cardSet); break;
		case   8: outputSet(cardSet); break;
		case -21: system("cls"); break;
		}
	}
	return 0;
}

/*

            _          _
 _   _ _|_ |_ o |  _  /   _  ._ _|_  _  ._ _|_  _
(_| (/_ |_ |  | | (/_ \_ (_) | | |_ (/_ | | |_ _>
_|
      DESCRIPTION : read file and convert it's contents to a single
      std::string, then return that std::string
*/
std::string getFileContents(std::ifstream& File)
{
	std::string   Lines = "";

	if (File.good())
	{
		while (File.good())
		{
			std::string TempLine;
			getline(File, TempLine);
			TempLine += "\n";
			Lines += TempLine;
		} return Lines;
	}
	else { return "File did not open\n"; }
}

/*

                                       __
 _.  _|  _| |\ |     ._ _  |_   _  ._ /__ ._ _. ._  |_  o  _
(_| (_| (_| | \| |_| | | | |_) (/_ |  \_| | (_| |_) | | | (_
                                                |
      DESCRIPTION : concatenate header graphic with number graphic
      to display various graphics headers (e.g. "Set1",
      "Set2", "Set3")
*/
std::string addNumberGraphic(std::string header, std::string num)
{
	std::string               Lines = "";
	std::ifstream             numFile;
	std::ifstream             headFile;
	std::string               blanks;
	std::vector<std::string>  tempFold;
	std::vector<std::string>  tempFold2;
	std::string               TempLine;
	std::string               TempLine1;

	headFile.open("Graphics\\Set.txt");
	if (headFile.fail()) std::cout << "Failed to open";
	while (!headFile.eof())
	{
		getline(headFile, TempLine);
		if (TempLine.length() == 1)
		{
			TempLine.pop_back();
		}
		tempFold.push_back(TempLine);
	}
	headFile.close();

	//for (int i = 0; i < tempFold.size(); i++)


	numFile.open("Graphics\\" + num + ".txt");
	if (numFile.fail()) std::cout << "numFile failed to open";

	while (!numFile.eof())
	{
		getline(numFile, TempLine1);
		if (TempLine1.length() == 1)
		{
			TempLine1.pop_back();
		}
		tempFold2.push_back(TempLine1);
	}

	for (unsigned int i = 0; i < tempFold.size(); i++)
	{
		Lines += tempFold[i] + tempFold2[i] + "\n";
	}

	numFile.close();

	return Lines;
}
/*
                 __
_|_ o _|_ |  _  (_   _ ._ _   _  ._
 |_ |  |_ | (/_ __) (_ | (/_ (/_ | |

      DESCRIPTION : load Menu graphic and return user-entered menu option
*/
int titleScreen()
{
	loadArtwork("MainMenu.txt");
	return (_getch() - 48);
}
/*
 _  _ _|_ | | ._  o  _  ._
_> (/_ |_ |_| | | | (_) | |

      DESCRIPTION : calculates the union between two sets and places
      the result in a new set
*/
void setUnion(std::vector<Set>& cardSet)
{
	Card* tmpPtr;
	Card* tmpPtr2;
	Set*  newSet = new Set;
	Set   s1;
	Set   s2;

	loadArtwork("SetUnion.txt");

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		tmpPtr = s1.getHashTable(i);
		while (tmpPtr != nullptr)
		{
			for (Card* tmpPtr2(s2.getHashTable(i)); tmpPtr2 != nullptr; tmpPtr2 = tmpPtr2->getNextPtr())
			{
				if (tmpPtr == tmpPtr2)
				{
					Card* tmpPtrNext(tmpPtr->getNextPtr());
					delete tmpPtr;
					tmpPtr = tmpPtrNext;
				}
			}
			if (tmpPtr != nullptr)
			{
				Card* tmpCard = new Card(tmpPtr);
				newSet->addCard(tmpCard);
				tmpPtr = tmpPtr->getNextPtr();
			}
		}
	}
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		tmpPtr2 = s2.getHashTable(i);
		if (tmpPtr2 != nullptr)
		{
			for (Card* tmpPtr2(s2.getHashTable(i)); tmpPtr2 != nullptr; tmpPtr2 = tmpPtr2->getNextPtr())
			{
				Card* tmpCard = new Card(tmpPtr2);
				newSet->addCard(tmpCard);
			}
		}
	} newSet->printHash("Graphics\\Set.txt");
}
/*
          ___
 _  _ _|_  |  ._ _  ._   _  ._ _|_
_> (/_ |_ _|_ | | | |_) (_) |   |_
                    |

      DESCRIPTION : get list of available "hand.txt" files from current
      directory, display to user, capture user-input,
      and load files into program
*/
void setImport(std::vector<Set>& cardSet)
{
	std::vector<std::string>  setFiles;
	std::ifstream             deckInputFile;
	std::ifstream             inFile;
	std::ifstream             artFile;
	std::ofstream             deckOutputFile;
	std::string               face;
	std::string               suit;
	std::string               file;
	std::string               Art_import;
	const char*               systemCall;
	int                       fileStringInput;
	int                       i = 1;
	int		              initialSize = cardSet.size();
	Set*                      tmpSet = new Set;


	loadArtwork("Import.txt");

	systemCall = "dir | gawk 'BEGIN { RS = \"\\n| \" }; {if ($1 ~ /^H.*(txt)$/) { printf(\"%s\\n\", $1)}}' > gawkFileList.txt";
	system(systemCall);
	inFile.open("gawkFileList.txt");

	std::cout << "\nAvailable .txt files: \n\n";
	do
	{
		inFile >> file;
		if (!inFile.eof())
		{
			setFiles.push_back(file);
			std::cout << "\t" << i << " - " << file << std::endl;
			i++;
		}
	} while (!inFile.eof());

	std::cout << "\n\nPress <1-" << setFiles.size() << "> to tag for import...\nPress <ENTER> to import\n\n";
	std::cout << "\nFiles to import:\n\n";

	int j = initialSize;
	while (((fileStringInput = _getch()) != 13) && (fileStringInput != 27))
	{
		std::cout << "\t" << setFiles[fileStringInput - 49] << std::endl;
		tmpSet->setFileName(setFiles[fileStringInput - 49]);
		cardSet.push_back(*tmpSet);
		cardSet[j].setFileName(setFiles[fileStringInput - 49]);
		j++;
	}
	int currentSize = cardSet.size();

	for (int i = initialSize; i < currentSize; i++)
	{
		deckInputFile.open(cardSet[i].getFileName());
		if (deckInputFile.fail()) std::cout << "File failed to open" << std::endl;

		std::cout << "\n\n>> Deck file successfully opened\n\n";

		while (!deckInputFile.eof())
		{
			deckInputFile >> face >> suit;
			Card* tempCard = new Card;

			tempCard->setFace(face);
			tempCard->setSuit(suit);

			cardSet[i].addCard(tempCard);
			std::cout << "\nCard added: ";
			tempCard->printCard();
		}
		std::cout << "\n\n...Closing Deck file" << i + 1 << std::endl;
		deckInputFile.close();
	}
	system("cls");
}
/*
          ___
 _  _ _|_  |  ._ _|_  _  ._ _  _   _ _|_ o  _  ._
_> (/_ |_ _|_ | | |_ (/_ | _> (/_ (_  |_ | (_) | |

      DESCRIPTION : prints the entire Set hashTable with bucket links
*/
void setIntersection(std::vector<Set>& cardSet)
{
	return;
}
/*
           _      _   _
 _  _ _|_ | \ o _|_ _|_ _  ._ _  ._   _  _
_> (/_ |_ |_/ |  |   | (/_ | (/_ | | (_ (/_

      DESCRIPTION : prints the entire Set hashTable with bucket links
*/
void setDifference(std::vector<Set>& cardSet)
{
	return;
}
/*
                     _
 _  _   _. ._ _ |_  /   _. ._ _|  _
_> (/_ (_| | (_ | | \_ (_| | (_| _>

      DESCRIPTION : prints the entire Set hashTable with bucket links
*/
void searchCards(std::vector<Set>& cardSet)
{
	return;
}
/*
                 __
._  ._ o ._ _|_ (_   _ _|_ |_|  _.  _ |_
|_) |  | | | |_ __) (/_ |_ | | (_| _> | |
|
      DESCRIPTION : prints the entire Set hashTable with bucket links
*/
void printSetHash(std::vector<Set>& cardSet)
{
	std::string    userR;
	std::string    printSetArt;
	std::ifstream  artImport;
	char           userResponse;


	loadArtwork("PrintHash.txt");

	do
	{
		std::cout << "\n\n\t=================================================================";
		std::cout << "\n\n\tPress <1-" << cardSet.size() << "> to print set: ";
		std::cout << "\n\tPress <ESC> for Main Menu\n";

		for (unsigned int i = 0; i < cardSet.size(); i++) { std::cout << "\n\t\t" << (i + 1) << " - " << cardSet[i].getFileName(); }

		userR.erase(0);
		userResponse = _getch();
		userR.push_back(userResponse);

		if (userResponse != '\x1b')
		{
			std::string graphic = addNumberGraphic("Graphics\\Set.txt", userR);
			cardSet[userResponse - 49].printHash(graphic);

		}
		else if (userResponse == '\x1b') { system("cls"); return; }

	} while (userResponse != '\x1b');

	system("cls");
	return;
}
/*
                 __
._  ._ o ._ _|_ (_   _ _|_ |  o  _ _|_
|_) |  | | | |_ __) (/_ |_ |_ | _>  |_
|
      DESCRIPTION : prints user-selected set as a list of cards
*/
void printSetList(std::vector<Set>& cardSet)
{
	std::vector<std::string>  setList;
	std::string               set;
	std::string               face;
	std::string               suit;
	std::string               userR;
	std::ifstream             setListFile;
	std::ifstream             setFile;
	int                       userInput;
	const char*               systemCall;

	//find set files in the current directory and output to setList.txt
	systemCall = "dir | gawk '/[ ][(Set)*].*(txt)$/' | gawk '{ print $5 }' > setList.txt";
	system(systemCall);

	loadArtwork("PrintSet.txt");

	//Input each line of setList.txt to std::string vector
	setListFile.open("setList.txt");
	while (!setListFile.eof())
	{
		setListFile >> set;
		if (!setListFile.eof())
		{
			setList.push_back(set);
		}
	} setListFile.close();

	//output user-selected set lists until ESC is pressed
	do
	{
		//display list of set files to user
		std::cout << std::endl;
		for (auto i = setList.begin(); i < setList.end(); i++)
		{
			std::cout << std::setw(7) << " ";
			std::cout << (distance(setList.begin(), i) + 1) << " - " << *i << "\n";
		}

		//capture user input and open corresponding set file
		userInput = _getch();
		if (userInput == '\x1b') return;
		userR.push_back(userInput);
		std::cout << addNumberGraphic("Set.txt", userR);
		userR.pop_back();
		setFile.open(setList[userInput - 49]);
		std::cout << "\n     ==================\n";
		//input file contents and output to console
		while (!setFile.eof())
		{
			setFile >> face;
			setFile >> suit;
			if (!setFile.eof())
			{
				std::cout << "\t" << face << " " << suit << std::endl;
			}
		} setFile.close();
		std::cout << "     ==================";
	} while (userInput != '\x1b');
}
/*
                       __
 _     _|_ ._     _|_ (_   _ _|_
(_) |_| |_ |_) |_| |_ __) (/_ |_
           |
      DESCRIPTION : creates file and outputs set to that file as a list
*/
void outputSet(std::vector<Set>& cardSet)
{
	std::ofstream  outputFile;
	std::ifstream  artImport;
	std::string    outputFileName;
	std::string    artFile;
	Card*          tmpPtr;
	int            fileNum;


	loadArtwork("ExportSet.txt");

	//display hash Set names
	for (unsigned int i = 0; i < cardSet.size(); i++)
	{
		std::cout << "\n" << i + 1 << " - " << cardSet[i].getFileName();
	}

	//prompt user to enter file number
	std::cout << "\nEnter file to output (1-" << cardSet.size() << "): ";
	std::cin >> fileNum;

	//create set file name and open corresponding output file
	outputFileName = "Set" + cardSet[fileNum - 1].getFileName();
	outputFile.open(outputFileName);

	//output each element of hash set to output file as a list
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		tmpPtr = cardSet[fileNum - 1].getHashTable(i);
		while (tmpPtr != nullptr)
		{
			outputFile << tmpPtr->getFace() << " " << tmpPtr->getSuit() << std::endl;
			tmpPtr = tmpPtr->getNextPtr();
		}
	}

	system("cls");
	system("dir");
	//system(sys += out);
	return;
}
/*
|  _   _.  _|  /\  ._ _|_       _  ._ |
| (_) (_| (_| /--\ |   |_ \/\/ (_) |  |<

      DESCRIPTION : opens graphic files and outputs to console
*/
void loadArtwork(std::string artFileName)
{
	std::ifstream  artImport;
	std::string    artFile;

	system("cls");
	artImport.open("Graphics//" + artFileName);
	artFile = getFileContents(artImport);
	std::cout << "\t" << artFile << std::endl;
	artImport.close();
	return;
}
