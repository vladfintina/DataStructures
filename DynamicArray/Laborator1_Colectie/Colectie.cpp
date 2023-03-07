#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

//Complexitate O(n)
void Colectie::redim() {
	//alocam un spatiu de capacitate dubla
	TElem* eNou = new int[2 * cp];

	//copiem vechile valori in noua zona
	for (int i = 0; i < n; i++)
		eNou[i] = e[i];

	//dublam capacitatea
	cp = 2 * cp;

	//eliberam vechea zona
	delete[] e;

	//vectorul indica spre noua zona
	e = eNou;
}
//Complexitate O(1)
Colectie::Colectie() {
	// setam capacitatea
	this->cp = 10;

	// alocam spatiu de memorie pentru vector
	e = new TElem[cp];

	// setam numarul de elemente
	this->n = 0;

}

//Complexitate O(n)
void Colectie::adauga(TElem elem) {
	auto ok = false;
	if (n == cp)
		redim();
	if (n == 0) {
		e[0] = elem;
		e[1] = 1;
		n = n + 2;
	}
	else {
		   for (int i = 0; i <n; i = i + 2){
			   if (e[i] == elem) {
				   e[i + 1]++;
				   ok = true;
			   }			
		   }
		   if (ok == false){
			   e[n] = elem;
			   e[n + 1] = 1;
			   n = n + 2;
		   }

	}

	
}

// Complexitate O(n)
bool Colectie::sterge(TElem elem) {
	for (int i = 0; i < n; i = i + 2) {
		if (e[i] == elem) {
			e[i + 1] = e[i + 1] - 1;
			if (e[i + 1] == 0) {
				//daca frecventa devine 0 stergem celula elementului si a frecventei sale
				for (int j = i; j < n - 2; j++)
					e[j] = e[j + 2];
				n = n - 2;
			}
			return true;
		}

	}
	return false;
}

//Complexitate O(n)
bool Colectie::cauta(TElem elem) const {
	for (int i = 0;i < n;i = i + 2) {
		if (e[i] == elem)
			return true;
	}
	return false;
}

//Complexitate O(n)
int Colectie::nrAparitii(TElem elem) const {
	for (int i = 0;i < n;i = i + 2) {
		if (e[i] == elem)
			return e[i+1];
	}
	return 0;
}

//Complexitate Teta(n)
int Colectie::dim() const {
	int dimensiune = 0;
	for (int i = 1;i < n;i = i + 2) {
		dimensiune = dimensiune + e[i];
	}
	return dimensiune;
}

//Complexitate O(1)
bool Colectie::vida() const {
	if (n == 0)
		return true;
	else
		return false;
}

//Complexitate O(1)
IteratorColectie Colectie::iterator() const {
	//returnam un iterator pe vector
	return  IteratorColectie(*this);
}

//Complexitate O(1)
Colectie::~Colectie() {
	// eliberam zona de memorie alocata vectorului
	delete[] e;
}
