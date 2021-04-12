/**********************************************
 *    UNIVERSADE POLITÉCNICA DE PERNAMBUCO    *
 **********************************************
 *   -ALUNO: Thiago Nunes                     *
 *   -TURMA: 2013.1 (turma 1)                 *
 *   -DISCIPLINA: LPI                         *
 *   -PROFESSOR: Byron Leite                  *
 *   -PROJETO: Maximum Rotation               *
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#define CIMA 72
#define BAIXO 80
#define ESQUERDA 75
#define DIREITA 77
#define ESC 27
#define N 9
#define M 4
#define T 100

/*********************************************************************************
 * Estrutura do jogador utilizada para armqzenamento das informações do usuario. *
 *********************************************************************************/
typedef struct {
    int n;
    int pontuacao;
    int duracao;
    char jogador [30];
} PLAYER;

/************************************
 * Captura a hora atual do sistema. *
 ************************************/
int inicio_tempo() {
    time_t inicio;

    return (inicio = time(0));
}

/***********************************************************************************
 * Faz a diferença entre a tempo atual do sistema e o tempo que se iniciou o jogo. *
 ***********************************************************************************/
int fim_tempo(int inicio) {
    return (time(0) - inicio);
}

/*********************************************************
 * Faz a organização visual do programa linha por linha. *
 *********************************************************/
void linha (int n, char c) {
    int i;

    for (i = 0; i <= n; i++)
        printf ("%c", c);
}

/******************************************************
 * Função customizada semelhante ao system ("pause"). *
 ******************************************************/
void carregando () {
    int ponto = 0;

    while (1) {
        printf("Pressione qualquer tecla para continuar");
        while (ponto < 3) { //Exibe 3 pontos em sequência na tela:
            Sleep (5*T);
            printf(".");
            ponto++;
        }
        break;
    }
    getch();
}

/******************************************************************************
 * Através do caractere '\n' conta as linhas do arquivo de texto Ranking.txt. *
 ******************************************************************************/
int linhas_arquivo_Ranking_txt (FILE *desc_arq) {
    int quant_linhas = 0;
    int ch;
    //Ler o arquivo de texto, caso não exista cria um novo arquivo de texto
    desc_arq = fopen("Ranking.txt", "r");
    if (desc_arq == NULL) {
        desc_arq = fopen("Ranking.txt", "w");
        if (desc_arq == NULL) {
            printf("\n[**Erro: Nao foi possivel acessar!**]\n");
            linha (79, '-');
            exit(1);
        }
    }
    //Verifica se existe quantos '\n' existem no arquivo de texto:
    while ((ch = fgetc(desc_arq)) != EOF) {
        if (ch == '\n') {
            quant_linhas++;
        }

    }
    fclose (desc_arq);
    //retorna o número de linhas:
    return quant_linhas;
}

/*****************************************************************************************
 * Exibe na tela o cabeçalho das informações contidas nas linhas do arquivo Ranking.txt. *
 *****************************************************************************************/
void cabecalho_ranking () {
    linha(78, '-');
    printf ("\nN\tPontuacao\tTempo [seg]\tJogador\t\n");
    linha(78, '-');
    linha(1, '\n');
}

/*************************************************
 * Exibe todo o conteúdo do arquivo Ranking.txt. *
 *************************************************/
void exibe_arquivo_Ranking_txt (FILE *arq) {
    char caractere;

    arq = fopen("Ranking.txt", "r");
    if (arq == NULL) {
        printf("\n[**Erro: Não foi possivel ler o Ranking!**]");
        exit (1);
    }
    //Exibe todos os caracteres do texto na tela
    while (!feof(arq)) {
        fscanf (arq, "%c", &caractere);
        printf("%c", caractere);
    }

    fclose (arq);
}

//
/******************************
 * Cadrastra um novo usuario. *
 ******************************/
