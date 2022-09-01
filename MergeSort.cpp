#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
Shane Kennedy
Sort a vector inputted by a file and output that vector to another file
*/

//Sort the elements into the temp vector then transfer the sorted vector to the main vector
void mergeVector(vector<long> &vec, vector<long> &temp, long curLeft, long curRight, long endRight)
{
  long endLeft = curRight - 1;
  long curTemp = curLeft;
  long numElems = endRight - curLeft + 1;

  while(curLeft <= endLeft && curRight <= endRight)
  {
    if(vec[curLeft] <= vec[curRight])
    {
      temp[curTemp++] = vec[curLeft++];       //set elements in temp vector to vec
    }
    else
      temp[curTemp++] = vec[curRight++];      //set elements in temp vector to vec
  }
  while(curLeft <= endLeft)
  {
    temp[curTemp++] = vec[curLeft++];         //set elements in temp vector to vec
  }
  while(curRight <= endRight)
  {
    temp[curTemp++] = vec[curRight++];        //set elements in temp vector to vec
  }
  for(int i = 0; i < numElems; i++, endRight--)
  {
    vec[endRight] = temp[endRight];           //set main vector to sorted temp vector
  }
}

//Merge sort
void mergeSort(vector<long> &vec, vector<long> &temp, long left, long right)
{
  long endRight = 0;
  long curRight = 0;

  for(long i = 1; i < right; i = 2*i)       //set the size of the merge section
  {
    for(long j = left; j < right-1; j += 2*i)   //set j to the left side of the merge section
    {

      long buffer = j + 2*i - 1;    //holder to set endRight
      if(buffer < right)            //stop endRight from going over the size
        endRight = j + 2*i - 1;
      else
        endRight = right;

      if(j+i > endRight)          //stop curRight from going over endRight
        curRight = endRight;
      else
        curRight = j+i;
      mergeVector(vec, temp, j, curRight, endRight);
    }
  }
}

//build the vector from the input file
void buildVector(char* inputFile, vector<long> &vec, long &size)
{
  long value = 0;
  ifstream unsorted;
  unsorted.open(inputFile);

  if(unsorted.good())
  {
    while(unsorted >> value)      //take in all elements in the input file
    {
      vec.push_back(value);
      size++;
    }
  }
  else
    cout << "Unable to open file" << endl;

  unsorted.close();
}

//print vector to the designated output file
void printToFile(char* outputFile, vector<long> &vec, long size)
{
  ofstream myFile;
  myFile.open(outputFile);

  if(myFile.is_open())
   {
    for(int k = 0; k < size; k++)   //print elements to output file
    {
      myFile << vec[k] << endl;
    }
  }
  else
  {
    cout << "Unable to write to file" << endl;
  }
  myFile.close();
}

//Main Method
int main(int argc, char** argv)
{
  if(argc < 3)
  {
    cout<<"Error: not enough data provided."<<endl;
  }
  else
  {
  char* inputFile = argv[1];
  char* outputFile = argv[2];

  vector<long> vec;
  long right = 0;
  long left = 0;
  long size = 0;

  buildVector(inputFile, vec, size);
  right = size-1;
  vector<long> temp(size);
  mergeSort(vec, temp, left, right);
  printToFile(outputFile, vec, size);
  }
  return 0;
}
