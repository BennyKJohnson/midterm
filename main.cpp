#include <iostream>
using namespace std;

struct cust
{
	char name[128];
	int size;
	cust *next;
};

void print(cust *&head)
{
	cust *temp = head;
	while(temp != NULL)
	{
		cout << temp->name << endl;
		cout << temp->size << endl;
		temp = temp-> next;
	}
}
bool add(char name[], int size, cust *&head)
{
	//cretate the node
	cust *node = new cust;
	if(node == NULL) return false;
	
	strcpy(node->name, name);
	node->size = size;
	node->next = NULL;
	
	cust *temp = head;
	while(temp->next != NULL)
	{
		temp = temp-> next;
	}
	temp->next = node;
	
	return true;
}
bool addemployee(employee*& record)
{
	cout << "Name: ";
	cin >> record->name;
	cout << "Number: ";
	cin >> record-> employee_no;

	return true;
}
void freeEmployees(employee[] &array, int size)
{
	for (int i = 0; i < size; ++i)
	{
		delete(array[i]);
	}
}

bool destroy(cust *& head)
{

		cust*= *temp;
		temp = head;
		bool state = false;
		char name[128];
		int size;

		bool state = false;
		while(remove(name, size, head) == true);
		return true
		
	
}
bool remove(char name[], int size, cust*& head)
{
	if(head == NULL)
		return false;
	else
	{
		cust *temp = head;
		strcpy(name, head->name);
		size = head-> size;
		head = head->next;
		delete temp;
		temp = NULL;
	}
	return true;
}



bool initialise(cust *& head)
{
	head = NULL;
	return true;	
}
int main()
{
	cust *head;
	initialise(head);

	add("Pinkman", 10, head);
	add("Hank",2,head);
	print(head);

	return 0;

}

