//DSPD2-HW-Assignment-2:BT21CSE084,BT21CSE086
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct course_tag
{
	int course_id;
	int slot;
}course;

typedef struct studentNode_tag
{
	char name[50];
	char enrollment_no[11];
	int roll_no;
	int height;
	course courses[5];
	struct studentNode_tag* left;
	struct studentNode_tag* right;
}studentNode;

typedef struct courseNode_tag
{
	char name[50];
	char enroll_no[11];
	int height;
	struct courseNode_tag* left;
	struct courseNode_tag* right;
	int roll_no;
}courseNode;

typedef struct courseTreeNode_tag
{
	char course_name[20];
	int course_id;
	int strength;
	int slot;
	courseNode* courseList_root;
	struct courseTreeNode_tag* left;
	struct courseTreeNode_tag* right;
	int height;
}courseTreeNode;

typedef struct classAllote_tag
{
	int flag;
	int id;
	char cname[20];
	courseNode* root;
}classAllote;

typedef struct examClass_tag
{
	int id;
	char cname[20];
	courseNode* root;
}examClass;

typedef struct examCLassAllote_tag
{
	int flag;
	examClass course[3];
}examCLassAllote;


typedef struct classroomNode_tag
{
	char name[20];
	int no_of_seats;
	classAllote slots[5];
	examCLassAllote examSlots[5];
	struct classroomNode_tag* left;
	struct classroomNode_tag* right;
	int height;
}classroomNode;

int max(int a, int b)
{
	int ret_val;
	if(a>b)
	{
		ret_val=a;
	}
	else
	{
		ret_val=b;
	}
	return ret_val;
}

