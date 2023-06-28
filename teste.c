

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>
#include <locale.h>

#define disciplinas_maximo 25


typedef struct {
	int disciplina1;
	int disciplina2;
}Disciplina;

void montarMatriz(const char* arquivoEntrada);
bool procurarConflitos(int **grade, int disciplinas[], int numDisciplinas, int novaDisciplina);
void montarGrade(int **grade, int *numDisciplinas, int numeroSorteado);
void montarGrade2(int **grade, int *numDisciplinas, int numeroSorteado);


int main() {
    setlocale(LC_ALL,"Portuguese");
    montarMatriz("entrada.txt");

    FILE* lista_conflitos;
    int numDisciplinas;
    int **grade;
    int* sorteio = NULL; 

    lista_conflitos = fopen("matriz.txt", "r");
    if (lista_conflitos == NULL) {
        printf("Erro ao abrir a lista de conflitos de entrada.\n");
        return 1;
    }

    fscanf(lista_conflitos, "%d", &numDisciplinas);

    grade = (int **)malloc(numDisciplinas * sizeof(int *));
    for (int i = 0; i < numDisciplinas; i++) {
        grade[i] = (int *)malloc(numDisciplinas * sizeof(int));
    }

    for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            fscanf(lista_conflitos, "%d", &grade[i][j]);
        }
    }

    fclose(lista_conflitos);

    srand(time(NULL));
   
    int numSorteios = 3;  // AlteraÃ§Ã£o: nÃºmero de sorteios desejados
    sorteio = (int*)malloc(numSorteios*sizeof(int));  // AlocaÃ§Ã£o dinÃ¢mica
    printf("Analises a partir de disciplinas sorteadas:\n\n");
    for (int i = 0; i < 3; i++) {
        sorteio[i] = rand() % numDisciplinas + 1;
        printf("Disciplina sorteada: %d\n", sorteio[i]);
        printf("Analise 1 -> ");
        montarGrade(grade, &numDisciplinas, sorteio[i]);
        printf("Analise 2 -> ");
        montarGrade2(grade, &numDisciplinas, sorteio[i]);
        
        printf("\n\n");
        
    }

    for (int i = 0; i < numDisciplinas; i++) {
        free(grade[i]);
    }
    free(grade);

    return 0;
}


//funçôes do código

void montarMatriz(const char* arquivoEntrada) {
    FILE* lista_conflitos = fopen(arquivoEntrada, "r");
    if (lista_conflitos == NULL) {
        printf("NÃ£o foi possÃ­vel abrir a lista de entrada.\n");
        exit(1);
    }

    int numDisciplinas, numConflitos;
    fscanf(lista_conflitos, "%d", &numDisciplinas);

    int grade[numDisciplinas][numDisciplinas]; 

    for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            grade[i][j] = 0;
        }
    }
	
	Disciplina disciplinas; 
	
    fscanf(lista_conflitos, "%d", &numConflitos);
    for (int j = 0; j < numConflitos; j++) {
        fscanf(lista_conflitos, "%d", &disciplinas.disciplina1);
        fscanf(lista_conflitos, "%d", &disciplinas.disciplina2);

        grade[disciplinas.disciplina1 - 1][disciplinas.disciplina2 - 1] = 1;
        grade[disciplinas.disciplina2 - 1][disciplinas.disciplina1 - 1] = 1;
    }

    fclose(lista_conflitos);

    
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

    // Verifica se hÃ¡ conflitos entre a nova disciplina e a disciplina atual
    if (grade[disciplinas[numDisciplinas - 1]][novaDisciplina] == 1 || grade[novaDisciplina][disciplinas[numDisciplinas - 1]] == 1) {
        return false; 
    }

    // Recursividade:
    return procurarConflitos(grade, disciplinas, numDisciplinas - 1, novaDisciplina);
}


void montarGrade(int **grade, int *numDisciplinas, int numeroSorteado) {
    // FunÃ§Ã£o para montar a grade de disciplinas a partir de um ponto de anÃ¡llise

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
    printf("\n");
}

void montarGrade2(int **grade, int *numDisciplinas, int numeroSorteado) {
    // FunÃ§Ã£o para montar a grade de disciplinas a partir de um ponto de anÃ¡lise
    
    int disciplinasEscolhidas[disciplinas_maximo];
    int numDisciplinasEscolhidas = 0;

    // Analisar a partir do nÃºmero sorteado atÃ© o Ãºltimo nÃºmero de disciplinas
    for (int i = numeroSorteado - 1; i < *numDisciplinas; i++) {
        if (procurarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }
    
    // Analisar da primeira disciplina atÃ© o nÃºmero sorteado - 2
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
    printf("\n");
}