int novo_usuario (PLAYER *ptr, FILE *desc_arq, int codigo) {
    int i, controle, valor;
    int cadastrar;
    char opcao, selecao;
    char nome[30];
    PLAYER p;

    ptr->n = codigo;
    ptr->pontuacao = 0;
    ptr->duracao = 0;

    printf("Jogador %d!\n", ptr->n);
    linha (79, '-');

    do {
        printf("\nNome: ");
        //Recebe e passa os caracteres da string de minúsculo para maiúsculo:
        strupr (gets (nome));
        //Substitui os caracteres espaço em branco (' ') em linha abaixo ('_'):
        for (i=0; i< strlen(nome); i++) {
            if (nome[i] == ' ') {
                nome[i] = '_';
            }

        }
        //Copia a string para o espaço na memória:
        strcpy (ptr->jogador, nome);

        desc_arq = fopen("Ranking.txt", "r");
        if (desc_arq == NULL) {
            printf("\n[**Erro: Nao foi possivel acessar!**]");
            exit(1);
        }
        for (i=0; !feof(desc_arq); i++) {
            //Verifica se já existe o usuário cadastrado:
            fscanf(desc_arq, "%d %d %d %s", &p.n, &p.pontuacao,&p.duracao, p.jogador);
            if (!strcmp(ptr->jogador, p.jogador)) {
                printf("\nINFO:\n**O jogador [%s] ja cadastrado!**\n\n", ptr->jogador);
                system("pause");
                system ("cls");
                cadastrar = 1;
            } else
                cadastrar = 0;
        }
        fclose(desc_arq);

    } while (cadastrar);

    desc_arq = fopen ("Ranking.txt", "a");
    if (desc_arq == NULL) {
        printf ("\n[**Erro: Nao foi possivel cadastrar o jogador!**]");
        exit (1);
    }//Escreve o novo usuário no arquivo de texto:
    fprintf (desc_arq, "%d\t%d\t\t%d\t\t%s\n",ptr->n, ptr->pontuacao, ptr->duracao, ptr->jogador);
    fclose(desc_arq);

    system("cls");

    printf ("CLASSIFICACAO GERAL\n");
    cabecalho_ranking ();
    exibe_arquivo_Ranking_txt (desc_arq);

    linha (79, '-');
    printf(" *Bem vindo(a) ao jogo [%s]!", ptr->jogador);
    printf("\n\n *Voce e o(a) jogador(a) numero [%d] a se cadrastrar!\n", ptr->n);
    linha (79, '-');
    printf(" [Cancela] <ESC>");
    linha (44, ' ');
    printf ("<ENTER> [Confirma]");

    do {
        selecao = getch ();
        switch (selecao) {
        case ESC:
            return 1;
            break;
        case '\r':
            controle = submenu(ptr, desc_arq);
            return 1;
            break;
        default:
            controle = 1;
        }
    } while (controle);

    return 0;
}

/*******************************************************************************
 * Exibe na tela o conteúdo da memoria (informações de um usuario específico), *
 *******************************************************************************/
int acessar_usuario (PLAYER *ptr, FILE *desc_arq, int codigo) {
    int i;
    int controle;
    char selecao;

    system("cls");

    printf ("USUARIO SELECIONADO\n");
    cabecalho_ranking();
    //Exibe na tela o usuário anteriormente selecionado:
    linha (codigo-2, '\n');
    printf("\n%d\t%d\t\t%d\t\t%s\t\n", ptr->n, ptr->pontuacao, ptr->duracao, ptr->jogador);
    linha (1, '\n');

    linha (79, '-');
    printf("\n [Cancela] <ESC>");
    linha (44, ' ');
    printf ("<ENTER> [Confirma]");

    do {
        selecao = getch ();
        switch (selecao) {
        case ESC:
            return 1;
            break;
        case '\r':
            controle = submenu(ptr);
            return 1;
            break;
        default:
            controle = 1;
        }
    } while (controle);

    return 0;
}

/********************************************
 * Exibe o conteúdo do arquivo Ranking.txt. *
 ********************************************/
int classificacao_geral (FILE *desc_arq, int codigo) {
    int controle;
    char selecao;

    if (codigo == 0) {
        printf("*INFO:\n Nao existe usuario cadastrado!\n Por favor, cadastre um novo usuario...\n");
        linha (79, '-');
        Sleep(30*T);
        return 1;
    }

    printf ("CLASSIFICACAO GERAL\n");
    cabecalho_ranking();

    exibe_arquivo_Ranking_txt(desc_arq);

    linha (79, '-');
    printf("\n[Voltar] <ESC>");

    do {
        selecao = getch ();
        switch (selecao) {
        case ESC:
            return 1;
            break;
        default:
            controle = 1;
        }
    } while (controle);
}