int checkVaildCourses(studentNode* ptr)
{
	int freq[5]={0,0,0,0,0};
    int flag=1,i,s;
    for(i=0; i<5&&flag==1;i++)
    {
    	s=ptr->courses[i].slot;
        freq[s-1]=freq[s-1]+1;
        if(freq[s-1]>1)
        {
            flag=0;
        }
    }
    if(flag==0)
    {
    	printf("%s took more than one course in slot %d\n",ptr->enrollment_no,s);
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

int C_get_height(courseTreeNode* root)
{
	int ret_val=0;
	if(root!=NULL)
	{
		ret_val= 1+ max( C_get_height(root->left),C_get_height(root->right) );
	}
	return ret_val;
}

int C_get_balance(courseTreeNode* root)
{
	return ( C_get_height(root->left)-C_get_height(root->right) );
}

courseTreeNode* C_rotate_right(courseTreeNode* root)
{
	courseTreeNode* x=root->left;
	root->left=x->right;
	x->right=root;
	return x;
}

courseTreeNode* C_rotate_left(courseTreeNode* root)
{
	courseTreeNode* x=root->right;
	root->right=x->left;
	x->left=root;
	return x;
}

courseTreeNode* C_insert(courseTreeNode* root, courseTreeNode* nptr)
{
	if(root==NULL)
	{
		root=nptr;
		nptr->height=1;
	}
	else
	{
		if(nptr->course_id<root->course_id)
		{
			root->left=C_insert(root->left,nptr);
			root->height=C_get_height(root);
		}
		else
		{
			root->right=C_insert(root->right,nptr);
			root->height=C_get_height(root);
		}
	}
	
	int balance=C_get_balance(root);
	
	if(balance>1 && nptr->course_id<root->left->course_id)
	{
		root=C_rotate_right(root);
	}
	else if(balance>1 && nptr->course_id>root->left->course_id)
	{
		root->left=C_rotate_left(root->left);
		root=C_rotate_right(root);
	}
	else if(balance<-1 &&nptr->course_id>root->right->course_id)
	{
		root=C_rotate_left(root);
	}
	else if(balance<-1 &&nptr->course_id<root->right->course_id)
	{
		root->right=C_rotate_right(root->right);
		root=C_rotate_left(root);
	}	
	return root;
}

int CL_get_height(courseNode* root)
{
	int ret_val=0;
	if(root!=NULL)
	{
		ret_val= 1+ max( CL_get_height(root->left),CL_get_height(root->right) );
	}
	return ret_val;
}

int CL_get_balance(courseNode* root)
{
	return ( CL_get_height(root->left)-CL_get_height(root->right) );
}

courseNode* CL_rotate_right(courseNode* root)
{
	courseNode* x=root->left;
	root->left=x->right;
	x->right=root;
	return x;
}

courseNode* CL_rotate_left(courseNode* root)
{
	courseNode* x=root->right;
	root->right=x->left;
	x->left=root;
	return x;
}

courseNode* CL_insert(courseNode* root, courseNode* nptr)
{
	if(root==NULL)
	{
		root=nptr;
		nptr->height=1;
	}
	else
	{
		if(nptr->roll_no<root->roll_no)
		{
			root->left=CL_insert(root->left,nptr);
			root->height=CL_get_height(root);
		}
		else
		{
			root->right=CL_insert(root->right,nptr);
			root->height=CL_get_height(root);
		}
	}
	
	int balance=CL_get_balance(root);
	
	if(balance>1 && nptr->roll_no<root->left->roll_no)
	{
		root=CL_rotate_right(root);
	}
	else if(balance>1 && nptr->roll_no>root->left->roll_no)
	{
		root->left=CL_rotate_left(root->left);
		root=CL_rotate_right(root);
	}
	else if(balance<-1 &&nptr->roll_no>root->right->roll_no)
	{
		root=CL_rotate_left(root);
	}
	else if(balance<-1 &&nptr->roll_no<root->right->roll_no)
	{
		root->right=CL_rotate_right(root->right);
		root=CL_rotate_left(root);
	}	
	return root;
}

int get_height(studentNode* root)
{
	int ret_val=0;
	if(root!=NULL)
	{
		ret_val= 1+ max( get_height(root->left),get_height(root->right) );
	}
	return ret_val;
}

int get_balance(studentNode* root)
{
	return ( get_height(root->left)-get_height(root->right) );
}

studentNode* rotate_right(studentNode* root)
{
	studentNode* x=root->left;
	root->left=x->right;
	x->right=root;
	return x;
}

studentNode* rotate_left(studentNode* root)
{
	studentNode* x=root->right;
	root->right=x->left;
	x->left=root;
	return x;
}

studentNode* insert(studentNode* root, studentNode* nptr)
{
	if(root==NULL)
	{
		root=nptr;
		nptr->height=1;
	}
	else
	{
		if(nptr->roll_no<root->roll_no)
		{
			root->left=insert(root->left,nptr);
			root->height=get_height(root);
		}
		else
		{
			root->right=insert(root->right,nptr);
			root->height=get_height(root);
		}
	}
	
	int balance=get_balance(root);
	
	if(balance>1 && nptr->roll_no<root->left->roll_no)
	{
		root=rotate_right(root);
	}
	else if(balance>1 && nptr->roll_no>root->left->roll_no)
	{
		root->left=rotate_left(root->left);
		root=rotate_right(root);
	}
	else if(balance<-1 &&nptr->roll_no>root->right->roll_no)
	{
		root=rotate_left(root);
	}
	else if(balance<-1 &&nptr->roll_no<root->right->roll_no)
	{
		root->right=rotate_right(root->right);
		root=rotate_left(root);
	}	
	return root;
}

void insertStudentData(studentNode* ptr,studentNode* studentList[])
{
	studentNode* root=studentList[indexYear(ptr->enrollment_no[3])];
	studentList[indexYear(ptr->enrollment_no[3])]=insert(root,ptr);
}

courseTreeNode* getCoursePtr(courseTreeNode* root,int corstud_id)
{
    courseTreeNode* ret_val=NULL;
    if(root!=NULL)
    {
        if(corstud_id==root->course_id)
        {
            ret_val=root;
        }
        else if(corstud_id<root->course_id)
        {
            ret_val=getCoursePtr(root->left,corstud_id);
        }
        else
        {
            ret_val=getCoursePtr(root->right,corstud_id);
        }
    }
    return ret_val;
}

void insertStudentDataInCourses(studentNode* nptr,courseTreeNode* root)
{
    int i;
    courseTreeNode* coursePtr=NULL;
    
    for(i=0;i<5;i++)
    {
		courseNode* ptr=(courseNode*)malloc(sizeof(courseNode));
    	strcpy(ptr->name,nptr->name);
    	strcpy(ptr->enroll_no,nptr->enrollment_no);
    	ptr->roll_no=nptr->roll_no;
    	ptr->left=NULL;
    	ptr->right=NULL;
        coursePtr=getCoursePtr(root,nptr->courses[i].course_id);  //return type courseTreeNode pointer
		coursePtr->courseList_root=CL_insert(coursePtr->courseList_root,ptr); //return type courseNode pointer
		coursePtr->strength++;
    }
}

void inorder(studentNode* root)
{
	int i;
	if(root!=NULL)
	{
		inorder(root->left);
		printf("Name: %s\n",root->name);
		printf("Enrollment.No: %s\n",root->enrollment_no);
		printf("Course Id's': ");
		for(i=0;i<5;i++)
		{
			printf("%d\t",root->courses[i].course_id);
		}
		printf("\n");
		inorder(root->right);
	}
}

void C_inorder(courseTreeNode* root)
{
    if(root!=NULL)
    {
        C_inorder(root->left);
        printf("%s %d\n",root->course_name,root->course_id);
        C_inorder(root->right);
    }
}

void CL_inorder(courseNode* root)
{
	if(root!=NULL)
	{
		CL_inorder(root->left);
		printf("%s %s %d\n",root->name,root->enroll_no,root->roll_no);
		CL_inorder(root->right);
	}
}

void CT_inorder(courseTreeNode* root)
{
	if(root!=NULL)
	{
		CT_inorder(root->left);
		printf("%s \n",root->course_name);
		CL_inorder(root->courseList_root);
		printf("Strength is %d \n",root->strength);
		printf("\n");
		CT_inorder(root->right);
	}
}

courseTreeNode* newCourseNode(char name[],int id,int size)
{
	courseTreeNode* ptr=(courseTreeNode*)malloc(sizeof(courseTreeNode));
	ptr->course_id=id;
	strcpy(ptr->course_name,name);
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}

courseTreeNode* AddCourse(courseTreeNode* root,char name[],int id,int size)
{
	courseTreeNode* cptr=newCourseNode(name,id,size);
	return C_insert(root,cptr);
}

int setRoll_no(char enroll[])
{
    int r=0;
    for(int i=0;i<3;i++)
    {
        r=r*10+enroll[7+i]-'0';
    }
    return r;
}

courseNode* delete_CL_node(courseNode* root, int key)  //deleting a node from courselist
{
    if(root == NULL)
        return root;
    
    if(key < root->roll_no)
        root->left = delete_CL_node(root->left, key);
    else if(key > root->roll_no)
        root->right = delete_CL_node(root->right, key);
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if(root->left == NULL)
        {
            courseNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL)
        {
            courseNode* temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            courseNode* temp = root->right;
            while(temp->left != NULL)
                temp = temp->left;
            root->roll_no=temp->roll_no;
            strcpy(root->name,temp->name);
            strcpy(root->enroll_no,temp->enroll_no);
            root->right = delete_CL_node(root->right, temp->roll_no);
        }
    }
    
    if(root == NULL)
        return root;
    
    root->height = 1 + max(CL_get_height(root->left), CL_get_height(root->right));
    
    int balance = CL_get_balance(root);
    
    if(balance > 1 && CL_get_balance(root->left) >= 0)
        return CL_rotate_right(root);
    
    if(balance > 1 && CL_get_balance(root->left) < 0)
    {
        root->left = CL_rotate_left(root->left);
        return CL_rotate_right(root);
    }
    
    if(balance < -1 && CL_get_balance(root->right) <= 0)
        return CL_rotate_left(root);
    
    if(balance < -1 && CL_get_balance(root->right) > 0)
    {
        root->right = CL_rotate_right(root->right);
        return CL_rotate_left(root);
    }
    
    return root;
}

studentNode* deleteStudent_node(studentNode* root,courseTreeNode* CT_root,int  key)  //deleting student data from studentlist
{
    if(root == NULL)
        return root;
    
    if(key < root->roll_no)
        root->left = deleteStudent_node(root->left,CT_root, key);
    else if(key > root->roll_no)
        root->right = deleteStudent_node(root->right,CT_root, key);
    else
    {
		for(int i=0;i<5;i++)
		{
			courseTreeNode* cptr=getCoursePtr(CT_root,root->courses[i].course_id);
			cptr->courseList_root=delete_CL_node(cptr->courseList_root,root->roll_no);
			cptr->strength--;
		}
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if(root->left == NULL)
        {
            studentNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL)
        {
            studentNode* temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            studentNode* temp = root->right;
            while(temp->left != NULL)
                temp = temp->left;
            root->roll_no = temp->roll_no;
			strcpy(root->enrollment_no,temp->enrollment_no);
			root->roll_no=temp->roll_no;
			for(int i=0;i<5;i++)
			{
				root->courses[i].course_id=temp->courses[i].course_id;
				root->courses[i].slot=temp->courses[i].slot;
			}
            root->right = deleteStudent_node(root->right,CT_root, temp->roll_no);
        }
    }
    
    if(root == NULL)
        return root;
    
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    
    int balance = get_balance(root);
    
    if(balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);
    
    if(balance > 1 && get_balance(root->left) < 0)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    
    if(balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);
    
    if(balance < -1 && get_balance(root->right) > 0)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    
    return root;
}

void deleteStudentdata(studentNode* studentList[],courseTreeNode* CT_root,char enroll[]) //Deleting student data from studentList
{
    int roll_no=setRoll_no(enroll);
	printf("%d \n",roll_no);
    studentList[indexYear(enroll[3])]=deleteStudent_node(studentList[indexYear(enroll[3])],CT_root,roll_no);
}

courseTreeNode* deleteCourse(courseTreeNode* root, int id)  // deleting a course from courseTreeNode
{
    if(root == NULL)
        return root;
    
    if(id < root->course_id)
        root->left = deleteCourse(root->left, id);
    else if(id > root->course_id)
        root->right = deleteCourse(root->right, id);
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if(root->left == NULL)
        {
            courseTreeNode* temp = root;
            root = root->right;
            free(temp);
        }
        else if(root->right == NULL)
        {
            courseTreeNode* temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            courseTreeNode* temp = root->right;
            while(temp->left != NULL)
                temp = temp->left;
            root->courseList_root = temp->courseList_root;
            root->course_id=temp->course_id;
			root->strength=temp->strength;
			root->slot=temp->slot;
            strcpy(root->course_name,temp->course_name);
            root->right = deleteCourse(root->right, temp->course_id);
        }
    }
    
    if(root == NULL)
        return root;
    
    root->height = 1 + max(C_get_height(root->left), C_get_height(root->right));
    
    int balance = C_get_balance(root);
    
    if(balance > 1 && C_get_balance(root->left) >= 0)
        return C_rotate_right(root);
    
    if(balance > 1 && C_get_balance(root->left) < 0)
    {
        root->left = C_rotate_left(root->left);
        return C_rotate_right(root);
    }
    
    if(balance < -1 && C_get_balance(root->right) <= 0)
        return C_rotate_left(root);
    
    if(balance < -1 && C_get_balance(root->right) > 0)
    {
        root->right = C_rotate_right(root->right);
        return C_rotate_left(root);
    }
    
    return root;
}

