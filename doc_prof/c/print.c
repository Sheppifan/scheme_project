#include<stdio.h>
#include"object.h"
#include"print.h"


// Fonction affichant un boolean
void print_boolean(object obj){
  if (obj->data.boolean==1){
       fprintf(stdout,"#t");
  }
  else 
    if(obj->data.boolean==0){
       fprintf(stdout,"#f");
    }
    else 
      fprintf(stderr, "L'object passé en parametre n'est pas un boolean" );
}


/// Fonction retournant 0,1,2,3 respectivement si ce qui est passé en paramètre est non défini, un atome, un liste, une empty_list
int test_atom_pair_empty(object obj){
  /* printf("entree dans test_atom_pair_empty\n");
    printf("add obj=%p\n",obj);
    printf("add obj->data=%p\n",&(obj->data));
    printf("obj->type=%d\n",obj->type);*/
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
  char* type= malloc(20);
  //printf("entree dans print_atom\n");
  if (test_atom_pair_empty(obj)==1){
  //  printf("obj->type %d\n",obj->type);
    switch (obj->type){
    case 6:
      type="symbol";
      fprintf(stdout, "%s" , obj->data.symbol);
      break;
    case 5:
      type="boolean";
      print_boolean(obj);
      //fprintf(stdout, "%d" , obj->data.boolean);
      break;
    case 0:
      type="integer";
      fprintf(stdout, "%d" , obj->data.number.this.integer);
      break;
    case 1:
      type="character";
      fprintf(stdout, "%c" , obj->data.character);
      break;
    case 2:
      type="string";
      fprintf(stdout, "%s" , obj->data.String);
      break;
      ///case '8':
      ///type="primitive";
      ///     fprintf(stdout, "Valeur : %s" , obj->this.special);
      ///break;
    }
    //printf("  ");
    //fprintf(stdout, "Type : %s" ,type);
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
   //printf("entree dans print\n");
   if (test_atom_pair_empty(obj)==2){
     //printf("test_atom effec=2\n");
	//printf("%p\n",&(obj->data.pair.car));
	// printf("%d\n",obj->data.pair.car->type);
     // if (test_atom_pair_empty(obj->data.pair.car)==2){
       // printf("test_atom data.pair.Car effec=2\n");
     // fprintf(stdout, "(");
     // }
     sfs_print_pair(obj);
     // if (test_atom_pair_empty(obj->data.pair.car)==2){
       // printf("test_atom data.pair.Car apres print_pair effec=2\n");
     // fprintf(stdout, ")");

     //}
   }
   else {

      if (test_atom_pair_empty(obj)==1){
	sfs_print_atom(obj);
	/* printf("vers line 90\n");
	   printf("car=%p\n",&(obj->data.pair.car));
	   printf("cdr=%p\n",&(obj->data.pair.cdr));
	   printf("cdr->type=%p\n",&(obj->data.pair.cdr->type));
	   if (obj->data.pair.cdr->type != SFS_NIL){
	   fprintf(stdout, " ");
	   }*/
      }
      else {
	if (test_atom_pair_empty(obj)==3){
	  //fprintf(stdout,"()");
	}
	else {
	  fprintf(stderr,"Erreur: l'object* n'est ni une liste ni un atome" );
	}
      }
  }
}


///Fonction affichant une paire
void sfs_print_pair(object paire){
  // printf("entree dans print_pair \n");
  if (test_atom_pair_empty(paire->data.pair.car)!=2){
    fprintf(stdout,"(");
  }
  sfs_print(paire->data.pair.car);
  if (test_atom_pair_empty(paire->data.pair.cdr)!=3){
  fprintf(stdout, " ");
  }
  sfs_print(paire->data.pair.cdr);
  if (test_atom_pair_empty(paire->data.pair.cdr)!=3){
    fprintf(stdout,")");
  }
}

