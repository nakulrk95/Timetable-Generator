#include "header.h"

extern char color[10][10];

/*
Prints teacher detail of the dept d1
*/
void print_teachers(dept *d1)
{
	int i = 0;
	printf("\nTeacher details:\n");

	printf("\n\tId\t\tName");
	while(i < d1->t_count)
	{
		printf("\n\t%d\t\t%s", d1->teachers[i].t_id, d1->teachers[i].t_name);
	
		i++;
	}

}

/*
Prints course details of teachers of the dept d1 to file pointd by fq 
*/
void fprint_teachers(dept *d1, FILE *fq)
{
	int i = 0;
	fprintf(fq, "\nTeacher details:\n");

	fprintf(fq, "\n\tId\t\tName");
	while(i < d1->t_count)
	{
		fprintf(fq, "\n\t%d\t\t%s", d1->teachers[i].t_id, d1->teachers[i].t_name);
	
		i++;
	}
	fprintf(fq, "\n\n");

}

/*
Prints course details of each class of the dept d1
*/
void print_courses(dept *d1)
{
	int yr_opt = 0, i = 0;
	while(yr_opt < d1->yr_count)
	{
		printf("\n\nClass %s(%d): ", d1->years[yr_opt].yr_name, yr_opt + 1);
		printf("\n\t\tCourse Id\tName\t\tCredits\t\tTeacher Id");

		i = 0;
		while(i < d1->years[yr_opt].s_count)
		{
			printf("\n\t\t%d\t\t%s\t\t   %d\t\t    %d", d1->years[yr_opt].subjects[i].s_id, d1->years[yr_opt].subjects[i].s_name, 					d1->years[yr_opt].subjects[i].credits, d1->years[yr_opt].subjects[i].t_id);
	
			i++;
		}
		yr_opt++;
	}
}

/*
Prints course details of each class of the dept d1 to the file pointd by fq
*/
void fprint_courses(dept *d1, FILE *fq)
{
	int yr_opt = 0, i = 0;
	while(yr_opt < d1->yr_count)
	{
		fprintf(fq, "\n\nClass %s(%d): ", d1->years[yr_opt].yr_name, yr_opt + 1);
		fprintf(fq, "\n\t\tCourse Id\tName\t\tCredits\t\tTeacher Id");

		i = 0;
		while(i < d1->years[yr_opt].s_count)
		{
			fprintf(fq, "\n\t\t%d\t\t%s\t\t   %d\t\t    %d", d1->years[yr_opt].subjects[i].s_id, d1->years			[yr_opt].subjects[i].s_name, d1->years[yr_opt].subjects[i].credits, d1->years[yr_opt].subjects[i].t_id);
	
			i++;
		}
		yr_opt++;
	}
	fprintf(fq, "\n\n--------------------------------------------------------------------------------------------------------------------------");
}

/*
Prints timetable of all classes on terminal and in file 'tt.txt' by default
dept *d1 => department struct
FILE *fq => file ptr of file in which tt is written
int attempt => is used to show how many rearrangements made in timetable
*/
void printtt(dept *d1, FILE *fq, int attempt)
{
	int yr_opt = 0;
	int i, j;

	while(yr_opt < d1->yr_count)
	{
		i = 0, j = 0;
		//printing tt
		printf("\n\n--------------------------------------------------------------------------------------------------------------------------");
		printf("\nTimetable for class %s:\n\n", d1->years[yr_opt].yr_name);

		fprintf(fq, "\n\n--------------------------------------------------------------------------------------------------------------------------");
		fprintf(fq, "\nTimetable for class %s:\n\n", d1->years[yr_opt].yr_name);

		while(j < d1->years[yr_opt].w.no_slots)
		{
			printf("\tSlot%d ", j + 1);
			fprintf(fq, "\tSlot%d ", j + 1);
			j++;
		}
	
		while(i < 5)
		{
			printf("\n\nDay %d|", i + 1);
			fprintf(fq, "\n\nDay %d|", i + 1);
			j = 0;	
			while(j < d1->years[yr_opt].w.no_slots)
			{

				if(d1->years[yr_opt].w.days[i].slots[j].status == 1)
				{

					if(j != d1->years[yr_opt].w.no_slots / 2)
					{
						printf("%s\tC%d", d1->years[yr_opt].w.days[i].slots[j].color, d1->years[yr_opt].w.days[i].slots[j].s_id);
						fprintf(fq, "\tC%d", d1->years[yr_opt].w.days[i].slots[j].s_id);

						printf(",T%d%s", d1->years[yr_opt].w.days[i].slots[j].t_id, color[6]);
						fprintf(fq, ",T%d", d1->years[yr_opt].w.days[i].slots[j].t_id);
					}

					else
					{
						printf("\t(Break)");
						fprintf(fq, "\t(Break)");				
					}
				}
				else
				{
					printf("\t  - ");
					fprintf(fq, "\t  - ");
				}
				j++;
			}
			i++;
		}
			
		printf("\n--------------------------------------------------------------------------------------------------------------------------");
		printf("\n");


		fprintf(fq, "\n--------------------------------------------------------------------------------------------------------------------------");
		fprintf(fq, "\n");
		yr_opt++;
	}
	
}