int CR_get_height(classroomNode* root)
{
	int ret_val=0;
	if(root!=NULL)
	{
		ret_val= 1+ max( CR_get_height(root->left),CR_get_height(root->right) );
	}
	return ret_val;
}

int CR_get_balance(classroomNode* root)
{
	return ( CR_get_height(root->left)-CR_get_height(root->right) );
}

classroomNode* CR_rotate_right(classroomNode* root)
{
	classroomNode* x=root->left;
	root->left=x->right;
	x->right=root;
	return x;
}

classroomNode* CR_rotate_left(classroomNode* root)
{
	classroomNode* x=root->right;
	root->right=x->left;
	x->left=root;
	return x;
}

classroomNode* CR_insert(classroomNode* root, classroomNode* nptr)
{
	if(root==NULL)
	{
		root=nptr;
		nptr->height=1;
	}
	else
	{
		if(nptr->no_of_seats<root->no_of_seats)
		{
			root->left=CR_insert(root->left,nptr);
			root->height=CR_get_height(root);
		}
		else
		{
			root->right=CR_insert(root->right,nptr);
			root->height=CR_get_height(root);
		}
	}
	
	int balance=CR_get_balance(root);
	
	if(balance>1 && nptr->no_of_seats<root->left->no_of_seats)
	{
		root=CR_rotate_right(root);
	}
	else if(balance>1 && nptr->no_of_seats>root->left->no_of_seats)
	{
		root->left=CR_rotate_left(root->left);
		root=CR_rotate_right(root);
	}
	else if(balance<-1 &&nptr->no_of_seats>root->right->no_of_seats)
	{
		root=CR_rotate_left(root);
	}
	else if(balance<-1 &&nptr->no_of_seats<root->right->no_of_seats)
	{
		root->right=CR_rotate_right(root->right);
		root=CR_rotate_left(root);
	}	
	return root;
}

