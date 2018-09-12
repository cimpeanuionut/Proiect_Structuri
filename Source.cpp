#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
struct pozitie
{
	int x;
	int y;
};
struct inreg
{
	char* id_utilizator;
	int nr_pag;
	int nr_clicks;
	pozitie p;
	float durata;
};
struct heap
{
	inreg* v;
	int dimensiune;
};
struct nod_arbore
{
	inreg info;
	nod_arbore* st;
	nod_arbore* dr;
};
nod_arbore* creare_nod_arbore(inreg info)
{
	nod_arbore* aux = (nod_arbore*)malloc(sizeof(nod_arbore));
	aux->info.id_utilizator = (char*)malloc(sizeof(char)*(strlen(info.id_utilizator) + 1));
	strcpy(aux->info.id_utilizator, info.id_utilizator);
	aux->info.durata = info.durata;
	aux->info.nr_clicks = info.nr_clicks;
	aux->info.nr_pag = info.nr_pag;
	aux->info.p = info.p;
	aux->st = NULL;
	aux->dr = NULL;
	return aux;
}
void afisare_nod_arbore(nod_arbore* n)
{
	printf("%s \n %d \n %d \n %d \n %d \n %3.1f \n", n->info.id_utilizator, n->info.nr_pag, n->info.nr_clicks, n->info.p.x, n->info.p.y, n->info.durata);
}
nod_arbore* insera_arbore(nod_arbore* rad, inreg info)
{
	if (rad)
	{
		if (rad->info.nr_pag < info.nr_pag)
			rad->dr = insera_arbore(rad->dr, info);
		else
			rad->st = insera_arbore(rad->st, info);
		return rad;
	}
	return creare_nod_arbore(info);
}
void afisare_arbore(nod_arbore* rad,int k)
{
	if (rad)
	{
		afisare_arbore(rad->st,k);
		if (rad->info.nr_pag >= k) { afisare_nod_arbore(rad); }
		afisare_arbore(rad->dr,k);
	}
}
struct nod
{
	inreg info;
	nod* next;
};
struct HashStruct
{
	nod** elemente;
	int dimensiune;
};

