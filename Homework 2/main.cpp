//
//  main.cpp
//  Homework 2
//
//  Program recieves a score on each line from stdin and adds to an array to calculate # of students,
//  average grade, print each score, calculate standard deviation, and print a histogram.
//  You can enter in a valid integer score line by line and when you are finished entering in your scores,
//  you can enter in -1 to signify that you are done. Up to 99 scores can be entered. Program will ignore
//  scores greater than 100 and less than 0 (other than the -1 exit command).
//
//  Created by Andres Flores on 9/11/20.
//  Copyright © 2020 Andres Flores. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>     // Library to use the pow function
#include <iomanip>

using namespace std;

int grabStudentScoresArr(int scores[]) {
   int breakAt = 0;
   int input;
   
   for (int i = 0; i < 100; i++) {
      cin >> input;   
      
      if (input == -1) {
         breakAt = i;
         break;
      }
      else {
         scores[i] = input;
      }
   }
   
   return breakAt; //return size of Array
}

void transferScores(int newArr[], int oldArr[], int sizeOfNew) {
   for (int i = 0; i < sizeOfNew; i++) {
      newArr[i] = oldArr[i];
   }
}

int numOfInvalids(int arr[], int size) {
   int amtInvalids = 0;
   
   for (int i = 0; i < size; i++) {
      if ((arr[i] < 0) || (arr[i] > 100)) {
//          cout << arr[i] << endl;
         amtInvalids++;
      }
   }
//    cout << "Amount of invalids are " << amtInvalids << endl;
   return amtInvalids;
}

void findAndFillInvalidScores(int arr[], int invalids[], int sizeOfArr) {
   int invalidLoc = 0;
   for (int i = 0; i < sizeOfArr; i++) {
       
//       cout << "i is " << i << endl;
       
      if ((arr[i] < 0) || (arr[i] > 100)) {
          
//          cout << "found invalid at " << i << " with value of " << arr[i] << endl;
          
         invalids[invalidLoc] = arr[i];
          
//          cout << invalids[invalidLoc] << endl;
          
         invalidLoc++;
      }
   }
//    cout << "Size of array is " << sizeOfArr << endl;
//    cout << "size of invalids is " << (sizeof(invalids) / sizeof(invalids[0])) << endl;
//    cout << "size of invalidsLoc is " << invalidLoc << endl;

   cout << "The following grades are invalid: ";
   for (int i = 0; i < invalidLoc; i++) {
//       cout << invalids[i] << endl;
      if (i == (invalidLoc - 1)) {
         cout << invalids[i] << endl;
      }
      else {
         cout << invalids[i] << ", ";
      }
   }
}

int printNumStudents(int arrSize, int sizeInvalids) { // amount of students - invalid scores
   int numStudents = arrSize - sizeInvalids;
   return numStudents;
}

void printGrades(int arr[], int size) { // WORKS
   cout << "Grades = ";
   for (int i = 0; i < size; i++) {
      if ((arr[i] >= 0) && (arr[i] <= 100) && (i != size - 1)) {
         cout << arr[i] << ",";
      }
      else if ((arr[i] >= 0) && (arr[i] <= 100) && (i == size - 1)) {
         cout << arr[i] << endl;
      }
   }
}

double classAverage(int arr[], int size, int numStudents) {
   double avg;
   int total = 0;
   
   for (int i = 0; i < size; i++) {
      if ((arr[i] >= 0) && (arr[i] <= 100)) {
         total += arr[i];
      }
   }
   avg = (static_cast<double>(total)) / (static_cast<double>(numStudents));
   return avg;
}

double standDev(int arr[], int size, double avg) {
   double means[size];
   int count = 0;
    double sum;
   
   for (int i = 0; i < size; i++) {
      if ((arr[i] >= 0) && (arr[i] <= 100)) {
         count++;
         means[i] = pow((static_cast<double>(arr[i]) - avg), 2);
      }
   }
   
   for (int i = 0; i < size; i++) {
      sum += means[i];
   }
   
   sum = sum / static_cast<double>(count);
      
   sum = sqrt(sum);
   
   return sum;
}

void howManyStars(int arr[], int size, int range) {
   for (int i = 0; i < size; i++) {
      if ((arr[i] >= range) && (arr[i] < (range+10))) {
         cout << "*";
      }
   }
}

void printHistogram(int arr[], int size) {
   
   cout << "Histogram: " << endl;
   
   
   for (int i = 0; i <= 100; i+=10) {

      if (i == 0) {
         cout << "  " << i << " | ";
         
         howManyStars(arr,size, i);
            
         cout << endl;
         }

         
      
      else if (i % 100 != 0) {
         cout << " " << i << " | ";
         
         howManyStars(arr,size, i);
         
         cout << endl;
      } else {
         cout << i << " | ";
         howManyStars(arr,size, i);
         cout << endl;
      }
   }
   
}

int main()
{
   int studentScoresArr[100];
   
   int sizeOfScores = grabStudentScoresArr(studentScoresArr);
   
   int smallerStudentScores[sizeOfScores];
   
   transferScores(smallerStudentScores, studentScoresArr, sizeOfScores); //transfer the full 100 length array into a smaller one without the ending 0s
   
   int amtOfInvalids = numOfInvalids(smallerStudentScores, sizeOfScores);
//    cout << "amount of invalids in main is " << amtOfInvalids << endl;
   int invalidScores[amtOfInvalids];

   if (amtOfInvalids > 0)
      findAndFillInvalidScores(smallerStudentScores, invalidScores, sizeOfScores);
   
   int numStudents = printNumStudents(sizeOfScores, amtOfInvalids);
   
   double avg = classAverage(smallerStudentScores, sizeOfScores, numStudents);
   
   double standDeviation = standDev(smallerStudentScores, sizeOfScores, avg);

   
   int choice = -1;
   
    while (choice != 0) {
       cout << "Select an option (1) # of students, (2) Grades, (3) Average, (4) Standard Deviation, (5) Histogram, (0) Exit: ";
       cin >> choice;
        if (choice == 0) {
            cout << endl;
            break;
            }
      
       else if (choice == 1) {
              cout << "Number of students = ";
              cout << numStudents << endl;
       }
       else if (choice == 2) {
           printGrades(smallerStudentScores, sizeOfScores);
       }
       else if (choice == 3) {
           cout << fixed << setprecision(2);
           cout << "Class Average = " << avg << endl;
       }
       else if (choice == 4) {
           cout << fixed << setprecision(2);
           cout << "Standard Deviation = " << standDeviation << endl;
       }
       else if (choice == 5) {
           printHistogram(smallerStudentScores, sizeOfScores);
       }
        else {
            cout << "Please enter a valid number (0-5)" << endl;
        }
    }
   
   return 0;
}
