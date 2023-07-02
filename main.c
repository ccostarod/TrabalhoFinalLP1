#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>
#include <locale.h>

#define disciplinas_maximo 25 

// Variaveis globais que indicam a quantidade de dsiciplinas escolhidas em cada analise
int nmr_dscp1; //
int nmr_dscp2;

typedef struct {
	int disciplina1;
	int disciplina2;
}Disciplina;

void montarMatriz(const char* arquivoEntrada);
bool procurarConflitos(int **grade, int disciplinas[], int numDisciplinas, int novaDisciplina);
void montarGrade(int **grade, int *numDisciplinas, int numeroSorteado);
void montarGrade_imprime(int **grade, int *numDisciplinas, int numeroSorteado);
void montarGrade2(int **grade, int *numDisciplinas, int numeroSorteado);
void montarGrade2_imprime(int **grade, int *numDisciplinas, int numeroSorteado);


int main() {
    setlocale(LC_ALL,"Portuguese");
    montarMatriz("entrada.txt");

    FILE* lista_conflitos;
    int numDisciplinas;
    int **grade;
    int* sorteio = NULL; 
    int i = 0, t1, t2;

    lista_conflitos = fopen("matriz.txt", "r");
    
	if (lista_conflitos == NULL) {
        printf("Erro ao abrir o lista_conflitos de entrada.\n");
        exit(1);
    }

    fscanf(lista_conflitos, "%d", &numDisciplinas);

    grade = (int **)malloc(numDisciplinas * sizeof(int *));
    
	for (i = 0; i < numDisciplinas; i++) {
        grade[i] = (int *)malloc(numDisciplinas * sizeof(int));
    }

    for (i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            fscanf(lista_conflitos, "%d", &grade[i][j]);
        }
    }

    fclose(lista_conflitos);

    srand(time(NULL));
   
    int numSorteios = 3;  // Indicando o número de sorteios desejados
    
    sorteio = (int*)malloc(numSorteios*sizeof(int));
    
	printf("Analises a partir de disciplinas sorteadas:\n\n");
    
    i=0;
	
	while (i < 3) {
	    sorteio[i] = rand() % numDisciplinas + 1;
	    printf("Disciplina sorteada: %d\n", sorteio[i]);
	    montarGrade(grade, &numDisciplinas, sorteio[i]);
	    montarGrade2(grade, &numDisciplinas, sorteio[i]);

		if (nmr_dscp1 > nmr_dscp2){
			printf("Analise Ideal -> ");
		    montarGrade_imprime(grade, &numDisciplinas, sorteio[i]);
		}
		
		if (nmr_dscp2 > nmr_dscp1){
			printf("Analise Ideal -> ");
		    montarGrade2(grade, &numDisciplinas, sorteio[i]);
		}
		
		if (nmr_dscp1 == nmr_dscp2){
			printf("Analise Ideal -> ");
	    	montarGrade_imprime(grade, &numDisciplinas, sorteio[i]);
		}
		
	    i++;
	}

    for (i = 0; i < numDisciplinas; i++) {
        free(grade[i]);
    }
    
	free(grade);

    return 0;
}

//Montando as funções

void montarMatriz(const char* arquivoEntrada) {
    // Variáveis a serem utilizadas dentro da função
	int numDisciplinas, numConflitos;
    Disciplina disciplinas;

    
	// Abrindo o arquivo de entrada e lendo o nº de conflitos e disciplinas
	FILE* lista_conflitos = fopen(arquivoEntrada, "r");
	if (lista_conflitos == NULL) {
        printf("Não foi possível abrir a lista de entrada.\n");
        exit(1);
    }
	fscanf(lista_conflitos, "%d", &numDisciplinas);
    fscanf(lista_conflitos, "%d", &numConflitos);
    
    // Iniciando a matriz que indica os conflitos existentes
    int grade[numDisciplinas][numDisciplinas];

    // Preechendo a matriz de conflitos primeiramente apenas com zeros
	for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            grade[i][j] = 0;
        }
    }
    
    // Identificando onde há conflito e colocando 1 na posição
	for (int j = 0; j < numConflitos; j++) {
        fscanf(lista_conflitos, "%d", &disciplinas.disciplina1);
        fscanf(lista_conflitos, "%d", &disciplinas.disciplina2);

        grade[disciplinas.disciplina1 - 1][disciplinas.disciplina2 - 1] = 1;
        grade[disciplinas.disciplina2 - 1][disciplinas.disciplina1 - 1] = 1;
    }

    fclose(lista_conflitos);
    
    // Abrindo ou criando o arquivo matriz.txt para receber a matriz com os conflitos
    FILE* arquivo_Matriz = fopen("matriz.txt", "w");
    if (arquivo_Matriz == NULL) {
        printf("Erro ao criar o arquivo da matriz.\n");
        exit(1);
    }
    fprintf(arquivo_Matriz, "%d\n", numDisciplinas); 
    for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            fprintf(arquivo_Matriz, "%d ", grade[i][j]);
        }
        fprintf(arquivo_Matriz, "\n");
    }
    fclose(arquivo_Matriz);
    printf("Matriz gerada e armazenada com sucesso em \"matriz.txt\".\n");
    
}


