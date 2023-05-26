#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void avg(int *arr, int n)
{
   int i;
   float avg = 0, sum = 0;
#pragma omp parallel reduction(+:sum)
   {
      // int id = omp_get_thread_num();
#pragma omp for
      for (i = 0; i < n; i++)
      {
         sum = sum + arr[i];
         cout << "\nthread id = " << omp_get_thread_num() << " and i = " << i;
      }
   }
   cout << "\n\nSum = " << sum << endl;
   avg = sum / n;
   cout << "\nAverage = " << avg << endl;
}
int main()
{
   omp_set_num_threads(4);
   int n, i;

   cout << "Enter the number of elements in the array: ";
   cin >> n;
   int arr[n];

   srand(time(0));
   for (int i = 0; i < n; ++i)
   {
   	// cin>>arr[i];
      arr[i] = rand() % 100;
   }

   cout << "\nArray elements are: ";
   for (i = 0; i < n; i++)
   {
      cout << arr[i] << ",";
   }


   avg(arr, n);
   return 0;
}
