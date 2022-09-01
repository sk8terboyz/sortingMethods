#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*
Shane Kennedy
Accepts an input file and output file to read/write a vector to a file using quick sort
*/

void swap(vector<long> &vec, long left, long right)
{
  long temp = vec[left];
  vec[left] = vec[right];
  vec[right] = temp;
}

void insertion(vector<long> &vec, long left, long right)
{
  for(long i = 1; i< right-1; i++)
  {
    long key = vec[i];
    long j = i-1;
    while(vec[j] > vec[j+1] && j>=0)
    {
      swap(vec, j+1, j);
      if(j != 0)
      {
        j = j-1;
      }
    }
    vec[j+1] = key;
  }
}
void quickSort(vector<long> &vec, long left, long right)
{
  long i, j, pivot, temp;
  if(right-left >= 50)
  {
    insertion(vec, left, right-1);
  }
  else
  {
    if(right-left > 0)
    {
      pivot = vec[right];
      i = left-1;
      j = right;
      bool loopFlag = true;
      while(loopFlag)
      {
        while(vec[++i] < pivot);
        while(vec[--j] > pivot);
        if(i >= j)
        {
          loopFlag = false;
        }
        else
        {
          swap(vec, i, j);
        }
      }
    }
    swap(vec, right, i);
    quickSort(vec, left, i-1);
    quickSort(vec, i+1, right);
  }
}

//read from file and build a vector with the longs given
void buildVector(char* &inputFile, vector<long> &vec, long value, long& size)
{
  ifstream unsorted;
  unsorted.open(inputFile);
//  unsorted.open("d1000.rand");
  if(unsorted.is_open())
  {
    while(unsorted>>value)        //push all values from the input documents into vector
    {
      vec.push_back(value);
      size++;
    }
  }
  else
    cout << "Unable to open file" << endl;

  unsorted.close();
}

//print the vector values to an output file
void printToFile(vector<long> &vec, char* outputFile, long size)
{
  ofstream myFile;
  myFile.open(outputFile);
//  myFile.open("output.txt");

  long outValues = 0;
  if(myFile.is_open())
  {
    while(outValues != size)             //push all values from the vector into the output file
    {
      myFile << vec.at(outValues) << endl;
      outValues++;
    }
    myFile.close();
  }
  else
    cout << "Unable to write to file" << endl;
}

//Main method
int main(int argc, char**argv)
{
//  argc = 3;
  if(argc < 3)
    cout<<"Error: not enough data provided."<<endl;

  char* inputFile = argv[1];
  char* outputFile = argv[2];

  vector<long> vec;
  long value = 0;
  long right = 0;
  long left = 0;
  long size = 0;

  buildVector(inputFile, vec, value, size);

  right = size-1;

  quickSort(vec, left, right);
  printToFile(vec, outputFile, size);

  return 0;
}
