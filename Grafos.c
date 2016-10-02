
#include<stdio.h>
#include<string.h>

int numCidades = 0;  // conta o numero de cidades cadastradas

typedef struct grafos{
      int id;  // identificador das cidades
      char cidade[30];  // nome da cidade
      int distancia[3];  // distancia de suas rotas
      int acesso[3];  // 1 asfalto, 0 estrada de chao
      struct grafos *incide[3];  // rotas da cidade
      struct grafos *prox;
}Grafos;

void imprimir(Grafos *g){  // lista todas as cidades em ordem crescente pelo teu id
     Grafos *p;
     for(p = g; p != NULL; p = p->prox)
           printf("\n %d\t%s", p->id, p->cidade);
}

void melhorRota(Grafos *g){
     system("cls");
     printf("\n > MELHOR ROTA \n\n");
     imprimir(g);
     printf("\n\n\n Qual cidade de origem (numero): ");
     int origem, destino, i, j, w;
     do{ scanf("%d", &origem); }while(origem < 0 || origem > numCidades);
     printf("\n Qual cidade de destino (numero): ");
     do{ scanf("%d", &destino); }while(destino < 0 || destino > numCidades);
     Grafos *o = g, *d = g, *p, *k;
     while(o->id != origem)  // encontra oritem
          o = o->prox;  
     while(d->id != destino)  // encontra destino
          d = d->prox;
     int rotas[numCidades], antDestino[numCidades], penDestino[numCidades], fila[numCidades];
     rotas[0] = 0; antDestino[0] = 0; penDestino[0] = 0; fila[0] = 0;  // primeira posicao dos vetores guardam quantos elementos tem no vetor
     for(p=g; p != NULL; p = p->prox){
          for(i=0; i<3; i++){  //  encontra cidades que chegam no destino
               if(p->incide[i] == d){
                    antDestino[0]++;  // antDestino aponta para as cidades que antecedem o destino
                    antDestino[antDestino[0]] = p->id;  
                    for(k=g; k != NULL; k = k->prox){  // encontra as cidades que chegam na penultima cidade do destino
                         for(j=0; j<3; j++){
                              if(k->incide[j] != NULL){
                                   if(k->incide[j]->id == antDestino[antDestino[0]] && k->incide[j] != o){
                                       penDestino[0]++;  // penDestino aponta para as cidades que chegam no antecessor do destino
                                       penDestino[penDestino[0]] = k->id;  // salva as cidades no vetor                     
                                  }
                              }
                         }         
                    }
               }         
          }        
     }
     if(antDestino[0] == 0 || penDestino[0] == 0) 
         printf("\n\n\n Nao possui rotas para este Destino.");
     else{  // possui mais rotas
           if(o->incide[0] == d || o->incide[1] == d || o->incide[2] == d)  // se origem e destino for vizinhos
                printf("\n\n\n Melhor Rota: %s -> %s", o->cidade, d->cidade);
           else{  // se estiver outras cidades e entre eles
                while(o != d){  // ate que origem encontre o destino
                     rotas[0]++;  // guarda quantos todas possui
                     rotas[rotas[0]] = o->id;  // adiciona o destino atual no caminho das rotas  
                     if(o->incide[1] == NULL) // se a origem tiver apenas uma rota, segue    
                         o = o->incide[0];
                     else{  // tem mais de um caminho pra seguir
                         int aux = 0;
                         fila[0] = 0;  
                         for(i=0; i<3; i++){  // adiciona os caminhos numa fila
                             if(o->incide[i] != NULL){
                                 fila[0]++;
                                 fila[fila[0]] = o->incide[i]->id;              
                             }
                             if(o->incide[i] == d){  // se uma das rotas for o destino
                                 aux++;  // auxiliar++ nao deixa navegar entre outras rotas
                                 o = o->incide[i];  // atua origem recebe o destino
                             }         
                         }
                         for(i=0; i<fila[0] && aux == 0; i++){  // ate que percorra todos os elemento da fila ou encontre um antecessor ao destino
                             p = g;
                             while(p->id != fila[i+1])  // encontra o elemento da fila
                                 p = p->prox;
                             for(j=0; j<3 && aux == 0; j++){  // percorre rotas da fila e verifica se ele n aponta para o antecessor do destino
                                 if(p->incide[j] != NULL){
                                      for(w=0; w<antDestino[0]; w++){
                                          if(p->incide[j]->id == antDestino[w+1] || p->incide[j] == d){
                                              antDestino[w+1] = -1;
                                              aux = 1;
                                              o = p;
                                          }
                                      }
                                 }
                             }
                         }
                         if(aux == 0){
                             for(i=0; i<fila[0] && aux == 0; i++){
                                 p = g;
                                 while(p->id != fila[i+1])  // encontra o elemento da fila
                                     p = p->prox;
                                 for(j=0; j<3 && aux == 0; j++){  // percorre rotas da fila e verifica se ele n aponta para penultimo antecessor do destino
                                     if(p->incide[j] != NULL){
                                         for(w=0; w<penDestino[0]; w++){
                                             if(p->incide[j]->id == penDestino[w+1]){
                                                 penDestino[w+1] = -1;
                                                 aux = 1;
                                                 o = p;
                                             }
                                         }
                                     }
                                 }     
                             } // for
                         }  // if
                     } // else
                } // while
                printf("\n\n\n Melhor rota: \n\n");
                for(i=0; i<rotas[0]; i++){
                    p = g;
                    while(p->id != rotas[i+1])
                        p = p->prox;
                    printf(" %s ->", p->cidade);
                }
                printf(" %s", d->cidade);
           }
     }
     printf("\n\n\n");
     system("pause"); 
}
 