/*
Prints tt of teacher with teacher-id equals id for his respective subjects and classes
If invalid id, error msg displayed
*/
void printSingleTeachertt(dept *d1, int id)
{
		int i = 0, j = 0;
		int index = returnIndexOnId(d1, id);
		if(index == -1)
		{
			printf("\n\tERROR! Invalid teacher id");
			return;
		}

		printf("\n\n--------------------------------------------------------------------------------------------------------------------------");
		printf("\nTimetable for %s:\n\n", d1->teachers[index].t_name);

		while(j < d1->teachers[index].w.no_slots)
		{
			printf("\tSlot%d ", j + 1);
			//fprintf(fq, "\tSlot%d ", j + 1);
			j++;
		}

		i = 0;
		while(i < 5)
		{
			printf("\n\nDay %d|", i + 1);
			//fprintf(fq, "\n\nDay %d|", i + 1);
			j = 0;	
			while(j < d1->teachers[index].w.no_slots)
			{

				if(d1->teachers[index].w.days[i].slots[j].status == 1)
				{

					if(j != d1->teachers[index].w.no_slots / 2)
					{
						printf("%s\tC%d", d1->teachers[index].w.days[i].slots[j].color, d1->teachers[index].w.days[i].slots[j].s_id);
						//fprintf(fq, "\tC%d", d1->years[yr_opt].w.days[i].slots[j].s_id);

						printf(",Y%d%s", d1->teachers[index].w.days[i].slots[j].yr_id, color[6]);
						//fprintf(fq, ",T%d", d1->years[yr_opt].w.days[i].slots[j].t_id);
					}

					else
					{
						printf("\t(Break)");
						//fprintf(fq, "\t(Break)");				
					}
				}
				else
				{
					printf("\t  - ");
					//fprintf(fq, "\t  - ");
				}
				j++;
			}
			i++;
		}

		printf("\n--------------------------------------------------------------------------------------------------------------------------");
		printf("\n");

}

/*
Prints tt of teacher with teacher-id equals id for his respective subjects and classes
in a file pointed by fq
*/
void fprintSingleTeachertt(dept *d1, int id, FILE *fq)
{
		int i = 0, j = 0;
		int index = returnIndexOnId(d1, id);
		if(index == -1)
		{
			printf("\n\tERROR! Invalid teacher id");
			return;
		}

		fprintf(fq, "\n\n--------------------------------------------------------------------------------------------------------------------------");
		fprintf(fq, "\nTimetable for %s:\n\n", d1->teachers[index].t_name);

		while(j < d1->teachers[index].w.no_slots)
		{
			//printf("\tSlot%d ", j + 1);
			fprintf(fq, "\tSlot%d ", j + 1);
			j++;
		}

		i = 0;
		while(i < 5)
		{
			//printf("\n\nDay %d|", i + 1);
			fprintf(fq, "\n\nDay %d|", i + 1);
			j = 0;	
			while(j < d1->teachers[index].w.no_slots)
			{

				if(d1->teachers[index].w.days[i].slots[j].status == 1)
				{

					if(j != d1->teachers[index].w.no_slots / 2)
					{
						//printf("%s\tC%d", d1->teachers[index].w.days[i].slots[j].color, d1->teachers[index].w.days[i].slots[j].s_id);
						fprintf(fq, "\tC%d", d1->teachers[index].w.days[i].slots[j].s_id);

						//printf(",Y%d%s", d1->teachers[index].w.days[i].slots[j].yr_id, color[6]);
						fprintf(fq, ",Y%d", d1->teachers[index].w.days[i].slots[j].yr_id);
					}

					else
					{
						//printf("\t(Break)");
						fprintf(fq, "\t(Break)");				
					}
				}
				else
				{
					//printf("\t  - ");
					fprintf(fq, "\t  - ");
				}
				j++;
			}
			i++;
		}

		fprintf(fq, "\n--------------------------------------------------------------------------------------------------------------------------");
		fprintf(fq, "\n");

}

/*
Displays teacher list and asks for teacher-id whose tt to be displayed(id)
Prints tt of teacher with teacher-id equals id for his respective subjects and classes
Can continue till -1 entered as id
*/
void printTeachertt(dept *d1)
{
	int id;
	print_teachers(d1);
	printf("\n\nEnter the teacher id whose tt to be displayed(-1 to exit): ");
	scanf("%d", &id);
	clear();
	while(id != -1)
	{
		printSingleTeachertt(d1, id);

		printf("\n\nEnter the teacher id whose tt to be displayed(-1 to exit): ");
		scanf("%d", &id);
		clear();
	}

}

/*
Prints tt of all teachers with for his respective subjects and classes
in file pointed by fq
*/
void fprintAllTeacherstt(dept *d1, FILE *fq)
{
	int t = 0;
	while(t < d1->t_count)
	{
		fprintSingleTeachertt(d1, d1->teachers[t].t_id, fq);
		t++;
	}
}
