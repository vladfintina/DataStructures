#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
#include <cstdlib>
Dictionar::Dictionar() {
	m = MAX;
	nr = 0;
	//se initializeaza vectorii
	for (int i = 0; i < m; i++) {
		e[i].first = LIBER;
		e[i].second = LIBER;
		urm[i] = -1;
	}
	//initializare primLIber
	primLiber = 0;

}

Dictionar::~Dictionar() {
	/* de adaugat */
}
//Complexitate AC(1) 
//WC:O(m)
void Dictionar::actPrimLiber()
{
	primLiber++;
	while (primLiber < m && e[primLiber].second != LIBER)
		primLiber++;
}

int Dictionar::d(TElem e)
{
	//dispersia prin diviziune
	return abs(e.first % m);

}
//Complexitate AC(1) 
//WC:O(m)
TValoare Dictionar::adauga(TCheie c, TValoare v) {
	TElem element;
	element.first = c;
	element.second = v;
	int poz = d(element);
	int j = 0;
	if (e[poz].first == LIBER)
	{
		e[poz].first = c;
		e[poz].second = v;
		if (poz == primLiber)
			actPrimLiber();
		nr++;
		return NULL_TVALOARE;
	}
	else
	{
		while (poz != -1 && e[poz].first != c)
		{
			j = poz;
			poz = urm[poz];
		}
		if (poz != -1)
		{
			int val = e[poz].second; //cheia se afla deja in dictionar
			e[poz].second = v;
			return val;
		}
		else
		{
			e[primLiber].first = c;
			e[primLiber].second = v;
			urm[j] = primLiber;
			actPrimLiber();
			nr++;
			return NULL_TVALOARE;
		}
	}
	
}


//Complexitate AC(1) 
//WC:O(m)
//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const {
	TElem element;
	element.first = c;
	element.second = 0;
	int poz_dispersie_de_cautat = abs(c % m); //functia d
	while (poz_dispersie_de_cautat != -1 && e[poz_dispersie_de_cautat].first != c)
		poz_dispersie_de_cautat = urm[poz_dispersie_de_cautat];
	if(poz_dispersie_de_cautat == -1)
		return NULL_TVALOARE;
	return e[poz_dispersie_de_cautat].second;
}

//Complexitate AC(1) 
//WC:O(m)
TValoare Dictionar::sterge(TCheie c) {
	TElem element;
	element.first = c;
	element.second = 0;
	int vd = d(element);
	int prec=-1;
	int i = 0;
	//cautam precedent pentru vd
	while (i < m && prec == -1)
	{
		if (urm[i] == vd)
			prec = i;
		else
			i = i + 1;
	}
	i = vd;//poz de pe care sterg
	int j = prec;//poz ant lui i
	while (i != -1 && e[i].first != c)
	{
		j = i;
		i = urm[i];
	}
	if( i == -1)
		return NULL_TVALOARE;
	else
	{
		bool gata = false;
		int v = e[i].second;
		do {
			int p,pp;
			p = urm[i];
			pp = i;
			while (p != -1 && d(e[p]) != i)
			{
				pp = p;
				p = urm[p];
			}
			if (p == -1) //daca nu am mai gasit niciun element inseamna ca nu mai avem ce muta
				gata = true;
			else //daca am gasit un element ce se disperseaza pe pozitia i il mutam si trecem mai departe
			{
				e[i] = e[p];
				i = p;
				j = pp;
			}

		} while (!gata);

		int prec = -1;
		int vd = d(element);
		if (j != -1)
		{
		
			urm[j] = urm[i];
		}
		//e[i] = NULL_TVALOARE;
		e[i].first = LIBER;
		e[i].second = LIBER;
		urm[i] = -1;
		if (i < primLiber)
			primLiber = i;
		nr--;
		return v;
	}
}

//Complexitate AC(n*m) 
//WC:O(n*m)
int Dictionar::adaugaInexistente(Dictionar& d)
{
	IteratorDictionar id = d.iterator();
	id.prim();
	int nr1 = 0;
	while (id.valid())
	{
		TElem element = id.element();
		int cheie = element.first;
		int valoare = element.second;
		if (this->cauta(cheie) == NULL_TVALOARE)
		{
			this->adauga(cheie, valoare);
			nr1++;
			nr++;
		}
		id.urmator();
	}

	return nr;
}
//Complexitate teta(1)
int Dictionar::dim() const {
	return nr;
}

//Complexitate teta(1) 
bool Dictionar::vid() const {
	if(nr == 0)
		return true;
	return false;
}

//Complexitate 1 
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


