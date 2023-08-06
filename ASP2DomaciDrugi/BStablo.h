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

