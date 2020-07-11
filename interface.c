#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "tabuleiro.h"
#include "dinamica.h"
#include "pecas.h"
//Pega uma string e retira todas as palavras, retornando uma matriz de strings.
char** get_palavras(char *string, int *num){
  //Quantidade de palavras;
  int count_palavra = 0;
  int a = 0;
  int i = 0;
  char** palavra;
  //Aloca dinamicamente uma matriz de chars.
  palavra = (char **) malloc(sizeof(char*)*10);
  if(!palavra){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }
  for(i = 0; i < 10; i++){
    palavra[i] = (char *) malloc(sizeof(char)*20);
    if(!palavra[i]){
    printf("Problema de alocacao de memoria!");
    exit(1);
    }
  }
  //Caso comece com espacos, avanca-se ate a primeira palavra
  while(string[a] == ' '){
    a++;
  }
  //Enquanto a string nao acabar, retiram-se as palavras
  while(string[a] != '\0'){
      i = 0;
      /*Se o char da posicao a nao for um espaco, coloca-se o caracter em uma string da matriz palavra*/
      while(string[a] != ' ' && string[a] != '\0'){
        palavra[count_palavra][i] = string[a];
        i++;
        a++;
      }
      /*
      Se o char da posicao a for um espaco, avanca-se
      */
      palavra[count_palavra][i] = '\0';
      count_palavra++;
      while(string[a] == ' ' && string[a] != '\0'){
        a++;
      }
  }
  *num = count_palavra;
  return palavra;
}


Peca** jogada(Peca **matriz, int *m, int *n, Peca n_peca, int *c_x, int *c_y, int *pos, int *linha, int **track, Peca * retirar){
    if(*c_x >= *m || *c_x < 0 || *c_y >= *n || *c_y < 0){
        printf("\n*****************\n");
        printf("entrada invalida 1!");
        printf("\n*****************\n");
        return matriz;
    }

    if(*pos == 1){
      if(ver(matriz, *c_x, *c_y, track, pos, 1)){
        *linha = 1;
      }else if(ver(matriz, *c_x, *c_y, track, pos, 0)){
        *linha = 0;
      }else{
        printf("\n*****************\n");
        printf("entrada invalida 2!");
        printf("\n*****************\n");
        return matriz;
      }
    }

    if(*pos > 1){
      if(!ver(matriz, *c_x, *c_y, track, pos, *linha)){
        printf("\n*****************\n");
        printf("entrada invalida 3!");
        printf("\n*****************\n");
        return matriz;
      }
    }
    
    if(matriz[*c_x][*c_y].forma != ' '){
      printf("\n*************************\n");
      printf("Invalid move 4!");
      printf("\n*************************\n");
    }else{
      matriz[*c_x][*c_y].forma = n_peca.forma;
      matriz[*c_x][*c_y].cor = n_peca.cor;
      if(check_move(matriz, *c_x, *c_y, *m, *n)){
       track[*pos][0] = *c_x;
       track[*pos][1] = *c_y;
       Peca **matriz_ = resize_tabuleiro(matriz, m, n, track, *pos);
       //update_tabuleiro(matriz, m, n, track, *pos);
       print_tabuleiro(matriz_, *m, *n);
       printf("\nx_old: %d y_old: %d\n", track[*pos][0], track[*pos][1]);
       (*pos)++;
       retirar->forma = ' ';
       retirar->cor = ' ';
       printf("\n*****************\n");
       return matriz_;
      }else{
        matriz[*c_x][*c_y].forma = ' ';
        matriz[*c_x][*c_y].cor = ' ';
        printf("\n*************************\n");
        printf("Invalid move 3!");
        printf("\n*************************\n");
       }
    }
    return matriz;
}

