#pragma once
#include<iostream>
#include<string>
#include<stdio.h>
//#include<termios.h>
#include<array>
#include<memory>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cctype>
#include<iterator>
#include<exception>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include"Card.h"
#include"Set.h"



int  titleScreen();
void setUnion(std::vector<Set>&);
void setImport(std::vector<Set>&);
void setIntersection(std::vector<Set>&);
void setDifference(std::vector<Set>&);
void searchCards(std::vector<Set>&);
void printSetHash(std::vector<Set>&);
void printSetList(std::vector<Set>&);
void outputSet(std::vector<Set>&);
void loadArtwork(std::string);

