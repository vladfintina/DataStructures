#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Nod::Nod(TElem e, PNod urm, PNod prec) {
	this->e = e;
	this->urm = urm;
	this->prec = prec;
}

TElem Nod::element() {
	return e;
}

PNod Nod::urmator() {
	return urm;
}

PNod Nod::precedent() {
	return prec;
}


//Complexitat Teta(1)
Multime::Multime() {
	prim = nullptr;
}

//average case:Complexitate O(n)
//best case: elementul pe care dorim sa il adaugam este deja in lista pe prima pozitie => Teta(1)
//worst case:elementul pe care dorim sa il adaugam este deja in lista pe ultima pozitie sau nu este deloc=> Teta(1) 
bool Multime::adauga(TElem elem) {
	/* de adaugat */
	if (prim == nullptr)
	{
		PNod p = new Nod(elem, nullptr, nullptr);
		prim = p;
		return true;
	}
	else 
	{
		bool ok = true;
		PNod curent = prim;
		while (curent != nullptr)
			if (curent->element() == elem)
			{
				ok = false;break;
			}
			else
				curent = curent->urmator();
		if(ok == true)
		{
			PNod p = new Nod(elem, nullptr, nullptr);
			p->urm = prim;
			prim->prec = p;
			prim = p;
			return true;
		}
	}
	return false;
	
}

//average case: O(n) 
//best case: elementul ce trebuie sters se afla pe prima pozitie => Teta(1)
//worst case: elementul ce trebuie sters nu se alfa in lista sau este pe ulima pozitie => Teta(n)
bool Multime::sterge(TElem elem) {
	PNod curent = prim;
	if (prim != nullptr)
	{
		//cazul 1 stergem de la inceput
		if (prim->element() == elem)
		{
			if (dim() == 1)
			{
				prim = nullptr;
				delete(prim);
				return true;
			}
				
			curent = prim;
			prim = prim->urmator();
			prim->prec = nullptr;
			delete (curent);
			return true;
		}
		while (curent != nullptr)
		{
			if (curent->element() == elem)
			{
				(curent->precedent())->urm = curent->urmator();
				if(curent->urmator()!= nullptr)
					(curent->urmator())->prec = curent->precedent();
				curent->prec = nullptr;
				curent->urm = nullptr;
				delete(curent);
				return true;
			}
			curent = curent->urmator();

		}
	}
	return false;
}

//average case: O(n) 
//best case: elementul ce trebuie cautat se afla pe prima pozitie => Teta(1)
//worst case: elementul ce trebuie cautat nu se alfa in lista sau este pe ulima pozitie => Teta(n)
bool Multime::cauta(TElem elem) const {
	PNod curent = prim;
	while (curent != nullptr)
	{
		if (curent->element() == elem)
			return true;
		curent = curent->urmator();
	}
	return false;
}

// Complexitat Teta(n)
// nu avem BC sau WC
int Multime::dim() const {
	int n = 0;
	PNod curent = prim;
	while (curent != nullptr)
	{
		n++;
		curent = curent->urmator();
	}
	return n;
}

//Complexitate Teta(1)
//nu avem BC sau WC
bool Multime::vida() const {
	if(prim == nullptr)
		return true;
	return false;
}

//Complexitate Teta(n)
//nu avem BC sau WC
Multime::~Multime() {
	while (prim != nullptr)
	{
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}//Complexitate
// Average case: O(n)
// Best case: primul element din multimea mea nu face parte din m si atunci se opreste subprogramul Teta(dim(m))
//Worst case: dimensiunea multimii mele este mai mare decat m si contine toate elementele din m 
//            sau multimea mea = m => Teta(n *dim(m))
bool Multime::submultime(Multime& m) const {
	//if (dim() > m.dim())
		//return false;
	PNod curent = prim;
	bool ok = true;
	while (curent != nullptr)
	{
		TElem elem = curent->element();
		if (m.cauta(elem) == false)
		{
			ok = false;
			break;
		}
		curent = curent->urmator();

	}
	return ok;


}
//Complexitate Teta(1)
//nu avem BC sau WC
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

