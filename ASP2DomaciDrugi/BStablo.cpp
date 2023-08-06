#pragma once
#include "BStablo.h"
#include<iostream>
#include<fstream>
using namespace std;
bool BStablo::daliNasao(int key) {
	elem* pok = koren, * pok2 = nullptr;
	while (!(nasao(pok, key))) {
		int i = 0;
		while (i < pok->cap && pok->keys[i] < key) i++;
		pok2 = pok;
		pok = pok->p[i];
	}
	if (pok != nullptr) return true;
	else return false;
}
bool BStablo::dodajUStablo(int key) {
	elem* pok = koren, * pok2 = nullptr;
	while (!(nasao(pok, key))) {
		int i = 0;
		while (i < pok->cap && pok->keys[i] < key) i++;
		pok2 = pok;
		pok = pok->p[i];
	}
	if (pok != nullptr) return false;
	else {
		this->broj++;
		dodaj(pok2, key);
		return true;
	}
}

BStablo::elem*& BStablo::split(elem*& pok) {
	while (pok->cap == red) {
		int k = (int)trunc((red - 1) / 2);
		int* kkeys1 = new int[red] {0}, * kkeys2 = new int[red] {0};
		elem** pp1 = new elem * [red + 1]{ nullptr }, ** pp2 = new elem * [red + 1]{ nullptr };

		for (int i = 0; i <= k; pp1[i] = pok->p[i++]);

		for (int i = 0; i <= red - k - 1; pp2[i] = pok->p[i++ + k + 1]);

		for (int i = 0; i < k; kkeys1[i] = pok->keys[i++]);

		for (int i = 0; i < red - k - 1; kkeys2[i] = pok->keys[i++ + k + 1]);

		if (pok->parent == nullptr) {
			koren = new elem(red);
			koren->keys[0] = pok->keys[k];
			koren->p[0] = new elem(kkeys1,pp1, k);
			koren->p[0]->parent = koren;
			koren->p[1] = new elem(kkeys2,pp2, red - k - 1);
			koren->p[1]->parent = koren;
			koren->cap = 1;		
			int i = 0;
			while (i <= koren->cap) {
				if (koren->p[0]->p[0] == nullptr) break;
				else {
					int j = 0;
					elem* pokazivac = koren->p[i++];
					while (j <= pokazivac->cap) {
						pokazivac->p[j]->parent = pokazivac;
						j++;
					}
				}
			}
			delete pok;
			pok = koren;
		}
		else {
			elem* pok1, * pok2, * pok3 = pok->parent;
			int i = 0;
			int l = pok3->cap + 1;
			int p = pok3->cap;
			while (pok3->keys[i] < pok->keys[k] && i < pok3->cap) i++;
			while (p > i) pok3->keys[p] = pok3->keys[p-- - 1];
			pok3->keys[i] = pok->keys[k];
			pok3->cap++;
			pok1 = new elem(kkeys1, pp1, k);
			pok2 = new elem(kkeys2, pp2, red - k - 1);
			pok3->p[i] = pok1;
			pok1->parent = pok3;
			while (l > i + 1) pok3->p[l] = pok3->p[l-- - 1];
			pok3->p[i + 1] = pok2;
			pok2->parent = pok3;
			int u = 0;
			while (u <= pok1->cap) {
				if (pok1->p[0] == nullptr) break;
				pok1->p[u++]->parent = pok1;
			}
			u = 0;
			while (u <= pok2->cap) {
				if (pok2->p[0] == nullptr) break;
				pok2->p[u++]->parent = pok2;
			}
			delete pok;
			pok = pok3;
		}
	}
	return pok;
}
void BStablo::dodaj(elem* pok, int key) {
	int i = 0;
	while (pok->keys[i] < key && i < pok->cap) i++;
	int k = pok->cap;
	while (k > i) pok->keys[k] = pok->keys[k-- - 1];
	pok->keys[i] = key;
	pok->cap++;
	if (pok->cap == red) pok = split(pok);
	return;
}

bool BStablo::nasao(elem* pok, int key) {
	if (pok == nullptr) return true;
	int i = 0;
	while (i != pok->cap) {
		if (pok->keys[i] == key) return true;
		else i++;
	}
	return false;
}

void BStablo::ispis() {
	int i = 0;
	Q q;
	elem* pok = koren, * prov;
	q.insert(pok);
	while (q.front != q.rear) {
		pok = q.ddelete();
		if (pok->tek == 0) { pok->tek++; }
		int i = 0;
		cout << "(";
		while (i < pok->cap) {
			cout << pok->keys[i++] << " | ";
		}
		cout << ")  ";
		prov = pok;
		while (prov != koren) prov = prov->parent;
		while (prov != pok && prov != nullptr) prov = prov->p[prov->cap];
		if (prov == pok) cout << endl;
		if (pok->p[0] == nullptr);
		else {
			int j = 0;
			while (pok->p[j] != nullptr)  q.insert(pok->p[j++]); 
		}
	}
}

