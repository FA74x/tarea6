/* 5088530 */

#include "../include/colaDePrioridad.h"
#include "../include/info.h"

struct _rep_colaDePrioridad {
  bool maM;
  nat tam;
  nat tope;
  TInfo *heap;
  nat *pos;
};

TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad cp = new _rep_colaDePrioridad;
  cp->maM = true;
  cp->tam = N;
  cp->heap = new TInfo[N+1];
  cp->tope = 0;
  cp->pos = new nat[N+1];
  for (nat i = 0; i <= N; i++)
    cp->pos[i] = 0;
  return cp;
}

void filtradoAscendente(nat pos, TColaDePrioridad cp) {
  TInfo aux = cp->heap[pos];
  while ((cp->maM && pos > 1 && realInfo(aux) < realInfo(cp->heap[pos/2])) || (!cp->maM && pos > 1 && realInfo(aux) > realInfo(cp->heap[pos/2]))) {
    cp->heap[pos] = cp->heap[pos/2];
    cp->pos[natInfo(cp->heap[pos])] = pos;
    pos = pos / 2;
  }
  cp->heap[pos] = aux;
  cp->pos[natInfo(cp->heap[pos])] = pos;
}

void filtradoDescendente(nat pos, TColaDePrioridad cp) {
  TInfo aux = cp->heap[pos];
  while (2 * pos <= cp->tope) {
    nat hijo = 2 * pos;
    if (cp->maM && hijo + 1 <= cp->tope && realInfo(cp->heap[hijo+1]) < realInfo(cp->heap[hijo]))
      hijo = hijo + 1;
    if (!cp->maM && hijo + 1 <= cp->tope && realInfo(cp->heap[hijo+1]) > realInfo(cp->heap[hijo]))
      hijo = hijo + 1;
    if ((cp->maM && realInfo(cp->heap[hijo]) < realInfo(aux)) || (!cp->maM && realInfo(cp->heap[hijo]) > realInfo(aux))) {
      cp->heap[pos] = cp->heap[hijo];
      cp->pos[natInfo(cp->heap[pos])] = pos;
      pos = hijo;
    } else {break;}
  }
  cp->heap[pos] = aux;
  cp->pos[natInfo(cp->heap[pos])] = pos;
}

void cambiarOrden(nat elem, double valor, TColaDePrioridad cp) {
  nat pos = cp->pos[elem];
  double valorAnt = realInfo(cp->heap[pos]);
  liberarInfo(cp->heap[pos]);
  cp->heap[pos] = crearInfo(elem,valor);
  if ((valorAnt > valor && cp->maM) || (valorAnt < valor && !cp->maM))
    filtradoAscendente(pos,cp);
  else if ((valorAnt < valor && cp->maM) || (valorAnt > valor && !cp->maM))
    filtradoDescendente(pos,cp);
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) {
  if (cp->maM)
    cp->maM = false;
  else
    cp->maM = true;
  for (nat i = 1; i <= cp->tope; i++)
    filtradoAscendente(i,cp);  
  return cp;
}
  
void liberarCP(TColaDePrioridad cp) {
  for (nat i = 1; i <= cp->tope; i++)
    liberarInfo(cp->heap[i]);
  delete[] cp->heap;
  delete[] cp->pos;
  delete cp;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if (!estaEnCP(elem,cp) && elem > 0 && elem <= cp->tam) {
    cp->tope = cp->tope + 1;
    cp->heap[cp->tope] = crearInfo(elem,valor);
    cp->pos[elem] = cp->tope;
    filtradoAscendente(cp->tope,cp);
  } else if (elem > 0 && elem <= cp->tam) {
    cambiarOrden(elem,valor,cp);
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
  return cp->tope == 0; 
}

nat prioritario(TColaDePrioridad cp)  {
  return natInfo(cp->heap[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)  {
  if (cp->tope == 1) {
    cp->pos[natInfo(cp->heap[1])] = 0;
    liberarInfo(cp->heap[1]);
    cp->tope = 0;
  } else if (cp->tope > 1) {
    cp->pos[natInfo(cp->heap[1])] = 0;
    liberarInfo(cp->heap[1]);
    cp->heap[1] = cp->heap[cp->tope];
    cp->heap[cp->tope] = NULL;
    cp->tope = cp->tope - 1;
    cp->pos[natInfo(cp->heap[1])] = 1;
    filtradoDescendente(1,cp);
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp)  {
  return elem <= cp->tam && cp->pos[elem] != 0;
}

double prioridad(nat elem, TColaDePrioridad cp)  {
  return realInfo(cp->heap[cp->pos[elem]]);
}
