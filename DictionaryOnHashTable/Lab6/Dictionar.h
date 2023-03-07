#pragma once
#pragma once


#define NULL_TVALOARE -1
#define MAX 80001
#define LIBER -100000
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Dictionar {
	friend class IteratorDictionar;

private:

	//reprezentare folosind o TD - rezolvare coliziuni prin liste intrepatrunse
	int m; //numarul de locatii din tabela de dispersie
	int nr;//numar elemente in tabela de dispersie
	TElem e[MAX]; //vectorul elementelor - vector static
	int urm[MAX]; //vectorul legaturilor
	int primLiber; // locatia primei pozitii libere din tabela

	//actualizare primLiber
	void actPrimLiber();
	//functia de dispersie
	int d(TElem e);




public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//adauga in dictionarul curent toate perechile din d a caror cheie nu se afla deja in dictionar
	// returneaza numarul de perechi adaugate
	int adaugaInexistente(Dictionar& d);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	int dim() const;

	//verifica daca dictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const;


	// destructorul dictionarului	
	~Dictionar();

};


