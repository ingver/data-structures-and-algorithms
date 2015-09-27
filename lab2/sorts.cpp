// sorts.cpp

#include <iostream>
#include "../lab1/sequence.hpp"

typedef unsigned int uint;

void swap( int & a, int & b )
{
    int t = a; a = b; b = t;
}

/* Insertion sort with sentinel */ 
int sort_insert_sent( int *arr, int size )
{
    if( !arr || size <= 0 ) 
        return 0;
    int i, j, t;
    for( i = size - 1; i > 0; --i ) {
        if( arr[i-1] > arr[i] )
            swap( arr[i-1], arr[i] );
    }
    for( i = 2; i < size; ++i ) {
        t = arr[i];
        for( j = i; t < arr[j-1]; --j )
            arr[j] = arr[j-1];
        arr[j] = t;
    }
    return 1;
}

/* Binary insertion sort */
int sort_insert_bin( int * arr, int size )
{
    if( !arr || size <= 0 )
        return 0;
    int i, j, low, high, pos;
    int t;
    for( i = 1; i < size; ++i ) {
        t = arr[i];
        for( low = 0, high = i - 1, pos = (low + high) >> 1;
            low <= high; pos = (low + high) >> 1 )
            {
                if( t < arr[pos] )
                    high = pos - 1;
                else
                    low = pos + 1;
            }
            for( j = i; j > low; --j )
                arr[j] = arr[j-1];
            arr[low] = t;
    }
    return 1;
}

int RadixPartition0( int * arr, int low, int high, uint mask )
{
	int i = low - 1, j = high + 1;
	for(;;) {
		while( (!(mask & (uint)arr[++i])) && i < high );
		while(   (mask & (uint)arr[--j])  && j > low  );
		if( i >= j )
			break;
		swap(arr[i], arr[j]);
	}
	if( i == j && i == high ) ++i;
	return i;
}

void MSRadix( int * arr, int low, int high, uint mask )
{
	int i;
	if( mask > 0 && low < high ) {
		i = RadixPartition0( arr, low, high, mask );
		MSRadix( arr, low, i-1 , mask >> 1 );
		MSRadix( arr, i  , high, mask >> 1 );
	}
}

int MSD2( int * arr, int size )
{
	if( !arr || size <= 0 )
		return 0;
	int i; 
	uint mask = 0;
	for( i = 0; i < size; ++i )
		mask |= (uint)arr[i];
	for( i = 31; i >= 1; --i )
		if( mask & (1 << i) )
			break;

	MSRadix( arr, 0, size-1, 1 << i );
	return 1;
}

int is_sorted( int * arr, int size )
{
    for( int i = 1; i < size; ++i )
        if( arr[i-1] > arr[i] )
            return 0;
        
        return 1;
}

#define SIZE 100

using namespace std;

int main( int argc, char ** argv )
{
    int arr[SIZE] = { 0 };

    cout << "\n*********************\n"; 
    if( !stepped( arr, SIZE, 7, 517, 11 ) ) {
        cout << "Error\n";
    }
    cout << "Generated sequence:\n";
    show_arr( arr, SIZE );
    
    if( !sort_insert_sent( arr, SIZE ) ) {
        cout << "Failed sort\n";
    }
    cout << "\nSorted with sentinel insertion:\n";
    show_arr( arr, SIZE );
    if( is_sorted( arr, SIZE ) )
        cout << "SUCCESS\n";
    else
        cout << "ARRAY IS UNSORTED\n";
    
    cout << "\n*********************\n"; 
    if( !stepped( arr, SIZE, 23, 113, 7 ) ) {
        cout << "Error\n";
    }
    cout << "Generated sequence:\n";
    show_arr( arr, SIZE );
    if( !sort_insert_bin( arr, SIZE ) ) {
        cout << "Failed sort\n";
    }
    cout << "\nSorted with binary insertion:\n";
    show_arr( arr, SIZE );
    if( is_sorted( arr, SIZE ) )
        cout << "SUCCESS\n";
    else
        cout << "ARRAY IS UNSORTED\n";

    cout << "\n*********************\n"; 
    if( !stepped( arr, SIZE, 19, 213, 11 ) ) {
        cout << "Error\n";
    }
    cout << "Generated sequence:\n";
    show_arr( arr, SIZE );
    if( !MSD2( arr, SIZE ) ) {
        cout << "Failed sort\n";
    }
    cout << "\nSorted with MSD sort:\n";
    show_arr( arr, SIZE );
    if( is_sorted( arr, SIZE ) )
        cout << "SUCCESS\n";
    else
        cout << "ARRAY IS UNSORTED\n";

    #ifdef _MSC_VER
    getchar();
    #endif
    return 0;
}
