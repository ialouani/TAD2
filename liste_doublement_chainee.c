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

void add__tail(DLIST dliste, int b){
  if(set__is_empty(dliste)){
    add__head(dliste,b);return;}
  else{
    struct block* temp2=dliste->tete;
    struct block* temp=dliste->tete;
    //temp->next!=NULL
    while(temp->next!=NULL){
      temp2=temp;
      temp=temp->next;
    }
    //*temp2 est l'encapsulation qui represente l'avant dernier block.
    struct block* addf=(struct block*)malloc(sizeof(*addf));
    addf->data=b;
    addf->prev=NULL;
    addf->next=NULL;
    //prise en compte de l'encapsulation precedente.
    temp->next=addf;
    addf->prev=temp2->next;
    return;
  }
}

void remove__tail(DLIST dliste){
  if(set__is_empty(dliste)){
    fprintf(stdout,"Error(2): Problem of removing from an empty set!\n");   
    exit(2);
  }
  else{
    struct block* temp2=dliste->tete;
    struct block* temp=dliste->tete;
    while(temp->next!=NULL){
      temp2=temp;
      temp=temp->next;
    }
    //temp represente le dernier block et temp2 l'avant dernier block.
    //si set__size(dliste)==1 alors: temp2 represente l'encapsulation de
    //depart 0 et temp represente l'encapsulation qui suit cette derniere.
    unsigned int len=set__size(dliste);
    if(len==1){
      //juste pour se convaincre que dans ce cas: temp ne represente pas
      //un vrai element.
      temp2->next=NULL;
      //temp->prev=NULL;
      temp->prev=NULL;
      //temp devient un block sans chainage derriere ou d'avant.
      free(temp);return;
    }
    else{//len>1
      //temp2 ne sera pas une correspondance de block nul.((nil))
      temp2->next=NULL;
      temp->prev=NULL;
      free(temp);
      return;
    }
  }
}

void add__after_elmnt(DLIST dliste, struct block* after, int d){
  if(set__is_empty(dliste) && after->data==0 && after->next==NULL && after->prev==NULL){
    add__head(dliste,d);return;
  }
  else if(!set__is_empty(dliste) && set__size(dliste)==1){
    if(after==dliste->tete){
      add__head(dliste,d);
    }
    else{
      add__tail(dliste,d);
    }
    return;
  }//pour savoir les add_head/remove quand ils se manifestent.
  else{//size>=2 donc si on prend 2 temp2 et temp
    //avec une boucle de parcours ; temp2 ne renfermera la fleche vers
    //un element de type int nulle(--valeur).
    struct block* temp2;
    struct block* temp=dliste->tete->next;
    while(temp!=after){
      temp=temp->next;
      //temp2=temp->next;
    }
    temp2=temp->next;//temp->next existe au plus NULL.
    if(temp2!=NULL){
    //a la sortie: temp=after
    //et: temp2 correspond a l'element qui suit after.
    struct block* add0=(struct block*)malloc(sizeof(*add0));
    add0->data=d;
    add0->prev=NULL;
    add0->next=NULL;
    add0->prev=temp;add0->next=temp->next;
    //temp->next=add0;//add0->prev=temp;
    //temp2->prev=add0;//add0->next=temp2;
    temp->next=add0;temp2->prev=add0;
    return;}
    else{//temp2==NULL(<=>after->next==NULL) donc after correspond au dernier element.
      add__tail(dliste,d);return;
    }
  }
}

void remove__after_elmnt(DLIST dliste, struct block* after){
  if(!set__find(dliste,after->data) || set__is_empty(dliste)){
    fprintf(stdout,"Operation impossible, a verifier les frees(<1) avant au pire.\n");
    exit(3);
  }
  else if(set__size(dliste)==1){
    remove__tail(dliste);return;}
  else{//size>=2
    struct block* temp=dliste->tete;//on generalise..
    while(temp!=after){
      temp=temp->next;
    }//a la sortie, on a temp==after.
    if(temp->next==NULL){//<=>temp pointe vers le dernier element.
      return;//impossible de supprimer ; il y a rien apres a SUPPRIMER.
    }
    else{//au moins temp se situe dans l'avant derniere position.
      if(temp->next->next==NULL){//ca revient au cas de ''base''
	//impliquant l'application de la fonction: remove__tail
	remove__tail(dliste);return;}
      else{
	//temp se situe logiquement(pour le point1) a la deuxieme position
	//au niveau des encapsulations + le fait que on a au minimum
	//2 elements in front of that.
	struct block* temp2=temp->next->next;
	struct block* temp_that_has_to_be_removed=temp->next;
	temp->next=temp2;temp2->prev=temp;
	temp_that_has_to_be_removed->prev=NULL;
	temp_that_has_to_be_removed->next=NULL;
	free(temp_that_has_to_be_removed);
	return;
      }
    }
  }
}







	  


    
