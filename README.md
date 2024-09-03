# Simulação de Exames de Raio-X e Diagnóstico (PARTE 2)

> _Grupo M: Kevin Kliss e Manuely Lemos_
## Descrição
A segunda parte do projeto tem por objetivo simular uma situação em que pacientes chegam ao hospital e, de acordo com a urgência dos seus pré diagnósticos, são organizados em uma fila virtual de atendimento. Além dos tipos abstratos de dados, ainda utilizados na primeira parte do projeto, serão implementadas filas e arquivos que armazenarão dados ao longo de todo percurso do paciente até a entrega do laudo final.

## Estrutura do Projeto
.
ESTDAD/ ---> Pasta

|_  main.c # Arquivo principal

|_ Makefile

|_  include/ ---> Pasta com os cabeçalhos

|____   exam2.h

|____   functions.h

|____   patient.h

|____   report.h

| _ src/ ---> Pasta com as implementações

|____   exam2.c

|____   functions.c

|____   patient.c

|____   report.c


|_ README.md # Este arquivo README

## Execução do Projeto

### Pré-requisitos
Certifique-se de ter os seguintes pacotes instalados:

- GCC (ou outro compilador C)
- Git

Para instalar o GCC e Git, você pode usar os seguintes comandos no seu terminal (para sistemas baseados em Debian/Ubuntu):
 ```
sudo apt update
sudo apt install gcc git
 ```

### Instalação
#### 1. Clone o repositório
Primeiro, clone o repositório do GitHub para seu ambiente local:

 ```
 git clone https://github.com/manaLow/Trabalho-ED.git
 cd Trabalho-ED
 ```

#### 2. Compile o projeto
Depois de clonar o repositório, compile o projeto usando o GCC. Execute o seguinte comando:

 ```
 make
 ```

#### 3. Executar o programa:
Para executar o programa compilado, use o seguinte comando:

 ```
 ./main
 ```

 ## Funcionalidades

### TADs

#### Patient

 - **create_patient:** Criação de paciente.
 - **create_qPatient:** Criação de fila vazia para pacientes.
 - **fila_vazia:** Verificar se a fila de paciente está vazia.
 - **enqueue_qPatient:** Inserir paciente na fila.
 - **dqueue_qPatient:** Retirar paciente da fila.
 - **arq_patient:** Gravar paciente no banco de dados.
 - **destroy_patient:** Libera a memória alocada para a estrutura do paciente.

#### Exam

- **create_qExam:** Criar fila vazia de exames.
- **fila_vazia_exam:** Verificar se a fila de exame está vazia
- **create_exam:** Criação de exame.
- **destroy_exam:** Elimina exame.
- **enqueue_qExam:** Inserir exame na fila de acordo com a prioridade.
- **dqueue_qExam:** Retirar exame da fila.
- **get_condition:** Retornar uma condição aleatória
- **arq_exam:** Gravar exame no banco de dados.
- **get_exam_time:** Retornar o momento que o exame foi realizado.
- **create_condition:** Criar condition.

#### Report

- **create_report:** Criar laudo.
- **destroy_report:** Eliminar laudo.
- **condition_check** Probabilidade da IA acertar o diagnóstico.
- **arq_report:** Gravar report no banco de dados.

#### Functions

- **create_empty_files:** Criar arquivo vazio.
- **fila_vazia:** Verificar se fila está vazia.
- **random_name:** Gerar nomes aleatórios.
- **get_condition_name_by_id:** Obter o nome da condição.
- **relatorio_print:** Imprimir o relatório
