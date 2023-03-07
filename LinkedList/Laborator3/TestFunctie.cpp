#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>
void testFunctieLaborator() { //apelam fiecare functie sa vedem daca exista

	Multime m, m2;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5) == true);
	assert(m.adauga(1) == true);
	assert(m.adauga(10) == true);
	assert(m.adauga(7) == true);
	assert(m.adauga(1) == false);
	assert(m.adauga(10) == false);
	assert(m.adauga(-3) == true);
	assert(m.dim() == 5);

	assert(m2.submultime(m) == true);
	assert(m2.adauga(5) == true);
	assert(m2.adauga(1) == true);
	assert(m2.adauga(10) == true);
	assert(m2.submultime(m) == true);
	assert(m2.adauga(21) == true);
	assert(m2.submultime(m) == false);
	m2.sterge(21);
	m2.adauga(7);
	m2.adauga(-3);
	assert(m2.submultime(m) == true);
	m2.adauga(30);
	assert(m2.submultime(m) == false);


	

}
