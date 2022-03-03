#include"liste_doublement_chainee.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct block{
  int data;
  struct block* prev;
  struct block* next;
};

static void test_set_empty(){
  DLIST dliste1=set__empty();
  DLIST dliste2=set__empty();
  assert(set__is_empty(dliste1)==1);
  assert(set__is_empty(dliste2)==1);
  free(dliste1->tete);free(dliste2->tete);
  free(dliste1);
  free(dliste2);
  printf("OK(1) pour create_empty_set && testing if a set is empty or not.\n");
  return;
}

static void test_add_remove__HEAD(){
  DLIST dliste1=set__empty();
  assert(set__is_empty(dliste1)==1);
  add__head(dliste1,3);
  add__head(dliste1,2);
  add__head(dliste1,1);
  assert(!set__is_empty(dliste1));
  assert(dliste1->tete->next->data==1);
  assert(dliste1->tete->next->next->data==2);
  assert(dliste1->tete->next->next->next->data==3);
  assert(dliste1->tete->next->next->next->prev->data==2);
  assert(dliste1->tete->next->next->next->next==NULL);
  assert(dliste1->tete->next->next->next->prev->prev->data==1);
  assert(dliste1->tete->next->next->next->prev->prev->prev->data==0);
  assert(dliste1->tete->next->next->next->prev->prev->prev->prev==NULL);
  printf("OK: 1/2 pour la 1er partie de add__HEAD.\n");
  remove__head(dliste1);
  remove__head(dliste1);
  assert(dliste1->tete->data==0);
  assert(dliste1->tete->next->data==3);
  assert(dliste1->tete->next->next==NULL);
  assert(dliste1->tete->prev==NULL);
  assert(dliste1->tete->next->prev->data==0);
  assert(dliste1->tete->next->next==NULL);
  remove__head(dliste1);
  free(dliste1->tete);
  free(dliste1);
  printf("OK: 2/2 pour la 2ieme partie de remove__HEAD.\n");
  return;
}

static void test_set_size(){
  DLIST dliste=set__empty();
  add__head(dliste,1);
  add__head(dliste,2);
  add__head(dliste,3);
  add__head(dliste,4);
  add__head(dliste,5);
  assert(set__size(dliste)==5);
  remove__head(dliste);
  remove__head(dliste);
  assert(set__size(dliste)==3);
  remove__head(dliste);
  assert(set__size(dliste)==2);
  remove__head(dliste);
  assert(set__size(dliste)==1);
  remove__head(dliste);
  free(dliste->tete);free(dliste);
  printf("OK(3): POUR SET__size(struct dliste*).\n");
  return;
}

static void test_debug_data(){
  void impression(void* p){
    printf("%d\t",*(int*)p);
  }
  DLIST dliste=set__empty();
  add__head(dliste,3);add__head(dliste,5);add__head(dliste,7);
  debug__data(dliste,impression);
  printf("**********************\n\n");
  remove__head(dliste);remove__head(dliste);
  add__head(dliste,2);add__head(dliste,1);
  debug__data(dliste,impression);
  printf("**********************\n\n");
  clear__dliste(dliste);
  printf("OK(4&5): pour debug__data of set encapsulation elements(clear__dliste donc IMPLICITEMENT.\n");
  return;
}

static void test_set_find(){
  DLIST dliste=set__empty();
  add__head(dliste,3);add__head(dliste,5);add__head(dliste,7);
  assert(set__find(dliste,3)==1);
  assert(set__find(dliste,0)==0);
  assert(set__find(dliste,1)==0);
  assert(set__find(dliste,2)==0);
  assert(set__find(dliste,4)==0);
  assert(set__find(dliste,5)==1);
  assert(set__find(dliste,6)==0);
  assert(set__find(dliste,7)==1);
  assert(set__find(dliste,8)==0);
  assert(set__find(dliste,9)==0);
  clear__dliste(dliste);
  printf("OK(6|++++8  .////): pour SET_FIND.//\n");
  return;
}

static void test_adding_from_end2(){
  DLIST dliste=set__empty();
  add__tail(dliste,2);
  add__tail(dliste,3);
  add__tail(dliste,4);
  add__head(dliste,1);
  void impression(void* p){
    printf("%d\t",*(int*)p);
  }
  debug__data(dliste,impression);
  //clear__dliste(dliste);(genere des erreurs de valgrind;attention)
  //clear__dliste(dliste);
  //au lieu de faire cela (deja verifiee);on supprimera les elements un a un..
  remove__tail(dliste);
  debug__data(dliste,impression);
  remove__head(dliste);
  debug__data(dliste,impression);
  remove__tail(dliste);
  debug__data(dliste,impression);
  clear__dliste(dliste);
  printf("OK(9+10( &    )) for adding/removing element from set's end.\n");
  return;
}

//rq: une fonction en static void designe le fait qu'elle est relatif a la
//classe seulement ; elle est pas parmi les methodes d'heritage au niveau
//des objets instanciés par la classe. (pensons a la fonction constructor
//sur un 'this')
//C'EST ~la particularite de la classe. (~ au niveau de PLUSIEURS cas)

static void test_adding_after_1(){
  DLIST dliste=set__empty();
  struct block* inter1=dliste->tete;
  add__after_elmnt(dliste,inter1,1);
  add__tail(dliste,2);
  add__head(dliste,3);
  void impression(void* p){
    printf("%d\t",*(int*)p);
  }
  debug__data(dliste,impression);
  struct block* inter2=dliste->tete->next;
  add__after_elmnt(dliste,inter2,4);
  assert(dliste->tete->data==0);
  assert(dliste->tete->next->data==3);
  assert(dliste->tete->next->next->data==4);
  assert(dliste->tete->next->next->next->data==1);
  assert(dliste->tete->next->next->next->next->data==2);
  assert(dliste->tete->next->next->next->next->next==NULL);
  assert(dliste->tete->prev==NULL);
  debug__data(dliste,impression);
  add__after_elmnt(dliste,dliste->tete->next->next,5);//3 4 5 1 2
  debug__data(dliste,impression);
  clear__dliste(dliste);
  printf("OK pour |11|: adding after an allocated in request encapsulation data.!!\n");
  /*clear__dliste(dliste);*/
  return;
}

static void test_removing_after_2(){
  void impression(void* p){
    printf("%d\t",*(int*)p);
  }
  DLIST dliste=set__empty();
  add__head(dliste,2);
  add__tail(dliste,3);
  add__tail(dliste,4);
  add__tail(dliste,5);
  add__head(dliste,1);
  debug__data(dliste,impression);
  struct block* inter_1=dliste->tete->next->next;
  remove__after_elmnt(dliste,inter_1);
  debug__data(dliste,impression);
  struct block* inter_2=dliste->tete->next;
  remove__after_elmnt(dliste,inter_2);
  debug__data(dliste,impression);
  struct block* inter_3=dliste->tete->next->next;
  remove__head(dliste);
  remove__after_elmnt(dliste,inter_3);
  debug__data(dliste,impression);
  clear__dliste(dliste);
  printf("OK pour le dernier <<12>>: removing after an 'element'..///\n");
  return;
}

int main(int argc, char* argv[]){
  test_set_empty();
  test_add_remove__HEAD();
  test_set_size();
  test_debug_data();
  test_set_find();
  test_adding_from_end2();
  test_adding_after_1();
  test_removing_after_2();
  return 0;
}
