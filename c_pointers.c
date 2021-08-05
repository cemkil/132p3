/*
THIS CODE IS MY OWN WORK. I DID NOT CONSULT TO ANY PROGRAM WRITTEN BY OTHER STUDENTS.
I READ AND FOLLOWED THE GUIDELINE GIVEN IN THE PROGRAMMING ASSIGNMENT 3.
NAME: CEM KILINC

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Grade{
    char examName[20];
    int points;
};
typedef struct Grade Grade;

struct Student{
    int id;
    char name[20];
    char surname[20];
    char letterGrade;
    struct Grade grades[5];
    int numberOfExamsGraded;
    struct Student * next;
};
typedef struct Student Student;

void addStudentSorted(Student** headPtr, int id, char name[], char surname[]); //done

Student* removeStudent(Student** headPtr, int id); //done

void addGrade(Student* head, int id, char exam[], int takenPoint);//done

void printCourseReportForAllStudents(Student* head);//done

double calculateClassAvarageForOneExam (Student* head, char examName[]);//done

int isStudentInList(Student * head, int id); //done

void calculateLetterGradesOfAllStudents (Student * head);

//helper methods
Student* findStudentById(Student* head, int id);//done

int isListEmpty(Student **headPtr);//done

void printStudent(Student* student);//done

void printList(Student *headPtr); //done

int main(){
    Student *studentList=NULL;
    int input=0;
    printf(" Enter 1 in order to add a new student into the course then press Enter \n Enter 2 in order to check if the student is in the course list \n Enter 3 in order to delete a student in the course then press Enter \n Enter 4 in order to add or change the grade the student then press Enter \n Enter 5 in order to calculate the class average point then press Enter \n Enter 6 in order to print the course report for one student \n Enter 7 in order to print the course report for all students then press Enter \n Enter 8 in order to exit then press Enter\n");
    while(input!=8){
        printf("Choose one option\n");
        scanf("%d",&input);

        if(input==1){
            char stuName[20];
            char stuSurname[20];
            int stuID;
            printf("Enter the student name, surname and ID separated by one space then press Enter \n");
            scanf("%s %s %d",&stuName,&stuSurname,&stuID) ;
            addStudentSorted(&studentList,stuID,stuName,stuSurname);
        }
        else if(input==2){
            int StuID;
            printf("Enter the student ID then press Enter \n");
            scanf("%d",&StuID);
            if(findStudentById(studentList,StuID)!=NULL){
                printf("%s %s %d is found\n",findStudentById(studentList,StuID)->name,findStudentById(studentList,StuID)->surname,StuID);
            }else{
                printf("The student whose ID is %d is not found\n",StuID);
            }
        }
        else if(input==3){
            int StuID;
            printf("Enter the student ID then press Enter \n");
            scanf("%d",&StuID);
            removeStudent(&studentList,StuID);
        }
        else if(input==4){
            int StuID;
            char quizName[10];
            int quizPoint;
            printf("Enter the student ID, quiz name (quiz1, quiz2Ö), and grade separated by one space then press Enter \n");
            scanf("%d %s %d",&StuID,quizName,&quizPoint);
            addGrade(studentList,StuID,quizName,quizPoint);
        }
        else if(input==5){
            char quizName[10];
            printf("Enter the quiz name (quiz1, quiz2Ö) then press Enter\n");
            scanf("%s",quizName);
            printf("Class average for %s is %f\n",quizName,calculateClassAvarageForOneExam(studentList,quizName));
        }
        else if(input==6){
            int StuID;
            printf("Enter the student ID then press Enter \n");
            scanf("%d",&StuID);
            printStudent(findStudentById(studentList,StuID));
        }
        else if (input==7){
            printCourseReportForAllStudents(studentList);
        }
        else if(input==8){
            printf("Bye Bye");
            return 0;
        }
        else if(input==9){
            printList(studentList);

        }

    }
    return 0;
}
double calculateClassAvarageForOneExam (Student* head, char examName[]){
    double total=0;
    double numberOfStudents=0;
    Student *current=head;
    int relatedGrade=0;
    while(current!=NULL){
        for(int i=0;i<current->numberOfExamsGraded;i++){
            if(strcmp(current->grades[i].examName,examName)==0){
                relatedGrade=current->grades[i].points;
            }

        }
        total+=relatedGrade;
        numberOfStudents++;
        current=current->next;
    }
    return total/numberOfStudents;

}

void addGrade(Student* head, int id, char exam[], int takenPoint){
    Grade newGrade;
    strcpy(newGrade.examName,exam);
    newGrade.points=takenPoint;
    Student *current=head;
    current=findStudentById(current,id);
    if(current->numberOfExamsGraded<5){
        current->grades[current->numberOfExamsGraded]=newGrade;
        current->numberOfExamsGraded++;
    }
    calculateLetterGradesOfAllStudents(current);

    // printf("%s %s %d %s %d",current->name,current->surname,current->id,current->grades[current->numberOfExamsGraded].examName,current->grades[current->numberOfExamsGraded].points);
}

void printCourseReportForAllStudents(Student* head){
    Student *current=head;
    while(current!=NULL){
        printStudent(current);
        current=current->next;
    }

}

void printList(Student *headPtr){
    Student *current=headPtr;
    while(current!=NULL){
        printf("%s %s %d\n",current->name,current->surname,current->id);
        current=current->next;

    }
}

Student* findStudentById(Student* head, int id){
    Student *current=head;
    while(current!=NULL){
        if(current->id==id)return current;
        current=current->next;
    }return NULL;
}

Student* removeStudent(Student** headPtr, int id){
    Student *current=*headPtr;
    Student *prev=NULL;

    while(current!=NULL){
        if(current->id==id){
            if(prev==NULL){
                *headPtr=current->next;
                return *headPtr;
            }
            prev->next=current->next;
            return current;
        }prev=current;
        current=current->next;

    }return NULL; //not found
}

void addStudentSorted(Student** headPtr, int id, char name[], char surname[]){
    Student *temp=*headPtr;
    Student *prev=NULL;
    Student *newStudentPTR;

    newStudentPTR=malloc(sizeof(Student));
    newStudentPTR->id=id;
    newStudentPTR->numberOfExamsGraded=0;
    for(int i=0;i<5;i++){

        strcpy(newStudentPTR->grades[i].examName," ");
        newStudentPTR->grades[i].points=0;

    }
    newStudentPTR->letterGrade='\0';
    strcpy(newStudentPTR->name,name);
    strcpy(newStudentPTR->surname,surname);
    newStudentPTR->next=NULL;
    //printf("%s %s %d\n",newStudentPTR->name,newStudentPTR->surname,newStudentPTR->id);

    if(temp==NULL){//LiST IS EMPTY
        newStudentPTR->next=NULL;
        *headPtr=newStudentPTR;
        return;
    }
    if(id<temp->id){
        //if the id to insert is less than the first element
        //make the student as head
        newStudentPTR->next=*headPtr;
        *headPtr=newStudentPTR;
        return;
    }else{
        //traverse the list
        while(temp!=NULL){
            if(id>temp->id){
                prev=temp;
                temp=temp->next;
                continue;
            }else{
                //insert the student
                prev->next=newStudentPTR;
                newStudentPTR->next=temp;
                return;
            }

        }//in case the id to be inserted is maximum
        prev->next=newStudentPTR;

    }
}

int isListEmpty(Student **headPtr){
    Student *temp=*headPtr;
    if(temp==NULL){return 1;}
    else{return 0;}
}

int isStudentInList(Student * head, int id){
    Student *current=head;
    while(current!=NULL){
        if(current->id==id)return 1;
        current=current->next;
    }return 0;
}

void printStudent(Student* student) {

    printf("%s %s\t id:%d\t", student->name, student->surname, student->id);
    printf("Graded exams: ");
    for (int i = 0; i <5; i++) {
        printf("%s :%d\t", student->grades[i].examName, student->grades[i].points);}
    printf("\nLetter : %c\n", student->letterGrade); }

void calculateLetterGradesOfAllStudents (Student * head){
    Student*current=head;
    double totalPoints=0;
    for(int i=0;i<current->numberOfExamsGraded;i++){
        totalPoints+=current->grades[i].points;
    }
    double average=totalPoints/current->numberOfExamsGraded;
    if (average < 60) current->letterGrade = 'F';
    else if (average < 70 && average >= 60) current->letterGrade = 'D';
    else if (average < 80 && average >= 70) current->letterGrade = 'C';
    else if (average < 90 && average >= 80) current->letterGrade = 'B';
    else if (average <= 100 && average >= 90) current->letterGrade = 'A';

}

