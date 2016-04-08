#include "header.h"

extern char color[10][10];

/*
To clear scanf buffer to avoid prob
*/ 
void clear(void)
{
	while(getchar() != '\n')
		continue;
}

/*
To clear file buffer fp to avoi prob
*/
void clearf(FILE *fp)
{
	while(getc(fp) != '\n')
		continue;
}

/*
Initializes all slots of all days so that all slots are empty
slot 3 is always reserved for break
dept *d1 => department struct
int x => class of dept
*/
void initialize_slots(dept *d1, int x)
{
	int i = 0, j = 0;
	while(i < 5)
	{
		j = 0;
		while(j < d1->years[x].w.no_slots)
		{

			if(j == (d1->years[x].w.no_slots / 2))
			{
				d1->years[x].w.days[i].slots[j].s_id = -1;
				d1->years[x].w.days[i].slots[j].t_id = -1;
				d1->years[x].w.days[i].slots[j].status = 1;
			}	
			else	
			{
				d1->years[x].w.days[i].slots[j].s_id = -1;
				d1->years[x].w.days[i].slots[j].t_id = -1;
				d1->years[x].w.days[i].slots[j].status = 0;				
			}
			j++;
		}
		i++;
	}
}

void initialize_allteachtt(dept *d1)
{
	int i = 0, j = 0, t = 0;
	while(t < d1->t_count)
	{
		d1->teachers[t].w.no_slots = d1->years[0].w.no_slots;
		i = 0;
		while(i < 5)
		{
			j = 0;
			while(j < d1->teachers[t].w.no_slots)
			{

				if(j == (d1->teachers[t].w.no_slots / 2))
				{
					d1->teachers[t].w.days[i].slots[j].s_id = -1;
					d1->teachers[t].w.days[i].slots[j].t_id = -1;
					d1->teachers[t].w.days[i].slots[j].status = 1;
				}	
				else	
				{
					d1->teachers[t].w.days[i].slots[j].s_id = -1;
					d1->teachers[t].w.days[i].slots[j].t_id = -1;
					d1->teachers[t].w.days[i].slots[j].status = 0;				
				}
				j++;
			}
			i++;
		}
		t++;
	}
}

/*
initializes day limit of each subj to 0
dept *d1 => department struct
int yr_count => no. of classes in dept
*/
void init_dayl(dept *d1, int yr_count)
{
	int i, j, k;
	i = 0;
	while(i < yr_count)
	{
		j = 0;
		while(j < d1->years[i].s_count)
		{
			k = 0;
			while(k < 5)
			{
				d1->years[i].subjects[j].day_limit[k] = 0;
				k++;
			}	
			j++;
		}
		i++;
	}
}

/*
Initializes day limit of all 5 days of each teacher to 0
*/
void init_daylt(dept *d1)
{
	int i = 0, j = 0;
	while(i < d1->t_count)
	{
		j = 0;
		while(j < 5)
		{
			d1->teachers[i].day_limit[j] = 0;
			j++;
		}
		i++;
	}
}

/*
Returns index of teachers array of dept d1 whose t_id is equal to input t_id
*/
int returnIndexOnId(dept *d1, int t_id)
{
	int i = 0;
	while(i < d1->t_count)
	{
		if(d1->teachers[i].t_id == t_id)
			return i;
		i++;
	}
	return -1;
}

/*
Takes ip of teacher from file entered
FILE *fp => file ptr of ip file
dept *d1 => department struct
returns 1 on successful read
returns err no on unsuccessful read
*/
int teacher_ip(FILE *fp, dept *d1)
{
	int i = 0;
	char tfile[10];
	printf("\nEnter the teacher file: ");
	scanf("%s", tfile);
	clear();

	fp = fopen(tfile, "r");
	if(fp == NULL) {
		perror("fopen failed");
		return errno;
	}

	fscanf(fp, "%d", &(d1->t_count));
	clearf(fp);

	i = 0;

	//taking details of d1.t_count teachers
	while(i < d1->t_count)
	{
		fscanf(fp, "%d, %[^\n,]", &(d1->teachers[i].t_id), d1->teachers[i].t_name);
		clearf(fp);
	
		i++;
	}
	fclose(fp);
	return 1;
}