/*****************************************************************************
 * Exibe na tela as instruções do jogo descrevendo suas teclas e utilidades. *
 *****************************************************************************/
int instrucoes () {
    char selecao;
    char controle;
    //Exibe as instruções do jogo na tela:
    system("cls");
    printf("\n[** Descricao: **]\n ----------------\n\n"
           " Organizar os numeros em ordem numerica, movendo-os no pequeno quadro.\n\n\n"
           "[** Como jogar Maximum Rotation: **]\n ----------------------------------\n\n"
           " Seta de cima, Seta de baixo, w, s, 2 e 8:\n"
           " Mover o pequeno quadro para cima e para baixo.\n\n"
           " Seta da esquerda, Seta da direita, a, d, 4 e 6:\n"
           " Mover o pequeno quadro para a esquerda e para a direita.\n\n"
           " 7, <:\n"
           " Mover os numeros que aparecem no pequeno quadro no sentido anti-horario.\n\n"
           " 9, >:\n"
           " Mover os numeros que aparecem no pequeno quadro no sentido horario.\n\n\n\n");
    printf (" [Voltar] <ESC>");

    do {
        selecao = getch ();
        switch (selecao) {
        case ESC:
            return 1;
            break;
        default:
            selecao = 1;
        }
    } while (selecao);
}

/********************************************
 * Exibe na tela um desenho (smile triste). *
 ********************************************/
void carinha_triste() {
    system ("color 0e");

    printf ("                                    #######      \n");
    Sleep(T);
    printf ("    .................          ################   \n");
    Sleep(T);
    printf ("    .Jogo cancelado!.        #####################   \n");
    Sleep(T);
    printf ("    .................      #########################   \n");
    Sleep(T);
    printf ("                   ,      #########  #####  ##########  \n");
    Sleep(T);
    printf ("                    ,    #########    ###    ##########  \n");
    Sleep(T);
    printf ("                     ,  ##########    ###    ###########  \n");
    Sleep(T);
    printf ("                       ###########    ###    ############ \n");
    Sleep(T);
    printf ("                       ############  #####  #############  \n");
    Sleep(T);
    printf ("                      ####################################  \n");
    Sleep(T);
    printf ("                      ####################################  \n");
    Sleep(T);
    printf ("                      ####################################  \n");
    Sleep(T);
    printf ("                       #######################      #####  \n");
    Sleep(T);
    printf ("                       ####################  #######  ### \n");
    Sleep(T);
    printf ("                        #################  #############  \n");
    Sleep(T);
    printf ("                         ############### ##############  \n");
    Sleep(T);
    printf ("                          ############# ##############  \n");
    Sleep(T);
    printf ("                           ########### #############   \n");
    Sleep(T);
    printf ("                              ####### ############   \n");
    Sleep(T);
    printf ("                                ###############    \n");
    Sleep(T);
    printf ("                                    #######      \n");
    Sleep(T);
}

/********************************************
 * Exibe na tela um desenho (smile alegre). *
 ********************************************/
void carinha_alegre () {
    system ("color 0e");

    linha (0,'\n');
    linha (20,' ');
    Sleep(T);
    printf ("^^^^^^^###^^^^^^^^^^^^^^^^^###^^^^^^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^^^#####^^^^^^^^^^^^^^^^^######^^^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^^####^^^^^^^^^^^^^^^^^^^^^#####^^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^####^^^^^^^^^^^^^^^^^^^^^^^#####^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^####^^^^^####^^^^^^^^^###^^^^^###^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^###^^^^^######^^^^^^^###^^^^^^####^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^####^^^^^######^^^^^^###^^^^^^^^###^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^###^^^^^^^####^^^^^^###^^^^^^^^^####\n");
    linha (20,' ');
    Sleep(T);
    printf ("^###^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^###\n");
    linha (20,' ');
    Sleep(T);
    printf ("^###^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^###\n");
    linha (20,' ');
    Sleep(T);
    printf ("^###^^^^##^^^^^^^^^^^^^^^^^##^^^^^###\n");
    linha (20,' ');
    Sleep(T);
    printf ("^###^^^^###^^^^^^^^^^^^^^^^##^^^^####\n");
    linha (20,' ');
    Sleep(T);
    printf ("^####^^^^####################^^^^###^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^###^^^^^^^^##^^^#^^^##^^^^^^^^####^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^####^^^^^^^##^^^#^^^##^^^^^^^^###^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^####^^^^^^##^^^#^^^##^^^^^^#####^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^^####^^^^^^########^^^^^^^#####^^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^^^#####^^^^^^^^^^^^^^^^^######^^^^\n");
    linha (20,' ');
    Sleep(T);
    printf ("^^^^^^#########################^^^^^^\n");
}

