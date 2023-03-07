#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//Complexitate teta(n)
//nu avem WC sau BC
void Multime::redim()
{
	//alocam un spatiu de capacitate dubla
	TElem* eNou = new int[2 * cp ];
	TElem* urmNou = new int[2 * cp ];
	TElem* precNou = new int[2 * cp ];
	//copiem vechile valori in noua zona
	for (int i = 0; i < n; i++)
		eNou[i] = e[i];
	for (int i = 0; i < n; i++)
		urmNou[i] = urm[i];
	for (int i = 0; i < n; i++)
		precNou[i] = prec[i];

	//dublam capacitatea
	cp = 2 * cp;

	//eliberam vechea zona
	delete[] e;
	delete[] urm;
	delete[] prec;

	//vectorul indica spre noua zona
	e = eNou;
	urm = urmNou;
	prec = precNou;

	//se initializeaza din nou lista spatiului liber
	for (int i = cp / 2;i < cp;i++)
	{
		urm[i] = i + 1;
		
	}
	for (int i = cp / 2; i < cp-1;i++)
	{
		prec[i + 1] = i;
	}
	//urm[ultim] = cp / 2;
	prec[cp / 2] = ultim;
	primLiber = cp / 2;
}

//Complexitate teta(1)
//nu avem wc sau bc
int Multime::aloca()
{
	//se sterge primul element din lista spatiului liber;
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//Complexitate teta(1)
//nu avem wc sau bc
void Multime::dealoc(int i)
{
	//se trece pozitia i in lista spatiului liber
	urm[i] = primLiber;
	primLiber = i;
}

//Complexitate O(n)
//best case: teta(1)
//worst case:Teta(n) atunci cand se faace redimensionare
int Multime::creeazaNod(TElem elem)
{
	if (n == cp)
		redim();
	int i = aloca();
	this->e[i] = elem;
	urm[i] = -1;
	prec[i] = -1;
	return i;
}

//Complexitate teta(1)
//nu avem wc sau bc
//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}
//Complexitate teta(m)  (m -capacitatea vectorului)
//nu avem wc sau bc
Multime::Multime() {
	//lista e vida
	prim = -1;
	ultim = -1;
	// setam capacitatea
	this->cp = 10;

	// alocam spatiu de memorie pentru vector
	e = new TElem[cp];
	urm = new TElem[cp];
	prec = new TElem[cp];

	// setam numarul de elemente
	this->n = 0;
	//se initializeaza lista spatiului liber - toate pozitile din vector sunt marcate ca fiind libere
	for (int i = 0;i < cp - 1;i++)
	{
		urm[i] = i + 1;
		prec[i + 1] = i;
	}
	urm[cp - 1] = -1;
	prec[0] = -1;
	primLiber = 0;
}



//Complexitate O(n)
//best case: teta(1) atunci cand adaugam pe prima pozitie
//worst case: teta(n) atunci cand adaugam pe ultima pozitie

bool Multime::adauga(TElem elem) {
	int poz = creeazaNod(elem);
	if (prim == -1) //lista este vida
	{
		n++;// crestem dimensiunea vectorului
		prim = poz;
		ultim = poz;
		urm[poz] = -1;
		prec[poz] = -1;
		return true;
	}
	else
	{
		auto curent = prim;
		while (rel(e[curent], elem) && curent!=-1)//cautam pozitia elementului in lista
		{
			if (e[curent] == elem)//verificam ca elementul sa nu se afle deja in multime
			{
				dealoc(poz);
				return false;
			}
			
			curent = urm[curent];
		}
			
		if (curent == prim)
		{
			prec[prim] = poz;
			urm[poz] = prim;
			prim = poz;
			n++;
			return true;
		}
		if (curent == -1)
		{
			urm[ultim] = poz;
			prec[poz] = ultim;
			ultim = poz;
			n++;
			return true;
		}
		//acum suntem in cazul inserarii intre 2 elemente
		urm[poz] = curent;
		auto pozitie_nod_precedent = prec[curent];
		urm[pozitie_nod_precedent] = poz;
		prec[poz] = pozitie_nod_precedent;
		prec[curent] = poz;
		n++;
		return true;


	}
	
	return false;
}

//Complexitate O(n)
//BC: Teta(1) - atunci cand stergem primul element
//WC: Teta(n) - atunci cand stergem ultimul element sau se doreste a se sterge un elem inexistent

bool Multime::sterge(TElem elem) {
	int curent = prim;
	while (e[curent] != elem && curent!=-1)
		curent = urm[curent];
	if(curent == -1)
		return false;
	if (curent == prim)
	{
		if (n == 1)
		{
			dealoc(curent);
			prim = -1;
			ultim = -1;
			n--;
			return true;
		}
		else
		{
			prec[urm[prim]] = -1;// legatura dintre nodul urmator si cel curent se distruge
			prim = urm[prim];
			dealoc(curent);
			n--;
			return true;
		}
	
	}
	if(curent == ultim)
	{
		auto poz_nod_precedent = prec[ultim];
		prec[ultim] = -1;
		urm[poz_nod_precedent] = -1;
		ultim = poz_nod_precedent;
		n--;
		dealoc(curent);
		return true;
	}
	auto poz_nod_precedent = prec[curent];
	auto poz_nod_urmator = urm[curent];
	prec[poz_nod_urmator] = poz_nod_precedent;
	urm[poz_nod_precedent] = poz_nod_urmator;
	urm[curent] = -1;
	prec[curent] = -1;
	n--;
	dealoc(curent);
	return true;


}

//Complexitate O(n)
//BC: Teta(1) - atunci cand elementul cautat se afla pe prima pozitie
//WC: Teta(n) - atunci cand elementul cautat se afla pe ultima pozitie sau nu exista
bool Multime::cauta(TElem elem) const {
	if (prim == -1)
		return false;
	int curent = prim;
	while (e[curent] != elem && curent!=-1)
		curent = urm[curent];
	if (curent == -1)
		return false;
	return true;
}

//Complexitate teta(1)
//nu avem wc sau bc
int Multime::dim() const {
	return this->n;
	return 0;
}


//Complexitate teta(1)
//nu avem wc sau bc
bool Multime::vida() const {
	if(prim == -1)
		return true;
	return false;
}

//Complexitate O(n^2*m)
//best case: Toate elementele sunt comune => Teta(n*m)
//worst case: Toate elementele difera => O(n^2*m)
void Multime::intersectie(const Multime& b) {
	int curent = prim;
	while (curent != -1)
	{
		if (b.cauta(e[curent]) == false)
		{
			auto copie_urmator= urm[curent];
			sterge(e[curent]);
			curent = copie_urmator;
		}
		else
		{
			curent = urm[curent];
		}

	}

}
//Complexitate teta(1)
//nu avem wc sau bc
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

//Complexitate teta(1)
//nu avem wc sau bc
Multime::~Multime() {
	delete[] e;
	delete[] urm;
	delete[] prec;
}






