#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

fstream plik;
string nazwa;
unsigned int n, ilosc = 3;
float sumaX, sumaY, srodekX, srodekY;

int main()
{
    //wprowadzenie przez użytkownika nazwy pliku
    cout << "Wprowadz nazwe pliku: ";
    cin >> nazwa;

    //otworzenie pliku
    plik.open(nazwa, ios::in | ios::out);

    //sprawdzenie czy plik istnieje
    if (!plik.good()) {
        cout << "Nie mozna otworzyc pliku!" << endl;
        return 0;
    }

    //wczytanie liczby punktów do zmiennej
    plik.ignore();
    plik >> n;

    if (n < 3) {
        cout << "Podano za malo punktow.";
        return 0;
    }

    float tablicaX[n], tablicaY[n], odleglosci[n];

    //wczytanie współrzędnych punktów do tablic
    plik.ignore();
    for (int i = 0; i < n; i++) {
        plik.ignore();
        plik >> tablicaX[i];
        plik >> tablicaY[i];
        plik.ignore();
    }

    plik.close();

    //obliczenie współrzędnych punktu znajdującego się na środku układu punktów
    for (int i = 0; i < n; i++) {
        sumaX += tablicaX[i];
        sumaY += tablicaY[i];
    }
    srodekX = sumaX / n;
    srodekY = sumaY / n;

    //obliczenie odległości punktów od środka układu
    for (int i = 0; i < n; i++)
        odleglosci[i] = sqrt((srodekX - tablicaX[i]) * (srodekX - tablicaX[i]) + (srodekY - tablicaY[i]) * (srodekY - tablicaY[i]));

    //sortowanie odległości i odpowiadających im współrzędnych malejąco
    for(int i=0;i<n;i++)
        for(int j=1;j<n-i;j++)
            if(odleglosci[j-1]<odleglosci[j]) {
                swap(odleglosci[j-1], odleglosci[j]);
                swap(tablicaX[j-1], tablicaX[j]);
                swap(tablicaY[j-1], tablicaY[j]);
            }
    //sprawdzenie czy punkty są wiesrzchołkami
    for (int i = 0; i < ilosc; i++)
        for (int j = ilosc; j < n; j++)
            if ( sqrt(((tablicaX[i] + tablicaX[i+1]) / 2 - srodekX) * ((tablicaX[i] + tablicaX[i+1]) / 2 - srodekX) + ((tablicaY[i] + tablicaY[i-1]) / 2 - srodekY) * ((tablicaY[i] + tablicaY[i-1]) / 2 - srodekY)) < odleglosci[j] ) {
                ilosc++;
                break;
            }

    //wypisanie wyniku
    cout << "[(" << tablicaX[0] << ", " << tablicaY[0] << ")";
    for (int i = 1; i < ilosc - 1; i++)
        cout << ", (" << tablicaX[i] << ", " << tablicaY[i] << ")";
    cout << "]" << endl;
    
    return 0;
}
