#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define disciplinas_maxima 100
//Função para montar matriz de conflitos a paratir do arquivoEntrada.
void montarMatrizConflitos(const char* arquivoEntrada) {
    FILE* arquivo = fopen(arquivoEntrada, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    int numDisciplinas, numConflitos;
    fscanf(arquivo, "%d %d", &numDisciplinas, &numConflitos);

    int grade[numDisciplinas][numDisciplinas]; //Matriz quadrada

    // Inicializar matriz com zeros
    for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            grade[i][j] = 0;
        }
    }

    // Ler conflitos e atualizar a matriz
    for (int j = 0; j < numConflitos; j++) {
        int disciplina1, disciplina2;
        fscanf(arquivo, "%d %d", &disciplina1, &disciplina2);
        grade[disciplina1 - 1][disciplina2 - 1] = 1;
        grade[disciplina2 - 1][disciplina1 - 1] = 1;
    }

    fclose(arquivo);

    // Salvar a matriz em um arquivo "matriz.txt"
    FILE* arquivoMatriz = fopen("matriz.txt", "w");
    if (arquivoMatriz == NULL) {
        printf("Erro ao criar o arquivo de matriz.\n");
        return;
    }

    fprintf(arquivoMatriz, "%d\n", numDisciplinas);

    for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            fprintf(arquivoMatriz, "%d ", grade[i][j]);
        }
        fprintf(arquivoMatriz, "\n");
    }

    fclose(arquivoMatriz);

    printf("Matriz de conflitos gerada e armazenada em \"matriz.txt\".\n");
}

bool verificarConflitos(int grade[disciplinas_maxima][disciplinas_maxima], int disciplinas[], int numDisciplinas, int novaDisciplina) {
    // Função para verificar se uma nova disciplina entra em conflito com as disciplinas existentes
    for (int i = 0; i < numDisciplinas; i++) {
        if (grade[disciplinas[i]][novaDisciplina] == 1 || grade[novaDisciplina][disciplinas[i]] == 1) {
            return false; //Conflito encontrado, retorna falso
        }
    }
    return true; // Não há conflitos, retorna verdadeiro
}

void montarGrade(int grade[disciplinas_maxima][disciplinas_maxima], int numDisciplinas, int numeroSorteado) {
    // Função para montar a grade de disciplinas a partir de um ponto de análise

    int disciplinasEscolhidas[disciplinas_maxima];
    int numDisciplinasEscolhidas = 0;

    
    for (int i = numeroSorteado - 1; i < numDisciplinas; i++) {
        if (verificarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
            disciplinasEscolhidas[numDisciplinasEscolhidas] = i;
            numDisciplinasEscolhidas++;
        }
    }

  
    for (int i = numeroSorteado - 2; i >= 0; i--) {
    
        if (verificarConflitos(grade, disciplinasEscolhidas, numDisciplinasEscolhidas, i)) {
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


int main() {
    montarMatrizConflitos("entrada.txt");

    FILE* arquivo;
    int numDisciplinas;
    int grade[disciplinas_maxima][disciplinas_maxima];
    int sorteio[3];

    arquivo = fopen("matriz.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    fscanf(arquivo, "%d", &numDisciplinas);

    for (int i = 0; i < numDisciplinas; i++) {
        for (int j = 0; j < numDisciplinas; j++) {
            fscanf(arquivo, "%d", &grade[i][j]);
        }
    }

    fclose(arquivo);

    srand(time(NULL));

    printf("Analises a partir de disciplinas sorteadas:\n");
    for (int i = 0; i < 3; i++) {
        sorteio[i] = rand() % numDisciplinas + 1;
        printf("Analise %d - Disciplina sorteada: %d\n", i + 1, sorteio[i]);
        montarGrade(grade, numDisciplinas, sorteio[i]);
        printf("\n");
    }

    return 0;
}
