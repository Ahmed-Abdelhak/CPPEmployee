#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "borland.h"

#define ENTER 13
#define BACKSPACE 8
#define EXTENDED -32
#define UPARROW 72
#define DOWNARROW 80
#define LEFTARROW 75
#define RIGHTARROW 77
#define HOME 71
#define END 79
#define DELETE 83

typedef struct _employee

{
	int id;
	char name[10];	// i have no string in fucking C ! ,so, instead, i use a char array
	float salary;  // xx.xx

}  // i  have not put ;   so i can call a type of it , which is Employee

Employee;	// type of _employee   

			// a new type of _employee is called Employee 
			// _employee is a struct



FILE* fileOut;
FILE* fileIn;		 // pointer of ( type: FILE ) 
int countOfEmp;
Employee* pEmp;     // pointer of type Employee 





				// Hoisting	 , here it's called Prototype, so the compiler can see that there's a function called.... and then he can match the signature of it with the invoked , then in runtime, it will excute its instructions
 //------------------------------//
char* lineEditor(int x, int y);	   // function returns a char pointer 
void renderMenu(int x, int y, int yModifier, Employee*, int*);						// function for rendering the menu
void newEmployeedata(int x, int y, Employee*, int*);				   // function for filling the employee data
void displayEmployees(int, int, Employee*, int*);
void saveToFile();
void loadFromFile();

void main(void) {

// pointer of type Employee
	pEmp = (Employee*)malloc(5 * sizeof(Employee));     // allocate 5 (for example)  - 5 is just a number for future scalibilty
																  // of the size of Employee in the memory  (casting it to Employee * )
					  
  countOfEmp = 0;	   //  i can change it later to a max of 5 employees

	renderMenu(20, 5, 2, pEmp, &countOfEmp);	// calling the function which will render the menu

	
}


