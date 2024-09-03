//Cabe�alho criado
#include "report.h"
#include "exam2.h"

#include <stdio.h>
#include <stdlib.h>

// Estrutura para Report
struct report
{
  int id;
  int exam_id;
  condition_IA *condition;
  int timestamp;
};

struct exam {
  int id;
  int patient_id;
  int rx_id;
  condition_IA *condition;
  int timestamp;
};

struct condition_IA {
  int id;
  char *name_condition;
  int severity;
};

// Criar laudo
Report *create_report(int id, Exam* exame, int timestamp){
    Report *new_report = (Report*)malloc(sizeof(Report));

    if(new_report == NULL){
        printf("\nErro ao alocar mem�ria para novo laudo");
        return NULL;
    }

    new_report->id = id;
    new_report->exam_id = exame->id;
    new_report->timestamp = timestamp;
    new_report->condition = exame->condition;
    arq_report(new_report,"db_report.txt");
    return new_report;
}

void destroy_report(Report* report){
    if (report!=NULL){
        if(report->condition!=NULL){
            free(report->condition);
        }
        free(report);
    }
}

// Fun��o sobre a probabilidade da IA estar correta sobre o diagn�stico
condition_IA* condition_check(Exam* exam){
    condition_IA* condition = exam->condition;
    double chance = rand() % 100;
    if (chance <= 80){
        return condition;
    }
    else{
        condition_IA* new_condition = get_condition();
        while (new_condition == condition){
            new_condition = get_condition();
        }
        return condition;
    }

}

// Arquivar laudo no banco de dados
void arq_report(Report* report, const char *filename) {
  FILE *file = fopen(filename, "ab");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  fprintf(file, "\nID do Laudo: %d\n", report->id);
  fprintf(file, "ID do Exame: %d\n", report->exam_id);
  fprintf(file, "Condição do Paciente: %s\n", report->condition->name_condition);
  fprintf(file, "Timestamp: %d\n", report->timestamp);


  fclose(file);
}