int contaVizinhos(Grafos *atual, Grafos *g){  // conta os vizinhos de uma cidade
       Grafos *p;
       int i;
       for(p=g; p != NULL; p = p->prox){
            for(i=0; i<3; i++){
                 if(p->incide[i] == atual)
                     return 1;         
            }          
       }
       return 0;
}

Grafos *removerCidades(Grafos *g){
     system("cls");
     printf("\n > REMOVER CIDADE \n\n");
     imprimir(g);
     printf("\n\n\n Qual cidade remover (numero): ");
     int c;
     do{ scanf("%d", &c); }while(c < 0 || c > numCidades);
     Grafos *p = g, *v;
     while(p->id != c)
          p = p->prox;  // encotra a cidade a ser excluida
     int vz, i, j;
     printf("\n\n");
     if(p->incide[0] == NULL){  // nao tem rotas
          vz = contaVizinhos(p, g);  // verificas se tem vizinhos
          if(vz == 1){  // possui vizinhos
               for(v=g; v != NULL; v = v->prox){   // procura ele
                    for(i=0; i<3; i++){
                         if(v->incide[i] == p){  // encontro vizinho
                              v->incide[i] = NULL;
                              v->distancia[i] = -1;  // apaga caminhos
                              v->acesso[i] = -1; 
                         }         
                    }     
               }
          }
     }
     else{  // tem rotas
         vz = vizinhos(p, g);  // mostra as rotas
         vz = contaVizinhos(p, g);  // verifica se tem vizinhos
         printf("\n\n Novas Rotas \n\n");
         if(vz == 1){  // possui vizinhos
              int contaRotas = 0;
              for(i=0; i<3; i++){  // conta quantas rotas ele possui
                  if(p->incide[i] != NULL)
                      contaRotas++;         
              }
              for(v=g; v != NULL; v = v->prox){  // ate que as rotas estejam somadas ou vizinhos nao tenham mais espaço pra rotas
                   for(i=0; i<3; i++){
                        if(v->incide[i] == p){  // encontro o vizinho
                            if(contaRotas > 0){  // se ainda tiver rotas para somar...
                                if(v->incide[i] != p->incide[contaRotas-1]){  // se as rotas nao se apontam
                                    int aux = v->distancia[i]; 
                                    v->distancia[i] = aux + p->distancia[contaRotas-1];  // soma rotas
                                    v->incide[i] = p->incide[contaRotas-1];  // reaponta para prox
                                    p->incide[contaRotas-1] = NULL;
                                    printf(" %d\t %d Km \t  %s -> %s \n", v->id, v->distancia[i], v->cidade, v->incide[i]->cidade);
                                    contaRotas--;  
                                    if(contaRotas > 0 && v->incide[2] == NULL){  // se possui mais rotas e ainda estiver espaço no vizinho
                                         if(v->incide[1] == NULL && v->incide[1] != p->incide[contaRotas-1]){
                                              v->distancia[1] = aux + p->distancia[contaRotas-1];  // soma rotas
                                              v->incide[1] = p->incide[contaRotas-1];  // reaponta para prox
                                              p->incide[contaRotas-1] = NULL;
                                              printf(" %d\t %d Km \t  %s -> %s \n", v->id, v->distancia[1], v->cidade, v->incide[1]->cidade);          
                                              contaRotas--;           
                                         }
                                         if(contaRotas > 0 && v->incide[2] == NULL && v->incide[2] != p->incide[contaRotas-1]){  
                                              v->distancia[2] = aux + p->distancia[contaRotas-1];  // soma rotas
                                              v->incide[2] = p->incide[contaRotas-1];  // reaponta para prox
                                              p->incide[contaRotas-1] = NULL;
                                              printf(" %d\t %d Km \t  %s -> %s \n", v->id, v->distancia[2], v->cidade, v->incide[2]->cidade);
                                              contaRotas--;              
                                         }
           
                                    }
                                }
                            }
                            else{  // se ja somo todas as rotas
                                v->incide[i] = NULL;
                                v->distancia[i] = -1;     
                                v->acesso[i] = -1;
                            }    
                        }
                   }
              } 
         } 
     }  // remove a cidade da lista
     if(p == g){  // se a cidade a ser removida é a primeira
          g = p->prox;
          free(p);
          for(p=g; p != NULL; p = p->prox)
               p->id--;     
     }
     else if(p->prox == NULL){  // se ele é o ultimo
          Grafos *ant = g;
          while(ant->prox != p)  // acha o anterior a cidade a ser excluida
               ant = ant->prox;
          ant->prox = NULL;
          free(p);
     }
     else{  // se esta no meio
          Grafos *ant = g;
          while(ant->prox != p)  // acha o anterior a cidade a ser excluida
               ant = ant->prox;
          ant->prox = p->prox;
          ant = p;
          p = p->prox;
          free(ant);
          while(p != NULL){
              p->id--;
              p = p->prox;
          }
     }
     numCidades--;
     printf("\n\n");
     system("pause");
     return g;
}      

