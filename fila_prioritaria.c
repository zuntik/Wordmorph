#include "estrt_const_bibliot.h"
#include "prototipos.h"
#include "fila_prioritaria.h"

/******************************************************************************
 * FPriorIni()
 *
 * Argumentos:size - tamanho da tabela
 * Retorna: ponteiro para a fila
 * Efeitos-colaterais: ----
 *
 * Descrição: Implementa uma fila prioritária por acervo
 *
 *****************************************************************************/
FilaP * FPriorIni(int size){
    FilaP * fp = (FilaP *)x_malloc(sizeof(FilaP));
    fp->queue = (unsigned short *)x_malloc(sizeof(unsigned short)*size);
    fp->size = size;
    fp->free = 0;
    return fp;
}



/******************************************************************************
 * FInsere()
 *
 * Argumentos:  fp - ponteiro para a fila
 *              item - o item a colocar na fila
 *              weight - a tabela que armazena os pesos
 * Retorna: ---
 * Efeitos-colaterais: ----
 *
 * Descrição: Insere um elemento na fila de modo a que se mantenha a condição de acervo
 *
 *****************************************************************************/
void FInsere(FilaP * fp, int item, unsigned short weight[]){
    if(fp->free < fp->size ){
        fp->queue[fp->free] = item;
        FixUp(fp,fp->free,weight);
        fp->free++;
        return;
    }
    /*printf("A fila prioritaria está cheia, por isso há aqui um prob\n");*/
}


/******************************************************************************
 * FInsereDirec()
 *
 * Argumentos:  fp - ponteiro para a fila
 *              item - o item a colocar na fila
 *              weight - a tabela que armazena os pesos
 * Retorna: ---
 * Efeitos-colaterais: ----
 *
 * Descrição: Insere um elemento na fila sem verificar se é mantida a condição de acervo
 *
 *****************************************************************************/
void FInsereDirec(FilaP * fp, int item) {
    if(fp->free < fp->size) {
        fp->queue[fp->free] = item;
        fp->free++;
    }
}


/******************************************************************************
 * FRemove()
 *
 * Argumentos:  fp - ponteiro para a fila
 *              weight - a tabela que armazena os pesos
 * Retorna: item
 * Efeitos-colaterais: ----
 *
 * Descrição: Retorna o item de maior prioridade e reodena a fila de modo a garantir condição de acervo
 *
 *****************************************************************************/
int FRemove(FilaP * fp,unsigned short weight[]){
    int aux;

    /* executar a troca */
    aux = fp->queue[0];
    fp->queue[0] = fp->queue[fp->free -1];

    /* fazer fixdown do trocado */
    fp->free--;

    FixDown(fp,0,fp->free, weight);

    return aux;
}




/******************************************************************************
 * FixUp()
 *
 * Argumentos:  fp - ponteiro para a fila
 *              idx - idice da tabela do termo a concertar
 *              weight - a tabela que armazena os pesos
 * Retorna: ----
 * Efeitos-colaterais: ----
 *
 * Descrição: Faz Fixup do vertice numa entrada da tabela
 *
 *****************************************************************************/
void FixUp(FilaP *fp , int idx, unsigned short weight[] ){
    int aux;
    while( (idx > 0) && ( weight[ fp->queue[(idx-1)/2] ] > weight[ fp->queue [idx] ]) ){
        aux = fp->queue[(idx-1)/2];
        fp->queue[(idx-1)/2] = fp->queue[idx];
        fp->queue[idx] = aux;
        idx=(idx-1)/2;
    }
}


/******************************************************************************
 * FixDown()
 *
 * Argumentos:  fp - ponteiro para a fila
 *              idx - idice da tabela do termo a concertar
 *              weight - a tabela que armazena os pesos
 * Retorna: ----
 * Efeitos-colaterais: ----
 *
 * Descrição: Faz fix down do vertice numa entrada da tabela
 *
 *****************************************************************************/
void FixDown( FilaP *fp, int idx, int n, unsigned short weight[] ){
    int child;
    int aux;

    while( 2 * idx < n -1){
        /* comparamos os 2 filhos */
        child = 2*idx+1; /* filho 1 */
        if( (child < n-1) &&  weight[fp->queue[child] ] >  weight[fp->queue[child+1] ] )
            child++;

        /* verificamos se o filho cuja prioridade é maior tem maior prioridade que o pai */
        if(weight[fp->queue[idx] ] <  weight[fp->queue[child] ])
            break;

        aux = fp->queue[idx];
        fp->queue[idx] = fp->queue[child];
        fp->queue[child] = aux;

        idx = child;
    }
}


/******************************************************************************
 * FPfree()
 *
 * Argumentos:  fp - ponteiro para a fila
 * Retorna: ---
 * Efeitos-colaterais: ----
 *
 * Descrição: Liberta a fila prioritária para a memória
 *
 *****************************************************************************/
void FPfree(FilaP *  fp){
    free(fp->queue);
    free(fp);
}


/******************************************************************************
 * FPDiscover()
 *
 * Argumentos:  fp - ponteiro para a fila
 *              v - vertice cuja localização queremos descobrir
 * Retorna:     i - indice do vértice
 * Efeitos-colaterais: ----
 *
 * Descrição: Procura o indice do vertice, ou retorna -1 em insucesso
 *
 *****************************************************************************/
int FPDiscover(FilaP *fp, int v) {
  int i;
  for(i=0;i<fp->free;i++) {
    if( fp->queue[i] == v ) return i;
  }
  return -1;
  exit(0);
}
