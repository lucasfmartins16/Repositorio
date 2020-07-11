#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tabuleiro.h"

//Checar se uma jogada e valida
int check_move(Peca **matriz, int x, int y, int m, int n){
    int i, j;
    //Flag que indica que a forma da peca nao bate com as demais
    int flag_forma = 0;
    //Flag que indica que a cor da peca nao bate com as demais
    int flag_cor = 0;
    //Flag que indica que aquela peca ja foi jogada na mesma linha
    int flag_mesma = 0;
    //Indica se a peca pode ser jogada na linha horizontal
    int flag_h = 0;
    //Indica se a peca pode ser jogada na linha vertical
    int flag_v = 0;
    //Indica se os arredores da peca estao vazios(a peca nao esta conectada ao resto do tabuleiro)
    int vazio = 0;
    //Checa se existe alguma peca acima, abaixo ou dos lados da posicao onde pretende-se jogar
    if(y == 0 || matriz[x][y -1].forma == ' '){
      if(y == n-1 || matriz[x][y + 1].forma == ' '){
        vazio++;
      }
    }
    if(x == 0 || matriz[x-1][y].forma == ' '){
      if(x == m-1 || matriz[x+1][y].forma == ' '){
        vazio++;
      }  
    }
    if(vazio == 2 && ((m != 1) && (n != 1))){
      return 0;
    }
    /*
    Checar se as jogadas sao validas numa certa posicao. Verificam-se as pecas acima, abaixo e de ambos os lados a fim de decidir se a jogada e valida. Verifica-se se, apos jogar a peca na posicao escolhida, todas as casas compartilhariam cor ou forma iguais. Checa-se tambem se nao ha pecas iguais na linha.
    */
    //ESQUERDA
    i = 1;
    printf("x: %d y: %d", x, y);
    while(y-i >= 0 && matriz[x][y-i].forma != ' '){
        printf("aqui 1\n");
        //Caso as formas nao sejam todas iguais
        if(matriz[x][y-i].forma != matriz[x][y].forma){
            flag_forma = 1;
            break;
        }else{
            //Caso haja outra peca igual na linha
            if(matriz[x][y-i].cor == matriz[x][y].cor){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
    i = 1;
    while(y-i >= 0 && matriz[x][y-i].forma != ' '){
        //Caso as cores nao sejam todas iguais
        if(matriz[x][y-i].cor != matriz[x][y].cor){
            flag_cor = 1;
            break;
        }else{
          //Caso haja outra peca igual na linha
          if(matriz[x][y-i].forma == matriz[x][y].forma){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }

    //DIREITA
    i = 1;
    while(y+i < n  && matriz[x][y+i].forma != ' '){
        //Caso as formas nao sejam todas iguais
        if(matriz[x][y+i].forma != matriz[x][y].forma){
            flag_forma = 1;
            break;
        }else{
            //Caso haja outra peca igual na linha
            if(matriz[x][y+i].cor == matriz[x][y].cor){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
    i = 1;
    while(y+i < n  && matriz[x][y+i].forma != ' '){
        //Caso as cores nao sejam todas iguais
        if(matriz[x][y+i].cor != matriz[x][y].cor){
            flag_cor = 1;
            break;
        }else{
            //Caso haja outra peca igual na linha
            if(matriz[x][y+i].forma == matriz[x][y].forma){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
    //Se ha divergencia de cor e de forma, a flag_h e ativada, indicando que nao se pode jogar naquela linha
    if(flag_cor == 1 && flag_forma == 1){
      flag_h = 1;
    }
    flag_cor = 0;
    flag_forma = 0;

    //CIMA
    i = 1;
    while(x-i >= 0 && matriz[x-i][y].forma != ' '){
        //Caso as formas nao sejam todas iguais
        if(matriz[x-i][y].forma != matriz[x][y].forma){
            flag_forma = 1;
            break;
        }else{
          //Caso haja outra peca igual na linha
          if(matriz[x-i][y].cor == matriz[x][y].cor){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
    i = 1;
    while(x-i >= 0  && matriz[x-i][y].forma != ' '){
        //Caso as cores nao sejam todas iguais
        if(matriz[x-i][y].cor != matriz[x][y].cor){
            flag_cor = 1;
            break;
        }else{
          //Caso haja outra peca igual na linha
          if(matriz[x-i][y].forma == matriz[x][y].forma){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
  
    //BAIXO
    i = 1;
    while(x+i < m && matriz[x+i][y].forma != ' '){
        //Caso as cores nao sejam todas iguais
        if(matriz[x+i][y].forma != matriz[x][y].forma){
            flag_forma = 1;
            break;
        }else{                    
          //Caso haja outra peca igual na linha
          if(matriz[x+i][y].cor == matriz[x][y].cor){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
    i = 1;
    while(x+i < m && matriz[x+i][y].forma != ' '){
        //Caso as cores nao sejam todas iguais
        if(matriz[x+i][y].cor != matriz[x][y].cor){
            flag_cor = 1;
            break;
        }else{
          //Caso haja outra peca igual na linha
          if(matriz[x+i][y].forma == matriz[x][y].forma){
              flag_mesma = 1;
              break;
            }
        }
        i++;
    }
    //Se ha divergencia de cor e de forma, a flag_h e ativada, indicando que nao se pode jogar naquela linha
    if(flag_cor == 1 && flag_forma == 1){
      flag_v = 1;
    }
    //Se nao houver problema na linha ou coluna ou pecas iguais, a jogada e valida e retorna-se 1. Caso contrario, retorna-se 0.
    if(flag_h == 0 && flag_v == 0 && flag_mesma == 0){
      return 1;
    }else{
      return 0;
    }
}
//Funcao para avaliar a pontuacao feita em uma jogada.
int points(Peca **matriz, int **track, int linha, int pos, int m, int n){
    //Apos jogar, pos e incrementada. Queremos a jogada antes, entao pos deve ter 1 subtraido.
    pos--;
    //Coordenadas da ultima jogada
    int c_x = track[pos][0];
    int c_y = track[pos][1];

    int i = 0;
    //Pontuacao na linha em que se esta jogando (quantas casas ha na linha em que se escolheu jogar)
    int pontuacao = 0;
    //Pontuacao por casas que completam linhas adjacentes a linha principal em que se joga.
    int pontuacao_ = 0;
    //Se foi jogado apenas uma vez, conta-se as pecas das linhas e colunas ao redor da posicao.
    if(!pos){
        int flag = 0;
        while(matriz[c_x][c_y+i+1].forma != ' '){
            if(i == 0){
              pontuacao++;
              flag++;
            }
            i++;
        }
        pontuacao += i;
        i = 0;
        while(matriz[c_x][c_y-i-1].forma != ' '){
            if(i == 0){
              pontuacao++;
              flag++;
            }
            i++;
        }
        pontuacao += i;
        //Caso ocorra Qwirkle: 6 casas em seguida.
        if(pontuacao == 6){
          pontuacao += 6;
        }
        i = 0;
        while(matriz[c_x+i+1][c_y].forma != ' '){
            if(i == 0){
              pontuacao++;
              flag++;
            }
            i++;
        }
        pontuacao += i;
        i = 0;
        while(matriz[c_x-i-1][c_y].forma != ' '){
            if(i == 0){
              pontuacao++;
              flag++;

            }
            i++;
        }
        pontuacao += i;
        //Caso ocorra Qwirkle: 6 casas em seguida.
        if(pontuacao == 6){
          pontuacao += 6;
        }
        if(!flag){
          return 1;
        }else{
          return pontuacao;
        }
    }
    /*
    Se linha == 1, quer dizer que se esta jogando em uma linha. Entao, contam-se as casas na linha da ultima casa jogada. Se linha == 0, esta-se jogando em uma coluna, entao contam-se as casas na coluna da ultima casa jogada.
    */
    if(linha){
        pontuacao = 1;
        while(matriz[c_x][c_y+i+1].forma != ' '){
            i++;
        }
        pontuacao += i;
        i = 0;
        while(matriz[c_x][c_y-i-1].forma != ' '){
            i++;
        }
        pontuacao += i;
        //Caso ocorra Qwirkle: 6 casas em seguida.
        if(pontuacao == 6){
          pontuacao += 6;
        }
        
        for(i = 0; i <= pos; i++){
          c_x = track[i][0];
          c_y = track[i][1];
          int j = 0;
          while(matriz[c_x+j+1][c_y].forma != ' ' && c_x +j+1 < m){
            if(j == 0){
               pontuacao_++;
            }
            j++;
          }
        pontuacao_ += j;
        j = 0;
        while(matriz[c_x-j-1][c_y].forma != ' ' && c_x -j-1 >= 0){
            if(j == 0){
               pontuacao_++;
            }
            j++;
        }
        pontuacao_ += j;
        //Caso ocorra Qwirkle: 6 casas em seguida.
        if(pontuacao_ == 6){
          pontuacao_ += 6;
        }
        pontuacao += pontuacao_;
        pontuacao_ = 0;
        }
        
    }else{
        pontuacao = 1;
        while(matriz[c_x+i+1][c_y].forma != ' '){
            i++;
        }
        pontuacao += i;
        i = 0;
        while(matriz[c_x-i-1][c_y].forma != ' '){
            i++;
        }
        pontuacao += i;
        //Caso ocorra Qwirkle: 6 casas em seguida.
        if(pontuacao == 6){
          pontuacao += 6;
        }
        
        for(i = 0; i <= pos; i++){
          c_x = track[i][0];
          c_y = track[i][1];
          int j = 0;
          while(matriz[c_x][c_y+j+1].forma != ' ' && c_y +j+1 < n){
            if(j == 0){
               pontuacao_++;
            }
            j++;
          }
        pontuacao_ += j;
        j = 0;
        while(matriz[c_x][c_y-j-1].forma != ' ' && c_y -j-1 >= 0){
            if(j == 0){
               pontuacao_++;
            }
            j++;
        }
        pontuacao_ += j;
        //Caso ocorra Qwirkle: 6 casas em seguida.
        if(pontuacao_ == 6){
          pontuacao_ += 6;
        }
        pontuacao += pontuacao_;
        pontuacao_ = 0;
      }
    }
    return pontuacao;
}
/*
Descobrir se a nova peca jogada mantem-se na linha ou coluna em que o usuario estava jogando naquela rodada 
*/
int ver(Peca **matriz, int c_x, int c_y, int **track, int *pos, int linha){
    //Coordenadas da ultima jogada
    int x_old = track[*pos-1][0];
    int y_old = track[*pos-1][1];
    int i;
    //Se o usuario estiver jogando em uma linha
    if(linha == 0){
        /*Se as coordenadas y entre a ultima jogada e essa sao diferentes o usuario nao esta jogando na mesma linha
        */
        if(y_old != c_y){
          return 0;
        }
        //Variaveis auxiliares
        int a  = c_x;
        int b = x_old;
        /*
        Descobrir se entre a ultima peca jogada e a anteriores ha algum espaco vazio, o que invalidaria a jogada.
        */
        if(x_old > c_x){
            a = x_old;
            b = c_x;
        }
        i = 1;
        while(b + i < a){
          if(matriz[b+i][y_old].forma == ' '){
            return 0;
          }
          i++;
        }
    }else{
        /*Analogo ao codigo anterior, mas agora supondo que o usuario joga em uma mesma coluna.
        */
        if(x_old != c_x){
          return 0;
        }
       int a = c_y;
        int b = y_old;
        if(y_old > c_y){
            a = y_old;
            b = c_y;
        }
        i = 1;
        while(b + i < a){
          if(matriz[x_old][b+i].forma == ' '){
            return 0;
          }
          i++;
        }
    }
    return 1;
}
//Funcao que indentifica quando todas as pecas foram jogadas e declara fim de jogo.
void fim_de_jogo(int *usadas, char **nomes, int num_jog, int *pontos){
  int i;
  int flag = 0;
  //Ver se todas as pecas ja foram jogadas.
  for(i = 0; i < 108; i++){
    if(usadas[i] == 0){
      flag = 1;
    }
  }
  if(!flag){
    printf("FIM DO JOGO!");

    for(i = 0; i < num_jog; i++){
      printf("\n***************\n");
      printf("\nNome: %s\n", nomes[i]);
      printf("Pontuacao total: %d\n", pontos[i]);
      printf("\n***************\n");
    }

  }
}