char* lineEditor(int x, int y) {	  // it must return a char pointer ( char array) , so i can receive it in the strcpy in getting employee data

	int startX = x;
	int startY = y;
	int length = 11;

	int currentPos, startPos, endPos;
	currentPos = startPos = endPos = 0;
	endPos++;

	//char arr[11];
	char* arr = (char*)malloc(11 * sizeof(char));
	char *pCurrent, *pStart, *pEnd;
	pCurrent = pStart = pEnd = arr;
	pEnd++;

	char ch;
	int flag = 1;
	do {
		gotoxy(startX + currentPos, startY);
		ch = _getch();
		int x = ch;

		switch (x) {
		case EXTENDED:
			ch = _getch();
			x = ch;
			switch (x)
			{
			case LEFTARROW:
				if (currentPos > startPos) {
					currentPos--;
					pCurrent--;
				}
				break;
			case RIGHTARROW:
				if (currentPos < endPos - 1) {
					currentPos++;
					pCurrent++;
				}
				break;
			case DELETE:
				if (currentPos >= startPos && currentPos < endPos - 1) {
					int tempPos = currentPos;
					char* pTemp = pCurrent;
					while (tempPos < endPos) {
						*(pTemp) = *(pTemp + 1);
						gotoxy(startX + tempPos, startY);
						printf("%c", *pTemp);
						pTemp++;
						tempPos++;
					}
					gotoxy(startX + endPos - 1, startY);
					printf("%c", ' ');
					gotoxy(startX + endPos - 2, startY);
					printf("%c", ' ');
					endPos--;
					pEnd--;
				}
				break;
			}
			break;
		case BACKSPACE:
			if (currentPos > startPos && currentPos < endPos - 1) {
				int tempPos = currentPos;
				char* pTemp = pCurrent;
				currentPos--;
				pCurrent--;
				while (tempPos < endPos) {
					*(pTemp - 1) = *pTemp;
					gotoxy(startX + tempPos - 1, startY);
					printf("%c", *pTemp);

					pTemp++;
					tempPos++;
				}
				gotoxy(startX + endPos - 2, startY);
				printf("%c", ' ');
				endPos--;
				pEnd--;
			}
			else if (currentPos == endPos - 1 && currentPos > startPos) {
				gotoxy(startX + endPos - 2, startY);
				printf("%c", ' ');
				currentPos--;
				pCurrent--;
				endPos--;
				pEnd--;
			}
			break;
		case ENTER:
			*(pEnd - 1) = '\0';
			flag = 0;
		case HOME:
			currentPos = startPos;
			pCurrent = pStart;
			break;
		case END:
			currentPos = endPos - 1;
			pCurrent = pEnd - 1;
			break;

		case 59:
			gotoxy(0,0);
			printf("please fill these fucking details");
			break;
		default: //All Letters
			if (currentPos < endPos && isprint(ch) && endPos - startPos < length) {
				gotoxy(startX + currentPos, startY);
				printf("%c", ch);
				*pCurrent = ch;
				currentPos++;
				pCurrent++;
				if (currentPos == endPos) {
					endPos++;
					pEnd++;
				}
			}
			break;
		}
	} while (flag);

	return arr;
}
void renderMenu(int x, int y, int yModifier, Employee* emp, int* count) {

	int xPos = x;	// cursor shit
	int yPos = y;	// cursor shit
	int current = 0;   // counter 
	int resume = 1;	 // Flag
	char options[5][10] = { "New","Display","load", "save","Exit"};

	
	while (resume) {    // while Loop is used to iterate through the input from the user

		yPos = y;
		clrscr();	   // clear the CMD

		for (int i = 0; i < 5; i++) {		   // Rendering of the Colors

			SetColorAndBackground(WHITE, BLACK);
			gotoxy(xPos, yPos * yModifier);
			if (current == i) {	     // current at the start equals zero, means rendering the first choice  ( foreground= text : black , box ground = white)
				SetColorAndBackground(BLACK, WHITE);
			}
			printf("%s", options[i]);
			yPos++;
		}

		gotoxy(0, 0);		   // setCursor Position
		char input;				 // get the Input from user
		input = _getch();

		switch (input) {	   // start switching on the input

		case ENTER:	  // once Entering the Choice ,  switch again on the Counter
			switch (current)
			{
			case 0:
				clrscr();
				newEmployeedata(30, 10, emp, count);   // call the function of filling new Employee Data
			
				break;
			case 1:
				clrscr();
				displayEmployees(30, 10, emp, count);  // call the function of Rendering the Employee Data
				_getch();
				
				break;
			case 2:
				loadFromFile();
				break;
			case 3:
				clrscr();
				saveToFile();
				break;
			case 4:
				resume = 0;			// Flag exit
				//clrscr();
				break;
			}
			break;
		case 27:  // ESC button
			resume = 0;
			break;
		case EXTENDED:	// Multi Functional KEY of my fucking keyboard   (compound key)

			input = _getch();

			switch (input) {
			case UPARROW:  //UP
				if (current == 0) {							// if my fucking choice is on the top option and stupid user clicked uparrow
					                                                                           // then set my counter to the end of my array
					current = sizeof(options) / 10 - 1;
				}
				else {
					current--;
				}
				break;
			case DOWNARROW: //Down	      //  if the counter is at last option, and user clicked down, then RESET the counter to zero ( first option)
				if (current == (sizeof(options) / 10 - 1)) {   // if current = arr[2] == last element of the options
					current = 0;							   // reset my fucking counter
				}
				else {
					current++;								// if counter is not at last option, then increase my fucking counter
					                                                                              // so, the rendering will work, 
					                                                                                     // rendering is located at top of my while loop
				}
				break;
			}
			break;
		case HOME: //Home
			current = 0;
			break;
		case END: //End
			current = ( sizeof(options) / 10) - 1;		    // this fucking code, means   current = last element of the array	  arr[2]
			                                                                               // size of options is 3x10 = 30/10 = 3-1 = arr[2]
			break;

		}

	}
}
void newEmployeedata(int x, int y, Employee* emp, int* count) {	 //  Employee* emp  is a pointer of type Employee, so when i invoke this function
	                                                                                                              // i will pass an emp object to it
	                                                                                                    // and this will be considered, call by Ref
	                 																				   // since my pointer will points to the obj i sent


	
	gotoxy(x, y);
	printf("Name     : ");
	gotoxy(x, y + 2);		 
	printf("ID       : ");
	gotoxy(x, y + 4);
	printf("Salary   : ");

	strcpy_s(emp[*count].name, lineEditor(x + 11, y));		// string copy funciton , copies the typed data of LineEditor to the name of emp
	emp[*count].id = atoi(lineEditor(x + 11, y + 2));		// atoi converts the string to int
	emp[*count].salary = atof(lineEditor(x + 11, y + 4));		  // converts the string to float
	(*count)++;											   // if i have more than one fucking Employees

	clrscr();
}
void displayEmployees(int x, int y, Employee* emp, int* count) {

	for (int i = 0; i < *count; i++) {
		gotoxy(x, y);
		printf("Name     : %s", emp[i].name);
		gotoxy(x, y + 1);
		printf("ID       : %d", emp[i].id);
		gotoxy(x, y + 2);
		printf("Salary   : %f", emp[i].salary);
		y += 6;
	}
}			

