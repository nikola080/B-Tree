#include "BStablo.h"
#include<fstream>
BStablo& Unos() {
	int k;
	cout << "Unesite red stabla:"; cin >> k;
	BStablo b(k);
	ifstream fajl1("numbers_20_normal.txt");
	int* niz = new int[1000];
	int i = 0;
	while (fajl1 >> k) {
		b.dodajUStablo(k);
		niz[i++] = k;
	}
	b.sortiraj(niz, i);
	cout << "Zavrsen unos!" << endl;
	return b;
}
void visinaBrojKljuceva(const BStablo& pok) {
	pok.ispisVisineIBrojaKljuceva();
}
void pretragaKljuca(BStablo& pok) {
	int key;
	cout << "Unesite vrednnost kljuca:"; cin >> key;
	if (pok.daliNasao(key)) cout << "Nasao" << endl;
	else cout << "Nije nasao" << endl;

}

void umetanje(BStablo& pok) {
	cout << "Unesite vrednost kljuca koji zelite da umetnete:"; 
	int key;
	cin >> key;
	if (pok.dodajUStablo(key)) cout << "Kljuc je umtenut" << endl;
	else cout << "Greska, kljuc vec postoji!" << endl;
}
void brisanje(BStablo& pok) {
	cout << "Unesite vrednost koji zelite da izbrisete:";
	int key;
	cin >> key;
	if (pok.brisi(key)) cout << "Cvor je obrisan" << endl;
	else cout << "Greska, cvor ne postoji!" << endl;
}
void meny() {
	cout << "1.Formiraj stablo zadatog reda" << endl;
	cout << "2.Odredjivanje visine i broj kljuceva" << endl;
	cout << "3.Pretraga kljuca" << endl;
	cout << "4.Ispisivanje stabla" << endl;
	cout << "5.Umetanje kljuca u stablo" << endl;
	cout << "6.Brisanje kljuca iz stabla" << endl;
	cout << "7.Stvaranje stabla sa novim redom" << endl;
	cout << endl;
}
int main() {
	int n;
	BStablo pok(3);
	while (true) {
		meny();
		cout << "Opcija:";
		cin >> n;
		switch (n) {
		case 1:pok = Unos(); break;
		case 2:visinaBrojKljuceva(pok); break;
		case 3:pretragaKljuca(pok); break;
		case 4:pok.ispis(); break;
		case 5:umetanje(pok); break;
		case 6:brisanje(pok); break;
		case 7:pok.modifikacija(); break;
		default: exit(1);
		}
	}
}