typedef struct slot {
	int s_id;		//course id
	int t_id;		//teacher id
	int yr_id;
	int status;		//if status = 1 slot occupied, if 0 empty
	char color[10];		//to define color
	char type;
}slot;

typedef struct day {
	slot slots[20];		//slots in a day
	int count;
}day;

typedef struct week {
	int no_slots;
	day days[5];		//5 working days a week
}week;

typedef struct teacher {
	char t_name[30];	//teacher name
	int t_id;		//teacher id
	int day_limit[5];	//max on 1 day teacher can take 3 courses
	week w;
}teacher;

typedef struct subject {
	char s_name[30];	//course name
	int s_id;		//course id
	int credits;		//no. of credits
	int t_id;		//teacher id who teaches this course
	int day_limit[5];	//every course has day limit 1 nd 0
	char color[10];
	char type;		//type 'T' theory, 'L' lab
}subject;


typedef struct year {
	char yr_name[30];	//class name
	week w;			//week represents tt
	int s_count;		//no. of courses		
	subject subjects[10];	//max 10 courses in a class
	int tot_credits;
}year;

typedef struct dept {
	char dept_name[30];	//department name
	int yr_count;		//total no. of classes in dept
	year *years;		//class array
	int t_count;		//no. of teachers in dept
	teacher teachers[20];	//max 20 teachers
}dept;


