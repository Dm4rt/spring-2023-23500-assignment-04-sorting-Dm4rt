#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <cstdlib>
#include <math.h>

// compile with -fconcepts and you
// can make the std::vector<int>
// into std::vector<auto>
void print_vector(std::vector<int> a){
  for(auto item:a){
    std::cout << item << ", ";
  }
  std::cout << "\n";
}


int index_of(int item, int data[], int len){
  for (int i = 0; i < len; i++){
    if (data[i] == item)
      return i;
  }

  return -1;
}


  int find_min_index(std::vector<int> a,
		   int start_index,
		   int stop_index){
  int min_index = start_index;
  int i;
  for (i = start_index; i < stop_index; i++){
    if (a[i] < a[min_index]){
      min_index = i;
    }
  }
  return min_index;
}

std::vector<int> ssort(std::vector<int> a){
  int i,min_index,tmp;
  int len = a.size();

  for (i=0;i<len;i++){
    min_index = find_min_index(a,i,len);

    tmp = a[i];
    a[i] = a[min_index];
    a[min_index] = tmp;
  }
  return a;
}

/*
  left and right are already sorted low to high
  create a new std::vector named merged
  and fill it with all the elements of left and right.
  When done, merged should be in order low to high.
*/
std::vector<int> merge(std::vector<int> left,
		       std::vector<int> right){
  std::vector<int> merged;
  int l=0,r=0; // indices into left and right;

  while (l < left.size() && r< right.size()){
    if (left[l] < right[r]){
      merged.push_back(left[l]);
      l++;
    } else {
      merged.push_back(right[r]);
      r++;
    }
  }

  while (l < left.size()){
    merged.push_back(left[l]);
    l++;
  }
  while (r < right.size()){
    merged.push_back(right[r]);
    r++;
  }
     
  return merged;
}

std::vector<int> msort(std::vector<int> data){

  std::vector<int> result;
  
  if (data.size() <= 1){
    return data;
  }
  
  std::vector<int> a,b;
  int i;
  int mid = data.size()/2;
  for (i=0;i<mid;i++){
    a.push_back(data[i]);
  }
  
  for (;i<data.size();i++){
    b.push_back(data[i]);
  }

  a = msort(a);
  b = msort(b);

  result= merge(a,b);
  
  return result;
}

std::vector<int> qsort(std::vector<int> list){
  int i,j;

  // base case
  if (list.size() <= 1){
    return list;
  }

  // select pivot value
  // for now we'll just pick list[0]
  int pivot = list[0];

  // make 2 new vectors
  std::vector<int> lower,higher;
  
  // copy all the values < pivot to lower
  // copy all the values >= pivot to higher;
  for (i=1;i<list.size();i++){
    if (list[i] < pivot){
      lower.push_back(list[i]);
    } else {
      higher.push_back(list[i]);
    }
  }

  // make our recursive calls
  lower = qsort(lower);
  higher = qsort(higher);

  // copy everything back
  for (i=0; i < lower.size(); i++){
    list[i] = lower[i];
  }
  list[i] = pivot;
  i++;
  for (j=0;j<higher.size(); j++){
    list[i] = higher[j];
    i++;
  }

  // return the sorted list
  return list;
}

void qsort2(std::vector<int>& list, int low, int high) {
    int i,j;
    // base case
    if (low >= high) {
        return;
    }
  
    // select pivot value (median of three method)
    int first = list[low];
    int middle = list[low + (high - low) / 2];
    int last = list[high];
    
    // find median value among first, middle, and last
    int pivot;
    if (first <= middle && middle <= last) {
        pivot = middle;
    } else if (last <= middle && middle <= first) {
        pivot = middle;
    } else if (first <= last && last <= middle) {
        pivot = last;
    } else if (middle <= last && last <= first) {
        pivot = last;
    } else {
        pivot = first;
    }

    // move all values less than pivot to left of vector, 
    //and all values greater to the right
    i = low;
    j = high;
    while (i <= j) {
    	
    	//Find a value greater than the pivot
        while (list[i] < pivot) {
            i++;
        }
        //Find a value thats less than the pivot
        while (list[j] > pivot) {
            j--;
        }
        //if the value greater than the pivot is on the left, 
        //and the value less than the pivot on the right,
        //we swap the values
        if (i <= j) {
            std::swap(list[i], list[j]);
            i++;
            j--;
        }
    }
    
    // make recursive calls
    qsort2(list, low, j);
    qsort2(list, i, high);
}

void print_help(char *command_name){
  std::cout << command_name << " usage: ";
  std::cout << command_name << "[OPTIONS]\n";
  std::cout << "  -h : help\n";
  std::cout << "  -p : print\n";
  std::cout << "  -s SIZE : array size\n";
  std::cout << "  -m MAX_VAL : maximum element value\n";
  std::cout << "  -a [s|m|q|Q|b] : selection, merge, quick sort, quick sort 2, or built-in\n";
  
}

extern char *optarg;

int main(int argc, char *argv[])
{


  int size = 20;
  int max_val = 100;
  char algorithm = 's' ; // selection sort
  bool print = false;
  char c;

  while ( ( c = getopt(argc, argv, "phs:m:a:")) != -1){
    switch(c) {
    case 'h' :
      print_help(argv[0]);
      exit(0);
      break;
    case 'p' :
      print = true;
      break;
    case 's' :
      size = std::stoi(optarg);
      break;
    case 'm' :
      max_val = std::stoi(optarg);
      break;
    case 'a' :
      algorithm = optarg[0];
    }
  }
  
  
  srand(time(nullptr));
  std::vector<int> a(size);
  for (int i = 0; i < size; i++){
    a[i] = rand()%max_val;
  }


  if (print){
    print_vector(a);
  }

  std::vector<int> b;
  
  std::cout << "Starting the sort.\n";
  struct timeval tp;
  gettimeofday(&tp, NULL);
  long start_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
  
  if (algorithm=='s'){
    b = ssort(a);
  } else if (algorithm=='m'){
    b = msort(a);
  } else if (algorithm=='q'){
    b = qsort(a);
  }
   else if (algorithm=='Q'){
    qsort2(a,0,size-1);
    b = a;
  }
   else if (algorithm=='b'){
    std::sort(a.begin(),a.end());
    b = a;
  }
  

  gettimeofday(&tp,NULL);
  long current_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
  long elapsed = current_time - start_time;
  
  if (print){
    print_vector(b);
  }

  std::cout << "\n----------------\nElapsed Time: ";
  std::cout << elapsed << "\n";
  return 0;
}
