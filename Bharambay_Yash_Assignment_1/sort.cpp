#include <cstdio>
#include <cstdlib>

#include "sort.h"

int ivector_length(int *v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int **A, int n, int l, int r)
{
  int i;
  int *key;

  for (int j = l + 1; j <= r; j++)
  {
    key = A[j];
    i = j - 1;

    while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
    {
      A[i + 1] = A[i];
      i = i - 1;
    }

    A[i + 1] = key;
  }
}

/*
 *   TO IMPLEMENT: Improved Insertion Sort for problem 1.
 */
void insertion_sort_im(int **A, int n, int l, int r)
{

  int *temporary_array = new int[r - l + 1];

  for (int i = 0; i <= r; i++)
  {
    temporary_array[i] = ivector_length(A[i], n);
  }
  int i;
  int *key;
  int temporary_key;
  for (int j = l + 1; j <= r; j++)
  {
    temporary_key = temporary_array[j];
    key = A[j];
    i = j - 1;

    while ((i >= l) && (temporary_array[i] > temporary_key))
    {
      temporary_array[i + 1] = temporary_array[i];
      A[i + 1] = A[i];
      i = i - 1;
    }
    temporary_array[i + 1] = temporary_key;
    A[i + 1] = key;
  }
}

/*
 *   TO IMPLEMENT: Improved Merge Sort for problem 2.
 */
void merge_sort(int **A, int n, int p, int r)
{
  int *temporary_array = new int[r - p + 1];
  for (int i = 0; i <= r; i++)
  {
    temporary_array[i] = ivector_length(A[i], n);
  }
  merge(A, temporary_array, n, p, r);
}
void merge(int **A, int *temporary_array, int n, int p, int r)
{
  if (p == r)
  {
    return;
  }
  int mid = (p + r) / 2;
  // merge left subarray
  merge(A, temporary_array, n, p, mid);
  // merge right subarray
  merge(A, temporary_array, n, mid + 1, r);
  // after merge of each subarray, sort the current array
  sorting_after_merge(A, temporary_array, n, p, mid, r);
}

void sorting_after_merge(int **A, int *temporary_array, int n, int p, int mid, int r)
{
  int *temporary_left = new int[mid - p + 1];     // For storing left most value
  int *temporary_right = new int[r - mid];        // For storing right most value
  int **temporaryA_left = new int *[mid - p + 1]; // For storing left most value
  int **temporaryA_right = new int *[r - mid];    // For storing right most value
  for (int i = 0; i < mid - p + 1; i++)
  {
    temporary_left[i] = temporary_array[p + i];
  }

  for (int i = 0; i < r - mid; i++)
  {
    temporary_right[i] = temporary_array[mid + 1 + i];
  }
  for (int i = 0; i < mid - p + 1; i++)
  {
    int *dimension = new int[n];

    for (int j = 0; j < n; j++)
    {
      dimension[j] = A[p + i][j];
    }
    temporaryA_left[i] = dimension;
  }

  for (int i = 0; i < r - mid; i++)
  {
    int *dimension = new int[n];
    for (int j = 0; j < n; j++)
    {
      dimension[j] = A[mid + 1 + i][j];
    }
    temporaryA_right[i] = dimension;
  }

  int i = 0, j = 0, k = p;

  for (; i < mid - p + 1 && j < r - mid; k++)
  {
    if (temporary_left[i] > temporary_right[j])
    {
      temporary_array[k] = temporary_right[j];
      A[k] = temporaryA_right[j];
      j++;
    }
    else
    {
      temporary_array[k] = temporary_left[i];
      A[k] = temporaryA_left[i];
      i++;
    }
  }

  while (i < mid - p + 1)
  {
    temporary_array[k] = temporary_left[i];
    A[k] = temporaryA_left[i];
    i++;
    k++;
  }
  while (j < r - mid)
  {
    temporary_array[k] = temporary_right[j];
    A[k] = temporaryA_right[j];
    j++;
    k++;
  }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(int **A, int n, int l, int r)
{
  for (int i = l + 1; i <= r; i++)
    if (ivector_length(A[i - 1], n) > ivector_length(A[i], n))
      return false;
  return true;
}

/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int **create_ivector(int n, int m)
{
  int **iv_array;

  iv_array = new int *[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int **iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int **create_sorted_ivector(int n, int m)
{
  int **iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i + j) / n;

  return iv_array;
}

int **create_reverse_sorted_ivector(int n, int m)
{
  int **iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m - i) + j) / n;

  return iv_array;
}

int **create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int **iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
    {
      rg >> iv_array[i][j];
      if (small)
        iv_array[i][j] %= 100;
      else
        iv_array[i][j] %= 65536;
    }

  return iv_array;
}