/****************************************************
 * Calcula os pontos e o tempo jogado;              *
 * Atualiza e exibe os dados do jogador na memória. *
 ****************************************************/
int fim_de_jogo (PLAYER *ptr, int rotacoes, int tempo_atual) {
    int pontos;
    int tempo_de_jogo;

    tempo_de_jogo = fim_tempo(tempo_atual);

    ptr->duracao = tempo_de_jogo;

    pontos = 2000 - (rotacoes + tempo_de_jogo); //Bônus positivo de 2000 pontos
    //Caso a pontuação do jogador for maior que o anterior, sua pontuação é atualizada:
    if (ptr->pontuacao < pontos)
        ptr->pontuacao = pontos;

    carinha_alegre ();

    linha (0,'\n');
    linha (30,' ');
    printf("Jogo Finalizado!\n\n");
    linha (22,' ');
    printf(" O tempo de jogo foi: %d seg.\n", tempo_de_jogo);
    linha (22,' ');
    printf(" A pontuacao foi: %d pontos.\n\n", pontos);
    linha (18,' ');

    carregando();

    system("cls");

    system("color 30");

    return 0;
}

/****************************************************
 * Calcula os pontos e o tempo jogado;              *
 * Atualiza e exibe os dados do jogador na memória. *
 ****************************************************/
int cancela_jogo (PLAYER *ptr, int rotacoes, int tempo_atual) {
    int pontos;
    int tempo_de_jogo;

    tempo_de_jogo = fim_tempo(tempo_atual);

    ptr->duracao = tempo_de_jogo;

    pontos = 500 - (rotacoes + tempo_de_jogo); //Bônus positivo de 500 pontos
    //Caso a pontuação do jogador for maior que o anterior, sua pontuação é atualizada:
    if (ptr->pontuacao < pontos)
        ptr->pontuacao = pontos;

    carinha_triste ();

    linha (22,' ');
    printf(" Menor tempo de jogo: [%d] seg.\n", tempo_de_jogo);
    linha (22,' ');
    printf(" Maior pontuacao e: [%d] pontos.\n\n", pontos);
    linha (18,' ');

    carregando();

    system("cls");

    system("color 30");

    return 0;
}

/******************************************
 * Aloca a memória de uma matriz do jogo. *
 ******************************************/
int **alocar_matriz (int m, int n) {
    int i;
    int **v;

    v = (int **) calloc(m, sizeof (int *)); //Aloca as linhas da matriz
    if (v == NULL) {
        printf("\n[**Erro: Memoria insuficiente**]");
        return (NULL); //Retorna o ponteiro nulo
    }
    for (i = 0; i < m; i++) { //Aloca as colunas da matriz
        v[i] = (int *) calloc(n, sizeof (int));
        if (v[i] == NULL) {
            printf("\n[**Erro: Memoria insuficiente**]");
            return (NULL); //Retorna o ponteiro nulo
        }
    }
    return (v); //Retorna o ponteiro para matriz
}

/*******************************************
 * Libera a memória de uma matriz do jogo. *
 *******************************************/
int **liberar_matriz (int m, int **v) {
    int i;

    if (v == NULL) {
        return (NULL);
    }
    for (i = 0; i < m; i++) { //Libera as linhas da matriz
        free(v[i]);
    }
    free(v); //Libera as colunas matriz

    return (NULL); //Retorna o ponteiro nulo
}

