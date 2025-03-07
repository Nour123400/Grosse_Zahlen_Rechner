#include "Zahl.hpp"

/****************************************************************************************************************************************************************************
* Kurze Erklerung wie ich auf das Programm kamm.
* Die Klasse soll Zahlen darstellen , die 32 mal so viel Bits wie unsigned int im Speicher verwenden.
 Also Ích habe die Maximale Zahl berechnet, die dargestellt verden kann.
 Size of ( unsigned int) = 4 bytes!, Zahl 4*32 = 128  bytes!
UINT_MAX= ULONG_MAX  = 4294967295// 10 Stellen  , maximale Zahl pow(pow(2,8),128)-1// 309 Stellen
179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215
 UINT_MAX = ULONG_MAX   4294967295 = 4294967295 ! So ich ging davon aus dass mit dem Hinwis in der Aufgabe
 unsigned long long gemeint ist.
 ULLONG_MAX= 18446744073709551615 // 20 Stelle
* Also Die Zahl kann nicht  mit einem Array (mit grosse 32) implementiert werden.
Ich brauche auf jeden Fall mehr Speicherplatz um die Zahlen zu implementieren die 32 mal so viele Bits im speicher verwnden.
Da ich so wie so mehr Speicherplatz verwnden muss und der Hinweis darauf deutet dass ich einen grosseren Typ verwenden muss habe ich mich fuer unsigned long long enschieden.
***************************************************************************************************+**************************************************************************/

// Konstraktor
Zahl::Zahl()
{
	//Das Array zahl soll direkt zugewiessen werden für den Ueberlauf.
	// Der Uberlauf ist nicht vollständig ich kamm damit nicht klar.
	set_Grenze();
}


// Funktion nimmt die Zahl als Parameter String und umwandelt sie in Array von unsigned long long (zahl).
//Das Array (zahl)ist bereits in der Header (Zahl.h) intialisiert und hat den Wert 0 als Anfangswert.
void Zahl::set_Zahl(std::string geg_zahl)
{
	//Array von char. fuer die Speicherung der Zahl (309 Stellen) falls die maximale Zahl eingegeben wird.
	//maximale zahl = (pow(pow(2,8),128))-1 und die zahl hat 309 Stellen!
	std::array <char, 309> speicher_Char = { 0 };

	for (size_t i = 0; i < 309; i++)
	{
		speicher_Char.at(i) = '0';
	}

	
	// Zwischenspeicher
	std::string eingang_speicher1;
	eingang_speicher1 = geg_zahl;

	//Die Ueberpruefung der Gueltigkeit von der eingegebenen Zahl (Funktion bool x )
	while (!(x1(eingang_speicher1)))
	{
		//Falls einen ungueltigen Cahrakter als Zahl eingegeben wird 
		//oder eine Zahl die ueber das Maximum ist!
		eingang_speicher1 = "0";
	}

	
	size_t lezte_Stelle = eingang_speicher1.length();

	// Zuweisung die Werte von dem gegebnen Zahl in Array von Charakters
	for (size_t i = 0; i < lezte_Stelle; i++)
	{
		speicher_Char.at(308 - i) = eingang_speicher1.at(lezte_Stelle - 1 - i);
	}

	for (size_t i = 0; i < 309; i++)
	{
		//Hier werden die ein gegebne Charakters vorbereitet um posative Zahlen zu werden
		speicher_Char.at(i) -= 48;
	}

	// Zwischen Speicherplatz. Bei mir ging es nicht direckt die Werte ins benötigtes Array reinzuschieben!
	std::array<unsigned int, 309 > zwisch_speich_int = { 0 };

	
	for (size_t i = 0; i < 309; i++)
	{
		zwisch_speich_int.at(i) = speicher_Char.at(i);
	}

	// Je 10 Stellen vom Zwischenspeicher werden in eine Stelle gespeichert.
	int counter = 0;
	for (size_t j = 0; j < 30; j++)
	{
		for (size_t i = 0; i < 10; i++)
		{
			zahl.at(31 - j) = zahl.at(31 - j) + ((zwisch_speich_int.at(308 - counter)) * (pow(10, i)));
			++counter;
		}
	}
	//Der Feld zahl.at(1) hat winger als 10 Stellen 
	for (size_t i = 0; i < 9; i++)
	{
		zahl.at(1) = zahl.at(1) + ((zwisch_speich_int.at(8 - i)) * (pow(10, i)));
	}

	//Ein Feld mehr falls ich sie bei der Berechnungen brauche;
	zahl.at(0) = 0;
}



