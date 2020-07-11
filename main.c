#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tabuleiro.h"
#include "interface.h"

int main(void) {
  //Numero de jogadores
  int num_jog;
  printf("Numero de jogadores: ");
  scanf("%d",&num_jog);
  
  //Lista de jogadores alocada dinamicamente
  char **nomes =(char **) malloc(sizeof(char *)*num_jog);
  if(!nomes){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }
  int i = 0;
  for( i = 0; i < num_jog; i++){
    nomes[i] = (char *) malloc(sizeof(char)*20);
    if(!nomes[i]){
    printf("Problema de alocacao de memoria!");
    exit(1);
    }
  }

  //Limpar o buffer
  setbuf(stdin, NULL);
   //Receber os nomes de todos os jogadores
  for(int i=0;i<num_jog;i++){
    printf("Nome do jogador %d: ", i+1);
    fgets(nomes[i], 20, stdin);
    for(int k=0;k<20;k++){
      if(nomes[i][k]=='\n'){
        nomes[i][k]='\0';
      }
    }
  }
  //Habilitar ou nao o modo de trapaca
  int cheatmode;
  printf("Cheat mode (Sim=1/Nao=0): ");
  scanf("%d",&cheatmode);
  //Numero inicial de linahs e colunas da matriz
  int n_linhas = 1;
  int n_colunas = 1;
  int *m = &n_linhas;
  int *n = &n_colunas;
  //Alocar o tabuleiro na heap
  Peca **matriz = aloca_tabuleiro(n_linhas, n_colunas);
  //Preencher o tabuleiro com espacos
  fill_tabuleiros(matriz, n_linhas, n_colunas, ' ');
  //Imprimir o tabuleiro em sua configuracao inicial
  print_tabuleiro(matriz, n_linhas, n_colunas);
  //Loop do jogo.
  while(1){
      menu(matriz, m, n, num_jog, nomes, cheatmode);
      //matriz_ = jogada(matriz_, m, n);
      break;
  }
  free(nomes);
  return 0;
}