void saveToFile() {

	clrscr();
	gotoxy(20, 10);
	printf("Enter file name you want to save : ");
	char* filename = lineEditor(55, 10);
	char fileDes[255] = "C:\\Users\\Silent\\Desktop\\";
	char* filePath = strcat(fileDes, filename);	   // string concatenate
	filePath = strcat(filePath, ".txt");	 // filepath = filedes + name + extension

	fopen_s(&fileOut, filePath, "w");

	for (int i = 0; i < countOfEmp; i++)
	{
		fprintf(fileOut, "Name: %s\n", pEmp[i].name);
		fprintf(fileOut, "ID: %d\n", pEmp[i].id);
		fprintf(fileOut, "Salary: %f\n", pEmp[i].salary);

	}
	fclose(fileOut);

	/*
	clrscr();
	gotoxy(20, 10);
	printf("Enter file name you want to save : ");
	char* filename = lineEditor(55, 10);
	char fileDes[255] = "C:\\Users\\Silent\\Desktop\\";
	char* filePath = strcat(fileDes, filename);	   // string concatenate
	filePath = strcat(filePath, ".employee");	 // filepath = filedes + name + extension

	fopen_s(&file, filePath, "w");	 // here 
	fwrite(&countOfEmp, sizeof(int), 1, file);
	fwrite(pEmp, sizeof(Employee), countOfEmp, file);
	fclose(file);
	*/

}
void loadFromFile() {

	clrscr();
	gotoxy(20, 10);
	printf("Enter file name you want to load : ");
	char* filename = lineEditor(55, 10);
	char fileDes[255] = "C:\\Users\\Silent\\Desktop\\";
	char* filePath = strcat(fileDes, filename);
	filePath = strcat(filePath, ".txt");
	

	fopen_s(&fileIn, filePath, "r");

	int i = 0;
	do
	{
		fscanf(fileIn, "Name: %s\n", pEmp[i].name);
		fscanf(fileIn, "ID: %d\n", &(pEmp[i].id));
		fscanf(fileIn, "Salary: %f\n", &(pEmp[i].salary));
		i++;
		countOfEmp++;
	} while (!feof(fileIn));

	fclose(fileIn);

	/*
	// using the same technique to load file as save , but i will change the mode from "w" to "read"
	clrscr();
	gotoxy(20, 10);
	printf("Enter file name you want to load : ");
	char* filename = lineEditor(55, 10);
	char fileDes[255] = "C:\\Users\\Silent\\Desktop\\";
	char* filePath = strcat(fileDes, filename);
	filePath = strcat(filePath, ".employee");


	if (!fopen_s(&file, filePath, "r")) {  // if true  ;  where   fopen return false if it find the fucking file
		fread(&countOfEmp, sizeof(int), sizeof(int), 1, file);
		fread(pEmp, sizeof(Employee)*countOfEmp, sizeof(Employee), countOfEmp, file);
		fclose(file);
	}
	else {					   // else, it returns true, it cannot find the file, then print error :)
		clrscr();
		gotoxy(20, 10);
		printf("Erorr in opening file");
		_getch();
		_getch();

	}
	*/
}