//Funktion holt das Array beim Bedarf
std::array<unsigned long long int, 32> Zahl::get_Zahl()
{
	return zahl;
}



//Funktion gibt die Zahl aus 
//Die Funktion wirkt  wie set_Zahl aber umgekhert
void Zahl::print_Zahl()
{
	std::array<unsigned int, 310 > zwisch_speich_int = { 0 };
	std::array<char, 311> zwisch_speich_Char = { 0 };
	std::string ausgabe;

	// Je Stelle vom Zwischenspeicher wird in 10 Stelle gespeichert.
	int counter = 0;
	for (size_t j = 0; j < 31; j++)
	{
		for (int i = 9; i >= 0; i--)
		{
			zwisch_speich_int.at(0 + counter) = (zahl.at(1 + j) / pow(10, i));
			zahl.at(1 + j) -= (zwisch_speich_int.at(0 + counter) * pow(10, i));
			++counter;
		}
	}

	for (size_t i = 0; i < 310; i++)
	{
		//Von int. Werte in Charakters
		zwisch_speich_Char.at(i) = zwisch_speich_int.at(i);

		//Hier werden die ein gegebne Charakters vorbereitet um posative Zahlen zu werden
		zwisch_speich_Char.at(i) += 48;
	}
	
	zwisch_speich_Char.at(310) = '\0';


	unsigned int* ptr;
	//Zeiger zeigt auf das Array int.
	ptr = &zwisch_speich_int.at(0);

	//Zeiger geht in die Funktion x2 um zu pruefen, ab welche Stelle(von links nach rechts) ausgeben wegen die Nullen vor der Zahl
	unsigned int ab_welch_stelle = x2(ptr);

	if (ab_welch_stelle == 100)
		ausgabe = "0";//Falls die Zahl 0 ist

	else
	{
		//Die gespeicherte Charakters virden in dem Strin von hinten rein geschoben.
		for (size_t i = ab_welch_stelle; i < 311; i++)
		{
			ausgabe.push_back(zwisch_speich_Char.at(i));
		}
	}
	//Ausgabe
	std::cout << ausgabe;
	std::cout << std::endl;

}



// Ich wusste nicht, wie ich die maximale Zahl praktischer speichern soll!!
void Zahl::set_Grenze()
{

	grenze.at(31) = 4224137215;//4 anstatt 5 für den Ueberlauf
	grenze.at(30) = 3535632962;
	grenze.at(29) = 4797163048;
	grenze.at(28) = 9947245938;
	grenze.at(27) = 8458629823;
	grenze.at(26) = 1633505106;
	grenze.at(25) = /*0*/540827237;//69-59
	grenze.at(24) = 8147391311;
	grenze.at(23) = 6823424628;
	grenze.at(22) = 5768838150;
	grenze.at(21) = 8295208500;
	grenze.at(20) = /*0*/941194530;//119-109
	grenze.at(19) = 2219601246;
	grenze.at(18) = 6548527630;
	grenze.at(17) = 7678934248;
	grenze.at(16) = 9474124377;
	grenze.at(15) = 9284743063;
	grenze.at(14) = 8144166224;
	grenze.at(13) = 7658789768;
	grenze.at(12) = 7987139335;
	grenze.at(11) = /*0*/211201138;//209-199
	grenze.at(10) = 7322407536;
	grenze.at(9) = 6313270847;
	grenze.at(8) = 6758055009;
	grenze.at(7) = /*00*/81157732;//249-239
	grenze.at(6) = 3065727343;
	grenze.at(5) = 7976978942;
	grenze.at(4) = 8902473361;
	grenze.at(3) = 7293051907;
	grenze.at(2) = 4862315907;
	grenze.at(1) = 179769313;
	grenze.at(0) = 0;

}



