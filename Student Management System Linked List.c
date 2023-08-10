
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct studentNode_tag
{
	char name[50];
	char enrollment_no[11];
	int roll_no;
	char courses[5][2];
	struct studentNode_tag* next;
}studentNode;

typedef struct courseNode_tag
{
	char name[50];
	char enrollment_no[11];
	int roll_no;
	struct courseNode_tag* next;
}courseNode;

typedef struct classCourse_tag
{
	int f;
	char c;
}classCourse;

typedef struct examClass_tag
{
	int f;
	char c[3];
}examClass;

typedef struct classNode_tag
{
	char name[50];
	int no_of_seats;
	classCourse solts[5];
	examClass exam[5];
}classNode;

int checkVaildCourses(studentNode* ptr)
{
	int freq[5]={0,0,0,0,0};
    int flag=1,i,slot;
    char course[2];
    for(i=0; i<5&&flag==1;i++)
    {
    	strcpy(course,ptr->courses[i]);
		slot=(course[0]%5)+1;
        freq[slot-1]=freq[slot-1]+1;
        if(freq[slot-1]>1)
        {
            flag=0;
        }
    }
    if(flag==0)
    {
    	printf("%s took more than one course in slot %d\n",ptr->enrollment_no,slot);
	}
	return flag;
}

int indexYear(char a)
{
	int ret_val;
	if(a=='1')
	{
		ret_val=0;
	}
	else if(a=='0')
	{
		ret_val=1;
	}
	else
	{
		ret_val=2;
	}
	return ret_val;
}

void insertStudentData(studentNode* ptr,studentNode* studentList[])
{
	studentNode* n=studentList[indexYear(ptr->enrollment_no[3])];
	studentNode *t=NULL,*p;
	if(n==NULL)
	{
		n=ptr;
	}
	else
	{
		p=n;
		while(p!=NULL && p->roll_no<ptr->roll_no)
		{
			t=p;
			p=p->next;
		}
		if(t==NULL)
		{
			ptr->next=p;
			n=ptr;
		}
		else
		{
			ptr->next=p;
			t->next=ptr;
		}
	}
	studentList[indexYear(ptr->enrollment_no[3])]=n;
}

void insertStudentDataInCourses(studentNode* ptr,courseNode* courseList[],int* corsStrn)
{
	int i,indexCourse;
	char course[1];
	for(i=0;i<5;i++)
	{
		courseNode* nptr=(courseNode*)malloc(sizeof(courseNode));
		strcpy(nptr->name,ptr->name);
		strcpy(nptr->enrollment_no,ptr->enrollment_no);
		nptr->roll_no=ptr->roll_no;
		nptr->next=NULL;
		strcpy(course,ptr->courses[i]);
		indexCourse=course[0]-65;
		corsStrn[indexCourse]++;
		courseNode* n=courseList[indexCourse];
		courseNode* t=NULL;
		courseNode* p;
		if(n==NULL)
		{
			n=nptr;
		}
		else
		{
			p=n;
			while((p!=NULL) && (p->roll_no<nptr->roll_no))
			{
				t=p;
				p=p->next;
			}
			if(t==NULL)
			{
				nptr->next=p;
				n=nptr;
			}
			else
			{
				nptr->next=p;
				t->next=nptr;
			}
		}
		courseList[indexCourse]=n;
	}
}

void deleteStudentDataInCourses(studentNode* ptr,courseNode* courseList[26],int* corsStrn)
{
	int i,indexCourse,found;
	char course[1];
	for(i=0;i<5;i++)
	{
		found=0;
		strcpy(course,ptr->courses[i]);
		indexCourse=course[0]-65;
		courseNode* n=courseList[indexCourse];
		courseNode* t=NULL;
		courseNode* p=n;
		while(p!=NULL && found==0)
		{
			if(!strcmp(ptr->enrollment_no,p->enrollment_no))
			{
				found=1;
			}	
			else
			{
				t=p;
				p=p->next;
			}
		}
		if(found==1)
		{
			corsStrn[indexCourse]--;
		    if(n==p)
			{
				n=p->next;
				free(p);
			}
			else
			{
				t->next=p->next;
				free(p);
			}
		}
		courseList[indexCourse]=n;
	}
}

