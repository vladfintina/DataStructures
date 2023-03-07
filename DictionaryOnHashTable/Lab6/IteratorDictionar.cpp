#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;


//Complexitate O(m)
//BC O(1)
void IteratorDictionar::deplasare() {
	while ((curent < dict.m) && dict.e[curent].first == LIBER)
		curent++;

}
//Complexitate O(m)
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d) {
	curent = 0;
	deplasare();
}

//Complexitate O(m)
void IteratorDictionar::prim() {
	curent = 0;
	deplasare();
}

//Complexitate O(m)
void IteratorDictionar::urmator() {
	curent++;
	deplasare();
}

//Complexitate teta(1)
TElem IteratorDictionar::element() const {
	/* de adaugat */
	return pair <TCheie, TValoare>(dict.e[curent].first, dict.e[curent].second);
}

//Complexitate O(1)
bool IteratorDictionar::valid() const {
	return (curent < dict.m);
}

