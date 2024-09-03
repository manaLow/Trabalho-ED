// Cabe�alho criado
#include "exam2.h"

#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o de estrutura do Condition_IA
struct condition_IA
{
  int id;
  char *name_condition;
  int severity;
};

// Estrutura do exame
struct exam
{
  int id;
  int patient_id;
  int rx_id;
  condition_IA *condition;
  int timestamp;
};

// Defini��o da estrutura da fila dos exames
struct qExam
{
  int count;
  qnExam *front;
  qnExam *rear;
};

// Defini��o da estrutura dos n�s da fila dos exames
struct qnExam
{
  Exam *info;
  qnExam *next;
  qnExam *prev;
};

// Cria��o de filas vazias para exames
qExam *create_qExam()
{
  qExam *q = (qExam *)malloc(sizeof(qExam));
  // Verifica se alocou corretament
  if (q == NULL)
  {
    printf("Erro ao alocar mem�ria para a fila vazia.\n");
    return NULL;
  }
  q->front = q->rear = NULL;
  q->count = 0;
  return q;
}

// Função para verificar se a fila de exames está vazia
int fila_vazia_exam(qExam *q)
{
  return q->front == NULL;
}

// Criar exame
Exam *create_exam(int id, int patient_id, int rx_id, condition_IA *condition, int timestamp)
{
  Exam *new_exam = (Exam *)malloc(sizeof(Exam)); // Aloca��o de mam�ria pra estrutura
  // Verifica se foi alocado
  if (new_exam == NULL)
  {
    printf("Erro ao alocar memria para o novo exame.");
    return NULL;
  }

  // Inicializar as variáveis do exame
  new_exam->id = id;
  new_exam->patient_id = patient_id;
  new_exam->rx_id = rx_id;
  new_exam->condition = condition;
  new_exam->timestamp = timestamp;
  arq_exam(new_exam, "db_exam.txt");
  return new_exam;
}

void destroy_exam(Exam *exame)
{
  if (exame != NULL)
  {
    if (exame->condition != NULL)
    {
      free(exame->condition);
    }
    free(exame);
  }
}

// Inserir exame na fila de exames de acordo com a severidade do paciente
void enqueue_qExam(qExam *q, Exam *exam)
{
  qnExam *node = (qnExam *)malloc(sizeof(qnExam));

  if (node == NULL)
  {
    printf("Erro ao alocar memória para o nó.\n");
    return;
  }

  node->info = exam;
  node->next = node->prev = NULL;

  // Se a fila estiver vazia, inserir como o primeiro n�
  if (fila_vazia_exam(q))
  {
    q->front = q->rear = node;
  }
  else
  {
    qnExam *temp = q->front;
    // Encontrar a posi��o correta para inserir o novo n�
    while (temp != NULL && node->info->condition->severity < temp->info->condition->severity)
    {
      temp = temp->next;
    }
    if (temp == q->front)
    {

      // Inserir no in�cio da fila
      node->next = q->front;
      q->front->prev = node;
      q->front = node;
    }
    else if (temp == NULL)
    {
      
      // Inserir no final da fila
      node->prev = q->rear;
      q->rear->next = node;
      q->rear = node;
    }
    else
    {
      
      // Inserir no meio da fila
      node->prev = temp->prev;
      node->next = temp;
      temp->prev->next = node;
      temp->prev = node;
    }
  }
 
  q->count++;
}

// Fun��o para tirar exame da fila
Exam *dqueue_qExam(qExam *q)
{

  Exam *p = q->front->info;
  qnExam *node = q->front;

  if (q->front != q->rear)
  {
    q->front = q->front->next;
  }
  else
  {
    q->front = q->rear = NULL;
  }
  q->count--;
  free(node);
  return p;
}


// Supondo que já existam as estruturas e funções para condição e alocação

// condition_IA *create_condition(int id, const char *name, int severity)
// {
//   condition_IA *cond = (condition_IA *)malloc(sizeof(condition_IA));
//   if (cond)
//   {
//     cond->id = id;
//     cond->name_condition = (char *)malloc(strlen(name) + 1);
//     if (cond->name_condition)
//     {
//       strcpy(cond->name_condition, name);
//     }
//     cond->severity = severity;
//   }
//   return cond;
// }

// Cria a Condition
condition_IA *create_condition(int id, const char *name, int gravity)
{
  condition_IA *new_condition = (condition_IA *)malloc(sizeof(condition_IA));

  if (new_condition == NULL){
    printf("Erro ao alocar memória para criar condição.");
    return NULL;
  }
  // Alocação de memória
  new_condition->id = id;
  new_condition->name_condition = strdup(name); // Reserva espaço de armazenamento para uma cópia da string name
  new_condition->severity = gravity;

  return new_condition;
}

condition_IA *get_condition()
{
  int id, severity;
  char *name;

  // Gera um número de 0 até 19
  int random_number = rand() % 20;

  // Atribui os valores com base no número aleatório
  if (random_number < 6)
  { // 30% de chance (0-5)
    id = 1;
    name = "Saúde Normal";
    severity = 1;
  }
  else if (random_number < 10)
  { // 20% de chance (6-9)
    id = 2;
    name = "Bronquite";
    severity = 2;
  }
  else if (random_number < 12)
  { // 10% de chance (10-11)
    id = 3;
    name = "Pneumonia";
    severity = 3;
  }
  else if (random_number < 14)
  { // 10% de chance (12-13)
    id = 4;
    name = "COVID";
    severity = 4;
  }
  else if (random_number < 15)
  { // 5% de chance (14)
    id = 5;
    name = "Embolia Pulmonar";
    severity = 4;
  }
  else if (random_number < 16)
  { // 5% de chance (15)
    id = 6;
    name = "Derrame Pleural";
    severity = 4;
  }
  else if (random_number < 17)
  { // 5% de chance (16)
    id = 7;
    name = "Fibrose Pulmonar";
    severity = 5;
  }
  else if (random_number < 18)
  { // 5% de chance (17)
    id = 8;
    name = "Tuberculose";
    severity = 5;
  }
  else
  { // 5% de chance (18-19)
    id = 9;
    name = "Câncer de Pulmão";
    severity = 6;
  }

  // Cria e retorna a condição
  return create_condition(id, name, severity);
}

// Arquiva exame no banco de dados
void arq_exam(Exam *exam, const char *filename)
{
  FILE *file = fopen(filename, "ab");
  if (file == NULL)
  {
    perror("Erro ao abrir o arquivo");
    return;
  }

  fprintf(file, "\nID do Exame: %d\n", exam->id);
  fprintf(file, "ID do Paciente: %d\n", exam->patient_id);
  fprintf(file, "ID da Máquina RX: %d\n", exam->rx_id);
  fprintf(file, "Timestamp: %d\n", exam->timestamp);
  fprintf(file, "Condição do Paciente: %s\n", exam->condition->name_condition);
  fprintf(file, "Gravidade: %d\n", exam->condition->severity);

  fclose(file);
}

// Retornar o horário da realização do exame
int get_exam_time(const Exam *exam)
{
  return exam->timestamp;
}
