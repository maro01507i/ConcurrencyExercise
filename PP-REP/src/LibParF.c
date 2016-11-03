#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "LibparF.h"


//Los va enlazando y nos devuelve la dirección al primero
tnodo * parbegin( int n, p_a_fun lista[]){
  int x, id;
  tnodo *p, *ini, *fin;
  for( x=0; x<n; x++ ){
     if( ( id=fork() ) != 0){//Padre
	p = malloc( sizeof(tnodo) );//Un new p
	if( x==0 ) ini = p;//Si es el primero, lo indicamos
	else fin->sig = p;//Si no, indicamos cual es el siguiente
	p->pid = id;//indicamos su pid
	fin = p;
     }
     else {//Hijo
	printf("\nHijo %d de %d.\n", x+1, n);
	lista[ x ]();
	exit(0);
     }
  }
  p->sig = NULL;
  return(ini);
}

void parend( tnodo * ini ){
  tnodo *q, *ant;
  int est, id;
  while( ini != NULL ){
     id = wait( &est );
     for( ant=NULL,q=ini; q!=NULL; ){
	if( q->pid==id ){
	   if( ant==NULL ) ini = q->sig;
	   else ant->sig = q->sig;
	   free( q );
	   q = NULL;
	}
	else{
	   ant = q;
	   q = q->sig;
	}
     }
  }
}
