#include "IteratorMultime.h"
#include "Multime.h"

//Complexitate teta(1)
//nu avem wc sau bc
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	curent = m.prim;
}

//Complexitate teta(1)
//nu avem wc sau bc
TElem IteratorMultime::element() const {
	return mult.e[curent];
}

//Complexitate teta(1)
//nu avem wc sau bc
bool IteratorMultime::valid() const {
	return curent != -1;
}

//Complexitate teta(1)
//nu avem wc sau bc
void IteratorMultime::urmator() {
	curent = mult.urm[curent];
}

//Complexitate teta(1)
//nu avem wc sau bc
void IteratorMultime::prim() {
	curent = mult.prim;
}

