#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;


//referire a clasei Nod

class Nod;



//se defineste tipul PNod ca fiind adresa unui Nod

typedef Nod* PNod;



class Nod

{

public:

	friend class Multime;

	//constructor

	Nod(TElem e, PNod urm, PNod prec);

	TElem element();

	PNod urmator();

	PNod precedent();

private:

	TElem e;

	PNod urm;

	PNod prec;

};


class Multime {
	friend class IteratorMultime;

private:
	/* aici e reprezentarea */
	//prim este adresa primului nod din multime
	PNod prim;

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;


	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//verifica daca multimea curenta este o submultime a multimii primite ca parametru
	bool submultime(Multime& m) const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
};