// Beim Bedarf
std::array<unsigned long long int, 32> Zahl::Get_Grenze()
{
	return grenze;
}



// Ueberpruefung der Gueltigkeit
bool Zahl::x1(std::string y)
{
	//Anfangswert ist Gueltig
	bool gueltig = true;

	if ((y.length()) >= 310)
	{
		gueltig = false;
		std::cout << "Die gegebne Zahl ist ueber das Maximum(mehrere Stellen)\n";
	}


	for (size_t i = 0; i < y.length(); i++)
	{
		if (y.at(i) < '0' || y.at(i) > '9')
		{
			gueltig = false;
			std::cout << "Sie haben falsche Zeichen eingegeben!\n";
			break;
		}
	}
	// Falls die Zahl so viele Stellen wie Das Maximum hat aber trozdem grosser ist!
	if ((y.length()) == 309)
	{
		std::string maxi = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215";
		// Unterscheidung beim ersten Feld 
		if (y.at(0) > maxi.at(0))
		{
			std::cout << y.at(0) << std::endl;
			gueltig = false;
			std::cout << "Die gegebne Zahl ist ueber das Maximum.\n";
		}

		for (size_t i = 0; i < 308; i++)
		{
			//Falls die Zahl an der stelle gleich das max. und an der nechsen Stelle grosser ist ungueltig!
			if ((y.at(i) == maxi.at(i)) && (y.at(i + 1) > maxi.at(i + 1)))
			{
				gueltig = false;
				std::cout << "Die gegebne Zahl ist ueber das Maximum.\n";
				break;
			}
		}
	}

	return gueltig;

}



// fuer die bestimmung von ab_welch_stelle  von print_Zahl (ab welche Stelle(von links nach rechts) ausgeben wegen die Nullen vor der Zahl).
unsigned int Zahl::x2(unsigned int* x)
{
	// Falls die Zahl 0 ist counter 100.
	unsigned int counter = 100;

	//Pruefung fuer alle andere Faelle
	for (size_t i = 1; i < 310; ++i)
	{
		//Falls die erste Zahl 0 und der nach folger ist nich gleich 0  gib mir wo an welche Stelle das ist und hör auf
		if (*(x - 1 + i) == 0 && *(x + i) != 0)
		{
			counter = i;
			break;
		}
	}
	return counter;
}



// An welche Stelle von rechts nach links eine Zahl <0 existiert (Aus nahme des letzten Felds)
unsigned int Zahl::x3()
{
	//Falls die Zahl unsigned int < grosse Zahl(Ueberlauf) counter 100;
	int counter3 = 100;

	for (size_t i = 1; i < 31; ++i)
	{
		if (zahl.at(31 - i) > 0)
		{
			counter3 = i;
			break;
		}
	}
	return counter3;
}



// Berechnung beim Ueberlau (unvollständig)
bool Zahl::x4(Zahl z)
{

	bool ueber = false;

	for (size_t i = 1; i < 32; i++)
	{
		//Falls die zahl in irgend einem Feld grosser ist -> uber = true
		if ((z.zahl.at(i - 1) == grenze.at(i - 1)) && (z.zahl.at(i) > grenze.at(i)))
		{
			ueber = true;
			break;
		}
	}

	return ueber;
}



