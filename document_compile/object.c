
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"
#include "read.h"


object make_object( uint type ) {

    object t = sfs_malloc( sizeof( *t ) );

    t->type = type;

    return t;
}

object make_nil( void ) {

    object t = make_object( SFS_NIL );

    t->data.special = t;

    return t;
}

int is_integer(char num)
{   //teste si num est un entier
    if (num>=0x30 && num<=0x39)
        return 1;
    else return 0;
}

int is_symbol(char sym)
{   //teste si sym est un caractere (lettre ou caractere speciaux)
    if((sym>=0x3A  && sym<=0x7E)|| (sym>=0x24 && sym<=0x26) || (sym>=0x2A && sym<=0x2F) || sym==0x21 )
        return 1;
    else return 0;
}



object make_symbol(char* input,uint * here,char c)
{
	object atome=make_object(6);
	char new_carac;
	int i=1;
	char symbole[10*STRLEN];//creation d'un tableau de char
	symbole[0]=c;
	new_carac=get_next_char(input,here);
	//test si le prochaine caractere est un symbole et remplissage du tableau
	while(is_symbol(new_carac)||is_integer(new_carac))
	{
		symbole[i]=new_carac;
		new_carac=get_next_char(input,here);
		i++;
	}
	symbole[i]='\0';
	strcpy(atome->data.String,symbole);//copie du tableau dans atome
	return atome;
}

object make_caractere(char* input,uint *here)
{
	object atome=make_object(1);
	char new_carac;
	int i=3;
	char caractere[STRLEN];//creation d'un tableau de char
	caractere[0]='#';
	caractere[1]=0x5C;
	caractere[2]=input[(*here)];
	new_carac=get_next_char(input,here);
	//pour tester les caracteres invalides
	if(new_carac!='\0'){
        if((is_symbol(new_carac)&& is_integer(caractere[2]))||(is_symbol(caractere[2])&& is_integer(new_carac)))
        {
            caractere[0]='\0';
            WARNING_MSG("caractere invalide");
            strcpy(atome->data.caractere,caractere);
            return atome;
        }
    }
    //remplissage du tableau de char
	while(is_symbol(new_carac) || new_carac==0x28 || new_carac==0x29)
	{
		caractere[i]=new_carac;
		new_carac=get_next_char(input,here);
		i++;
	}
	//test de caracteres invalides
    if(new_carac!='\0' && i>3){
           if((is_symbol(new_carac)&& is_integer(caractere[i-1]))||(is_symbol(caractere[i-1])&& is_integer(new_carac)))
        {
            caractere[0]='\0';
            strcpy(atome->data.caractere,caractere);
            return atome;
        }
    }
	caractere[i]='\0';
	strcpy(atome->data.caractere,caractere);//copie du tableau dans atome
	return atome;
}

object make_integer( char* input, uint * here,char c)
{
	object atome=make_object(0);
	char next;
	int integer=0;
	integer = c-0x30;
    next=get_next_char(input,here);
	while (next>=0x30 && next<=0x39)
	{
        integer=integer*10+(next-0x30);
		next=get_next_char(input,here);

	}
	atome->data.number.this.integer=integer;
	return atome;
}


object make_string(char *input,uint * here)
{
	object atome=make_object(2);
	char next;
	int i=1;
	char chaine[10*STRLEN];//creation d'un tableau de caractere
	chaine[0]='"';
	next=get_next_char(input,here);
	while ((next != 0x22))
	{
		chaine[i]=next;
		next=get_next_char(input,here);
		i++;
		//test pour empecher qu'un " éludé par un \ soit pris en compte comme fin de chaine
		if(chaine[i-1]==0x5C && next==0x22)
        {
             chaine[i]=next;
             next=get_next_char(input,here);
             i++;
        }
	}
	chaine[i]='"';
	chaine[i+1]='\0';
	(*here)++;
	strcpy(atome->data.String,chaine);
	return atome;
}
