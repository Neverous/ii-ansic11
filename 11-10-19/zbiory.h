/* Plik naglowkowy: zbiory.h                                   */
/*          Bitowa implementacja operacji na zbiorach          */
#include <limits.h>

#define MAX_ELEM     10000000UL
#define BITOW_W_INT  (CHAR_BIT*sizeof(unsigned int))
#define ROZMIAR      (MAX_ELEM/BITOW_W_INT+1)

typedef unsigned long int ELEMENT; // po zmianie sprawdzic format drukowania
typedef unsigned int ZBIOR[ROZMIAR];

/***************** PROTOTYPY FUNKCJI ********************/

void suma_z(const ZBIOR z1,const ZBIOR z2,ZBIOR wynik);
void przekroj_z(const ZBIOR z1,const ZBIOR z2,ZBIOR wynik);
void roznica_z(const ZBIOR z1,const ZBIOR z2,ZBIOR wynik);
void dopelnienie_z(ZBIOR z);
void wyczysc_z(ZBIOR Z);
void dodaj_e(const ELEMENT e,ZBIOR z);
void usun_e(const ELEMENT e,ZBIOR z);
int czy_pusty_z(const ZBIOR  z);
int element_z(const ELEMENT e,const ZBIOR z);
