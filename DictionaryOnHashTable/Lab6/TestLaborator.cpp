
#include "TestLaborator.h"
#include <iostream>
#include <assert.h>
#include "Dictionar.h"
#include "IteratorDictionar.h"


void testLaborator()
{
	Dictionar d1;
	assert(d1.vid() == true);
	assert(d1.dim() == 0); //adaug niste elemente
	assert(d1.adauga(5, 5) == NULL_TVALOARE);
	assert(d1.adauga(1, 111) == NULL_TVALOARE);
	assert(d1.adauga(10, 110) == NULL_TVALOARE);
	assert(d1.adauga(7, 7) == NULL_TVALOARE);
	assert(d1.adauga(1, 1) == 111);
	assert(d1.adauga(10, 10) == 110);

	Dictionar d2;
	assert(d2.vid() == true);
	assert(d2.dim() == 0); //adaug niste elemente
	assert(d2.adauga(5, 5) == NULL_TVALOARE);
	assert(d2.adauga(1, 111) == NULL_TVALOARE);
	assert(d2.adauga(10, 110) == NULL_TVALOARE);
	assert(d2.adauga(7, 7) == NULL_TVALOARE);
	assert(d2.adauga(1, 1) == 111);
	assert(d2.adauga(10, 10) == 110);
	assert(d2.adauga(11, 11));

	
	assert(d1.adaugaInexistente(d2)==1);
	assert(d1.cauta(11) == 11);
	assert(d1.adaugaInexistente(d2) == 0);
	assert(d2.adauga(12, 12));
	assert(d2.adauga(13, 13));
	assert(d1.adaugaInexistente(d2) == 2);
}