void cadastrarCidade(Grafos *g){ 
     system("cls");
     printf("\n > CADASTRAR CIDADE \n\n");
     Grafos *novo = (Grafos*) malloc(sizeof(Grafos));  // cria a nova cidade
     numCidades++;  // adiciona a cidade
     novo->id = numCidades;
     printf("\n Nome da Cidade: ");
     fflush(stdin);
     gets(novo->cidade);
     printf("\n\n Quantas Rotas (minimo 0, maximo 3): ");
     int x, i, y;
     do{ scanf("%d", &x); }while(x < 0 || x > 3);
     printf("\n");
     imprimir(g);
     Grafos *p = g;
     for(i=0; i<3; i++){  // maximo de 3 rotas
          if(i<x){  // seguir para uma cidade
               printf("\n\n Para qual cidade seguir (numero): ");
               do{ scanf("%d", &y); }while(y < 0 || y > numCidades || y == novo->id);
               while(p->id != y)
                   p = p->prox;
               novo->incide[i] = p;
               printf("\n Distancia: ");
               scanf("%d", &novo->distancia[i]);
               printf("\n Estrada (Asfalto = 1 / E. Chao = 0): ");
               scanf("%d", &novo->acesso[i]);
          }else{  // caminho nulo
               novo->incide[i] = NULL;
               novo->distancia[i] = -1;
               novo->acesso[i] = -1;
          }
     }  
     novo->prox = NULL;  // adiciona a nova cidade criada no fim da fila de cidades
     p = g;
     while(p->prox != NULL)
         p = p->prox;
     p->prox = novo;
     printf("\n\n");
     system("pause");
}

