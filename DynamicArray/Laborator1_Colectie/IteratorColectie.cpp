#include "IteratorColectie.h"
#include "Colectie.h"

//Complexitate O(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
	frecventa = 1;
}

//Complexitate O(1)
void IteratorColectie::prim() {
	curent = 0;
	
}

//Complexitate O(1)
void IteratorColectie::urmator() {
	if (frecventa == col.e[curent + 1]) {

		curent = curent + 2;
		frecventa = 1;
	}
	else {
		frecventa++;
	}
	
}

//Complexitate O(1)
bool IteratorColectie::valid() const {
	return curent < col.n;
}


//Complexitate O(1)
TElem IteratorColectie::element() const {
	//elementul curent
	return col.e[curent];
}