bool BStablo::brisi(int key) {
	elem* pok = koren;
	while (!(nasao(pok, key))) {
		int i = 0;
		while (i < pok->cap && pok->keys[i] < key) i++;
		pok = pok->p[i];
	}
	if (pok == nullptr) return false;
	else {
		this->broj--;
		if (pok->p[0] == nullptr) {
			skrati(pok, key);
			if (pok->cap >= min) return true;
			else {
				while (pok->cap < min) {
					if (rotation(pok)) break;
					else {
						pok = merge(pok);
						if (pok == koren) {
							if (koren->keys[0] == 0) {
								koren = pok->p[0];
								pok->p[0]->parent = nullptr;
								delete pok;
								break;
							}
						}
					}
				}
			}
		}
		else {
			pok = find(pok, key);
			skrati(pok, key);
			if (pok->cap >= min) return true;
			else {
				while (pok->cap < min) {
					if (rotation(pok)) break;
					else {
						pok = merge(pok);
						if (pok == koren) {
							if (koren->keys[0] == 0) {
								koren = pok->p[0];
								pok->p[0]->parent = nullptr;
								delete pok;
								break;
							}
						}
					}
				}
			}
		}
		return true;
	}
}

void BStablo::skrati(elem* pok,int key) {
	int i = 0;
	while (pok->keys[i] < key && i < pok->cap) i++;
	int k = i;
	while (i != red - 1) pok->keys[i] = pok->keys[i++ + 1];
	while (k != red) pok->p[k] = pok->p[k++ + 1];
	pok->cap--;
}
BStablo::elem*& BStablo::merge(elem*& pok) {
	elem* pok1 = pok->parent;

	if (pok1->p[pok1->cap] == pok) {
		insertKey(pok1->p[pok1->cap - 1], pok1->keys[pok1->cap - 1]);
		elem* pok2 = pok1->p[pok1->cap];
		pok1->p[pok1->cap] = nullptr;
		pok1->keys[pok1->cap - 1] = 0;
		pok1->cap--;
		pok1 = pok1->p[pok1->cap];
		int j = 0;
		for (int i = pok1->cap; i < pok1->cap + pok2->cap; i++) {
			pok1->keys[i] = pok2->keys[j];
			pok1->p[i] = pok2->p[j++];
		}
		pok1->cap += pok2->cap;
		pok1->p[pok1->cap] = pok2->p[pok2->cap];
		if (pok2->p[0] != nullptr) {
			for (int i = 0; i <= pok2->cap; pok2->p[i++]->parent = pok1);
		}
		pok1 = pok1->parent;
		delete pok2;
	}
	else {
		int i = 0, p = 0;
		if (pok->cap == 0) {
			while (pok1->p[p]->keys[0] != 0) p++;
			p = pok1->keys[p];
		}
		else p = pok->keys[pok->cap - 1];
		while (pok1->keys[i] < p) i++;
		elem* pok2 = pok1->p[i + 1];
		insertKey(pok, pok1->keys[i]);
		int k = i + 1, k1 = pok1->cap;
		while (i < red - 1) {
			pok1->keys[i] = pok1->keys[i++ + 1];
		}
		while (k < red) {
			pok1->p[k] = pok1->p[k++ + 1];
		}
		pok1->cap--;
		int j = 0;
		for (int i = pok->cap; i < pok->cap + pok2->cap; i++) {
			pok->keys[i] = pok2->keys[j];
			pok->p[i] = pok2->p[j++];
		}
		pok->cap += pok2->cap;
		pok->p[pok->cap] = pok2->p[pok2->cap];
		if (pok2->p[0] != nullptr) {
			for (int i = 0; i <= pok2->cap; pok2->p[i++]->parent = pok);
		}
		delete pok2;
	}
	return pok1;
}

BStablo::elem* BStablo::find(elem* pok,int key) {
	int i = 0;
	while (pok->keys[i] < key) i++;
	elem* pok1 = pok->p[i + 1];
	while (pok1->p[0] != nullptr && pok1 != nullptr) pok1 = pok1->p[0];
	int temp = pok1->keys[0];
	pok1->keys[0] = key;
	pok->keys[i] = temp;
	return pok1;
}
void BStablo::insertKey(elem* pok,int key) {
	pok->keys[pok->cap++] = key;
}

bool BStablo::rotation(elem* pok) {
	elem* pok1 = nullptr;
	if (pok->parent->p[0] == pok) {
		pok1 = pok->parent->p[1];
		if (pok1->cap > min) {
			leftRotation(pok1,0);
			return true;
		}
		else return false;
	}
	else {
		if (pok->parent->p[pok->parent->cap] == pok) {
			pok1 = pok->parent->p[pok->parent->cap - 1];
			if (pok1->cap > min) {
				rightRotation(pok1, pok->parent->cap - 1);
				return true;
			}
			else return false;
		}
		else {
			pok1 = pok->parent;
			int i = 0;
			if (pok->keys[0] == 0) {
				while (pok1->p[i]->keys[0] != 0) i++;
			}
			else {
				while (pok1->keys[i] < pok->keys[pok->cap - 1] && i < pok->cap) i++;
			}
			if (pok1->p[i + 1]->cap > min) {
				leftRotation(pok1->p[i + 1], i);
				return true;
			}
			else if (pok1->p[i - 1]->cap > min) {
				rightRotation(pok1->p[i - 1], i - 1);
				return true;
			}
			else return false;
		}
	}
}