/*********************************************************
 * Cria uma matriz numerica 4x4 (de 1 a 16) do jogo.     *
 * Mistura aleatoriamente os elementos da matriz 4x4.    *
 *********************************************************/
void matriz_4x4 (int **MATRIX) {
    int matrix [M][M] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    int i, j;
    int a, b;
    int tmp;
    //Semente da função randômica (relógio do sistema):
    srand(time(NULL));
    //Transfere a matriz estática à matriz dinâmica (de "1" a "16"):
    for(i = 0; i < M; i++) {
        for(j = 0; j < M; j++) {
            MATRIX [i][j] = matrix[i][j];
        }
    }
    //Mistura os elementos da matriz dinâmica:
    for(i = 0; i < M; i++) {
        for(j = 0; j < M; j++) {
            a = rand() % M;
            b = rand() % M;

            tmp = MATRIX[a][b];
            MATRIX[a][b] = MATRIX[i][j];
            MATRIX[i][j] = tmp;
        }
    }
}

/***************************************************************
 * Transfere os números da matriz 4x4 (aleatória) à futura...  *
 * ...matriz 9x9 (mista) composta por números e caracteres .   *
 ***************************************************************/
void matriz_4x4_para_9x9 (int **MATRIX, int **MATRIZ) {
    MATRIZ [1][1] = MATRIX [0][0];
    MATRIZ [1][3] = MATRIX [0][1];
    MATRIZ [1][5] = MATRIX [0][2];
    MATRIZ [1][7] = MATRIX [0][3];
    MATRIZ [3][1] = MATRIX [1][0];
    MATRIZ [3][3] = MATRIX [1][1];
    MATRIZ [3][5] = MATRIX [1][2];
    MATRIZ [3][7] = MATRIX [1][3];
    MATRIZ [5][1] = MATRIX [2][0];
    MATRIZ [5][3] = MATRIX [2][1];
    MATRIZ [5][5] = MATRIX [2][2];
    MATRIZ [5][7] = MATRIX [2][3];
    MATRIZ [7][1] = MATRIX [3][0];
    MATRIZ [7][3] = MATRIX [3][1];
    MATRIZ [7][5] = MATRIX [3][2];
    MATRIZ [7][7] = MATRIX [3][3];
}

/***********************************************************************************************************
 * Inicia um novo jogo;                                                                                    *
 * Transfere os caracteres (elementos que a completa) à matriz de números e caracteres 9x9;                *
 * Exibe na tela os caracteres da matriz 9x9 por meio do teclado;                                          *
 * Movimenta os elementos em torno de uma matriz 2x2 no sentido horario e antihorario por meio do teclado. *
 ***********************************************************************************************************/