nod* creare_nod(inreg info)
{
	nod* aux = (nod*)malloc(sizeof(nod));
	aux->info.id_utilizator = (char*)malloc(sizeof(char)*(strlen(info.id_utilizator)+1));
	strcpy(aux->info.id_utilizator, info.id_utilizator);
	aux->info.durata = info.durata;
	aux->info.nr_clicks = info.nr_clicks;
	aux->info.nr_pag = info.nr_pag;
	aux->info.p = info.p;
	aux->next = NULL;
	return aux;
}
nod* inserare_lista(inreg info, nod* cap)
{
	nod* nou = creare_nod(info);
	if (cap)
	{
		nou->next = cap;
		return nou;
	}
	else
		return nou;
}
void afisare_nod(nod* n)
{
	printf("%s \n %d \n %d \n %d \n %d \n %3.1f \n",n->info.id_utilizator,n->info.nr_pag,n->info.nr_clicks,n->info.p.x,n->info.p.y,n->info.durata);
}
nod* stergere_lista(char* id, nod* cap)
{
	if (cap)
	{
		nod* temp = cap;
		if (!strcmp(temp->info.id_utilizator, id))
		{
			nod* aux = cap;
			cap = cap->next;
			free(aux->info.id_utilizator);
			free(aux);
			
		}
		else {
			int ok = 0;
			while (temp->next)
			{
				if (!strcmp(temp->next->info.id_utilizator, id))
				{
					nod* aux = temp->next;
					temp->next = temp->next->next;
					free(aux->info.id_utilizator);
					free(aux);
					ok = 1;
				}
				if (temp->next)
				{
					temp = temp->next;
				}
			}
			if (ok == 0)
			{
				throw "Nu exista un nod cu acest id";
			}
		}
		return cap;
	}
	else throw"nu exista lista";
}
void cauta_utilizator_lista(char* id, nod* cap)
{
	if (cap)
	{
		nod* temp = cap;
		if (!strcmp(temp->info.id_utilizator, id))
		{
			afisare_nod(temp);
			return;
		}
		while (temp->next&&strcmp(temp->next->info.id_utilizator, id))
		{
			temp = temp->next;
		}
		if (temp->next == NULL&&strcmp(temp->next->info.id_utilizator, id))
		{
			throw "Nu exista un nod cu acest id";
		}
		else
		{
			afisare_nod(temp->next);
		}

	}
	else throw"nu exista lista";
}
nod* inserare_crescatoare_lista(nod* cap, inreg info)
{
	if (cap == NULL)
		return creare_nod(info);
	else
	{
		nod* temp = cap;
		if (temp->info.nr_clicks > info.nr_clicks)
		{
			cap = inserare_lista(info, cap);
		}
		else
		{
			while (temp->next&&temp->next->info.nr_clicks <= info.nr_clicks)
			{
				temp = temp->next;
			}
			if (temp->next == NULL)
			{
				temp->next = creare_nod(info);
			}
			else
			{
				nod* nou = creare_nod(info);
				nou->next = temp->next;
				temp->next = nou;
			}
		}
		return cap;
	}
}
void over_1000_clicks(nod* cap)
{
	if (cap)
	{
		nod* temp = cap;
		while (temp)
		{
			if (temp->info.nr_clicks > 1000)
			{
				afisare_nod(temp);
			}
			temp = temp->next;
		}
	}
	else throw"Nu exista lista";
}
void afisare_lista(nod* cap)
{
	nod* temp = cap;
	while (temp)
	{
		afisare_nod(temp);
		temp = temp->next;
	}
}
int incadrare_hashcode(int n)
{
	while(n/100)
	{
		n = n / 10;
	}
	return n;
}
int hashcode(char* id, HashStruct t)
{
	return incadrare_hashcode(atoi(id));
}
int inserare_hash(HashStruct t, inreg i)
{
	int poz = hashcode(i.id_utilizator, t);
	if (t.elemente)
	{
		if (t.elemente[poz] == NULL)
			t.elemente[poz] = creare_nod(i);
		else
		{
			nod* temp = t.elemente[poz];
			if(strcmp(t.elemente[poz]->info.id_utilizator,i.id_utilizator)>0)
			{
				nod* nou = creare_nod(i);
				nou->next = t.elemente[poz];
				t.elemente[poz] = nou;
			}
			else
			{
				while (temp->next&&(strcmp(temp->next->info.id_utilizator,i.id_utilizator)<0))
				{
					temp = temp->next;
				}
				if (temp->next == NULL)
				{
					temp->next = creare_nod(i);
				}
				else
				{
					nod* nou = creare_nod(i);
					nou->next = temp->next;
					temp->next = nou;
				}
			}
			
		}
		return poz;
	}
	else throw"Nu exista tabela";

}
void afisare_hash(HashStruct t)
{
	if(t.elemente)
	{
		for(int i=0;i<t.dimensiune;i++)
		{
			if(t.elemente[i])
			{
				afisare_lista(t.elemente[i]);
			}
		}
	}
	else throw"Nu exista tabela";
}
void cauta_utilizator(nod_arbore* rad,int nr)
{
	if(rad->info.nr_pag==nr)
	{
		afisare_nod_arbore(rad);
	}
	else
	{
		if (rad->info.nr_pag < nr)
			cauta_utilizator(rad->dr, nr);
		else cauta_utilizator(rad->st, nr);
	}
}
void stergereLogica(nod_arbore*&root, nod_arbore*&subArbore)
{
	if (subArbore->dr != NULL)
	{
		stergereLogica(root, subArbore->dr);
	}
	else
	{
		free(root->info.id_utilizator);
		root->info = subArbore->info;
		nod_arbore*tmp = subArbore;
		subArbore = subArbore->st; 
		free(tmp);

	}
}

