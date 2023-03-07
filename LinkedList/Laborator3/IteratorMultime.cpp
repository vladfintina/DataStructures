#include "IteratorMultime.h"
#include "Multime.h"

//Complexitate Teta(1)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	curent = m.prim;
}

//Complexitate Teta(1)
void IteratorMultime::prim() {
	curent = multime.prim;
}

//Complexitate Teta(1)
void IteratorMultime::urmator() {
	curent = curent->urmator();
}

//Complexitate Teta(1)
void IteratorMultime::precedent() {
	curent = curent->precedent();
}
//Complexitate Teta(1)
TElem IteratorMultime::element() const {
	return curent->element();
}

//Complexitate Teta(1)
bool IteratorMultime::valid() const {
	return curent != nullptr;
}