void listarVizinhos(Grafos *g){  // mostra os vizinhos de uma cidade selecionada pelo usuario
     system("cls");
     printf("\n > LISTAR VIZINHOS \n\n");
     imprimir(g);
     printf("\n\n 0\tCADASTRAR CIDADE");
     printf("\n\n\n Qual cidade visualizar (numero): ");
     int c;
     do{ scanf("%d", &c); }while(c < 0 || c > numCidades);
     if(c == 0)
          cadastrarCidade(g);
     else{
          Grafos *p = g;
          while(p->id != c)
               p = p->prox;
          printf("\n\n");    
          int ret = vizinhos(p, g);
          printf("\n\n");
          system("pause");
     }
}

int vizinhos(Grafos *p, Grafos *g){  // lista todas as rotas de uma cidade e os vizinhos
     int vizinho = 0, aux, i;
     char estrada[10];
     printf(" Id \t Km \t Acesso     Cidade \n\n");
     for(i=0; i<3; i++){  // lista as rotas da cidade
           if(p->incide[i] != NULL){
                 vizinho++;
                 if(p->acesso[i] == 0)
                      strcpy(estrada, "E. Chao");
                 else
                      strcpy(estrada, "Asfalto");
                 printf(" %d\t %d Km \t %s    %s -> %s \n", p->incide[i]->id, p->distancia[i], estrada, p->cidade, p->incide[i]->cidade);
           }         
     }
     Grafos *x;
     for(x=g; x != NULL; x = x->prox){
           for(aux = 0; aux < 3; aux++){  // e os vizinhos
                if(x->incide[aux] == p){
                    vizinho++;
                    if(x->acesso[aux] == 0)
                         strcpy(estrada, "E. Chao");
                    else
                         strcpy(estrada, "Asfalto");
                    printf(" %d\t %d Km \t %s    %s -> %s \n", x->id, x->distancia[aux], estrada, x->cidade, p->cidade);
                }
           }
     }
     if(vizinho == 0){
            printf(" Nao possui vizinhos!");
            return 0;
     }
     return 1;    
}

