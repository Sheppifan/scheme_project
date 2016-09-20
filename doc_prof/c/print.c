#include<stdio.h>
#include"object.h"
#include"print.h"


/// Fonction retournant 0,1,2,3 respectivement si ce qui est passé en paramètre est non défini, un atome, un liste, une empty_list
int test_atom_pair_empty(object obj){
  if (((obj->type>=0)&&(obj->type<=2))||((obj->type<=8)&&(obj->type>=5))){
    return 1;
  }
  else {
    if(obj->type==3) {
	return 2;
      }
      else{
	if(obj->type==4){
	  return 3;
	}
	else 
	  {
	    fprintf(stderr, "Erreur: L'object* n'a pas de type défini!!");
	    exit(1);
	    ///Faire arreter le programme !!
	  }
      }
      }
  }

///Fonction prenant un object* en parametre pour retourner le type et la valeur d'un atome
///Elle vérifie que c'est bien un atome PUIS trouve son type PUIS renvoie sa valeur et son type
void sfs_print_atom(object obj){
  char* type;
  if (test_atom_pair_empty(obj)==1){
    switch (obj->type){
    case '6':
      type="symbol";
      fprintf(stdout, "Valeur : %s" , obj->data.symbol);
      break;
    case '5':
      type="boolean";
      fprintf(stdout, "Valeur : %d" , obj->data.boolean);
      break;
    case '0':
      type="integer";
      fprintf(stdout, "Valeur : %d" , obj->data.number.this.integer);
      break;
    case '1':
      type="character";
      fprintf(stdout, "Valeur : %c" , obj->data.character);
      break;
    case '2':
      type="string";
      fprintf(stdout, "Valeur : %s" , obj->data.String);
      break;
      ///case '8':
      ///type="primitive";
      ///     fprintf(stdout, "Valeur : %s" , obj->this.special);
      ///break;
    }
    fprintf(stdout, "Type : %s" ,type);
  }
  else
    {
      if (test_atom_pair_empty(obj)==2){
	fprintf(stderr, "Erreur: La fonction ne traite pas les paires ! Il faut lui donner un atome !!!");
      }
      else {
	fprintf(stderr, "Erreur: L'object* n'a pas de type défini !!");
      }
      exit(EXIT_FAILURE);
    }
}


///Fonction print globale !
 void sfs_print(object obj){
   if (test_atom_pair_empty(obj)==2){
     if (test_atom_pair_empty(obj->data.pair.car)==2){
       fprintf(stdout, "(");
     }  
     sfs_print_pair(obj);
     if (test_atom_pair_empty(obj->data.pair.car)==2){
       fprintf(stdout, ")");

     }
   }
  else {
    if (test_atom_pair_empty(obj)==1){
      sfs_print_atom(obj);
      if (obj->data.pair.cdr->type != SFS_NIL){
	fprintf(stdout, " ");
      }
    }
    else {
      if (test_atom_pair_empty(obj)==3){
	fprintf(stdout,".................");
      }
      else {
      fprintf(stderr,"Erreur: l'object* n'est ni une liste ni un atome" );
      }
    }
  }
}


///Fonction affichant une paire
void sfs_print_pair(object paire){
     sfs_print(paire->data.pair.car);
     sfs_print(paire->data.pair.cdr);
}
    