//Additions operator für die Klasse
Zahl Zahl::operator+(Zahl zahl2)
{

	Zahl add_sum;
	// Falls kein Uebertrag in die Stellen des Arrays entsteht!
	for (size_t i = 0; i < 31; i++)
	{
		add_sum.zahl.at(31 - i) += zahl.at(31 - i) + zahl2.zahl.at(31 - i);
	}

	// Falls doch ein Uebertrag entsteht
	for (size_t i = 0; i < 31; i++)
	{

		unsigned long long Feld_10_Stellen = add_sum.zahl.at(31 - i);

		if (Feld_10_Stellen > 9999999999)
		{
			for (size_t j = 1; j <= 9; j++)
			{
				//Falls ein Uebertrag entsteht wird den Ubertag auf den nechsen Feld addiert und von dem Feld subtrahiert.
				if (Feld_10_Stellen >= (10000000000 * j) && Feld_10_Stellen < (10000000000 + (10000000000 * j)))
				{
					add_sum.zahl.at(31 - i) -= (10000000000 * j);
					add_sum.zahl.at(31 - i - 1) += j;
				}
			}
		}
	}
	add_sum.get_Zahl().at(0) = 0;


	//Ueberlauf wegen max Zahl // problem berechnung von mod ist falsch!weil maxi in manschen Felder > als 10 stellen ist (0 am anfang der 10 Stellen)

	if (x4(add_sum) != false)
	{
		//Falls die Zahl uber das maximum ist wird das( Maximum -1 ) subrahiert
		for (size_t i = 1; i < 32; i++)
		{
			add_sum.zahl.at(i) = (zahl2.zahl.at(i) + zahl.at(i)) - grenze.at(i);
		}
		add_sum.zahl.at(31) -= 1;
		std::cout << "Die Summe der Addituon ist ueber die maximale Grenze, deshalb stimmt die Berechnung nicht ganz!\n";
	}
	return add_sum;
}



//Subtraktion einer Zahl (unsigned int) von Grosser Zahl
Zahl Zahl::operator-(unsigned int zahl2_sub)
{
	Zahl sub_sum;

	for (size_t i = 0; i < 31; i++)
	{
		// sub_sum bekommt die Werte von dem ersten operant.
		sub_sum.zahl.at(31 - i) += zahl.at(31 - i);
	}

	// normaler Fall falls die Zahl die im letzen feld grosser als die (Zahl von unsigned int) ist.
	if (zahl2_sub <= sub_sum.zahl.at(31))
		sub_sum.zahl.at(31) -= zahl2_sub;

	// falls doch die Zahl die im ersten Feld nicht grosser als die zahl vom typ unsigned int.
	else
	{
		// w = an welcher stelle ab das neschtes Feld finde ich eine Zahl grosser 0;(Funktion x3);
		unsigned int w;
		w = x3();

		// Falls die Zahl unsigned int < grossere Zahl (Ueberlauf)
		if (w == 100)
		{
			unsigned long long g;
			g = sub_sum.zahl.at(31);

			for (size_t i = 0; i < 32; i++)
			{
				// sub_sum = maximum
				sub_sum.zahl.at(31 - i) = grenze.at(31 - i);

			}
			//Es wird von dem integer die Zahl von dem letzen Feld abgezogen und das ergebniss wird von dem max abgezogen.
			sub_sum.zahl.at(31) -= (zahl2_sub - g);
		}

		// Falls die grosse Zahl > die Zahl unsigned int
		else
		{
			//Gehe an die nechste Stelle wo keine 0 steht ziehe 1 ab und fuege alle stellen dahinter 9 zu.
			//dann sbtrahiere int von der letzten Feld.
			--(sub_sum.zahl.at(31 - w));
			for (unsigned int i = 0; i < w; i++)
			{
				sub_sum.zahl.at(31 - i) += 9999999999;
			}
			sub_sum.zahl.at(31) += 1;
			sub_sum.zahl.at(31) -= zahl2_sub;
		}

	}
	return sub_sum;
}