void alterarCidades(Grafos *g){ 
     system("cls");
     printf("\n > ALTERAR DADOS \n\n");
     imprimir(g);
     printf("\n\n\n Qual cidade alterar (numero): ");
     int c, op;
     do{ scanf("%d", &c); }while(c < 0 || c > numCidades);  // nao permite selecionar cidades que nao estejam dentro da faixa
     do{
        Grafos *p = g;
        while(p->id != c)  // encontra a cidade na lista
              p = p->prox; 
        system("cls");  // menu
        printf("\n > ALTERAR DADOS \n\n");
        printf("\n Cidade: %s", p->cidade);  // mostra a cidade escolhida
        printf("\n\n\n Qual campo alterar: ");
        printf("\n\n 1. Nome");
        printf("\n 2. Distancia entre Vizinhos");
        printf("\n 3. Estrada entre Vizinhos");
        printf("\n 4. Alterar Rota");
        printf("\n 5. Excluir Rota");
        printf("\n 6. Adicionar Rota");
        printf("\n\n 0. Voltar ao Inicio");
        printf("\n\n\n Opcao: ");
        scanf("%d", &op);
        printf("\n\n");
        int i;
        if(op == 1){  //  alterar o nome de uma cidade
              printf(" Novo Nome: ");
              fflush(stdin);
              gets(p->cidade);  // nome digitado passa a ser o novo nome
        }
        else if(op == 2){
              system("cls");
              printf("\n > ALTERAR DADOS/DISTANCIA ENTRE VIZINHOS \n\n");
              printf("\n Cidade: %s", p->cidade);
              printf("\n\n\n Vizinhos: \n\n\n");
              int ret;  // verifica se tem vizinhos
              if(ret = vizinhos(p, g) == 1){  // se tiver 
                   printf("\n\n\n Qual vizinho alterar (Id): ");
                   scanf("%d", &op);
                   Grafos *x; 
                   for(x=g; x->id != op && x != NULL; x = x->prox){}  // encontra na lista
                   int n;
                   printf("\n\n\n Nova Distancia: ");
                   scanf("%d", &n);  // inserir a nova distancia
                   for(i=0; i<3; i++){
                        if(x->incide[i] == p)  // encontra o vizinho, se ele for rota para o elemento a ser alterado
                           x->distancia[i] = n;
                        if(p->incide[i] == x)  // ou se o elemento a ser alterado ter rotas para o vizinhos
                           p->distancia[i] = n;     
                   }
              }
              printf("\n\n");
              system("pause");
        }
        else if(op == 3){
              system("cls");
              printf("\n > ALTERAR DADOS/ESTRADA ENTRE VIZINHOS \n\n");
              printf("\n Cidade: %s", p->cidade);
              printf("\n\n\n Vizinhos: \n\n\n");
              int ret;
              if(ret = vizinhos(p, g) == 1){
                   printf("\n\n\n Qual vizinho alterar (Id): ");
                   scanf("%d", &op);
                   Grafos *x;
                   for(x=g; x->id != op && x != NULL; x = x->prox){}  // encotna o vizinho a alterar
                   for(i=0; i<3; i++){  // altera o valor de 1 pra 0 ou de 0 pra 1
                        if(x->incide[i] == p){
                            if(x->acesso[i] == 1)
                               x->acesso[i] = 0;
                            else
                               x->acesso[i] = 1;           
                        }
                        else if(p->incide[i] == x){
                            if(p->acesso[i] == 1)
                               p->acesso[i] = 0;
                            else
                               p->acesso[i] = 1;           
                        }                  
                   }
              }
              printf("\n\n");
              system("pause");     
        }
        else if(op == 4){
              system("cls");
              printf("\n > ALTERAR DADOS/ALTERAR ROTAS \n\n");
              printf("\n Cidade: %s", p->cidade);
              printf("\n\n\n Rotas: \n\n\n");
              printf(" Id \t Km \t Acesso     Cidade \n\n");
              int vizinho = 0;
              char estrada[10];
              for(i=0; i<3; i++){  // mostra todas a rotas da cidade selecionada 
                    if(p->incide[i] != NULL){
                        vizinho++;
                        if(p->acesso[i] == 0)
                             strcpy(estrada, "E. Chao");
                        else 
                             strcpy(estrada, "Asfalto");
                        printf(" %d\t %d Km \t %s    %s -> %s \n", p->incide[i]->id, p->distancia[i], estrada, p->cidade, p->incide[i]->cidade);                
                    }         
              }
              if(vizinho > 0){  // se tiver vizinhos
                   printf("\n\n Qual Rota alterar (Id): ");
                   scanf("%d", &op);
                   imprimir(g);
                   int q;
                   printf("\n\n Para qual cidade seguir: ");
                   do scanf("%d", &q); while(q < 0 || q > numCidades || q == p->id);
                   Grafos *x;
                   for(x=g; x->id != q && x != NULL; x = x->prox){}
                   for(i=0; i<3; i++){  // encontra o elemento e altera a rota
                       if(p->incide[i] != NULL){
                            if(p->incide[i]->id == op){
                                p->incide[i] = x;
                                printf("\n Distancia: ");
                                scanf("%d", &p->distancia[i]);
                                printf("\n Estrada (Asfalto = 1 / E. Chao = 0): ");
                                scanf("%d", &p->acesso[i]);
                            }
                       }        
                   }
              }else
                   printf("\n Nao possui Rotas");
              printf("\n\n");
              system("pause");    
        }
        else if(op == 5){
              system("cls");
              printf("\n > ALTERAR DADOS/EXCLUIR ROTAS \n\n");
              printf("\n Cidade: %s", p->cidade);
              printf("\n\n\n Rotas: \n\n\n");
              printf(" Id \t Km \t Acesso     Cidade \n\n");
              int vizinho = 0;
              char estrada[10];
              for(i=0; i<3; i++){  // mostra todas a rotas da cidade selecionada 
                    if(p->incide[i] != NULL){
                        vizinho++;
                        if(p->acesso[i] == 0)
                             strcpy(estrada, "E. Chao");
                        else 
                             strcpy(estrada, "Asfalto");
                        printf(" %d\t %d Km \t %s    %s -> %s \n", p->incide[i]->id, p->distancia[i], estrada, p->cidade, p->incide[i]->cidade);                
                    }         
              }
              if(vizinho > 0){
                   printf("\n\n Qual Rota excluir (Id): ");
                   scanf("%d", &op);
                   Grafos *x;
                   for(x=g; x->id != op && x != NULL; x = x->prox){}
                   for(i=0; i<3; i++){
                       if(p->incide[i] != NULL){
                           if(p->incide[i]->id == op){
                               p->incide[i] = NULL;
                               p->distancia[i] = -1;
                               p->acesso[i] = -1;
                           }
                       }    
                   }
              }else
                   printf("\n Nao possui Rotas");
              printf("\n\n");
              system("pause");         
        }
        else if(op == 6){
              system("cls");
              printf("\n > ALTERAR DADOS/ADICIONAR ROTAS \n\n");
              printf("\n Cidade: %s", p->cidade);
              printf("\n\n\n Rotas: \n\n\n");
              printf(" Id \t Km \t Acesso     Cidade \n\n");
              int vizinho = 0;
              char estrada[10];
              for(i=0; i<3; i++){  // mostra todas a rotas da cidade selecionada 
                    if(p->incide[i] != NULL){
                        vizinho++;
                        if(p->acesso[i] == 0)
                             strcpy(estrada, "E. Chao");
                        else 
                             strcpy(estrada, "Asfalto");
                        printf(" %d\t %d Km \t %s    %s -> %s \n", p->incide[i]->id, p->distancia[i], estrada, p->cidade, p->incide[i]->cidade);                
                    }         
              }
              if(vizinho < 3){  // permite novas rotas
                    printf("\n");
                    imprimir(g);
                    printf("\n\n Para qual cidade seguir (numero): ");
                    int x;
                    do{ scanf("%d", &x); }while(x < 0 || x > numCidades || x == p->id);
                    Grafos *q = g;
                    while(q->id != x)
                         q = q->prox;
                    p->incide[vizinho] = q;
                    printf("\n Distancia: ");
                    scanf("%d", &p->distancia[vizinho]);
                    printf("\n Estrada (Asfalto = 1 / E. Chao = 0): ");
                    scanf("%d", &p->acesso[vizinho]);
              }
              else
                  printf("\n\n A cidade escolhida ja possui 3 Rotas.");
              printf("\n\n");
              system("pause");     
        }
     }while(op != 0);
}

