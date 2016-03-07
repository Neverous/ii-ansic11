#include "zbiory.h"

void suma_z(const ZBIOR z1,const ZBIOR z2,ZBIOR wynik)
{
  ELEMENT i;

  for (i=0; i < ROZMIAR; ++i)
    wynik[i]=z1[i] | z2[i];
}
void przekroj_z(const ZBIOR z1,const ZBIOR z2,ZBIOR wynik)
{
  ELEMENT i;

  for (i=0; i < ROZMIAR; ++i)
    wynik[i]=z1[i] & z2[i];
}
void roznica_z(const ZBIOR z1,const ZBIOR z2,ZBIOR wynik)
{
  ELEMENT i;

  for (i=0; i < ROZMIAR; ++i)
    wynik[i]=z1[i] & ~z2[i];
}

void dopelnienie_z(ZBIOR z)
{
  ELEMENT i;

  for (i=0; i < ROZMIAR; ++i)
    z[i]=~z[i];
}

void wyczysc_z(ZBIOR z)
{
  ELEMENT i;

  for (i=0; i < ROZMIAR; ++i)
    z[i]=0;
}

void dodaj_e(const ELEMENT e,ZBIOR z)
{
  z[e/BITOW_W_INT] |= (1 << e % BITOW_W_INT);
}

void usun_e(const ELEMENT e,ZBIOR z)
{
  z[e/BITOW_W_INT] &= ~(1 << e % BITOW_W_INT);
}

int czy_pusty_z(const ZBIOR  z)
{
  ELEMENT i;

  for (i=0; i < ROZMIAR; ++i)
    if (z[i]) 
      return 1;
  return 0;
}

int element_z(const ELEMENT e,const ZBIOR z)
{
  return z[e/BITOW_W_INT] & (1 << e % BITOW_W_INT);
}
