#include "header.h"

char color[10][10];

int main()
{
	system("clear");
	printf("\n\n\t\t******** TIMETABLE GENERATOR ********\n");
	FILE *fp, *fq, *fq1, *fq2;
	
	char try_again = 'Y';
	
	dept d1;


	int attempt = 1, ret = 1, iserror = 0, no_slots;

	time_t tt;
	srandom(time(&tt));

	strcpy(color[0], "\x1b[31m");
	strcpy(color[1], "\x1b[32m");
	strcpy(color[2], "\x1b[33m");
	strcpy(color[3], "\x1b[34m");
	strcpy(color[4], "\x1b[35m");
	strcpy(color[5], "\x1b[36m");
	strcpy(color[6], "\x1b[0m");

	//tt.txt stores resultant dept timetables with attempt no.
	fq = fopen("Timetable.txt", "w");
	if(fq == NULL) {
		perror("fopen failed");
		return errno;
	}

	//Teachertt.txt stores tt of all teachers
	fq1 = fopen("Teachertt.txt", "w");
	if(fq1 == NULL) {
		perror("fopen failed");
		return errno;
	}

	//details.txt stores details of classes and courses
	fq2 = fopen("Details.txt", "w");
	if(fq2 == NULL) {
		perror("fopen failed");
		return errno;
	}


	printf("\nEnter the Dept name: ");
	scanf("%[^\n]", d1.dept_name);
	clear();
	
	printf("\nEnter no. of slots in a day(max 12): ");
	scanf("%d", &no_slots);
	clear();

	//no more than 12 slots allowed in a day
	while(no_slots > 12)
	{
		printf("\n\tERROR! Limit of 12 slots exceeded");
		printf("\nEnter no. of slots in a day(max 12): ");
		scanf("%d", &no_slots);
		clear();
	}

	fprintf(fq, "\nTimetable for %s dept:\n", d1.dept_name);

	ret = teacher_ip(fp, &d1);
	
	if(ret != 1)
	{
		fclose(fq);
		fclose(fq1);
		fclose(fq2);
		exit(1);
	}

	print_teachers(&d1);			//print teacher details
	fprint_teachers(&d1, fq);		//store tecaher details in file
	fprint_teachers(&d1, fq2);

	ret = class_course_ip(fp, &d1, no_slots);
	
	if(ret != 1)
	{
		fclose(fq);
		fclose(fq1);
		fclose(fq2);
		exit(1);
	}

	print_courses(&d1);			//print course details
	fprint_courses(&d1, fq);		//store tecaher details in file
	fprint_courses(&d1, fq2);

	while(try_again == 'Y' || try_again == 'y')
	{
		printf("\n\n\t\t\t\tPREPARING TIMETABLE.....\n\n");
		system("sleep 1");
		system("clear");
 
		iserror = check_errors(&d1);	//check for errors

		if(iserror)
		{
			fclose(fq);
			fclose(fq1);
			fclose(fq2);
			exit(1);
		}

		iserror = makett(&d1);		//if no errors, generate tt

		if(iserror)
		{
			fclose(fq);
			fclose(fq1);
			fclose(fq2);
			exit(1);
		}
		
		printf("\nATTEMPT %d:", attempt);
		fprintf(fq, "\nATTEMPT %d:", attempt);
		fprintf(fq1, "\nATTEMPT %d:", attempt);
		
		printtt(&d1, fq, attempt);

		fprintAllTeacherstt(&d1, fq1);

		//if u want to rearrange tt; earlier tt will be as it is in the tt.txt file with attempt no. 
		printf("\n\nRearrange timetable? Press 'Y' for Yes and 'N' for No: ");
		try_again = getchar();
		clear();
	
		attempt++;
	}
	
	fclose(fq);
	fclose(fq1);
	fclose(fq2);

	printTeachertt(&d1);			//To display tt of particular teacher on terminal

	printf("\n(Check Timetable.txt, Details.txt, Teachertt.txt for results)\n\n");

	return 0;
}
