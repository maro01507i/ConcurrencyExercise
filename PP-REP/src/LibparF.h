/*
 * LibparF.h
 *
 *  Created on: 02/11/2016
 *      Author: ivan
 */

#ifndef LIBPARF_H_
#define LIBPARF_H_

struct nodo {
  int pid;
  struct nodo *sig;
};

typedef struct nodo tnodo;

typedef void (*p_a_fun)( void );

tnodo * parbegin( int, p_a_fun[] );

void parend ( tnodo * );

#endif /* LIBPARF_H_ */