void classCourse_inorder(classroomNode* root,courseTreeNode* c,int* f)
{
	if(root!=NULL && *f!=1)
	{
		classCourse_inorder(root->left,c,f);
		if(root->no_of_seats>=c->strength && root->slots[c->slot - 1].flag==0)
		{
			*f=1;
			root->slots[c->slot - 1].id=c->course_id;
			strcpy(root->slots[c->slot - 1].cname,c->course_name);
			root->slots[c->slot -1].root=c->courseList_root;
		}
		classCourse_inorder(root->right,c,f);
	}
}

void courseAllote_inorder(courseTreeNode* root,classroomNode* cr_root)
{
	if(root!=NULL)
	{
		courseAllote_inorder(root->left,cr_root);
		int f=0;
		classCourse_inorder(cr_root,root,&f);
		if(f==0)
		{
			printf("Classroom is not alloted for course %s",root->course_name);
		}
		courseAllote_inorder(root->right,cr_root);
	}
}

void examCLass_inorder(classroomNode* root,courseTreeNode* c,int* x)
{
	if(root!=NULL && *x>0)
	{
		examCLass_inorder(root->left,c,x);
		if(root->examSlots[c->slot -1].flag<3)
		{
			root->examSlots[c->slot -1].course[root->examSlots[c->slot -1].flag].id=c->course_id;
			strcpy(root->examSlots[c->slot -1].course[root->examSlots[c->slot -1].flag].cname,c->course_name);
			root->examSlots[c->slot -1].course[root->examSlots[c->slot -1].flag].root=c->courseList_root;
			root->examSlots[c->slot -1].flag++;
			*x=*x-((root->no_of_seats)/3);
		}
		examCLass_inorder(root->right,c,x);
	}
}

