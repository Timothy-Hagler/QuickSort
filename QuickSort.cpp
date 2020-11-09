// 
//  Author: Timmy Hagler
//  Date: November 4, 2020
//  Section: CS 317-03
//  Description: The QuickSort program shall take input and output files from the user. The input file will contain lines of strings
//  that will be sorted line by line into the output file using a quicksort. The program can handle more than 200,000 lines from the input file.
//

//Define this for ctime use
#define _CRT_SECURE_NO_WARNINGS

//Include all required headers
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>


//Include the standard library
using namespace std;

//Declare all functions
void QuickSort(string lines[], int left, int right);
int Partition(string lines[], int left, int right);
void PrintArray(string lines[], int length);



//Output file. It is global to avoid some parameters
ofstream outfile;


//Main function
int main()
{
    time_t startTime;   //Starting time of algorithms
    time_t endTime;     //Ending time of algorithms


    string *lines = NULL;     //Create a NULL set of memory for all possible lines in the file
    string input;       //The user input for the input file
    string output;      //The user input for the output file
    int size;           //Size of the number of lines. It will later be set to the number of lines in the file
    ifstream infile;    //The input file the sort will read from
    string temp;        //temp string to store lines for counting

    bool goodFile = false;  //Determines if the input file is in existence

    int index = 0;      //Index to count number of lines in the file



   //Loop to determine if the input file is valid. If not, ask the user for another file
    while (!goodFile)
    {
        //User inputs the file here
        cout << "Enter your input file for the QuickSort" << endl;
        cin >> input;

        //Open the user file
        infile.open(input.c_str());

        //Check if the file is valid
        if (infile.is_open())
        {
            cout << "Input file Opened" << endl << endl;
            goodFile = true;    //Ends the loop
        }
        else
            cout << "Enter a valid file" << endl;   //Continues the loop since the file was invalid


    }
    
    //User inputs the output file
    cout << "Enter your output file for the QuickSort" << endl;
    cin >> output;


    //Opens the output file. If that file does not exist, create a new one.
    outfile.open(output.c_str());


    //Appends all lines from the file into the lines array to prepare for sorting
    while (!infile.eof())
    {
        getline(infile, temp);  //Constantly replaces temp so it does not take much storage
        index++;    //Increase the index so the lines index is not replacing previous. Also counts number of lines in file

    }


    //Set the size to use in other functions as the number of lines
    size = index;

    //Set the amount of memory to use for the lines array
    lines = new string[size + 1];

    //Reset the index
    index = 0;

    //Reset the input file
    infile.close();
    infile.open(input.c_str());


    //Appends all lines from the file into the lines array to prepare for sorting
    while (!infile.eof())
    {
        getline(infile, lines[index]);  //Place each line into the lines array
        index++;    //Increase the index so the lines index is not replacing previous. Also counts number of lines in file
       
    }

    //Get the start time
    startTime = time(&startTime);
    auto start = chrono::high_resolution_clock::now();

    //Call QuickSort function
    QuickSort(lines, 0, size - 1);

    //Get ending time of QuickSort. Do not count PrintArray in time since it is not part of the sort
    endTime = time(&endTime);
    auto end = chrono::high_resolution_clock::now();

    //Call PrintArray function
    PrintArray(lines, size);

    //Delete the lines array to avoid a memory leak
    delete[] lines;

    //Close all files
    infile.close();
    outfile.close();

    //Calculate time duration of algorithm
    chrono::duration<float> duration = end - start;

    //Print starting, ending, and total times
    cout << endl;
    cout << "Starting time: " << ctime(&startTime) << endl;
    cout << "Ending time: " << ctime(&endTime) << endl;
    cout << "Approximate total elapsed time: " << duration.count() * 1000.0 << " milliseconds." << endl;     //Multiplying by 1000.0 to put into miliseconds


    //Return 0 since the program has ended
    return 0;
}


//Quicksort the data. This function will recursively split the data up and partition the data together.
//It will find a partition point and compare the data on each side of the point and continuously split 
//the data until no data is left
void QuickSort(string lines[], int left, int right)
{
    //Check if the left value is less than the right value. Determines if it is the only value of an array
    if (left < right)
    {
        int s = Partition(lines, left, right);  //Find the partition point

        QuickSort(lines, left, s - 1);          //Take the left side of the array
        QuickSort(lines, s + 1, right);         //Take the right side of the array
    }
}

//Finds the partition point of the data. If the left side of the array at the index is greater than the partion,
//it stops walking, and j starts walking until the right side of the array at the index is less than the partition.
//Most of the work is done in the Partition function
int Partition(string lines[], int left, int right)
{
    string p = lines[left];     //The partition point is automatically set to the left-most element 
    int i = left;               //Start at the beginning of the array.
    int j = right + 1;          //Start at one spot right of the array 

    //Loop where the partition point is decided. Swaps elements where needed
    do 
    {
        //Walk i until the value of lines at i is greater than the partition point
        do
        {
            i++;        //Increment i

            //Ensure there is not a read error
            if (i > right)
                break;
        } while (lines[i] < p);

        //Walk j until the value of lines at j is less than the partition point
        do
        {
            j--;        //Decrement j
            
            //Ensure there is not a read error
            if (j < left)
                break;
           
        } while (lines[j] > p);

        
        //Swap the two values where i and j stopped since i will be greater than j
        lines[i].swap(lines[j]);

    } while (i < j);

    //Undo last swap where i >= j
    lines[i].swap(lines[j]);
    
    //Replace the left-most element with lines at j 
    lines[left].swap(lines[j]);
    
    //Return the partition point
    return j;
}


//Prints the sorted array to the output file
void PrintArray(string lines[], int length)
{
    //Loops through all of lines
    for (int i = 0; i < length; i++)
    { 
        outfile << lines[i] << endl;
    }
}