//Multiplikation Grosser Zahl mit (unsigned int)
Zahl Zahl::operator*(unsigned int zahl2_multi)
{
	Zahl sum_multi;
	Zahl Uebertrag;

	// multipliziere jeden Feld mit dem int.
	for (size_t i = 0; i < 31; i++)
	{
		sum_multi.zahl.at(31 - i) = zahl.at(31 - i) * zahl2_multi;
	}
	// berchne Ubertag
	for (size_t i = 0; i < 31; i++)
	{
		Uebertrag.zahl.at(31 - i) = sum_multi.zahl.at(31 - i) / 10000000000;
	}
	//Ziehe den Ubertrag von dem Feld ab
	for (size_t i = 0; i < 31; i++)
	{
		sum_multi.zahl.at(31 - i) -= (Uebertrag.zahl.at(31 - i) * (10000000000));
	}
	//Addiere Ubertrag auf dem nechsten Feld
	for (size_t i = 1; i < 31; i++)
	{
		sum_multi.zahl.at(31 - i) += Uebertrag.zahl.at(32 - i);
	}
	sum_multi.zahl.at(0) = 0;

	//Ueberlau wie beim Addition
	if (x4(sum_multi) != false)
	{
		for (size_t i = 1; i < 32; i++)
		{

			sum_multi.zahl.at(i) = (zahl2_multi * zahl.at(i)) - grenze.at(i);
		}
		sum_multi.zahl.at(31) -= 1;
		std::cout << "Die Summe der Multiplikation ist ueber die maximale Grenze, deshalb stimmt die Berechnung nicht ganz!\n";
	}
	return sum_multi;
}



bool Zahl::operator==(Zahl zahl2_glich)
{

	bool gleich = true;

	for (size_t i = 1; i < 32; i++)
	{
		//Falls die Zahlen nicht an jede Stelle bzw. jeden Feld gleich sind
		if (zahl.at(i) != zahl2_glich.zahl.at(i))
		{
			gleich = false;
			break;
		}
	}

	return gleich;
}



bool Zahl::operator!=(Zahl zahl2_unglich)
{
	//falls die Zahlen nicht gleich sind -> ungleiche Zahlen
	bool ungleich = !(operator ==(zahl2_unglich));

	return ungleich;
}



bool Zahl::operator<(Zahl zahl2_k)
{
	//Falls gleich-> Anfangswert =false 
	bool klein = false;
	// prueft ob die Zhal an der grosseste Stelle kleiner oder grosser ist
	for (size_t i = 0; i < 32; i++)
	{
		//wenn die Zahl an die grosste Stelle klainer ist
		if (zahl.at(i) < zahl2_k.zahl.at(i))
		{
			klein = true;
			break;
		}
		//wenn die Zahl an die grosste Stelle grosser ist
		if (zahl.at(i) > zahl2_k.zahl.at(i))
		{
			klein = false;
			break;
		}
	}

	return klein;
}



bool Zahl::operator>(Zahl zahl2_g)
{
	//Falls gleich Anfangswert =false 
	bool gross = false;
	// prueft ob die Zhal an der grosseste Stelle grosser oder Kleiner ist.
	for (size_t i = 0; i < 32; i++)
	{
		//wenn die Zahl an die grosste Stelle grosser ist
		if (zahl.at(i) > zahl2_g.zahl.at(i))
		{
			gross = true;
			break;
		}

		//wenn die Zahl an die grosste Stelle klainer ist
		if (zahl.at(i) < zahl2_g.zahl.at(i))
		{
			gross = false;
			break;
		}
	}

	return gross;
}


//Fakulitaet berechnen
//Die Maximal moegliche Zahl zu berechben ist 170
//f(170)=7257415615307998967396728211129263114716991681296451376543577798900561843401706157852350749242617459511490991237838520776666022565442753025328900773207510902400430280058295603966612599658257104398558294257568966313439612262571094946806711205568880457193340212661452800000000000000000000000000000000000000000
Zahl Zahl::f(unsigned int fk)
{
	Zahl FK;
	FK.zahl.at(31) = 1;

	unsigned count = fk;

		if (fk > 170)
		{
			std::cout << "Die Berechnung stimmt nicht ganz.Die Fakulitaet kann bis die Zahl 170 berechnet werden";

		}


		for (unsigned int i = count; i > 0; i--)
		{
			//die Multiplikation von der Klasse!
			FK = FK * fk;
			--fk;
		}
	

	return FK;
}




