#ifndef REPORT_H
#define REPORT_H
#include "exam2.h"

typedef struct report Report;

Report *create_report(int id, Exam* exame, int timestamp);
void destroy_report(Report* report);
condition_IA* condition_check(Exam* exam);
void arq_report(Report *report, const char *filename);


#endif // REPORT_H
