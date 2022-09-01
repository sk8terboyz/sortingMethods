#include <iostream>
#include <fstream>
using namespace std;

/*
Shane Kennedy
Insertion sort program with double linked lists only using node connections and pointers
*/

//structure of the nodes
struct Node
{
  long data;
  struct Node* next;    //next node in the DLL
  struct Node* prev;    //previous node in the DLL
};

//Sort the nodes from the given input file
void insertionSort(struct Node* &head, struct Node* &tail, struct Node* &current, long max)
{
  bool streamFlag = false;
  int tailTest=0;

  struct Node* staple = head->next;     //staple for current node to work from

  for(long i = 1; i < max; i++)
  {
    current = staple;
    staple = staple->next;        //incremental for current node

    for(long j = i-1; j > 0; j--)
    {
      if(head == NULL)              //if head is empty
      {
        head->data = current->data;   //set head data to current data
        tail->data = current->data;   //set tail data to current data
        head->prev = NULL;            //set previous pointer to NULL
        head->next = NULL;            //set next pointer to NULL
        tail->prev = NULL;            //set previous pointer to NULL
        tail->next = NULL;            //set next pointer to NULL
      }
      else if(current->data <= head->data && j > 1)   //if current data is less than or equal to head data
      {
        if(current->next == NULL){        //if current node is the head
          current->prev->next = NULL;
          current->next = head;
          current->prev = NULL;
          head->prev = current;
          head = current;
          j = 0;
        }
        else
        {
          current->next->prev = current->prev;  //remove current node from list
          current->prev->next = current->next;  //remove current node from list
          current->next = head;                 //place current node before head
          current->prev = NULL;                 //place current node before head
          head->prev = current;                 //set temp previous to current (head)
          head = current;                       //set head to current
          j = 0;
        }
      }
      else if(current->data >= tail->data && j > 1)   //if current data is greater than or equal to tail data
      {
        if(current->prev == NULL)       //if current node is the head
        {
          current->next->prev = NULL;
          current->next = NULL;
          current->prev = tail;
          tail->next = current;
          tail = current;
          j = 0;
          max++;
        }
        else if(current->next == NULL)      //if current node is the tail
        {
          tail = tail;
        }
        else
        {
          current->next->prev = current->prev;  //remove current node from list
          current->prev->next = current->next;  //remove current node from list
          current->next = NULL;                 //place current node before head
          current->prev = tail;                 //place current node before head
          tail->next = current;                 //set temp next to current
          tail = current;                       //set tail to current
          j = 0;
          max++;
        }
      }
      else
      {
        struct Node* temp = current->prev;      //set temp to node before current for comparison
        while(current->data < temp->data && temp != head && j > 0)
        {
          //move temp to the next node until it is no longer greater than current data
          temp = temp->prev;
        }
        if(temp == head)      //if temp node is the head
        {
          current->next->prev = current->prev;    //remove current node from list
          current->prev->next = current->next;    //remove current node from list
          temp->next->prev = current;             //place current node before temp
          current->prev = temp;                   //place current node before temp
          current->next = temp->next;             //place current node befoer temp
          temp->next = current;
        }
        else if(current == tail)    //if current node is the tail
        {
          tail = tail;    //this seems pointless but fixed the final seg fault
        }
        else
        {
          current->next->prev = current->prev;    //remove current node from list
          current->prev->next = current->next;    //remove current node from list
          current->prev = temp;             //place current node befoer temp
          temp->next->prev = current;                   //place current node before temp
          current->next = temp->next;             //place current node before temp
          temp->next = current;                   //place current node before temp
        }
      }
    }
  }
}

//Add all nodes to the list from the file
void add(char* fileName, struct Node* &head, struct Node* &tail, struct Node* current, long &max)
{
  ifstream unsorted;
//  unsorted.open("d1000.rand");
  unsorted.open(fileName);
  long value=0;
  bool fileFlag = true;
  if(unsorted.is_open())      //if file is open
  {
    struct Node* temp = new Node;

    while(unsorted>>value)     //while there are more lines to the input file
    {
      if(head == NULL)      //if head is empty
      {
        head = new Node;
        temp->data = value;
        temp->next = NULL;
        temp->prev = NULL;
        head = temp;
        current = temp;
        tail = temp;
      }
      else
      {
        struct Node* inserter = new Node;
        inserter->data = value;
        inserter->next = nullptr;
        inserter->prev = tail;
        tail->next = inserter;
        tail->prev = current;
        current = inserter->prev;
        tail = inserter;
      }
      max++;
    }
  }
  else
    cout << "Unable to open file";

  unsorted.close();       //close input file
}

//print the double linked list to a designated output file
void printToFile(char* outFile, struct Node* &printNodes, struct Node* tail, long max)
{
  long printFlag = 0;
  ofstream myFile;
  myFile.open(outFile);

  if(myFile.is_open())      //if output file is open
  {
    while(printNodes != NULL)     //until printNodes reaches the end of the DLL
    {
      myFile << printNodes->data << endl;
      printNodes = printNodes->next;
      printFlag++;

    }
    myFile.close();     //close output file
  }
  else
    cout << "Unable to write to file";
}

//Main Method
int main(int argc, char** argv)
{
  if(argc < 3)    //if 3 arguments are made in command line
    cout<<"Error: Not enough data provided."<<endl;

  char* inputFile = argv[1];         //store input file name
  char* outputFile = argv[2];        //store output file name

  struct Node* head = NULL;          //head of linked list
  struct Node* tail = new Node;      //tail of linked list
  struct Node* current = new Node;   //current value being worked with in the sorting process

  long max = 0;

  add(inputFile, head, tail, current, max);
  insertionSort(head, tail, current, max);
  printToFile(outputFile, head, tail, max);

  return 0;
}