bool procurarConflitos(int **grade, int disciplinas[], int numDisciplinas, int novaDisciplina) {
    
    if (numDisciplinas == 0) {
        return true; 
    }

    // Verifica se há conflitos entre a nova disciplina e a disciplina atual
    if (grade[disciplinas[numDisciplinas - 1]][novaDisciplina] == 1 || grade[novaDisciplina][disciplinas[numDisciplinas - 1]] == 1) {
        return false; 
    }

    // Recursividade:
    return procurarConflitos(grade, disciplinas, numDisciplinas - 1, novaDisciplina);
}

// Função para montar a grade de disciplinas a partir de um ponto de anállise mas sem imprimir na tela o resultado
void montarGrade(int **grade, int *numDisciplinas, int numeroSorteado) {
	// Varáveis a serem utilizadas na função
    int disciplinasEscolhidas[disciplinas_maximo];
    int numDisciplinasEscolhidas = 0;

    // Preenchendo a lista de disciplinas escolhidas
    // Crescente
    for (int i = numeroSorteado - 1; i < *numDisciplinas; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }
  	// Decrescente
    for (int i = numeroSorteado - 2; i >= 0; i--) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
        disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
        numDisciplinasEscolhidas++;
        }
    }
    
    // Variável Global que indica a quantidade de disciplinas ideais com base na Análise 1
    nmr_dscp1 = numDisciplinasEscolhidas;

}

// Mesma função de cima porém agora imprimindo o resultado
void montarGrade_imprime(int **grade, int *numDisciplinas, int numeroSorteado) {
    int disciplinasEscolhidas[disciplinas_maximo];
    int numDisciplinasEscolhidas = 0;
    for (int i = numeroSorteado - 1; i < *numDisciplinas; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }
	for (int i = numeroSorteado - 2; i >= 0; i--) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
        disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
        numDisciplinasEscolhidas++;
        }
    }
    printf("Disciplinas escolhidas: ");
    for (int i = 0; i < numDisciplinasEscolhidas; i++) {
        printf("%d ", disciplinasEscolhidas[i] + 1);
    }
    printf("\n\n");
    
}

// Função para montar a grade de disciplinas a partir de um ponto de anállise mas sem imprimir na tela o resultado
void montarGrade2(int **grade, int *numDisciplinas, int numeroSorteado) {
    // Varáveis a serem utilizadas na função
    int disciplinasEscolhidas[disciplinas_maximo];
    int numDisciplinasEscolhidas = 0;

	// Preenchendo a lista de disciplinas escolhidas
    // Analisando a partir do número sorteado até o último número de disciplinas
    for (int i = numeroSorteado - 1; i < *numDisciplinas; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }
    // Analisando da primeira disciplina até o número sorteado - 2
    for (int i = 0; i < numeroSorteado - 1; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }

    // Variável Global que indica a quantidade de disciplinas ideais com base na Análise 2
    nmr_dscp2 = numDisciplinasEscolhidas;
    
}

// Mesma função de cima porém agora imprimindo o resultado
void montarGrade2_imprime(int **grade, int *numDisciplinas, int numeroSorteado) {
    int disciplinasEscolhidas[disciplinas_maximo];
    int numDisciplinasEscolhidas = 0;
    for (int i = numeroSorteado - 1; i < *numDisciplinas; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }
    for (int i = 0; i < numeroSorteado - 1; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }
    printf("disciplinas escolhidas: ");
    for (int i = 0; i < numDisciplinasEscolhidas; i++) {
        printf("%d ", disciplinasEscolhidas[i] + 1);
    }
    printf("\n\n");
    
}