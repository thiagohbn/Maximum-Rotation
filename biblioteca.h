/**********************************************
 *    UNIVERSADE POLITÉCNICA DE PERNAMBUCO    *
 **********************************************
 *   -ALUNO: Thiago Nunes                     *
 *   -TURMA: 2013.1 (turma 1)                 *
 *   -DISCIPLINA: LPI                         *
 *   -PROFESSOR: Byron Leite                  *
 *   -PROJETO: Maximum Rotation               *
 **********************************************/

#include "biblioteca.c"

extern int inicio_tempo();

extern int fim_tempo(int );

extern void linha (int , char );

extern void carregando ();

extern int linhas_arquivo_Ranking_txt (FILE *);

extern int **alocar_matriz (int , int );

extern int **liberar_matriz (int , int **);

extern void matriz_4x4 (int **);

extern void matriz_4x4_para_9x9 (int **, int **);

extern void logo_maximum_rotation ();

extern void cabecalho_ranking ();

extern int novo_usuario (PLAYER *, FILE *, int );

extern int acessar_usuario (PLAYER *, FILE *, int );

extern int classificacao_geral (FILE *, int );

extern int instrucoes ();

extern int submenu ();

extern void carinha_triste ();

extern void carinha_alegre ();

extern int fim_de_jogo (PLAYER *, int , int );

extern int cancela_jogo (PLAYER *, int , int );

extern int novo_jogo (PLAYER *);

extern void logo_maximum_rotation ();