void deleteStudentData(char enrollment_no[],studentNode* studentList[],courseNode* courseList[26],int* corsStrn)
{
	int found=0;
	studentNode* n=studentList[indexYear(enrollment_no[3])];
	studentNode *p=n,*t=NULL;
	while(p!=NULL && found==0)
	{
		if(!strcmp(enrollment_no,p->enrollment_no))
		{
			found=1;
		}
		else
		{
			t=p;
			p=p->next;
		}
	}
	if(found==1)
	{
		deleteStudentDataInCourses(p,courseList,corsStrn);
	    if(n==p)
		{
			n=p->next;
			free(p);
		}
		else
		{
			t->next=p->next;
			free(p);
		}
		printf("Student data of %s deleted\n",enrollment_no);
	}
	else
	{
		printf("Student not found!\n");
	}
	studentList[indexYear(enrollment_no[3])]=n;
}

void sort(int a[],int n)
{
    int t,i,j,sorted=0;
    for(i=0;i<n-1&&sorted==0;i++)
    {
        sorted=1;
        for(j=0;j<n-i-1;j++)
        {
            if(a[j]<a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                sorted=0;
            }
        }
    }
}

void intializeClassList(classNode* classList,int size)
{
	int i,j;
	for(i=0;i<size;i++)
	{
		for(j=0;j<5;j++)
		{
			classList[i].solts[j].f=0;
			classList[i].exam[j].f=0;
		}
	}
}

void alloteClassroomToCourse(classNode* classList,courseNode* courseList[26],int classListSize,int* corsStrn)
{
	int i,found,j;
	for(i=0;i<26;i++)
	{
		courseNode* n=courseList[i];
		if(n!=NULL)
		{
			found=0;
			for(j=0;j<classListSize && found==0;j++)
			{
				if(classList[j].no_of_seats>=corsStrn[i])
				{
					if(classList[j].solts[(i+65)%5].f==0)
					{
						found=1;
						classList[j].solts[(i+65)%5].f=1;
						classList[j].solts[(i+65)%5].c=i+65;
					}
				}
			}
		}
	}
}

void alloteClassroomToExam(classNode* classList,courseNode* courseList[26],int classListSize,int* corsStrn,int* noOfCoursesInSlot)
{
	int i,j,x;
	for(i=0;i<26;i++)
	{
		courseNode* n=courseList[i];
		x=corsStrn[i];
		if(n!=NULL)
		{
			for(j=0;j<classListSize && x>0;j++)
			{
				if(classList[j].exam[(i+65)%5].f<3)
				{
					classList[j].exam[(i+65)%5].c[classList[j].exam[(i+65)%5].f]=i+65;
					classList[j].exam[(i+65)%5].f++;
					x=x-(classList[j].no_of_seats/3);
				}
			}
		}
	}
}
	
void printExamSeatAllotement(classNode* classList,courseNode* courseList[26],int classListSize)
{
	int i,j;
	for(i=0;i<classListSize;i++)
	{
		for(j=0;j<3;j++)
		{
			
		}
	}
}
	
