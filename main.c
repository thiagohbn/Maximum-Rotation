/**********************************************
 *    UNIVERSADE POLIT�CNICA DE PERNAMBUCO    *
 **********************************************
 *   -ALUNO: Thiago Nunes                     *
 *   -TURMA: 2013.1 (turma 1)                 *
 *   -DISCIPLINA: LPI                         *
 *   -PROFESSOR: Byron Leite                  *
 *   -PROJETO: Maximum Rotation               *
 **********************************************/

#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define T 100

/*****************************************************************************************************************
 * L� os dados contidos em cada linha do arquivo Ranking.txt e associa a um local na mem�ria (carrega usu�rios); *
 * Exibe o menu prinipal do jogo;                                                                                *
 * Cria novos dados que ser�o inseridos em um local na memoria (novo usu�rio);                                   *
 * Passa os dados de um dos usuarios como par�metro para uso e atualiza��o (acessa usu�rio);                     *
 * Transfere parametros do tipo estrutura contidos cada um dos locais da memoria...                              *
 *  ...(pontua��o na ordem decrescente, e n crescente), organizando-os (usu�rios);                               *
 * Excreve os dados contidos nos locais da memoria (usu�rios) em cada linha do arquivo Ranking.txt atualizando-o.*
 *****************************************************************************************************************/
int main () {
    int i, j, k;
    int novo_indice, indice, ind;
    int controle;
    char selecao;
    PLAYER *pessoa;
    PLAYER aux;
    FILE *arq;

    logo_maximum_rotation();

    do {
        //Conta o n�mero de linhas no arquivo txt:
        j = novo_indice = linhas_arquivo_Ranking_txt(arq);
        //Esse n�mero ser� associado:
        //Ao vetor de estruturas que vai conter os dados de cada jogador (de "0" a "novo indice");
        //A ordena��o dos dados na mem�ria ("j");
        //Escrita dos dados da mem�ria ao arquivo de texto ("j").

        //Aloca um vetor de estruturas que vai conter os dados dos jogadores:
        pessoa = (PLAYER *) malloc ( (1 + novo_indice) * sizeof (PLAYER) );
        if (pessoa == NULL) {
            printf("[**Erro: Nao foi possivel expandir a memoria!**]");
            exit(1);
        }

        arq = fopen("Ranking.txt", "r");
        if (arq == NULL) {
            printf("\n**Erro: Nao foi possivel acessar!**");
            exit(1);
        }
        //Carrega na mem�ria os dados dos jogadores (arquivo txt):
        for (i=0; !feof(arq); i++) {
            fscanf(arq, "%d %d %d %s", &pessoa[i].n, &pessoa[i].pontuacao ,&pessoa[i].duracao, pessoa[i].jogador);
        }
        fclose(arq);
        //Exibe o menu principal:
        system ("cls");
        Sleep(030);
        printf("MENU A\n");
        linha(79, '-');
        linha (4, '\n');
        Sleep(2*T);
        linha (10, ' ');
        printf("[**1**] Novo usuario");
        Sleep(2*T);
        linha (12, ' ');
        printf("[**2**] Selecionar usuario");
        linha (3, '\n');
        Sleep(2*T);
        linha (10, ' ');
        printf("[**3**] Classificacao geral");
        Sleep(2*T);
        linha (5, ' ');
        printf("[**4**] Finalizar...\n");
        linha (10, '\n');
        linha (79, '-');
        //Recebe o comando do teclado:
        selecao = getch();
        system("cls");
        switch (selecao) {
        case '1':
            controle = novo_usuario (&pessoa[novo_indice], arq, novo_indice+1);
            j += 1;
            break;

        case '2':
            if (novo_indice == 0) { //Informa caso n�o exista usu�rio cadastrado:
                printf("*INFO:\n Nao existe usuario cadastrado!\n Por favor, cadastre um novo usuario...\n");
                linha (79, '-');
                Sleep(30*T);
                continue;
                system ("cls");
            }

            printf ("CLASSIFICACAO GERAL\n");
            cabecalho_ranking();
            exibe_arquivo_Ranking_txt (arq);
            //Seleciona o �ndice associado ao jogador na mem�ria:
            do {
                linha(79, '-');
                printf("Indice do jogador: ");
                scanf(" %d", &indice);
            } while (indice < 0 ||indice > novo_indice+1);

            controle = acessar_usuario(&pessoa[indice-1], arq, indice);
            break;

        case '3':
            controle = classificacao_geral (arq, novo_indice);
            break;

        case '4':
            controle = 0;
            break;
            //Caso seja pressionada a tecla <ENTER> exibe um informativo:
        case '\r':
            printf ("*INFO:\n Nao e possivel acessar o proximo menu!\n Por favor, selecione um usuario...\n");
            linha(79, '-');
            Sleep(30*T);
            system("cls");
            //Bloqueia as outras teclas:
        default:
            controle = 1;
        }
        //Organiza os dados dos jogadores:
        for (k = 0; k < j-1; k++) {
            for (i = 0; i < j-1; i++) {
                if (pessoa[i].pontuacao < pessoa[i+1].pontuacao) { //ordem decrescente de pontua��o.
                    aux = pessoa[i];
                    pessoa[i] = pessoa[i+1];
                    pessoa[i+1] = aux;
                    //ordem crescente de c�digo ("n", coloca��o):
                    ind = pessoa[i].n;
                    pessoa[i].n = pessoa[i+1].n;
                    pessoa[i+1].n = ind;
                }
            }
        }

        arq = fopen("Ranking.txt", "w+");
        if (arq == NULL) {
            printf("\n**Erro: Nao foi possivel acessar!**");
            exit(1);
        }
        //Escreve os dados dos jogadores (mem�ria) no arquivo txt:
        for (i=0; i < j; i++) {
            fprintf(arq, "%d\t%d\t\t%d\t\t%s\n", pessoa[i].n, pessoa[i].pontuacao, pessoa[i].duracao, pessoa[i].jogador);
        }

        fclose(arq);
        //Libera a mem�ria, vetor de estruturas (dados dos jogadores):
        free(pessoa);

    } while (controle);

    return 0;
}
