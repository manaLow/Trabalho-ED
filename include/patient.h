#ifndef PATIENT
#define PATIENT

typedef struct Patient Patient;
typedef struct qPatient qPatient;
typedef struct qnPatient qnPatient;

Patient* create_patient(int id, const char *name, int timestamp); //Alocar, inicializar e arquivar paciente;
qPatient* create_qPatient(); //Criação de filas vazias para pacientes;
int fila_vazia (qPatient* q); //Verificar se a fila de pacientes está vazia;
void enqueue_qPatient(qPatient* q, Patient* patient); //Inserir paciente na fila;
Patient* dqueue_qPatient(qPatient* q); //Excluir paciente da fila;
void arq_patient(Patient* patient, const char* filename); //Arquivar paciente no banco de dados;
void destroy_patient(Patient* patient); //Eliminar paciente;

#endif
