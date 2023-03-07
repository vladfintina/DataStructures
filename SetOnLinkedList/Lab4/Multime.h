#pragma once

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

class Multime {

	friend class IteratorMultime;

private:
	//capacitate
	int cp;

	//numar elemente(dimensiune)
	int n;

	//vector elemente
	TElem *e;

	//vector pentru legaturi urmatoare
	TElem* urm;

	//vector pentru legaturi precedente
	TElem* prec;

	//referinta catre primul element al listei
	int prim;

	//referinta catre ultimul element al listei
	int ultim;

	//referinta catre primul element din lista spatiului liber
	int primLiber;

	//functii pentru alocarea/dealocarea unui spatiu liber
	//se returneaza pozitia unui spatiu liber in lista
	int aloca();

	//dealoca spatiul de indice i
	void dealoc(int i);

	//functie privata care creeaza un nod in lista inlantuita
	int creeazaNod(TElem elem);

	// pentru redimensionare
	void redim();

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

	//pastreaza doar elementele care apar si in multimea b
	void intersectie(const Multime& b);

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();

};

