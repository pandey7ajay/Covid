#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
// define maximum number of patients in a queue
#define MAXPATIENTS 2
// define structure for patient data
struct patient
{
	char FirstName[50];
	char LastName[50];
	char ID[20];
};
// define class for queue
class queue
{
public:
	queue(void);
	int AddPatientAtEnd(patient p);
	int AddPatientAtBeginning(patient p);
	patient GetNextPatient(void);
	int RemoveDeadPatient(patient* p);
	void OutputList(void);
	char DepartmentName[50];
private :
	int NumberOfPatients;
	patient List[MAXPATIENTS];
};
// declare member functions for queue
queue::queue()
{
	// constructor
	NumberOfPatients = 0;
}
int queue::AddPatientAtEnd(patient p)
{
	// adds a normal patient to the end of the queue.
	// returns 1 if successful, 0 if queue is full.
	if (NumberOfPatients >= MAXPATIENTS)
	{
		// queue is full
		return 0;
	}
	// put in new patient
	else
		List[NumberOfPatients] = p; NumberOfPatients++;
	return 1;
}
int queue::AddPatientAtBeginning(patient p)
{
	// adds a critically ill patient to the beginning of the queue.
	// returns 1 if successful, 0 if queue is full.
	int i;
	if (NumberOfPatients >= MAXPATIENTS)
	{
		// queue is full
		return 0;
	}
	// move all patients one position back in queue
	for (i = NumberOfPatients - 1; i >= 0; i--)
	{
		List[i + 1] = List[i];
	}
	// put in new patient
	List[0] = p; NumberOfPatients++;
	return 1;
}
patient queue::GetNextPatient(void)
{
	// gets the patient that is first in the queue.
	// returns patient with no ID if queue is empty
	int i; patient p;
	if (NumberOfPatients == 0) {
		// queue is empty
		strcpy_s(p.ID, "");
			return p;
	}
	// get first patient
	p = List[0];
	// move all remaining patients one position forward in queue
	NumberOfPatients--;
	for (i = 0; i < NumberOfPatients; i++)
	{
		List[i] = List[i + 1];
	}
	// return patient
	return p;
}
int queue::RemoveDeadPatient(patient* p)
{
	// removes a patient from queue.
	// returns 1 if successful, 0 if patient not found
	int i, j, found = 0;
	// search for patient
	for (i = 0; i < NumberOfPatients; i++)
	{
		if (_stricmp(List[i].ID, p->ID) == 0)
		{
			// patient found in queue
			*p = List[i]; found = 1;
			// move all following patients one position forward in queue
			NumberOfPatients--;
			for (j = i; j < NumberOfPatients; j++)
			{
				List[j] = List[j + 1];
			}
		}
	}
	return found;
}
void queue::OutputList(void)
{
	// lists entire queue on screen
	int i;
	if (NumberOfPatients == 0)
	{
		cout << "Queue is empty" << endl;;
	}
	else
	{
		for (i = 0; i < NumberOfPatients; i++)
		{
			cout << " " << List[i].FirstName;
			cout << " " << List[i].LastName;
			cout << endl;
			cout << " " << List[i].ID;
			cout << endl;
		}
	}
}
// declare functions used by main:
patient InputPatient(void)
{
	// this function asks user for patient data.
	patient p;
	cout << "Please enter data for new patient\nFirst name : ";
	cin.getline(p.FirstName, sizeof(p.FirstName));
	cout << "\nLast name : ";
	cin.getline(p.LastName, sizeof(p.LastName));
	cout << "\nPatientID : ";
	cin.getline(p.ID, sizeof(p.ID));
	// check if data valid
	if (p.FirstName[0] == 0 || p.LastName[0] == 0 || p.ID[0] == 0)
	{
		// rejected
		strcpy_s(p.ID, "");
			cout << "Error : Data not valid.Operation cancelled." << endl;;
		_getch();
	}
	return p;
}
void OutputPatient(patient* p)
{
	// this function outputs patient data to the screen
	if (p == NULL || p->ID[0] == 0)
	{
		cout << "No patient" << endl;;
		return;
	}
	else
		cout << "Patient data : " << endl;;
	cout << "First name : " << p->FirstName << endl;;
	cout << "Last name : " << p->LastName << endl;;
	cout << "PatientID : " << p->ID << endl;;
}
int ReadNumber()
{
	// this function reads an integer number from the keyboard.
	// it is used because input with cin >> doesn�t work properly!
	char buffer[20];
	cin.getline(buffer, sizeof(buffer));
	return atoi(buffer);
}
void DepartmentMenu(queue* q)
{
	// this function defines the user interface with menu for one department
		int choice = 0, success; patient p;
	while (choice != 6)
	{
		// clear screen
		system("CLS");
		// print menu
		cout << "Welcome to department : " << q->DepartmentName <<endl;
		cout << "Please enter your choice : " << endl;
		cout << "1: Add normal patient" << endl;
		cout << "2: Add critically ill patient" << endl;
		cout << "3: Take out patient for operation" << endl;
		cout << "4: Remove dead patient from queue" << endl;
		cout << "5: List queue" << endl;
		cout << "6: Change department or exit" << endl;
		// get user choice
		choice = ReadNumber();
		// do indicated action
		switch (choice)
		{
		case 1: // Add normal patient
			p = InputPatient();
			if (p.ID[0])
			{
				success = q->AddPatientAtEnd(p);
				system("CLS");
				if (success)
				{
					cout << "Patient added :" << endl;;
				}
				else
				{
					// error
					cout << "Error : The queue is full.Cannot add patient : " << endl;;
				}
				OutputPatient(&p);
				cout << "Press any key" << endl;;
				_getch();
			}
			break;
		case 2: // Add critically ill patient
			p = InputPatient();
			if (p.ID[0])
			{
				success = q->AddPatientAtBeginning(p);
				system("CLS");
				if (success)
				{
					cout << "Patient added :" << endl;;
				}
				else
				{
					// error
					cout << "Error : The queue is full.Cannot add patient : " << endl;;
				}
				OutputPatient(&p);
				cout << "Press any key" << endl;;
				_getch();
			}
			break;
		case 3: // Take out patient for operation
			p = q->GetNextPatient();
			system("CLS");
			if (p.ID[0])
			{
				cout << "Patient to operate :" << endl;;
				OutputPatient(&p);
			}
			else
			{
				cout << "There is no patient to operate." << endl;;
			}
			cout << "Press any key" << endl;;
			_getch();
			break;
		case 4: // Remove dead patient from queue
			p = InputPatient();
			if (p.ID[0])
			{
				success = q->RemoveDeadPatient(&p);
				system("CLS");
				if (success)
				{
					cout << "Patient removed :" << endl;;
				}
				else
				{
					// error
					cout << "Error : Cannot find patient :" << endl;;
				}
				OutputPatient(&p);
				cout << "Press any key" << endl;;
				_getch();
			}
			break;
		case 5: // List queue
			system("CLS");
			q->OutputList();
			cout << "Press any key" << endl;;
			_getch(); break;
		}
	}
}
// main function defining queues and main menu
void main()
{
	int i, MenuChoice = 0;
	// define three queues
	queue departments[2];
	// set department names
	strcpy_s(departments[0].DepartmentName, "Non covid Ward");
	strcpy_s(departments[1].DepartmentName, "Covid Ward");
	while (MenuChoice != 4)
	{
		// clear screen
		system("CLS");
		// print menu
		cout << "Manage Your Patients\n";
		cout << "Please enter your choice :\n";
		for (i = 0; i < 2; i++)
		{
			// write menu item for department i
			cout << " " << (i + 1) << ": " << departments[i].DepartmentName<<endl;
		}
		cout << " 3: Exit"<<endl;
		// get user choice
		MenuChoice = ReadNumber();
		// is it a department name?
		if (MenuChoice >= 1 && MenuChoice <= 2)
		{
			// call submenu for department
			// (using pointer arithmetics here:)
			DepartmentMenu(departments + (MenuChoice - 1));
		}
		else if (MenuChoice == 3)
			exit(0);
	}
}