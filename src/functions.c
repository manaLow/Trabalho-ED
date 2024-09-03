//Cabe�alho criado
#include "functions.h"
#include "patient.h"
#include "exam2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o da estrutura da fila dos exames
struct qExam {
  int count;
  qnExam *front;
  qnExam *rear;
};

//Definiçãoo da estrutura da fila dos pacientes
struct qPatient{
    int count;
	qnPatient* front;
	qnPatient* rear;
};

void create_empty_files(const char* filename) {

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }
    fclose(file);
};

char* get_condition_name_by_id(int id){
    char* condition_names[] = {"Saúde Normal","Bronquite","Pneumonia","COVID","Embolia Pulmonar","Derrame Pleural", "Fibrose Pulmonar","Tuberculose","Câncer de Pulmão"};

    return condition_names[id - 1];
}


// Gerar nome aleatório
char* random_name() {

    const char* nomes[] = {"João", "Maria", "Pedro", "Ana", "Lucas", "Carla", "Zé", "Chico", "Bia", "Tina", "Fulano", "Beltrano", "Ciclano", "Zé Ninguém", "Tio Patinhas"};
    const char* sobrenomes[] = {"Silva", "Santos", "Oliveira", "Souza", "Pereira", "Costa", "Pinto", "Almeida", "Nogueira", "da Silva", "da Esquina", "do Pão", "da Silva Sauro", "do Pé Rachado"};


    // Selecionar aleatoriamente um nome e um sobrenome
    const char* nome = nomes[rand() % (sizeof(nomes) / sizeof(nomes[0]))];
    const char* sobrenome = sobrenomes[rand() % (sizeof(sobrenomes) / sizeof(sobrenomes[0]))];

    char* nome_completo = malloc(strlen(nome) + strlen(sobrenome) + 2);
    if (nome_completo == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(1);
    }

    // Concatena o primeiro nome e o sobrenome
    sprintf(nome_completo, "%s %s", nome, sobrenome);

    return nome_completo;
}

// Imprimir relatório geral do hospital
void relatorio_print(qPatient* qp, int total, qExam* qe, int last_id_exam, int last_id_report, int count_time_queue, int *count_time_condition, int *count_exam_condition, int exam_relat){

    printf(" ---- RELATÓRIO ----\n\n");
    printf("Visitaram o hospital: %d.\n", total);
    printf("Na fila aguardando exame: %d.\n", qp->count);
    printf("Já realizaram exame: %d. \n",last_id_exam-1);
    printf("Na fila aguardando laudo: %d.\n", qe->count);
    printf("Porcentagem dos pacientes que já fizeram exames e receberam laudos: %2.f%%\n",(last_id_report/(float)last_id_exam)*100 );
    printf("Tempo médio que os exames ocupam a fila de prioridades: %.2f unidades de tempo.\n", count_time_queue/(float)last_id_report); // TEM QUE FAZER ESSA FUNÇÃO AINDA
    printf("\nTempo médio de laudo por condição:");
    for(int i = 0; i < 9; i++){
        float median_exam_report = 0;
        // Não contenha divisão por zero
        if(count_exam_condition[i] > 0)
            median_exam_report = count_time_condition[i]/count_exam_condition[i];

        //printf("\nCondição %d: %d, %d", i, count_time_condition[i], count_exam_condition[i]); // Verificação das variáveis.
        // A função ja normaliza o início no 0...
        printf("\n\t%s: %.0f ut.", get_condition_name_by_id(i+1), median_exam_report);
    }
    printf("\nNúmero de exames realizados após tempo limite: %d", exam_relat);

}
