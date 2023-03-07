#pragma once

typedef int TCheie;
typedef int TValoare;
#include <vector>
#include <iostream>
#include <algorithm>


#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
	friend class Iterator;
    private:
	/* aici e reprezentarea */
	Relatie rel;
	typedef struct node {
		TCheie c;
		TValoare v;

		node(TCheie c, TValoare v) : c(c), v(v) {};
	} node;

	typedef struct node_list {
		int stanga{ -1 }, dreapta{ -1 };
		node* el{ nullptr };

		~node_list() {
			//delete el;
		}
	} node_list;


	int capacity, size;
	node_list* list;
	int rad;
	int first_free;

	void alloc(int);

	int find(int, TCheie) const;

	int parinte(int nod) const {
		//theta inaltime
		if (nod == rad) {
			return -1;
		}
		auto poz = rad;
		auto c = list[nod].el->c;
		while (list[poz].dreapta != nod && list[poz].stanga != nod) {
			if (rel(c, list[poz].el->c)) {
				poz = list[poz].stanga;
			}
			else
				poz = list[poz].dreapta;
		}

		return poz;
	}

	int succesor(int nod) const {
		//O inaltime
		if (list[nod].dreapta != -1) {
			return min(list[nod].dreapta);
		}
		auto p = parinte(nod);

		while (p != -1 && nod == list[p].dreapta) {
			//cout<<"galati"<<endl;
			nod = p;
			p = parinte(nod);
		}
		return p;
	}

	int min(int p) const {
		//O inaltime
		if (p == -1)
			return -1;
		while (list[p].stanga != -1)
			p = list[p].stanga;
		return p;
	}

	bool del(int, TCheie, TValoare);

	void update_free() {
		//O n
		first_free = 0;
		while (first_free < capacity && list[first_free].el != nullptr)
			first_free++;
	}

    public:

	// constructorul implicit al dictionarului
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//elimina toate elementele din dictionar
	void goleste();

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// destructorul dictionarului
	~DO();

};
