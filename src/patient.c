//Cabe�alho criado
#include "patient.h"

#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura do Paciente
struct Patient{
    int id;
    char* name;
    int timestamp;
};

//Defini��o da estrutura da fila dos pacientes
struct qPatient{
    int count;
	qnPatient* front;
	qnPatient* rear;
};

//Defini��o da estrutura dos n�s da fila dos pacientes
struct qnPatient{
	Patient* info;
	qnPatient* next;
};

//Fun��o para alocar mem�ria e inicializar um paciente
Patient *create_patient(int id, const char *name, int timestamp){
    // Aloca��o de mem�ria
    Patient* new_patient = (Patient *)malloc(sizeof(Patient));
    // Verifica se alocou corretamente
    if (new_patient == NULL)
    {
        printf("Erro ao alocar mem�ria para novo paciente.\n");
        return NULL;
    }

    // Inicializa vari�veis
    new_patient -> id = id;
    new_patient -> timestamp = timestamp;
    new_patient -> name = strdup(name);
    // Verificando se aloca��o e inicializa��o deu certo
    if (new_patient->name == NULL){
        printf("Erro ao alocar mem�ria para o nome do paciente.\n");
        free(new_patient);
        return NULL;
    }
    arq_patient(new_patient, "db_patient.txt");
    return new_patient;
}

//Cria��o de filas vazias para pacientes
qPatient* create_qPatient(){
	qPatient *q = (qPatient*)malloc(sizeof(qPatient));
    // Verifica se alocou corretament
    if (q == NULL){
        printf("Erro ao alocar mem�ria para a fila vazia.\n");
        return NULL;
    }
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;

    return q;
}

// Fun��o para verificar se a fila de pacientes est� vazia
int fila_vazia (qPatient* q){
    return q->front == NULL;
}

//Fun��o para inserir paciente na fila
void enqueue_qPatient(qPatient* q, Patient* patient){
    qnPatient* node = (qnPatient*)malloc(sizeof(qnPatient));

    if (node == NULL){
        printf("Erro ao alocar mem�ria para o n�.\n");
        return;
    }

    node->info = patient;
    node->next = NULL;

    if (fila_vazia(q)){
        q->front = node;
    }
    else{
        q->rear->next = node;
    }
    q->rear = node;
    q->count++;
}

//Fun��o para tirar o paciente da fila
Patient* dqueue_qPatient(qPatient* q){

    Patient* p = q->front->info;
    qnPatient* node = q->front;

    if (q->front != q->rear){
        q->front = q->front->next;
    }
    else{
        q->front = q->rear = NULL;
    }
    q->count--;
    free(node);
    return p;
}

// Fun��o para liberar mem�ria de um cadastro de paciente
void destroy_patient(Patient* patient){
    // Verificando se o paciente existe (tem alguma mem�ria alocada j�)
    if (patient != NULL){

        if (patient->name != NULL){
            free(patient -> name);
        }

        free(patient);
    }
}

//Gravar paciente no banco de dados
void arq_patient(Patient* patient, const char* filename) {
  FILE* file = fopen(filename, "ab");
  if (file == NULL) {
      perror("Erro ao abrir o arquivo");
      return;
  }

  fprintf(file, "ID do Paciente: %d\n", patient->id);
  fprintf(file, "Nome: %s\n", patient->name);
  fprintf(file, "Chegada: %d\n", patient->timestamp);

  fclose(file);
}