void stergTreeNode(nod_arbore *&root, int cheie)
{
	if (root != NULL)
	{
		if (root->info.nr_pag> cheie)
		{
			stergTreeNode(root->st, cheie);
		}
		else
		{
			if (root->info.nr_pag< cheie)
				stergTreeNode(root->dr, cheie);
			else
			{
				if (root->st == NULL && root->dr == NULL)
				{
					free(root->info.id_utilizator);
					free(root);
					root = NULL; 
				}
				else
				{
					if (root->st != NULL &&root->dr == NULL)
					{
						nod_arbore*tmp = root;
						root = root->st;

						free(tmp->info.id_utilizator);
						free(tmp);
					}
					else if (root->st == NULL&&root->dr != NULL)
					{
						nod_arbore*tmp = root;
						root = root->dr;

						free(tmp->info.id_utilizator);
						free(tmp);
					}
					else
					{
						stergereLogica(root, root->st); 
					}
				}
			}
		}
	}

	else
	{
		printf("Element inexistent");
	}
}
void filtrareHeap(heap h,int poz)
{
	int pozm = poz;
	int pozst = 2 * poz + 1;
	int pozdr = 2 * poz + 2;
	if(pozst<h.dimensiune&&h.v[pozst].durata>h.v[pozm].durata)
	{
		pozm = pozst;
	}
	else if(pozdr<h.dimensiune&&h.v[pozdr].durata>h.v[pozm].durata)
	{
		pozm = pozdr;
	}
	if(poz!=pozm)
	{
		inreg aux = h.v[poz];
		h.v[poz] = h.v[pozm];
		h.v[pozm] = aux;
		if(pozm<(h.dimensiune-1)/2)
		{
			filtrareHeap(h, pozm);
		}
	}
}
void stergere_arbore(nod_arbore*&rad)
{
	if(rad)
	{
		stergere_arbore(rad->st);
		stergere_arbore(rad->dr);
		free(rad->info.id_utilizator);
		free(rad);

	}
}
void inserare_heap(heap &h,inreg info)
{
	inreg* temp = (inreg*)malloc(sizeof(inreg)*(h.dimensiune+1));
	for(int i=0;i<h.dimensiune;i++)
	{
		temp[i] = h.v[i];
	}
	temp[h.dimensiune] = info;
	h.dimensiune++;
	if (h.dimensiune != 1)
	{
		free(h.v);
	}
	h.v = temp;
	for(int i=(h.dimensiune-1)/2;i>=0;i--)
	{
		filtrareHeap(h, i);
	}
}
void afisare_heap(heap h)
{
	for(int i=0;i<h.dimensiune;i++)
	{
		afisare_nod(creare_nod(h.v[i]));
	}
}
nod* parsare(heap h)
{
	nod* x = NULL;
	if (h.v[1].durata < h.v[2].durata)
	{
		x = inserare_lista(h.v[1], x);
		x = inserare_lista(h.v[2], x);
	}
	else
		if (h.v[1].durata > h.v[2].durata)
		{
			x = inserare_lista(h.v[2], x);
			x = inserare_lista(h.v[1], x);
		}
	x = inserare_lista(h.v[0], x);
	return x;
}
void main()
{
	heap h1;
	h1.dimensiune = 0;
	FILE* f = fopen("Date.txt", "r");
	nod* lista = NULL;
	nod_arbore* a = NULL;
	HashStruct t;
	t.dimensiune = 200;
	t.elemente = (nod**)malloc((sizeof(nod*)*t.dimensiune));
	for (int i = 0; i < t.dimensiune; i++)
	{
		t.elemente[i] = NULL;
	}
	while (!feof(f))
	{
		inreg i;
		char buffer[20];
		fscanf(f, "%s", buffer);
		i.id_utilizator = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
		strcpy(i.id_utilizator, buffer);
		fscanf(f, "%d", &i.nr_pag);
		fscanf(f, "%d", &i.nr_clicks);
		fscanf(f, "%d", &i.p.x);
		fscanf(f, "%d", &i.p.y);
		fscanf(f, "%f", &i.durata);
		lista = inserare_crescatoare_lista(lista, i);
		inserare_hash(t, i);
		a = insera_arbore(a, i);
		inserare_heap(h1, i);
	}
	int k, n;
	while (true)
	{
		printf("\n Alegeti o strucura:\n1)Lista simplu inlantuita\n2)HashTable\n3)Arbore binar de cautare\n4)Heap\n5)Exit\n");
		scanf("%d", &k);
		switch (k)
		{
		case 1:
		{
			printf("Alegeti o prelucrare:\n1)Afisare crescatoare dupa nr de click-uri\n2)Utilizatori ce au efectuat peste 1000 de click-uri\n3)Cauta utilizator\n4)Stergere utilizator\n5)Primii 3 cei mai activi utilizatori\n");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
			{
				afisare_lista(lista);
				break;
			}
			case 2:
			{
				over_1000_clicks(lista);
				break;
			}
			case 3:
			{
				char id[30];
				printf("\nIntroduceti id cautat: ");
				scanf("%s", &id);
				cauta_utilizator_lista(id, lista);
				break;
			}
			case 4:
			{
				char id[30];
				printf("\nIntroduceti id pe care doriti sa il stergeti: ");
				scanf("%s", &id);
				lista = stergere_lista(id, lista);
				break;
			}
			case 5:
			{
				afisare_lista(parsare(h1));
				break;
			}
			default:
			{
				throw"Nu exista optiunea";
			}
			}
			break;
		}
		case 2:
		{
			printf("Alegeti o prelucrare:\n1)Afisare in ordinea alfabetica  \n2)Utilizatori ce au petrecut un minim de timp utilizand navigatorul\n3)Cauta utilizator\n4)Stergere utilizator\n");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
			{
				afisare_hash(t);
				break;
			}
			case 2:
			{
				printf("\n Introduceti timpul minim petrecut de fiecare utilizator:\n");
				float timp;
				scanf("%f", &timp);
				if (t.elemente)
					for (int i = 0; i < t.dimensiune; i++)
					{
						if (t.elemente[i])
						{
							nod* temp = t.elemente[i];
							while (temp)
							{
								if (temp->info.durata >= timp)
								{
									afisare_nod(temp);
								}
								temp = temp->next;
							}
						}
					}
				else throw"Nu exista elemente in tabela";
				break;
			}
			case 3:
			{
				char id[30];
				printf("\nIntroduceti id cautat: ");
				scanf("%s", &id);

				cauta_utilizator_lista(id, t.elemente[hashcode(id, t)]);
				break;
			}
			case 4:
			{
				char id[30];
				printf("\nIntroduceti id pe care doriti sa il stergeti: ");
				scanf("%s", &id);
				lista = stergere_lista(id, t.elemente[hashcode(id, t)]);
				break;
			}
			default:
			{
				throw"Nu exista optiunea";
			}

			}

			break;
		}
		case 3:
		{
			printf("Alegeti o prelucrare:\n1)Afisare in ordinea crescatoare a numarului de pagini accesate de fiecare utilizator \n2)Utilizatori ce au accesat un minim de pagini web\n3)Cauta utilizator dupa nr de pag accesate\n4)Stergerea utilizatorului care a accesat un anumit nr de pagini \n");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
			{
				afisare_arbore(a,0);
				break;
			}
			case 2:
			{

				printf("\n Introduceti numarul minim de pagini accesate de fiecare utilizator:\n");
				float min;
				scanf("%f", &min);
				afisare_arbore(a, min);
				break;
			}
			case 3:
			{
				int x;
				printf("\nIntroduceti numarul de pagini pe care le-a accesat: ");
				scanf("%d", &x);
				cauta_utilizator(a, x);
				break;
			}
			case 4:
			{
				int x;
				printf("\nIntroduceti numarul de pagini pe care le-a accesat: ");
				scanf("%d", &x);
				stergTreeNode(a, x);
				break;
			}
			default:
			{
				printf("\nOptiune inexistenta\n");
				break;
			}
			}

			break;
		}
		case 4:
		{
			printf("Alegeti o prelucrare:\n1)Afisare in ordinea descrescatoare a timpului petrecut de fiecare utilizator \n2)Utilizatori ce au cursorul situat intre anumite intervale la momentul inregistrarii\n3)Cauta utilizator dupa timpul petrecut utilizand navigatorul\n4)Stergerea utilizatorului care a utilizat navigatorul un anumit timp \n");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
			{
				afisare_heap(h1);
				break;
			}
			case 2:
			{
				int x1, x2;
				int y1, y2;
				printf("\nVloarea minima pe axa OX:");
				scanf("%d", &x1);
				printf("\nVloarea maxima pe axa OX:");
				scanf("%d", &x2);
				printf("\nVloarea minima pe axa OY:");
				scanf("%d", &y1);
				printf("\nVloarea maxima pe axa OY:");
				scanf("%d", &y2);
				for(int i=0;i<h1.dimensiune;i++)
				{
					if (h1.v[i].p.x<x2&&h1.v[i].p.x>x1&&h1.v[i].p.y<y2&&h1.v[i].p.y>y1)
						afisare_nod(creare_nod((h1.v[i])));
				}
				break;
			}
			case 3:
			{
				float x;
				printf("\nIntroduceti timpul petrecut de utilizatorul respectiv utilizand navigatorul: ");
				scanf("%f", &x);
				for (int i = 0; i<h1.dimensiune; i++)
				{
					if (h1.v[i].durata==x)
						afisare_nod(creare_nod((h1.v[i])));
				}
				break;
			}
			case 4:
			{
				float x;
				printf("\nIntroduceti timpul petrecut de utilizatorul respectiv utilizand navigatorul: ");
				scanf("%f", &x);
				inreg* temp;
				k = 0;
				temp = (inreg*)malloc(sizeof(inreg)*(h1.dimensiune-1));
				for (int i = 0; i<h1.dimensiune; i++)
				{
					if (h1.v[i].durata != x)
						temp[k++] = h1.v[i];
				}
				h1.dimensiune--;
				free(h1.v);
					h1.v = temp;
					for(int i= h1.dimensiune-1;i>=0;i--)
					{
						filtrareHeap(h1, i);
					}
					break;
			}
			default:
			{
				printf("\nOptiune inexistenta\n");
				break;
			}
			}
		
			break;
		}
		case 5:
		{
			nod* aux;
			while(lista)
			{
				aux = lista;
				lista = lista->next;
				free(aux->info.id_utilizator);
				free(aux);
			}
			for(int i=0;i<t.dimensiune;i++)
			{
				if(t.elemente[i])
				{
					while (t.elemente[i])
					{
						aux = t.elemente[i];
						t.elemente[i] = t.elemente[i]->next;
						free(aux->info.id_utilizator);
						free(aux);
					}
				}
			}
			free(t.elemente);
			t.elemente = NULL;
			stergere_arbore(a);
			a = NULL;
			for(int i=0;i<h1.dimensiune;i++)
			{
				free(h1.v[i].id_utilizator);
			}
			free(h1.v);
			h1.v = NULL;
			exit(0);
		}
		default:
		{
			printf("Optiune inexistenta\n");
			break;
		}
		}
	}
}
