#include "patient.h"
#include "functions.h"
#include "exam2.h"
#include "report.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

#define XR_MACHINE_QUANTITY 5
#define XR_MACHINE_DURATION 10
#define DOCTOR_DURATION 30

struct qExam
{
    int count;
    qnExam *front;
    qnExam *rear;
};

struct qPatient{
    int count;
	qnPatient* front;
	qnPatient* rear;
};


struct Patient
{
    int id;
    char *name;
    int timestamp;
};

struct condition_IA
{
    int id;
    char *name_condition;
    int severity;
};

struct exam
{
    int id;
    int patient_id;
    int rx_id;
    condition_IA *condition;
    int timestamp;
};

struct report
{
  int id;
  int exam_id;
  condition_IA* condition;
  int timestamp;
};

int main(void)
{
    setlocale(LC_ALL, "Portuguese"); // Permitir acentos
    srand(time(NULL));               // Inicializar o gerador de n�meros aleat�rios com a hora atual

    // Resetar os arquivos (em breve)

    // Inicializar simula��o de tempo
    int unid_t = 0;
    int total_t = 10000;

    // Inicializar vari�veis
    int id_p = 0;    // ID do paciente
    int id_e = 0;    // ID do exame
    int id_l = 0;    // ID do laudo
    int p_total = 0; // Quantidade total de pacientes

    // Variável para relatório
    int last_exam_id;   // Guardar o id do último exame feito
    int last_report_id; // Guardar o id do útimo laudo feito
    int count_exam_condition[9];
    int count_time_condition[9];
    int count_time_queue = 0;

    // Variáveis da struct
    Patient *next_patient;
    Exam *new_exam;

    // Criar arquivo vazio
    create_empty_files("db_patient.txt");
    create_empty_files("db_exam.txt");
    create_empty_files("db_report.txt");

    // Criar fila
    qPatient *fila_pacientes = create_qPatient(); // Fila de pacientes
    qExam *fila_exames = create_qExam();          // Fila de exames

    // Criar máquinas
    Patient *XRMachineManager[XR_MACHINE_QUANTITY] = {};
    int XRMachineManager_Timer[XR_MACHINE_QUANTITY];

    // Criar médico
    Exam *doctor = NULL;
    int Doctor_timer;

    printf("Iniciando o programa:\n\n\n");
    
    // Início da simulação
    while (unid_t < total_t)
    {

        double chance = rand() % 100; // Gerar número aleatório entre 0 e 99

        // Possibilidade do paciente aparecer no hospital
        if (chance <= 20)
        {

            char *nome = random_name();                               // Gerar nome aleatório
            Patient *paciente = create_patient(id_p++, nome, unid_t); // Criar paciente
            enqueue_qPatient(fila_pacientes, paciente);               // Inserir paciente na fila
            paciente = NULL;                                          // Resetar paciente

            p_total++;
        }

        // Avaliar a disponibilidade das máquinas
        for (int i = 0; i < XR_MACHINE_QUANTITY; i++)
        {
            if (XRMachineManager[i] == NULL && !fila_vazia(fila_pacientes))
            {
                Patient *next_patient = (Patient *)dqueue_qPatient(fila_pacientes); // Retira o próximo da paciente da fila
                // printf("Nome: %s.\n", next_patient->name); //TESTE
                XRMachineManager[i] = next_patient; // Aloca esse paciente para a máquina disponível
                // printf("Nome: %s.\n", XRMachineManager[i]->name); //TESTE
                XRMachineManager_Timer[i] = unid_t + XR_MACHINE_DURATION; // Tempo que terminar o procedimento
                // printf("Machine[%d]: %d unidade de tempo.\n", i, XRMachineManager_Timer[i]); //TESTE
            }
        }

        // Avaliar se algum exame j� terminou
        for (int i = 0; i < XR_MACHINE_QUANTITY; i++)
        {
            // Tempo atingido do procedimento
            if (XRMachineManager[i] != NULL && XRMachineManager_Timer[i] == unid_t)
            {
                next_patient = (Patient *)XRMachineManager[i]; // Recebe o paciente que estava na m�quina de raio-x
                // printf("\n\nExame terminado: %s.\n\n", next_patient->name);

                // Criar exame
                condition_IA *condition = get_condition(); // Gerar condition do IA

                // printf("Condition: %s, Severidade: %d\n\n", condition->name_condition, condition->severity); //TESTE (N�O EST� PRINTANDO)
                new_exam = create_exam(id_e++, id_p, (i + 1), condition, unid_t); // Criar exame com a condition fornecida pelo IA
                
                // printf("ID: %d, P.ID: %d, RXID: %d, Severidade: %d, Timestamp: %d \n\n", id_e, id_p, (i + 1), condition->severity, unid_t);
                enqueue_qExam(fila_exames, new_exam); // Inserir na fila de exames de acordo com a prioridade

                // printf("\n\nQuantidade de exames na fila: %d\n\n", fila_exames->count);
                last_exam_id = id_e;

                destroy_patient(next_patient); // Liberar a memória utilizada pelo paciente
                condition = NULL;
                new_exam = NULL;               // Resetando o valor do exame
                XRMachineManager[i] = NULL;    // Máquina disponibilizada novamente
                XRMachineManager_Timer[i] = 0; // Tempo zerado
            }
        }
        
        //Avaliar a disponibilidade do médico para receber um novo exame
        if (doctor == NULL && !fila_vazia_exam(fila_exames))
        {
            Exam *next_exam = (Exam *)dqueue_qExam(fila_exames);

            doctor = next_exam;
            // printf("Id do exame: %d\n", doctor->id);
            Doctor_timer = unid_t + DOCTOR_DURATION;
        }

        
        //Criação do laudo e atualização da disponibilidade do médico
        if (doctor != NULL && Doctor_timer == unid_t)
        {
            Report *new_report = create_report(id_l++, doctor, unid_t);
            
            last_report_id = id_l;
            // printf("Tempo do Novo Report: %d \n", new_report->timestamp);
            count_time_queue += unid_t - get_exam_time(doctor); //SOMAR TEMPO DE ESPERA NA FILA DE PRIORIDADE)
            
            count_exam_condition[doctor->condition->id-1] += 1;
            count_time_condition[doctor->condition->id-1] += unid_t - doctor->timestamp;
            destroy_report(new_report);
            
            doctor = NULL;
            Doctor_timer = 0;
        }

        unid_t++;
        //printf("time: %d\n", unid_t);
        if (unid_t % 100 == 0)
        {
            // relatorio_print(fila_pacientes, p_total, fila_exames, id_e, id_l, count_time_queue);
            sleep(2);
        }
    }
    relatorio_print(fila_pacientes, p_total, fila_exames, last_exam_id, last_report_id, count_time_queue);
    printf("TAnto de gnt na fila: %d", fila_pacientes->count);
    return 0;
}
