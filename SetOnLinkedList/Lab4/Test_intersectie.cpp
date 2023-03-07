#include "TestScurt.h"
#include "Multime.h"
#include "IteratorMultime.h"
#include <assert.h>
#include <iostream>
using namespace std;
void Test_intersectie() { //apelam fiecare functie sa vedem daca exista
	int vverif[5];
	int iverif;
	TElem e;

	Multime m1;
	assert(m1.adauga(5) == true);
	assert(m1.adauga(1) == true);
	assert(m1.adauga(10) == true);
	IteratorMultime im1 = m1.iterator();


	Multime m;
	m1.intersectie(m);
	assert(m1.dim() == 0);
	//return;
	assert(m1.adauga(5) == true);
	assert(m1.adauga(1) == true);
	assert(m1.adauga(10) == true);
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
	m.intersectie(m1);
	assert(m.dim() == 3);
	assert(m.cauta(10) == true);
	assert(m.cauta(7) == false);
	assert(m.cauta(-3) == false);
	Multime m2;
	assert(m2.adauga(100) == true);
	assert(m2.adauga(101) == true);
	assert(m2.adauga(102) == true);
	m1.intersectie(m2);
	assert(m1.dim() == 0);
	

}