int checkDuplicateTeachers(dept *d1)
{
	int i = 0, j = 0;
	while(i < d1->t_count)
	{
		j = i + 1;
		while(j < d1->t_count)
		{
			if(d1->teachers[i].t_id == d1->teachers[j].t_id)
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

/*
Takes ip of classes and courses from file entered
FILE *fp => file ptr of ip file
dept *d1 => department struct
returns 1 on successful read
returns err no on unsuccessful read
*/
int class_course_ip(FILE *fp, dept *d1, int no_slots)
{
	int i = 0, j = 0, c_i = 0, yr_opt = 0;
	char cfile[10];
	printf("\n\nEnter the class and course file: ");
	scanf("%s", cfile);
	clear();	

	fp = fopen(cfile, "r");
	if(fp == NULL) {
		perror("fopen failed");
		return errno;
	}

	fscanf(fp, "%d", &(d1->yr_count));
	clearf(fp);

	d1->years = (year *)malloc(sizeof(year) * d1->yr_count);
	
	i = 0;

	yr_opt = 0;

	while(yr_opt < d1->yr_count)
	{
		d1->years[yr_opt].w.no_slots = no_slots;

		fscanf(fp, "%[^\n,], %d", d1->years[yr_opt].yr_name, &(d1->years[yr_opt].s_count));
		clearf(fp);
		i = 0;
		d1->years[yr_opt].tot_credits = 0;

		//taking details of each course
		while(i < d1->years[yr_opt].s_count)
		{

			fscanf(fp, "%d, %[^\n,], %d, %c, %d", &(d1->years[yr_opt].subjects[i].s_id), d1->years[yr_opt].subjects[i].s_name, &(d1->years[yr_opt].subjects[i].credits), &(d1->years[yr_opt].subjects[i].type), &(d1->years[yr_opt].subjects[i].t_id));
			clearf(fp);

			d1->years[yr_opt].tot_credits = d1->years[yr_opt].tot_credits + d1->years[yr_opt].subjects[i].credits;


			c_i = i % 6;	//to assign a colour to each course
			strcpy(d1->years[yr_opt].subjects[i].color, color[c_i]);
		
			j = 0;
			//initialize each day each subj to 0, each subj max 1 lec per day
			while(j < 5)
			{
				d1->years[yr_opt].subjects[i].day_limit[j] = 0;
				j++;
			}
		
			i++;
		}

		yr_opt++;
	}

	fclose(fp);
	return 1;
}



int checkDuplicateCourses(dept *d1)
{
	int i = 0, j = 0, k = 0;
	while(i < d1->yr_count)
	{
		while(j < d1->years[i].s_count)
		{
			k = j + 1;
			while(k < d1->years[i].s_count)
			{
				if(d1->years[i].subjects[k].s_id == d1->years[i].subjects[j].s_id)
					return 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return 0;
}

/*
Checks for any error in data provided through file
Returns 1 if error found else retuens 0
*/
int check_errors(dept *d1)
{
	int i = 0;
	if(checkDuplicateTeachers(d1))
	{
		printf("\n\n\tERROR! Teacher id duplicated\n\n");
		return 1;
	}

	if(checkDuplicateCourses(d1))
	{
		printf("\n\n\tERROR! Course id duplicated\n\n");
		return 1;
	}

	while(i < d1->yr_count)
	{
		if(d1->years[i].tot_credits > 5 * (d1->years[i].w.no_slots - 1))
		{
			//total no of credits cannot be more than total slots in 1 week
			printf("\n\n\tERROR! Total number of courses is more than total number of slots in a week for\n\tclass %s", d1->years[i].yr_name);
			printf("\n\tMake required changes in course file.\n\n");
			return 1;

		}
		i++;
	}
	return 0;
}

/*
Generates timetable using huristic and backtracking algo
Day k and Slot l are generated randomly
dept *d1 => department struct
Returns 0 on successful generation
Returns 1 if error or loop goes on continuously
*/
int makett(dept *d1)
{
	int yr_opt = 0, index, loop = 0;
	int i, j, k, l, m, y, temp, cre;
	int f, f1, f2;
	char try_again = 'Y';

	yr_opt = 0;
	init_dayl(d1, d1->yr_count);

	init_daylt(d1); 
	
	initialize_allteachtt(d1);

	while(yr_opt < d1->yr_count)
	{
		initialize_slots(d1, yr_opt);

		i = 0;
		m = yr_opt;
		while(i < d1->years[yr_opt].s_count)
		{
			j = 0;
			k = 0;

			loop = 0;
			while(j < d1->years[yr_opt].subjects[i].credits)
			{

				//max loop can run for 50000 times, if exceeded shows error and returns from func
				if(loop > 50000)
				{
					printf("\n\n\tERROR! Improper mapping of course & teacher data for class %s\n\tTimetable cannot be generated further\n\n", d1->years[yr_opt].yr_name);
					return 1;
				}

				k = random() % 5;	//generating random day
				if(d1->years[yr_opt].subjects[i].day_limit[k] == 0)
				{
					l = random() % d1->years[yr_opt].w.no_slots;		//generating random slot

					while(l == d1->years[yr_opt].w.no_slots / 2)		//middle slot reserved for break only
						l = random() % d1->years[yr_opt].w.no_slots;

					index = returnIndexOnId(d1, d1->years[m].subjects[i].t_id);

					//if lec is of 'T' type, no need of comtinuous slots
					if(d1->years[yr_opt].subjects[i].type == 'T')
					{

						f = 1, y = 0;
						while(y < m)
						{
							//checks if slot is already occupied by same teacher
							if(d1->years[y].w.days[k].slots[l].t_id == d1->years[m].subjects[i].t_id)
							{
								f = 0;
								break;
							}
							y++;
						}

						index = returnIndexOnId(d1, d1->years[m].subjects[i].t_id);

				
						//check status of slot and flag f and day limit < 3
						if(d1->years[yr_opt].w.days[k].slots[l].status == 0 && f && d1->teachers[index].day_limit[k] < 3)
						{		
							d1->years[yr_opt].w.days[k].slots[l].status = 1;
							d1->teachers[index].w.days[k].slots[l].status = 1;

							d1->years[yr_opt].w.days[k].slots[l].s_id = d1->years[yr_opt].subjects[i].s_id;
							d1->teachers[index].w.days[k].slots[l].s_id = d1->years[yr_opt].subjects[i].s_id;

							d1->years[yr_opt].w.days[k].slots[l].t_id = d1->years[yr_opt].subjects[i].t_id;
							d1->teachers[index].w.days[k].slots[l].t_id = d1->years[yr_opt].subjects[i].t_id;

							d1->years[yr_opt].w.days[k].slots[l].type = d1->years[yr_opt].subjects[i].type;
							d1->teachers[index].w.days[k].slots[l].type = d1->years[yr_opt].subjects[i].type;

							d1->teachers[index].w.days[k].slots[l].yr_id = yr_opt + 1;

							strcpy(d1->years[yr_opt].w.days[k].slots[l].color, d1->years[yr_opt].subjects[i].color); 
							strcpy(d1->teachers[index].w.days[k].slots[l].color, d1->years[yr_opt].subjects[i].color); 

							d1->years[yr_opt].subjects[i].day_limit[k] = 1;
							d1->teachers[index].day_limit[k]++;
							j++;
						}
					}

					//if course is of 'L' type, practicals need continuous slots
					else
					{
						temp = l;
						f1 = 1;
						cre = 0;

						//checks for continuous credits no. of slots (f1 flag)
						while(cre < d1->years[yr_opt].subjects[i].credits)
						{
						
							if(d1->years[yr_opt].w.days[k].slots[temp].status == 1 || temp >= d1->years[yr_opt].w.no_slots)
							{
								f1 = 0;
								break;
							}

							temp++;
							cre++;
						}

						y = 0;
						temp = l;
						f2 = 1;
						//checks if teacher is available at that slots
						while(y < m && f1)
						{
							cre = 0;
							temp = l; 
							//checks if slot is already occupied by same teacher
							while(cre < d1->years[yr_opt].subjects[i].credits)
							{
							
								if(d1->years[y].w.days[k].slots[temp].t_id == d1->years[m].subjects[i].t_id)
								{
									f2 = 0;
									break;
								}
							
								cre++;
								temp++;	
							}
							if(f2 == 0)
								break;
							y++;
						}

						if(f1 && f2)
						{
							cre = 0;
							temp = l;

							//assigns slots to practicals
							while(cre < d1->years[yr_opt].subjects[i].credits)
							{		
					
								d1->years[yr_opt].w.days[k].slots[temp].status = 1;
								d1->teachers[index].w.days[k].slots[temp].status = 1;

								d1->years[yr_opt].w.days[k].slots[temp].s_id = d1->years[yr_opt].subjects[i].s_id;
								d1->teachers[index].w.days[k].slots[temp].s_id = d1->years[yr_opt].subjects[i].s_id;
								d1->years[yr_opt].w.days[k].slots[temp].t_id = d1->years[yr_opt].subjects[i].t_id;
								d1->teachers[index].w.days[k].slots[temp].t_id = d1->years[yr_opt].subjects[i].t_id;
								d1->years[yr_opt].w.days[k].slots[temp].type = d1->years[yr_opt].subjects[i].type;
								d1->teachers[index].w.days[k].slots[temp].type = d1->years[yr_opt].subjects[i].type;
								strcpy(d1->years[yr_opt].w.days[k].slots[temp].color, d1->years[yr_opt].subjects[i].color); 
								strcpy(d1->teachers[index].w.days[k].slots[temp].color, d1->years[yr_opt].subjects[i].color); 

								d1->teachers[index].w.days[k].slots[temp].yr_id = yr_opt + 1;

								d1->years[yr_opt].subjects[i].day_limit[k] = 1;
								j++;
								temp++;
								cre++;
							}
						}	//end of if(f1 && f2)
					
					}	//end of else
				

				}	//end of if(d1->years[yr_opt].subjects[i].day_limit[k] == 0)
				loop++;
			}	//end of while(j < d1->years[yr_opt].subjects[i].credits)
		
			i++;
		}	//end of while(i < d1->years[yr_opt].s_count)
			
		yr_opt++;
	}	//end of while(yr_opt < d1->yr_count)

	return 0;
}


