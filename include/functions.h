#ifndef FUNCTIONS
#define FUNCTIONS

#include "patient.h"
#include "exam2.h"

void create_empty_files(const char* filename); //Criar arquivo vazio;
int fila_vazia (qPatient* q);//Verificar se a fila de paciente est� vazia;
char* random_name(); //Gerar nomes aleat�rios;
void relatorio_print(qPatient* qp, int total, qExam* qe, int last_exam_id,int last_report_id, int count_time_queue); //Imprimir relat�rio do hospital;

#endif