void examAllote_inorder(courseTreeNode* root,classroomNode* cr_root)
{
	if(root!=NULL)
	{
		examAllote_inorder(root->left,cr_root);
		int x= root->strength;
		examCLass_inorder(cr_root,root,&x);
		if(x!=0)
		{
			printf("Examination class is not allocated for some students in Course %s",root->course_name);
		}
		examAllote_inorder(root->right,cr_root);
	}
}

void CR_inorder(classroomNode* root)
{
	if(root!=NULL)
	{
		CR_inorder(root->left);
		printf("%s %d\n",root->name,root->no_of_seats);
		CR_inorder(root->right);
	}
}

void Range_Search(courseTreeNode* root,int low,int high,int* f)
{
	if(root!=NULL && *f!=1)
	{
		Range_Search(root->left,low,high,f);
		if(root->course_id>low&&root->course_id<high)
		{
			printf("%s %d\n",root->course_name,root->course_id);
		}
		if(root->course_id>high)
		{
			*f=1;
		}
		Range_Search(root->right,low,high,f);
	}
}

int main()
{
	int i,check,j;
	studentNode* studentList[3];
	for(i=0;i<3;i++)
	{
		studentList[i]=NULL;
	}
    studentNode* nptr;

    courseTreeNode* courseTree_root=NULL;
    courseTreeNode* cptr;
    FILE *file;
    file=fopen("Course_Data.csv","r");
    if(file==NULL)
    {
        perror("unable to open tthe file !!\n");
        exit(1);
    }
    char line1[200];
    while(fgets(line1,200,file))
    {
        cptr=(courseTreeNode*)malloc(sizeof(courseTreeNode));
        char *token;
        token=strtok(line1,",");
        strcpy(cptr->course_name,token);
        token=strtok(NULL,",");
        cptr->course_id=atoi(token);
		token=strtok(NULL,",");
        cptr->slot=atoi(token);
        cptr->left=NULL;
        cptr->right=NULL;
		cptr->strength=0;
		cptr->courseList_root=NULL;
        courseTree_root=C_insert(courseTree_root,cptr);
    }
    //C_inorder(courseTree_root);
    FILE *the_file;
    the_file=fopen("stedent_Data.csv","r");
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
        for(i=0;i<5;i++)
        {
        	token=strtok(NULL,",");
        	nptr->courses[i].course_id=atoi(token);
        	token=strtok(NULL,",");
        	nptr->courses[i].slot=atoi(token);
		}
        nptr->left=NULL;
        nptr->right=NULL;
		// for(i=0;i<5;i++)
        // {
        // 	printf("%d %d\n",nptr->courses[i].course_id,nptr->courses[i].slot);
		// }
        check=checkVaildCourses(nptr);
        if(check==1)
        {
        	insertStudentData(nptr,studentList);
        	insertStudentDataInCourses(nptr,courseTree_root);
		}
    }

	classroomNode* classroomTree_root=NULL;
	classroomNode* crptr=NULL;
	FILE *file1;
    file1=fopen("ClassRoom_Data.csv","r");
    if(file1==NULL)
    {
        perror("unable to open tthe file !!\n");
        exit(1);
    }
    char line2[200];
    while(fgets(line2,200,file1))
	{
		crptr=(classroomNode*)malloc(sizeof(classroomNode));
		char *token;
        token=strtok(line2,",");
		strcpy(crptr->name,token);
		token=strtok(NULL,",");
		crptr->no_of_seats=atoi(token);
		crptr->left=NULL;
		crptr->right=NULL;
		for(int i=0;i<5;i++)
		{
			crptr->slots[i].flag=0;
			crptr->examSlots[i].flag=0;
		}
		classroomTree_root=CR_insert(classroomTree_root,crptr);
	}

    // for(i=0;i<3;i++)
    // {
    // 	if(studentList[i]!=NULL)
    // 	{
    // 		inorder(studentList[i]);
	// 	}
	// }
	//char cn[10];
	// printf("Enter Course name :\n");
	// scanf("%s",cn);
	//courseTree_root=AddCourse(courseTree_root,cn,100,10);

	//courseTree_root=AddCourse(courseTree_root,cn,110,10);
	//C_inorder(courseTree_root);
	//printf("\n");
	//CT_inorder(courseTree_root);
	//deleteStudentdata(studentList,courseTree_root,"BT21CSE001");
	//deleteCourse(courseTree_root,100);
	//C_inorder(courseTree_root);
	// for(i=0;i<3;i++)
    // {
    // 	if(studentList[i]!=NULL)
    // 	{
    // 		inorder(studentList[i]);
	// 	}
	// }
	//CT_inorder(courseTree_root);
	//CR_inorder(classroomTree_root);
	//Range_Search(courseTree_root,102,105,&count);
	int done=0;
	while(!done)
	{
		printf("1:Adding a studentData\n");
		printf("2:Deleting a studentData\n");
		printf("3:Adding a Course & Deleting a course\n");
		printf("4:Allotment of classrooms for lectures.\n");
		printf("5:Range-search\n");
		printf("6:Display student tree \n");
		printf("7:Display courseTree\n");
		printf("8:Display course list tree\n");
		printf("9:Display classroomTree\n");
		printf("\nEnter your choice :\n");
		int choice;
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				studentNode* sptr=(studentNode*)malloc(sizeof(studentNode));
				char name[50];
				printf("Enter name of the student :");
				scanf("%s",name);
				strcpy(sptr->name,name);
				char enroll[11];
				printf("Enter enrollment  no:");
				scanf("%s",enroll);
				strcpy(sptr->enrollment_no,enroll);
				int roll;
				printf("Enter Roll no:");
				scanf("%d",&roll);
				sptr->roll_no=roll;
				int arr[5];
				printf("Enter course id's :");
				for(int i=0;i<5;i++)
				{
					scanf("%d",&arr[i]);
					sptr->courses[i].course_id=arr[i];
				}
				sptr->left=NULL;
				sptr->right=NULL;
				insertStudentData(sptr,studentList);
				insertStudentDataInCourses(sptr,courseTree_root);
				break;
			}
			case 2:
			{
				char enroll[11];
				printf("Enter enrollment  no:");
				scanf("%s",enroll);
				deleteStudentdata(studentList,courseTree_root,enroll);
				break;
			}
			case 3:
			{
				int id; 
				char a[11];
				printf("Enter course Name :");
				scanf("%s",a);
				printf("Enter course id :");
				scanf("%d",&id);
				courseTree_root=AddCourse(courseTree_root,a,id,11);
				break;
			}
			case 4:
			{
				int id;
				printf("Enter course id :");
				scanf("%d",&id);
				courseTree_root=deleteCourse(courseTree_root,id);
				break;
			}
			case 5:
			{
				int l,h,f=0;
				printf("Lower bound and upper bound\n");
				scanf("%d %d",&l,&h);
				Range_Search(courseTree_root,l,h,&f);
				// if(count==0)
				// {
				// 	printf("no courses are there in between %d & %d\n",l,h);
				// }
				break;
			}
			case 6:
			{
				inorder(studentList[0]);
				break;
			}
			case 7:
			{
				C_inorder(courseTree_root);
				break;
			}
			case 8:
			{
				CT_inorder(courseTree_root);
				break;
			}
			default:
			{
				printf("Enter a valid choice !!\n");
				break;
			}
		}
		printf("Do you want to continue ?\n");
		int a;
		scanf("%d",&a);
		if(a!=1)
		{
			done=1;
		}
	}
}

