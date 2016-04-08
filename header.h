#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include "structure.h"

void clear(void);
void clearf(FILE *fp);

void initialize_slots(dept *d1, int x);
void initialize_allteachtt(dept *d1);
void init_dayl(dept *d1, int yr_count);
void init_daylt(dept *d1);

int class_course_ip(FILE *fp, dept *d1, int no_slots);
int teacher_ip(FILE *fp, dept *d1);

int makett(dept *d1);

void printtt(dept *d1, FILE *fq, int attempt);
void print_courses(dept *d1);
void print_teachers(dept *d1);
void printSingleTeachertt(dept *d1, int id);
void printTeachertt(dept *d1);

void fprintSingleTeachertt(dept *d1, int id, FILE *fq);
void fprint_courses(dept *d1, FILE *fq);
void fprint_teachers(dept *d1, FILE *fq);
void fprintAllTeacherstt(dept *d1, FILE *fq);

int returnIndexOnId(dept *d1, int t_id);

int check_errors(dept *d1);
int checkDuplicateCourses(dept *d1);
int checkDuplicateTeachers(dept *d1);
