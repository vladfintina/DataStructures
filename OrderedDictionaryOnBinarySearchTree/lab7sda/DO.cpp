#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) {
	//theta 1
	/* de adaugat */
	this->rel = r;
	rad = -1;
	size = 0;
	capacity = 50;
	list = new node_list[50];
	first_free = 0;
}


void DO::alloc(int new_cap) {
	//theta n
	auto new_list = new node_list[new_cap];

	for (int i = 0; i < capacity; i++) {
		new_list[i] = list[i];
		list[i].el = nullptr;
	}

	first_free = capacity;
	capacity = new_cap;
	delete[] list;
	list = new_list;
}

int DO::find(int nod, TCheie key) const {
	//theta inaltime


	if (list[nod].el->c == key)
		return nod;

	if (rel(key, list[nod].el->c)) {
		if (list[nod].stanga == -1)
			return nod;
		return find(list[nod].stanga, key);
	}
	else {
		if (list[nod].dreapta == -1)
			return nod;
		return find(list[nod].dreapta, key);
	}

}
//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	//theta inaltime
	/* de adaugat */
	size++;
	if (rad == -1) {
		rad = first_free;
		list[first_free].el = new node(c, v);
		update_free();
		return NULL_TVALOARE;
	}

	auto poz = find(rad, c);


	if (list[poz].el->c == c) {
		TValoare v_vechi = list[poz].el->v;
		list[poz].el->v = v;
		size--;
		return v_vechi;
	}

	if (first_free == capacity)
		alloc(2 * capacity);

	list[first_free].el = new node(c, v);

	if (rel(c, list[poz].el->c))
		list[poz].stanga = first_free;
	else
		list[poz].dreapta = first_free;

	update_free();
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	//theta inaltime
	if (rad == -1) {
		return NULL_TVALOARE;
	}

	auto poz = find(rad, c);


	if (list[poz].el->c == c)
		return list[poz].el->v;

	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	//theta inaltime
	/* de adaugat */
    if (rad == -1) {
		return NULL_TVALOARE;
    }
    auto nod = find(rad, c);
    if (list[nod].el->c != c)
        return NULL_TVALOARE;


    size--;
	int v_vechi = list[nod].el->v;
    list[nod].el->v= NULL_TVALOARE;

	if (list[nod].stanga == -1 && list[nod].dreapta == -1) {
		auto parinteNod = parinte(nod);
		delete list[nod].el;
		if (nod == rad) {
			rad = -1;
			return v_vechi;
		}
		if (list[parinteNod].dreapta == nod)
			list[parinteNod].dreapta = -1;
		else
			list[parinteNod].stanga = -1;
		list[nod].el = nullptr;
		update_free();
        return v_vechi;
    }
    else if (list[nod].stanga != -1 && list[nod].dreapta != -1) {
        auto last = nod;
        auto temp = list[nod].dreapta;
        while (list[temp].stanga != -1) {
            last = temp;
            temp = list[temp].stanga;
        }
        delete list[nod].el;
        if (last == nod) {
            list[nod].el = list[temp].el;
            list[nod].dreapta = list[temp].dreapta;
        }
        else {
            list[nod].el = list[temp].el;
            list[last].stanga = list[temp].stanga;
        }
        list[temp].el = nullptr;
        list[temp].stanga = -1;
        list[temp].dreapta = -1;
		update_free();
        return v_vechi;
    }
    else {
		if (rad == nod)
		{
			if (list[nod].stanga == -1) 
				rad = list[nod].dreapta;
			else
				rad = list[nod].stanga;
			
			delete list[nod].el;
			list[nod].stanga = -1;
			list[nod].dreapta = -1;
			list[nod].el = nullptr;
		}
		else {
			auto parinteNod = parinte(nod);
			if(list[nod].stanga == -1)
				if (list[parinteNod].dreapta == nod)
					list[parinteNod].dreapta = list[nod].dreapta;
				else
					list[parinteNod].stanga = list[nod].dreapta;
				else
				if (list[parinteNod].dreapta == nod)
					list[parinteNod].dreapta = list[nod].stanga;
				else
					list[parinteNod].stanga = list[nod].stanga;
			delete list[nod].el;
			list[nod].stanga = -1;
			list[nod].dreapta = -1;
			list[nod].el = nullptr;
		}
		
    }
	update_free();
    return v_vechi;
}


void DO::goleste() {
	//theta n
	for (int i = 0; i < capacity; i++) {
		list[i].el = nullptr;
		list[i].dreapta = -1;
		list[i].stanga = -1;
	}
	size = 0;
	update_free();
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	//theta 1
	/* de adaugat */
	return size;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	/* de adaugat */
	//theta 1
	return size == 0;
}

Iterator DO::iterator() const {
	//theta 1
	return  Iterator(*this);
}

DO::~DO() {
	/* de adaugat */
	//theta 1
	delete[] list;
}
