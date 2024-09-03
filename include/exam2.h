#ifndef EXAM
#define EXAM

typedef struct condition_IA condition_IA;
typedef struct exam Exam;
typedef struct qExam qExam;
typedef struct qnExam qnExam;

qExam *create_qExam(); //Criar fila de exames;
int fila_vazia_exam(qExam *q); //Verificar se a fila de exames est� vazia;
Exam *create_exam(int id, int patient_id, int rx_id, condition_IA* condition, int timestamp); //Criar e inicializar exame;
void destroy_exam(Exam* exame); // Destruir exames
void enqueue_qExam(qExam *q, Exam *exam); //Inserir exame na fila de exame;
Exam *dqueue_qExam(qExam *q); //Retirar exame da fila de exame;
condition_IA* get_condition(); //Retornar uma condi��o aleat�ria;
void arq_exam(Exam *exam, const char *filename); //Arquivar exame no banco de dados;
int get_exam_time(const Exam* exam); //Retornar o momento em que o exame foi realizado;
condition_IA* create_condition(int id, const char *name, int gravity); //Criar condition;

#endif