void menu(Peca **matriz, int *m, int *n, int num_jog, char **nomes, int cheatmode){
    int pos = 0;

    int x_old = 0;

    int y_old = 0;

    int turno = 0;

    int c_x = 0;

    int c_y = 0;

    int linha = 0;

    int i = 0;

    int *usadas = (int *) malloc(sizeof(int)*108);
    
    if(usadas==NULL){
      exit(1);
    }

    for(i = 0; i < 108; i++){
      usadas[i] = 0;
    }

    Peca **pecas = (Peca**) malloc(sizeof(Peca*)*num_jog);

    for(i = 0; i < num_jog; i++){
      pecas[i] = (Peca *) malloc(sizeof(Peca)*6);
    }

    for(i = 0; i < num_jog; i++){
      int j;
      for(j = 0; j < 6; j++){
        pecas[i][j].cor = ' ';
        pecas[i][j].forma = ' ';
      }
    }

    Peca **matriz_ = matriz;
    int *pontos = (int *) malloc(sizeof(int )*num_jog);
    int **track = (int **) malloc(sizeof(int *)*6);
    for(i = 0; i < 6; i++){
      track[i] = (int *) malloc(sizeof(int)*2);
    }
    
    for(i=0;i<num_jog;i++){
      puxar_pecas(pecas[i], usadas);
    }

    char buffer;

    scanf("%c", &buffer);
    //LOOP
  while(1){
    fim_de_jogo(usadas, nomes, num_jog, pontos);
    int flag_passar = 0;
    for(int k=0;k<num_jog;k++){
      printf("Jogador %s (Score: %d): ",nomes[k], pontos[k]);
      print_pecas(pecas[k]);
    }
    printf("===========\n");
    printf("Jogada de %s\n", nomes[turno]);
    printf("Pecas disponiveis: ");
    print_pecas(pecas[turno]);
    if(!pos){
      printf("opcoes: trocar p1 [p2 p3...] | jogar p1 x y | passar\n");
    }else{
      printf("opcoes: jogar p1 x y | passar\n");
    }
    
    printf("\nx_old: %d y_old: %d\n", x_old, y_old);

      
  char entrada[40];
  fgets(entrada, 40, stdin);
  int count_palavras = 0;
  char **palavra = get_palavras(entrada, &count_palavras);
  print_tabuleiro(matriz_, *m, *n);
  
  char e = palavra[0][0];
  
  Peca* todas_as_pecas = todas_pecas();
   
    if(e == 'j'){
      Peca peca;
      peca.forma = toupper(palavra[1][0]);
      peca.cor = palavra[1][1];

      int i;
      int flag = 0;
      for(i = 0; i < 6; i++){
        if(cheatmode == 1){
          flag = 1;
        }
        if(peca.forma == pecas[turno][i].forma &&     peca.cor == pecas[turno][i].cor){ 
            flag = 1;
            break;
        }
      }
      if(!flag){
        printf("\n****************\n");
        printf("entrada invalida 0!");
        printf("\n****************\n");
      }else{
        c_x = atoi(palavra[2]);
        c_y = atoi(palavra[3]);
        matriz_ = jogada(matriz_, m, n, peca, &c_x, &c_y, &pos, &linha, track, &(pecas[turno][i]));
        if(!cheatmode){
          //pecas[turno][i].forma = ' ';
          //pecas[turno][i].cor = ' ';
        }
      }
    }else if(e == 'p'){
      flag_passar = 1;
    }else if(e == 't'  && !pos){
      flag_passar = 1;
      int k;
      for(k = 1; k <= count_palavras; k++){
        Peca peca;
        peca.forma = toupper(palavra[k][0]);
        peca.cor = palavra[k][1];
        int i;
        for(i = 0; i < 6; i++){
          if(peca.forma == pecas[turno][i].forma &&       peca.cor == pecas[turno][i].cor){
            retornar_peca(usadas, pecas[turno][i]);
            pecas[turno][i].forma = ' ';
            pecas[turno][i].cor = ' ';
            break;
          }
        }
      }
    }else{
      printf("\n****************\n");
      printf("entrada invalida 0!");
      printf("\n****************\n");
      flag_passar = 0;
    }

    if(flag_passar==1){
      int pontos_rodada = 0;
      if(pos != 0){
          pontos_rodada = points(matriz_, track, linha, pos, *m, *n); 
      }
      pontos[turno]+= pontos_rodada;
      printf("\n***************\n");
      printf("Pontuacao na rodada: %d\n", pontos_rodada);
      printf("Pontuacao total: %d\n", pontos[turno]);
      printf("\n***************\n");
      pos = 0;
      puxar_pecas(pecas[turno], usadas);
      turno++;
      if(turno == num_jog){
      turno = 0;
      }
    }
  }
}
