#include"liste_doublement_chainee.h"
#include<stdlib.h>
#include<stdio.h>

struct block{
  int data;
  struct block* prev;
  struct block* next;
};

DLIST set__empty(void){
  DLIST dliste=(DLIST)malloc(sizeof(struct dliste));
  dliste->tete=(struct block*)malloc(sizeof(*dliste->tete));
  dliste->tete->data=0;
  dliste->tete->prev=NULL;
  dliste->tete->next=NULL;
  return dliste;
}

Bool set__is_empty(DLIST dliste){
  return dliste->tete->next==NULL;
}

//convention d'une structure doublement chainee vide est:>
// NULL reliee a la cellule contenant data=0 & reliee a NULL
//donc toute cellule dont .tete->next==NULL revient a dire
//qu'on s'arrete des le 0 (element tjrs de depart existant)
//=>pas d'element nouveau=>liste doublement chainee vide. 

void add__head(DLIST dliste, int b){
  if(b<0) return;
  else if(set__is_empty(dliste)){
    struct block* add=(struct block*)malloc(sizeof(*add));
    add->data=b;
    add->prev=dliste->tete;
    add->next=NULL;
    dliste->tete->next=add;
  }
  else{//!set__is_empty(dliste)
    struct block* add=(struct block*)malloc(sizeof(*add));
    add->data=b;add->next=NULL;add->prev=NULL;
    struct block* tmp=dliste->tete->next;
    dliste->tete->next=add;
    add->prev=dliste->tete;add->next=tmp;
    tmp->prev=add;
  }
  return;
}

void remove__head(DLIST dliste){
  if(set__is_empty(dliste)){
    fprintf(stdout,"Error: set are already empty, no element to be removed!\n");
    exit(1);
  }
  else if(dliste->tete->next->next==NULL){
    struct block* tmp2=dliste->tete->next;
    struct block* tmp=dliste->tete->next;
    tmp->prev=NULL;
    dliste->tete->next=NULL;
    //tmp->prev=NULL;(avant la derniere)
    //dliste->tete->next->next=NULL;(on a deja cette information)
    free(tmp2);
    return;
  }
  else{//set__size(dliste)>1.(dliste->tete->next->next!=NULL, 2 en terme
    //d'elements differents de 0.
    struct block* tmp2=dliste->tete->next->next;
    struct block* tmp=dliste->tete->next;
    tmp->next=NULL;tmp->prev=NULL;
    dliste->tete->next=tmp2;
    tmp2->prev=dliste->tete;
    free(tmp);
    return ;
  }
}

unsigned int set__size(DLIST dliste){
  unsigned int len=0;
  if(set__is_empty(dliste)) return len;
  else{
    len++;
    struct block* tmp=dliste->tete->next;//!=NULL cat !set__is_empty(dliste).
    while(tmp->next!=NULL){
      len++;
      tmp=tmp->next;
    }
  }
  return len;
}
//pas forcément trié car pas disponibilité de deux interfaces d'abstraction
//dépendants.
Bool set__find(DLIST dliste, int a){
  if(set__is_empty(dliste)) return false;
  else if(dliste->tete->next->next==NULL) return dliste->tete->next->data==a;
  else{
    struct block* tmp=dliste->tete->next;
    while(tmp->next!=NULL){
      if(tmp->data==a) return true;
      tmp=tmp->next;
    }
    return tmp->data==a;
  }
}

void debug__data(DLIST dliste,void (*print)(void*)){
   if(set__is_empty(dliste)) return;
   else if(dliste->tete->next->next==NULL){
     print((void*)(&(dliste->tete->next->data)));
     printf("\n");
   }
   else{
     struct block* tmp=dliste->tete->next;
     while(tmp->next!=NULL){
       print((void*)(&(tmp->data)));
       //printf("\n");
       tmp=tmp->next;
     }
     print((void*)(&(tmp->data)));printf("\n");return;
   }
}

void clear__dliste(DLIST dliste){
  if(set__is_empty(dliste)){
    free(dliste->tete);
    free(dliste);
  }
  else{
    struct block* tmp=dliste->tete;
    //!=NULL car !set__is_empty(dliste).
    while(tmp->next!=NULL){
      struct block* tmp2=tmp->next;
      free(tmp);
      tmp=tmp2;
    }
    free(tmp);free(dliste);
    //le dernier non vidé tel que LA BOUCLE est le dernier struct element ''''
    //CAR: il vérifie tmp->next==NULL et on fait un free(tmp) pour chaque
    //tmp vérifiant tmp->next!=NULL donc a la fin de la boucle le dernier
    //element a savoir tmp (verifiant logiquement DONC tmp->next==NULL) qui est
    //pas libere=>pas de problemes-==>&&&:
    //free(tmp) puis reste l'indicateur de pointage --depart via: free(dliste).
  }
}





  























    
    