int novo_jogo (PLAYER *ptr) {
    int **MATRIX, **MATRIZ;
    int i, j;
    int x=0, y=0;
    int A, B, C, D;
    char char1=708, char2=691, char3=769;
    char tecla;
    int movimentos = 0;
    int tempo_de_jogo;

    MATRIX = alocar_matriz(M, M);
    matriz_4x4(MATRIX);

    MATRIZ = alocar_matriz(N, N);

    matriz_4x4_para_9x9(MATRIX, MATRIZ);

    MATRIX = liberar_matriz(M, MATRIX);
    //Inicia a contagem do tempo do jogo:
    tempo_de_jogo = inicio_tempo ();

    while (tecla != ESC) {
        //Insere em locais definidos os caracteres na matriz do jogo ("9x9"):
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (i==y+2 && (j>=x+3 && j<=x+5) || i==y+6 && (j>=x+3 && j<=x+5))                                                      MATRIZ [i][j] = char1;
                else if (j==x+2 && (i>=y+3 && i<=y+5) || j==x+6 && (i>=y+3 && i<=y+5))                                                 MATRIZ [i][j] = char2;
                else if (i==y+2 && j==x+2 ||i==y+2 && j==x+6 || i==y+6 && j==x+2 || i==y+6 && j==x+6)                                  MATRIZ [i][j] = char3;
                else if (i==y-2||i==y||i==y+2||i==y+4||i==y+6||i==y+8||i==y+10||j==x-2||j==x||j==x+2||j==x+4||j==x+6||j==x+8||j==x+10) MATRIZ [i][j] = ' ';
            }
        }
        //Exibe na tela a área selecionada pelo jogador:
        printf("Selecao:");
        linha (40, ' ');
        printf ("%30s\n", ptr->jogador);
        printf(" %.2d",     MATRIZ [y+3][x+3]);
        printf(" %.2d\n",   MATRIZ [y+3][x+5]);
        printf(" %.2d",     MATRIZ [y+5][x+3]);
        printf(" %.2d\n\n", MATRIZ [y+5][x+5]);
        //Exibe na tela os números e caracteres da matriz do jogo ("9x9"):
        for (i = 0; i < N; i++) {
            printf("\n                             ");
            for (j = 0; j < N; j++) {
                if (i==y+2 && (j>=x+3 && j<=x+5) || i==y+6 && (j>=x+3 && j<=x+5))                                                      printf ("%2.c", MATRIZ[i][j]);
                else if (j==x+2 && (i>=y+3 && i<=y+5) || j==x+6 && (i>=y+3 && i<=y+5))                                                 printf ("%2.c", MATRIZ[i][j]);
                else if (i==y+2 && j==x+2 ||i==y+2 && j==x+6 || i==y+6 && j==x+2 || i==y+6 && j==x+6)                                  printf ("%2.c", MATRIZ[i][j]);
                else if (i==y-2||i==y||i==y+2||i==y+4||i==y+6||i==y+8||i==y+10||j==x-2||j==x||j==x+2||j==x+4||j==x+6||j==x+8||j==x+10) printf ("%2.c", MATRIZ[i][j]);
                else                                                                                                                   printf ("%.2d", MATRIZ[i][j]);
            }
        }
        linha(10, '\n');
        printf("Movimentos: ");
        printf("%.3d", movimentos);
        linha (50, ' ');
        printf("<ESC> [sair]");
        //Define as teclas da matriz 2x2 (interna a matriz 9x9):
        //Teclas de direção e sentido.
        tecla = getch ();
        switch (tecla) {
        case 'a':
        case 'A':
        case '4':
        case ESQUERDA:
            x-=2;
            if (x<-2) x=-2;
            system("cls");
            break;
        case 'd':
        case 'D':
        case '6':
        case DIREITA:
            x+=2;
            if (x>2) x=2;
            system("cls");
            break;
        case 'w':
        case 'W':
        case '2':
        case CIMA:
            y-=2;
            if (y<-2) y=-2;
            system("cls");
            break;
        case 's':
        case 'S':
        case '8':
        case BAIXO:
            y+=2;
            if (y>2) y=2;
            system("cls");
            break;
        case '7':
        case ',':
            A = MATRIZ [y+3][x+3];
            B = MATRIZ [y+3][x+5];
            C = MATRIZ [y+5][x+3];
            D = MATRIZ [y+5][x+5];
            MATRIZ [y+3][x+3] = B;
            MATRIZ [y+3][x+5] = D;
            MATRIZ [y+5][x+3] = A;
            MATRIZ [y+5][x+5] = C;
            movimentos++;
            system("cls");
            break;
        case '9':
        case '.':
            A = MATRIZ [y+3][x+3];
            B = MATRIZ [y+3][x+5];
            C = MATRIZ [y+5][x+3];
            D = MATRIZ [y+5][x+5];
            MATRIZ [y+3][x+3] = C;
            MATRIZ [y+3][x+5] = A;
            MATRIZ [y+5][x+3] = D;
            MATRIZ [y+5][x+5] = B;
            movimentos++;
            system("cls");
            break;
        case ESC:
            system("cls");
            MATRIZ = liberar_matriz (N, MATRIZ);
            return cancela_jogo (ptr, movimentos, tempo_de_jogo); //retorna o retorno da função.
            break;
        default:
            system("cls");
            break;
        }
        //Verifica se as linhas da matriz estão organizadas (ordem crescente de "1" a "16").
        //Se a matriz estever organizada é finalizado o jogo.
        if (MATRIZ [1][1] == 1 && MATRIZ [1][3] == 2 && MATRIZ [1][5] == 3 && MATRIZ [1][7] == 4) {
            if (MATRIZ [3][1] == 5 && MATRIZ [3][3] == 6 && MATRIZ [3][5] == 7 && MATRIZ [3][7] == 8) {
                if (MATRIZ [5][1] == 9 && MATRIZ [5][3] == 10 && MATRIZ [5][5] == 11 && MATRIZ [5][7] == 12) {
                    if (MATRIZ [7][1] == 13 && MATRIZ [7][3] == 14 && MATRIZ [7][5] == 15 && MATRIZ [7][7] == 16) {
                        MATRIZ = liberar_matriz (N, MATRIZ);
                        return fim_de_jogo(ptr, movimentos, tempo_de_jogo); //retorna o retorno da função.
                        break;
                    }
                }
            }
        }
    }
}

