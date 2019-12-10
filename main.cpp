#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <ctime>

using namespace std;

// Declare functions
void bubbleSort(double myArray[], int n);
void selectionSort(double myArray[], int n);
void insertionSort(double myArray[], int n);
void merge(double myArray[], int l, int m, int r);
void mergeSort(double myArray[], int l, int r);
int partition(double myArray[], int low, int high);
void quickSort(double myArray[], int low, int high);
void printArray(double myArray[], int n);

int main(int argc, char** argv){
  cout << "test main" << endl;

  // Ask user to generate numbers
  cout << "Would you like to generate random float numbers before we sort? (y/n)" << endl;
  string answer;
  getline(cin, answer);
  if (answer == "y"){
    // Generate random doubles
    cout << "How many numbers would you like to generate: " << endl;
    string input;
    getline(cin, input);
    int doubleCount = stoi(input);

    cout << "Name of file to write to: " << endl;
    string writeFileName;
    getline(cin, writeFileName);

    ofstream o;
    o.open(writeFileName);
    o << doubleCount << endl;

    for (int i = 0; i < doubleCount; ++i){
      double r = (double)rand()*doubleCount / RAND_MAX;
      cout << r << endl;
      o << r << endl;
    }

  }

  // Declare arrays
  double *bubbleSortArray;
  double *selectionSortArray;
  double *insertionSortArray;
  double *mergeSortArray;
  double *quickSortArray;

  // Handle command line args
  string filename;
  if (argc > 2){ // More than 1 arg after a.out
    cout << "Too many arguments. Please try again." << endl;
    exit(1);
  }
  else if (argc < 2){ // No command arg --> ask for filename via input
    cout << "Please input a filename: " << endl;
    getline(cin, filename);
  }
  else{ // Correct usage, set command line arg to file name
    filename = argv[1];
  }

  // Try to open the file
  ifstream f;
  f.open(filename);

  if (!f.is_open()){ // File is NOT open --> exit program
    cout << "File could not be opened. Please try again with correct filename." << endl;
    exit(1);
  }
  // File is open and we can continue
  else{
    cout << "file is open!" << endl;

    // Read in the contents of the file

    // Get first line --> array size
    string str_size;
    int array_size;
    getline(f, str_size);
    // Handles errors in first line of text file
    try{
      array_size = stoi(str_size);
    }
    catch (invalid_argument e){
      cout << "Array size could not be read. Please fix the file and try again." << endl;
      exit(1);
    }
    catch (out_of_range e){
      cout << "Array size too large. Please lower/fix number at beginning of file and try again." << endl;
      exit(1);
    }

    // Initialize the arrays

    bubbleSortArray = new double[array_size];
    selectionSortArray = new double[array_size];
    insertionSortArray = new double[array_size];
    mergeSortArray = new double[array_size];
    quickSortArray = new double[array_size];

    // Made it here, let's grab all the doubles
    string str_double;
    double dbl;
    for (int i = 0; i < array_size; ++i){
      // Gets new double
      getline(f, str_double);

      // Handle potential input errors
      try{
        dbl = stod(str_double);
      }
      catch (invalid_argument e){
        cout << "Line in file could not changed to type double: " << str_double << endl;
        // cout << "Line being excluded from array; continuing to next line." << endl;
        // continue;
        exit(1);
      }

      // Add double to array --> the important part
      bubbleSortArray[i] = dbl;
      selectionSortArray[i] = dbl;
      insertionSortArray[i] = dbl;
      mergeSortArray[i] = dbl;
      quickSortArray[i] = dbl;

    }

    // ----------------- Sort the arrays -------------------------

    bubbleSort(bubbleSortArray, array_size);
    selectionSort(bubbleSortArray, array_size);
    insertionSort(insertionSortArray, array_size);

    // Merge Sort
    // Time information is calculated here because of the RECURSION
    // Get start time
    auto start = std::chrono::system_clock::now();
    cout << "Merge Sorting..." << endl;
    // Sort array
    mergeSort(mergeSortArray, 0, array_size-1);
    // Time printing
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    time_t start_time = std::chrono::system_clock::to_time_t(start);
    time_t end_time = std::chrono::system_clock::to_time_t(end);
    cout << "start: " << ctime(&start_time);
    cout << "end:   " << ctime(&end_time);
    cout << "duration: " << elapsed_seconds.count() << "s\n" << endl;

    // Quick Sort --> RECURSION
    // Get start time
    auto start2 = std::chrono::system_clock::now();
    cout << "Quick Sorting..." << endl;
    // Sort array
    quickSort(quickSortArray, 0, array_size-1);
    // Time printing
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    time_t start_time2 = std::chrono::system_clock::to_time_t(start2);
    time_t end_time2 = std::chrono::system_clock::to_time_t(end2);
    cout << "start: " << ctime(&start_time2);
    cout << "end:   " << ctime(&end_time2);
    cout << "duration: " << elapsed_seconds2.count() << "s\n" << endl;


  }

  // Close the file
  f.close();

  // Delete linkedlists after everything
  delete bubbleSortArray;
  delete selectionSortArray;
  delete insertionSortArray;
  delete mergeSortArray;
  delete quickSortArray;

  return 0;
}