void percorrerAmplitude(Grafos *g){  // percore o grafo por amplitude
     system("cls");
     printf("\n > PERCURSO POR AMPLITUDE \n\n");
     int visitado[numCidades], fila[numCidades], i, fim = 0, aux2, numVisitas = 1;
     for(i=0; i<numCidades; i++){  // inicializa o vetor que contem as cidades que ja foram visitadas
          visitado[i] = 0;  // de acordo com o numero de cidades cadastradas
     }
     Grafos *p = g, *aux;
     printf("\n %d\t%s", p->id, p->cidade);  // mostra o cabeca
     visitado[0] = 1;  // e marca como visitado
     while(visitado[numCidades-1] == 0 || numVisitas != numCidades){  // ate que o ultimo elemento da lista ainda nao esteja visitado
          for(i=0; i<3; i++){  // adiciona as rotas da cidade a ser percorrida em uma fila
                if(p->incide[i] != NULL && visitado[p->incide[i]->id-1] != 1){  // se exister rota e esta rota ainda nao estiver visitada
                     numVisitas++;  // conta como visitada
                     printf("\n %d\t%s", p->incide[i]->id, p->incide[i]->cidade);  // mostra a cidade
                     visitado[p->incide[i]->id-1] = 1;
                     fila[fim] = p->incide[i]->id;  // adiciona na fila para visitas suas rotas
                     fim++;
                }      
          }
          aux2 = 0;
          aux = g;
          while(fila[aux2] == -1 && aux2 < fim)  // percorre a fila das cidades a serem visitas
               aux2++;
          if(aux2 == fim){  // se nao tiver nenhuma cidade na fila
               aux2 = -1;
               for(i=0; i<numCidades && aux2 == -1; i++){  // encontra uma cidade ainda nao visitada na lista dos visitados
                   if(visitado[i] == 0)  
                        aux2 = i+1;
               }
               while(aux->id != aux2)  // encontra ela na lista
                   aux = aux->prox;
               numVisitas++;  // visita esta cidade
               printf("\n %d\t%s", aux->id, aux->cidade); // cai aqui possivelmente cidades que nao tenham nenhuma rota ou nao possui vizinhos
               visitado[aux2-1] = 1;  // marca como visitada
          }else{   // encontro o proximo elemento da fila
               while(aux->id != fila[aux2])  // encontra ele na lista
                   aux = aux->prox;
               p = aux;  // ele passa a ser o proximo caminho
               fila[aux2] = -1;  // retira ele da fila
          }
     }
     printf("\n\n\n");
     system("pause");
}

