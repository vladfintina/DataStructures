#include "Iterator.h"
#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	/* de adaugat */
	prim();
}

void Iterator::prim(){
	//O inaltime
	poz = dict.min(dict.rad);
}

void Iterator::urmator(){
	//O inaltime
	/* de adaugat */
	if (!valid())
		throw exception();
	/* de adaugat */
	poz = dict.succesor(poz);

}

bool Iterator::valid() const{
	//theta 1
	/* de adaugat */
	return poz != -1;
}

TElem Iterator::element() const{
	// theta 1 
	/* de adaugat */
	if (!valid())
		throw exception();
	return pair <TCheie, TValoare>(dict.list[poz].el->c, dict.list[poz].el->v);
}