// Bubble sort
void bubbleSort(double myArray[], int n){
  cout << "Bubble Sorting..." << endl;
  // Get start time
  auto start = std::chrono::system_clock::now();

  for (int i = 0; i < n; ++i){
    double temp = 0;
    for (int j = 0; j < n-i-1; ++j){
      if (myArray[j] > myArray[j+1]){
        temp = myArray[j+1];
        myArray[j+1] = myArray[j];
        myArray[j] = temp;
      }
    }
  }
  // Time printing
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  time_t start_time = std::chrono::system_clock::to_time_t(start);
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << "start: " << ctime(&start_time);
  cout << "end:   " << ctime(&end_time);
  cout << "duration: " << elapsed_seconds.count() << "s\n" << endl;
}

// Selection sort
void selectionSort(double myArray[], int n){
  cout << "Selection Sorting..." << endl;
  // Get start time
  auto start = std::chrono::system_clock::now();

  int i, j, minIndex;
  double temp;
  for (i = 0; i < n-1; ++i){
    minIndex = i;
    for (j = i + 1; j < n; ++j){
      if (myArray[j] < myArray[minIndex]){
        minIndex = j;
      }
    }
    if (minIndex != i){
      temp = myArray[i];
      myArray[i] = myArray[minIndex];
      myArray[minIndex] = temp;
    }
  }
  // Time printing
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  time_t start_time = std::chrono::system_clock::to_time_t(start);
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << "start: " << ctime(&start_time);
  cout << "end:   " << ctime(&end_time);
  cout << "duration: " << elapsed_seconds.count() << "s\n" << endl;
}

// Insertion sort
void insertionSort(double myArray[], int n){
  cout << "Insertion Sorting..." << endl;
  // Get start time
  auto start = std::chrono::system_clock::now();

  for (int j = 1; j < n; ++j){
    double temp = myArray[j]; // store marked item
    int k = j; // where to start sorting
    while (k > 0 && myArray[k-1] >= temp){ // while the thing to the left is larger, shift
      myArray[k] = myArray[k-1];
      --k;
    }
    myArray[k] = temp; // put marked item in right spot
  }
  // Time printing
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  time_t start_time = std::chrono::system_clock::to_time_t(start);
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << "start: " << ctime(&start_time);
  cout << "end:   " << ctime(&end_time);
  cout << "duration: " << elapsed_seconds.count() << "s\n" << endl;
}

// Merge
void merge(double myArray[], int l, int m, int r){
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  // declare temp arrays
  double left[n1], right[n2];

  // Inserts data from main array into temp arrays
  for (i = 0; i < n1; ++i){
    left[i] = myArray[l+i];
  }
  for (j = 0; j < n2; ++j){
    right[j] = myArray[m+1+j];
  }

  // Merge temp array back into main array
  i = 0; // first index of left array
  j = 0; // first index of right array
  k = l; // first index of merged array
  while (i < n1 && j < n2){
    if (left[i] <= right[j]){
      myArray[k] = left[i];
      i++;
    }
    else{
      myArray[k] = right[j];
      j++;
    }
    k++;
  }
  // Copy the rest of the elements in the left temp array into main array, if any
  while (i < n1){
    myArray[k] = left[i];
    i++;
    k++;
  }
  // Copy the rest of the elements in the right temp array into main array, if any
  while (j < n2){
    myArray[k] = right[j];
    j++;
    k++;
  }

}

// Merge sort
// l is left index of sub-array to be sorted (starts at 0)
// r is right index of sub-array to be sorted (starts at size-1)
void mergeSort(double myArray[], int l, int r){
  if (l < r){

    // Grabs middle index
    int m = l + (r-l)/2; // Same as (l+r)/2 but avoids overflow error
    mergeSort(myArray, l, m); // Runs recursion mergeSort for left half
    mergeSort(myArray, m+1, r); // Runs recursion mergeSort for right half

    // Merge the arrays
    merge(myArray, l, m, r);

  }
}

// Partition for quick sort
int partition(double myArray[], int low, int high){

  // Declare variables
  double temp;
  double pivot = myArray[high]; // pivot point = last element
  int i = (low - 1); // Index of smaller element

  for (int j = low; j <= high - 1; ++j){
    // If current element is smaller than the pivot
    if (myArray[j] < pivot){
      i++; // increment index of smaller double
      // Swap
      temp = myArray[i];
      myArray[i] = myArray[j];
      myArray[j] = temp;
    }
  }
  // Swap again
  temp = myArray[i+1];
  myArray[i+1] = myArray[high];
  myArray[high] = temp;

  return (i+1);
}

// Quick Sort
void quickSort(double myArray[], int low, int high){
  if (low < high){

    // Pi is partitioning index, arr[pi] is now at the right place
    int pi = partition(myArray, low, high);

    quickSort(myArray, low, pi-1);
    quickSort(myArray, pi+1, high);
  }
}

// Print array
void printArray(double myArray[], int n){
  cout << "------------------PRINTING ARRAY--------------------" << endl;
  for (int i = 0; i < n; ++i){
    cout << myArray[i] << endl;
  }
  cout << "------------------END OF ARRAY----------------------" << endl;
}