int main()
{
	int i,check,j;
	int courseStrength[26];
	int noOfCoursesInSlot[5]={0,0,0,0,0};
	for(i=0;i<26;i++)
	{
		courseStrength[i]=0;
	}
	studentNode* studentList[3];
	for(i=0;i<3;i++)
	{
		studentList[i]=NULL;
	}
    studentNode* nptr;
    
    courseNode* courseList[26];
    for(i=0;i<26;i++)
	{
		courseList[i]=NULL;
	}
    
    FILE *the_file;
    the_file=fopen("Book1.csv","r");
    if(the_file==NULL)
    {
        perror("unable to open tthe file !!\n");
        exit(1);
    }
    char line[200];
    while(fgets(line,200,the_file))
    {
        nptr=(studentNode*)malloc(sizeof(studentNode));
        char *token;
        token=strtok(line,",");
        strcpy(nptr->name,token);
        token=strtok(NULL,",");
        strcpy(nptr->enrollment_no,token);
        token=strtok(NULL,",");
        nptr->roll_no=atoi(token);
        token=strtok(NULL,",");
        strcpy(nptr->courses[0],token);
        token=strtok(NULL,",");
        strcpy(nptr->courses[1],token);
        token=strtok(NULL,",");
        strcpy(nptr->courses[2],token);
        token=strtok(NULL,",");
        strcpy(nptr->courses[3],token);
        token=strtok(NULL,",");
        strcpy(nptr->courses[4],token);
        nptr->next=NULL;
        check=checkVaildCourses(nptr);
        if(check==1)
        {
        	insertStudentData(nptr,studentList);
        	insertStudentDataInCourses(nptr,courseList,courseStrength);
		}
    }
    for(i=0;i<26;i++)
    {
    	if(courseList[i]!=NULL)
    	{
    		noOfCoursesInSlot[(i+65)%5]++;
		}
	}
	
	int maxClass=0;
	for(i=0;i<5;i++)
	{
		if(maxClass<noOfCoursesInSlot[i])
		{
			maxClass=noOfCoursesInSlot[i];
		}
	}
	
	classNode classList[maxClass];
	
	int a[26];
	for(i=0;i<26;i++)
	{
		a[i]=courseStrength[i];
	}
	
	sort(a,26);
	
	for(i=0,j=maxClass-1;i<maxClass && j>=0;i++)
	{
        char class[6]="CRC0";
        char c[2];
        if(j>9)
        {
            c[0]=(j%10)-'0';
            class[3]='1';
        }
        else c[0]=j-'0';
        strcat(class,c);
		strcpy(classList[j].name,class);
		if(a[i]%3==0)
		{
			classList[j].no_of_seats=a[i];
		}
		else
		{
			classList[j].no_of_seats=12*(a[i]/12)+12;
		}
		j--;
	}
	
//	//Menu Driven Program
//	int key;
//    printf("1:Student Insertion \n");
//    printf("2:Student Deletion \n");
//    printf("3:Examm seating Allotment\n");
//    int done=0;
//    while(!done)
//    {
//        done=1;
//        printf("Enter your choice: ");
//        scanf("%d",key);
//        switch(key)
//        {
//            case 1:
//            {
//                char name[50];
//                printf("Enter name of the student :\n");
//                scanf("%s",name);
//	            char enrollment_no[11];
//                printf("Enrollment number :\n");
//                scanf("%s",enrollment_no);
//	            int roll_no;
//                printf("Enter Roll_no :\n",&roll_no);
//	            char courses[5][2];
//                printf("Enter List of Cources Registered :\n");
//                for(i=0;i<5;i++)
//                {
//                    scanf("%s",courses[i]);
//                }
//                studentNode* nptr;
//                nptr=(studentNode*)malloc(sizeof(studentNode));
//                strcpy(nptr->name,name);
//                strcpy(nptr->enrollment_no,enrollment_no);
//                nptr->roll_no=roll_no;
//                strcpy(nptr->courses[0],courses[0]);
//                strcpy(nptr->courses[1],courses[1]);
//                strcpy(nptr->courses[2],courses[2]);
//                strcpy(nptr->courses[3],courses[3]);
//                strcpy(nptr->courses[4],courses[4]);
//                nptr->next=NULL;
//                insertStudentData(nptr,studentList);
//                insertStudentDataInCourses(nptr,courseList,courseStrength);
//                break;
//            }
//            case 2:
//            {
//                char enrollment_no[11];
//                printf("Enrollment number :\n");
//                scanf("%s",enrollment_no);
//                deleteStudentData(enrollment_no,studentList,courseList,courseStrength);
//                break;
//            }
//            case 3:
//            {
//                printf("NOT DONE\n");
//                break;
//            }
//            default:
//            {
//                printf("Enter a valid case !!\n");
//                break;
//            }
//            printf("Do you want to continue :\n");
//            int y;
//            scanf("%d",&y);
//            if(y==1)
//            {
//                done=0;
//            }
//        }
//    }
	
//	for(i=0;i<5;i++)
//	{
//		printf("%d ",noOfCoursesInSlot[i]);
//	}

    
    for(i=0;i<3;i++)
    {
    	studentNode* ptr=studentList[i];
    	while(ptr)
       {
        printf("Name :%s \n",ptr->name);
        printf("Enroll :%s \n",ptr->enrollment_no);
        printf("roll.no :%d\n",ptr->roll_no);
        printf("c1 :%s\n",ptr->courses[0]);
        printf("c2 :%s\n",ptr->courses[1]);
        printf("c3 :%s\n",ptr->courses[2]);
        printf("c2 :%s\n",ptr->courses[3]);
        printf("c3 :%s\n",ptr->courses[4]);
        printf("\n");
        ptr=ptr->next;
       }
	}
//	
//    for(i=0;i<26;i++)
//    {
//    	courseNode* ptr=courseList[i];
//    	if(ptr!=NULL)
//    	{
//    		printf("\n");
//    		printf("Course:%c\n",i+65);
//			printf("Strength:%d\n",courseStrength[i]);
//    		printf("\n");
//		}
//    	while(ptr!=NULL)
//       {
//        printf("Name :%s \n",ptr->name);
//        printf("Enroll :%s \n",ptr->enrollment_no);
//        printf("roll.no :%d\n",ptr->roll_no);
//        printf("\n");
//        ptr=ptr->next;
//       }
//	}

}
