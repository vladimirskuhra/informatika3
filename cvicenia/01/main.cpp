#include <iostream> // treba vscode prinutit pouzivat kniznice ktore sme si stiahli z ucrt64!!!!!!!!
#include <cmath>

int main()
{
    std::cout << "Ahoj svet\n"; // alebo std::cout << "Ahoj svet" << "\n";
    double a;
    std::cout << "Zadaj reálne číslo:"
    std::cin >> a;
    std::cout << "Zadal si: " << a << "\n";
    double sr = std::sqrt(a);
    std::cout << "Jeho odmocnina je: " << sr << "\n";
    return 0; // main je jedina trieda/funkcia kde prekladac nepotrebuje return 0/1, v ostatnych funkciach bude chybat navratova hodnota
}