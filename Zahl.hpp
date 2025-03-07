#pragma once

#include <iostream>
#include <cmath>//fuer die Funktion Pow() (Bei der Funktion set_Zahl und print_Zahl)
#include <string>
#include <array>
#include <vector>//Bei der arbeit mir Strings

class Zahl
{
private:
	std::array<unsigned long long int, 32 > zahl = {0};
	std::array<unsigned long long int, 32> grenze = {0};

public:
	Zahl();
	
	void set_Zahl(std::string geg_zahl);
	std::array<unsigned long long  int, 32 > get_Zahl();
	void set_Grenze();
	std::array<unsigned long long  int, 32 > Get_Grenze();
	void print_Zahl();

	bool x1(std::string y);
	unsigned int x2(unsigned int *x);
	unsigned int x3();
	bool x4(Zahl z);

	Zahl operator + (Zahl zahl2_add);
	Zahl operator - (unsigned int zahl2_sub);
	Zahl operator *(unsigned int zahl2_multi);
	bool operator ==(Zahl zahl2_glich);
	bool operator !=(Zahl zahl2_unglich);
	bool operator < (Zahl zahl2_k);
	bool operator > (Zahl zahl2_g);

	Zahl f (unsigned int fk);



};