/*************************************
 * Exibe um menu secundário do jogo. *
 *************************************/
int submenu (PLAYER *p, FILE *arq) {
    int controle;
    char selecao;

    do {
        system ("cls");
        Sleep(030);
        printf("MENU B\n");
        linha(79, '-');
        linha (4, '\n');
        Sleep(2*T);
        linha (10, ' ');
        printf("[**5**] Novo jogo");
        Sleep(2*T);
        linha (17, ' ');
        printf("[**6**] Instrucoes\n\n\n\n");
        Sleep(2*T);
        linha (10, ' ');
        printf("[*ESC*] Voltar...\n");
        linha (10, '\n');
        linha (79, '-');

        selecao = getch();
        system("cls");
        switch (selecao) {
        case '5':
            controle = novo_jogo (p);
            break;
        case '6':
            controle = instrucoes ();
            break;
        case ESC:
            return 1;
            break;
        default:
            controle = 1;
        }
    } while (controle);

    return 0;
}

/*****************************************************************
 * Exibe o desenho da tela principal do jogo (MAXIMUM ROTATION). *
 *****************************************************************/
void logo_maximum_rotation () {
    system("color 30");
    linha(2, '\n');
    Sleep(200);
    Sleep(T);
    printf("       ##     ##    ###    ##     ## #### ##     ## ##     ## ##    ##     \n");
    system("color 30");
    Sleep(T);
    printf("       ###   ###   ## ##    ##   ##   ##  ###   ### ##     ## ###   ##     \n");
    system("color 03");
    Sleep(T);
    printf("       #### ####  ##   ##    ## ##    ##  #### #### ##     ## ####  ##     \n");
    system("color 30");
    Sleep(T);
    printf("       ## ### ## ##     ##    ###     ##  ## ### ## ##     ## ## ## ##     \n");
    system("color 03");
    Sleep(T);
    printf("       ##     ## #########   ## ##    ##  ##     ## ##     ## ##  ####     \n");
    system("color 30");
    Sleep(T);
    printf("       ##     ## ##     ##  ##   ##   ##  ##     ## ##     ## ##   ###     \n");
    system("color 03");
    Sleep(T);
    printf("       ##     ## ##     ## ##     ## #### ##     ##  #######  ##    ##     \n");
    system("color 30");
    Sleep(T);
    printf("								                                           \n");
    system("color 03");
    Sleep(T);
    printf("    ########   #######  ########    ###    ######## ####  #######  ##    ##\n");
    system("color 30");
    Sleep(T);
    printf("    ##     ## ##     ##    ##      ## ##      ##     ##  ##     ## ###   ##\n");
    system("color 03");
    Sleep(T);
    printf("    ##     ## ##     ##    ##     ##   ##     ##     ##  ##     ## ####  ##\n");
    system("color 30");
    Sleep(T);
    printf("    ########  ##     ##    ##    ##     ##    ##     ##  ##     ## ## ## ##\n");
    system("color 03");
    Sleep(T);
    printf("    ##   ##   ##     ##    ##    #########    ##     ##  ##     ## ##  ####\n");
    system("color 30");
    Sleep(T);
    printf("    ##    ##  ##     ##    ##    ##     ##    ##     ##  ##     ## ##   ###\n");
    system("color 03");
    Sleep(T);
    printf("    ##     ##  #######     ##    ##     ##    ##    ####  #######  ##    ##\n");
    system("color 30");
    linha(2, '\n');
    linha(18, ' ');
    Sleep(T);
    carregando ();
    system("cls");
}
