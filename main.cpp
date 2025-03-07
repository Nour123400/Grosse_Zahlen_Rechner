/*******************************************
* Hussain, Nouralrahman
* Matrikel_Nr:79968
* Aufgabe 9 (Grosse Zahlen)
********************************************/


#include <fstream>//Fuer das Einlesen aus dem Datei 
#include "Zahl.hpp"


    

int main()
{
    //intialisierung und Zuweisung von dem Datei
    std::ifstream datei("Rechenvorschriften");
    

    if (datei.is_open())
    {
        char rechnung;
        //Die schleife geht solange den Text eingelesen werden kann.
        //liest der ersten Operation ob +,-,* oder f.
        while (datei >> rechnung)
        {
            //s1,s2 gehen in die set-Funktion als Parameters ein.
            std::string s1;
            std::string s2;

            
            Zahl zahl1_1;
            Zahl zahl2_1;
            Zahl ergebniss;

            
            unsigned int s2_2;

            // Fuer die Fallunterscheidung bei der Operationen
            //*Es ist nicht verlangt dass das Hauptprogramm Operationen wie ==,!= ,<,> macht!. Diese Operationen existieren in der Klasse 
            //und falls das Hauptprogramm doch die zusätzliche Operationen machen soll dann muss ich mit String anstatt char arbeiten und switch funktioniert nicht gut mit string!
            switch (rechnung)
            {
            case'+':
                //lese die Zahlen aus dem Datei ein.
                datei >> s1;
                datei >> s2;
               
                std::cout << "+\n";
                std::cout << s1 << "\n";

                //intialisierung der grosse zahl mit dem gegebnen String
                zahl1_1.set_Zahl(s1);
                std::cout << s2 << "\n";
                zahl2_1.set_Zahl(s2);

                ergebniss = zahl1_1 + zahl2_1;

                std::cout << "____________________________________________________________________________________________________________\n";
                ergebniss.print_Zahl();
                std::cout << std::endl;
                break;

            case'-':

                datei >> s1;
                datei >> s2_2;

                std::cout << "-\n";
                std::cout << s1 << "\n";
                zahl1_1.set_Zahl(s1);
                std::cout << s2_2 << std::endl;

                ergebniss = zahl1_1 - s2_2;

                std::cout << "____________________________________________________________________________________________________________\n";
                ergebniss.print_Zahl();
                std::cout << std::endl;
                break;

            case'*':
                //erste Zahl als String einlesen
                datei >> s1;
                datei >> s2_2;

                std::cout << "*\n";
                std::cout << s1 << "\n";
                zahl1_1.set_Zahl(s1);
                std::cout << s2_2 << std::endl;

                ergebniss = zahl1_1 * s2_2;

                std::cout << "____________________________________________________________________________________________________________\n";
                ergebniss.print_Zahl();
                std::cout << std::endl;
                break;

            case'f':
                datei >> s2_2;

                std::cout << "f\n";
                std::cout << s2_2 << std::endl;

                ergebniss = ergebniss.f(s2_2);

                std::cout << "____________________________________________________________________________________________________________\n";
                ergebniss.print_Zahl();
                std::cout << std::endl;
                break;

            //Falls ein komisches Zeichen als Oeration eingegeben wird.
            default:
                std::cout<< rechnung <<"\nFalsche Eingabe\n"<< rechnung<<" ist keine Operation\n";

            }

        }
        datei.close();
    }
 
    else
    {
        std::cout << "Kein Zugriff auf dem datei Rechenvorschriften\nBitte beachten Sie, dass die Datei Rechenvorschriften keine Eundung hat!\n";
    }

    return 0;
}