Grafos *iniciarMapa(Grafos *g){
       numCidades++;
       switch(numCidades){
            case 1: {
                 Grafos *a = (Grafos*) malloc(sizeof(Grafos));
                 a->id = 1;
                 strcpy(a->cidade, "Santa Maria");
                 Grafos *b = (Grafos*) malloc(sizeof(Grafos));  
                 Grafos *c = (Grafos*) malloc(sizeof(Grafos));     
                 a->incide[0] = b; a->distancia[0] = 50; a->acesso[0] = 1;  // <1,2>
                 a->incide[1] = c; a->distancia[1] = 13; a->acesso[1] = 1;  // <1,8>
                 a->incide[2] = NULL; a->distancia[2] = -1; a->acesso[2] = -1;
                 a->prox = b;
                 b->id = 2;
                 c->id = 8;
                 b->prox = c;
                 c->prox = NULL;
                 return a;
                 break;
           }case 2: {
                 Grafos *b = (Grafos*) malloc(sizeof(Grafos));
                 Grafos *c = (Grafos*) malloc(sizeof(Grafos)); 
                 strcpy(g->incide[0]->cidade, "Restinga Seca");
                 g->incide[0]->incide[0] = b; g->incide[0]->distancia[0] = 30; g->incide[0]->acesso[0] = 1;  // <2,3>
                 g->incide[0]->incide[1] = c; g->incide[0]->distancia[1] = 40; g->incide[0]->acesso[1] = 0;  // <2,7>
                 g->incide[0]->incide[2] = NULL; g->incide[0]->distancia[2] = -1; g->incide[0]->acesso[2] = -1;
                 b->id = 3;
                 c->id = 7;
                 c->prox = g->incide[0]->prox;
                 g->incide[0]->prox = b;
                 b->prox = c;
                 break;
           }case 3: {
                 strcpy(g->incide[1]->cidade, "Agudo");
                 Grafos *a = (Grafos*) malloc(sizeof(Grafos));
                 Grafos *p = g->incide[0]->incide[0];
                 strcpy(p->cidade, "Agudo");
                 p->incide[0] = a; p->distancia[0] = 12; p->acesso[0] = 1; // <3,4>
                 p->incide[1] = NULL; p->distancia[1] = -1; p->acesso[1] = -1;
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 a->prox = p->prox;
                 p->prox = a;
                 a->id = 4;
                 break;
           }case 4: {
                 Grafos *p = g;
                 while(p->id != 4)
                     p = p->prox;
                 strcpy(p->cidade, "Dona Francisca");
                 Grafos *b = (Grafos*) malloc(sizeof(Grafos));   
                 p->incide[0] = g->incide[0]->incide[0]; p->distancia[0] = 12; p->acesso[0] = 1; // <4,3>
                 p->incide[1] = b; p->distancia[1] = 20; p->acesso[1] = 0; // <4,5>
                 p->incide[2] = p->prox; p->distancia[2] = 15; p->acesso[2] = 1; // <4,7>
                 b->id = 5;
                 b->prox = p->prox;
                 p->prox = b;
                 break;
           }case 5: {
                 Grafos *p = g;
                 while(p->id != 5)
                     p = p->prox;
                 Grafos *a = (Grafos*) malloc(sizeof(Grafos));
                 strcpy(p->cidade, "Pinhal Grande");    
                 p->incide[0] = a; p->distancia[0] = 35; p->acesso[0] = 1; // <5,6>
                 p->incide[1] = NULL; p->distancia[1] = -1; p->acesso[1] = -1;
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 a->id = 6;
                 a->prox = p->prox;
                 p->prox = a;
                 break;
           }case 6: {
                 Grafos *p = g, *aux;
                 while(p->id != 6)
                     p = p->prox;
                 strcpy(p->cidade, "Nova Palma");
                 aux = g->incide[0]->incide[0];
                 p->incide[0] = aux->incide[0]; p->distancia[0] = 10; p->acesso[0] = 1; // <6,4>
                 p->incide[1] = NULL; p->distancia[1] = -1; p->acesso[1] = -1;
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 break;   
           }case 7: {
                 Grafos *a = (Grafos*) malloc(sizeof(Grafos));
                 Grafos *p = g;
                 while(p->id != 7)
                     p = p->prox;
                 strcpy(p->cidade, "Polesine");
                 p->incide[0] = p->prox; p->distancia[0] = 7; p->acesso[0] = 0; // <7,8>
                 p->incide[1] = a; p->distancia[1] = 5; p->acesso[1] = 1; // <7,10>
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 a->id = 10;
                 p->incide[0]->prox = a;
                 a->prox = NULL;
                 break;     
           }case 8: {
                 Grafos *a = (Grafos*) malloc(sizeof(Grafos));
                 Grafos *p = g;
                 while(p->id != 8)
                     p = p->prox;
                 strcpy(p->cidade, "Silveira Martins");
                 p->incide[0] = a; p->distancia[0] = 21; p->acesso[0] = 1; // <8,9>
                 p->incide[1] = NULL; p->distancia[1] = -1; p->acesso[1] = -1;
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 a->prox = p->prox;
                 p->prox = a;
                 a->id = 9;
                 break;
           }case 9: {
                 Grafos *p = g;
                 while(p->id != 9)
                     p = p->prox; 
                 strcpy(p->cidade, "Ivora");
                 p->incide[0] = p->prox; p->distancia[0] = 19; p->acesso[0] = 1; // <9,10>
                 p->incide[1] = NULL; p->distancia[1] = -1; p->acesso[1] = -1;
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 break;
           }case 10: {
                 Grafos *p = g, *aux = g;
                 while(p->id != 10)
                     p = p->prox;
                 while(aux->id != 6)
                     aux = aux->prox;
                 strcpy(p->cidade, "Faxinal");
                 p->incide[0] = aux;  p->distancia[0] = 14; p->acesso[0] = 1; // <10,6>
                 p->incide[1] = NULL; p->distancia[1] = -1; p->acesso[1] = -1;
                 p->incide[2] = NULL; p->distancia[2] = -1; p->acesso[2] = -1;
                 break;    
           }case 11: {
                 Grafos *p = g;
                 while(p->prox != NULL)
                     p = p->prox;
                 Grafos *a = (Grafos*) malloc(sizeof(Grafos));
                 strcpy(a->cidade, "Porto Alegre");
                 a->id = 11;
                 a->incide[0] = NULL; a->distancia[0] = -1; a->acesso[0] = -1;
                 a->incide[1] = NULL; a->distancia[1] = -1; a->acesso[1] = -1;
                 a->incide[2] = NULL; a->distancia[2] = -1; a->acesso[2] = -1;
                 a->prox = NULL;
                 p->prox = a;
                 break;
           }
       }
       return g;
}

main(){
      Grafos *g = NULL;
      int i;
      for(i=0; i<11; i++)
           g = iniciarMapa(g);
      do{
           system("cls");
           printf("\n Cidades Cadastradas: %d", numCidades);
           printf("\n\n\n 1. Cadastrar Cidade");
           printf("\n 2. Alterar Dados");
           printf("\n 3. Remover Cidade");
           printf("\n 4. Percorrer Regiao");
           printf("\n 5. Melhor Rota entre Cidades");
           printf("\n 6. Listar Vizinhos");
           printf("\n\n 0. Sair");
           printf("\n\n\n Opcao: ");
           scanf("%d", &i);
           if(i == 1){ cadastrarCidade(g); }
           else if(i == 2){ alterarCidades(g); }
           else if(i == 3){ g = removerCidades(g); }
           else if(i == 4){ percorrerAmplitude(g); }
           else if(i == 5){ melhorRota(g); }
           else if(i == 6){ listarVizinhos(g); }    
      }while(i != 0);
}
