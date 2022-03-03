#ifndef __ID
#define __ID
//entiers >0 sur ce TAD d'ensemble sous forme de double chainage.
enum Bool{false,true};
//pour etre clair: definir le type enum Bool en tant que Bool via:
//typedef enum Bool Bool:->
typedef enum Bool Bool;

struct block;

typedef struct dliste{
  struct block* tete;
}*DLIST;

//donc ici: au lieu d'avoir un pointeur vers *DLISTE de type struct dliste ;
//on pourrait déclarer un pointeur directement avec le type DLISTE===au type
//struct dliste*.


unsigned int set__size(DLIST dliste);//type meme que struct dliste*.
Bool set__find(DLIST dliste, int a);//retourne a dans *dliste --cellules ou nn.
void debug__data(DLIST dliste,void (*print)(void*));

//passons au regroupement numero 2 de fonctions: initialisation+assistance.
DLIST set__empty(void);
Bool set__is_empty(DLIST dliste);

//dernier regroupement de fonctions:
void add__head(DLIST dliste, int b);
void remove__head(DLIST dliste);
void clear__dliste(DLIST);

/*void add__tail(DLIST dliste, int b);
void remove__tail(DLIST dliste);

void add__after_elmnt(DLIST,struct block*,int);
void remove__after_elmnt(DLIST,struct block*,int);*/

#endif
//~Inversement, on commencera par implementer le groupe 2 puis le groupe 3
//(pour suivre le suivi 'naturel' des tests fonctionnels puis le dernier
//groupe; à savoir le:  1.