void BStablo::leftRotation(elem* pok,int index) {
	int key = pok->parent->keys[index];
	pok->parent->keys[index] = pok->keys[0];
	elem* pok3 = pok->p[0];
	for (int i = 0; i < red - 1; i++) {
		pok->keys[i] = pok->keys[i + 1];
		pok->p[i] = pok->p[i + 1];
	}
	pok->p[red - 1] = pok->p[red];
	pok->cap--;
	elem* pok1 = pok->parent->p[index];
	insertKey(pok1, key);
	pok1->p[pok1->cap] = pok3;
	if(pok3 != nullptr) pok3->parent = pok1;
	
}

void BStablo::rightRotation(elem* pok, int index) {
	int key = pok->parent->keys[index];
	pok->parent->keys[index] = pok->keys[pok->cap - 1];
	pok->keys[pok->cap - 1] = 0;
	elem* pok2 = pok->parent->p[index + 1];
	elem* pok3 = pok->p[pok->cap];
	for (int i = red - 1; i > 0; i--) {
		pok2->keys[i] = pok2->keys[i - 1];
		pok2->p[i] = pok2->p[i - 1];
	}
	pok2->p[red] = pok2->p[red - 1];
	pok2->keys[0] = key;
	pok2->cap++;
	if (pok3 != nullptr) pok3->parent = pok2;
	pok2->p[0] = pok3;
	pok->p[pok->cap] = nullptr;
	pok->cap--;
}


void BStablo::sortiraj(int*& niz, int& broj) {
	for (int i = 0; i < broj - 1; i++) {
		for (int j = i + 1; j < broj; j++) {
			int temp;
			if (niz[j] < niz[i]) {
				temp = niz[j];
				niz[j] = niz[i];
				niz[i] = temp;
			}

		}
	}
	int j = 0;
	for (int i = 0; i < broj - 1; i++)
		if (niz[i] != niz[i + 1])
			niz[j++] = niz[i];
	niz[j++] = niz[broj - 1];
	this->broj = j;

}
void BStablo::modifikacija() {
	ifstream fajl1("numbers_20_normal.txt");
	cout << "Unesite red novi red stabla: ";
	int k;
	cin >> k;
	BStablo b1(k);
	while (fajl1 >> k) b1.dodajUStablo(k);
	cout << endl;
	b1.ispis();
}
void BStablo::ispisVisineIBrojaKljuceva() const {
	elem* pok = koren;
	int i = 0;
	while (pok != nullptr) {
		i++;
		pok = pok->p[0];
	}
	cout << "Broj nivoa je (" << i << "), a broj kljuceva je (" << this->broj << ")" << endl;
}

/*          MAIN
================================= 
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

===================================
             H.FILE
#pragma once
#include<iostream>
#include<string>
using namespace std;
class BStablo
{
	struct elem {
		int* keys, cap, tek = 0;
		elem** p, * parent;
		elem(int m) :cap(0) {
			keys = new int[m] {0};
			p = new elem * [m + 1];
			for (int i = 0; i <= m; p[i++] = nullptr);
			parent = nullptr;
		}
		elem(int *kkeys,elem **pp,int c):keys(kkeys),p(pp),cap(c),parent(nullptr){}

	};
	int red, min, broj = 0;
	struct Q {
		int front = 0, rear = 0;
		elem** niz = new elem*[1000];
		elem* ddelete() {
			return niz[front++];
		}
		void insert(elem*& pok) {
			niz[rear++] = pok;
		}
	};
	struct Stack {
		elem** niz;
		int top, bottom;
		Stack(int k) {
			niz = new elem * [k];
			bottom = 0;
			top = 0;
		}
		elem* pop() {
			return niz[--top];
		}
		void push(elem*& pok) {
			niz[top++] = pok;
		}
	};
protected:
	void dodaj(elem* pok, int key);
	elem*& split(elem*& pok);
	elem*& merge(elem*& pok);
	void skrati(elem* pok,int key);
	elem* find(elem* pok,int key);
	void insertKey(elem* pok, int key);
	elem*& findNext(elem*& pok);
	bool rotation(elem* pok);
	void rightRotation(elem* pok,int index);
	void leftRotation(elem* pok,int index);
	bool nasao(elem* pok, int key);
public:
	elem* koren;
	BStablo(int m) :red(m), min(int(ceil(m / 2))) {
		koren = new elem(m);
	}
	void sortiraj(int*& niz, int& broj);
	bool daliNasao(int key);
	void ispisVisineIBrojaKljuceva() const;
	bool dodajUStablo(int key);
	bool brisi(int key);
	void ispis();
	void modifikacija();
	int dohvatiBroj() const { return this->broj; }
};


*/