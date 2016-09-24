
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"


typedef struct object_t {

    uint type;

    union{

        num              number;
        string          caractere;
        string           String;
        string           symbol;
        int              boolean;

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        }                pair;

        struct object_t *special;

    } data;

} *object;


object make_object( uint type );
object make_nil( void );
int is_integer(char num);
int is_symbol(char sym);
object make_symbol(char* input,uint * here,char c);
object make_caractere(char* input,uint *here);
object make_integer( char* input, uint * here,char c);
object make_string(char *input,uint * here);

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06


extern object nil;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
