#include "sorting.hh"
#include <cstdlib>

int main(int argc, char** argv)
{
	/* Selection Sort */
	int a[] = {1, 2, 3, 4, 5}; //Already sorted
	int b[] = {5, 4, 3, 2, 1}; //Backwards
	int c[] = {-2, -5, 0, 2, 5}; //Zero and negatives, unsorted

	Sortings<int, intintCompare>::select(a, 5);	
	Sortings<int, intintCompare>::select(b, 5);	
	Sortings<int, intintCompare>::select(c, 5);	
	
	cout << "SELECTION SORT" << endl << endl;
	cout << "Already sorted: " << endl;
	for(int i = 0; i < 5; i++)
		cout << a[i] << " ";
	cout << endl;

	cout << "Backwards: " << endl;
	for(int j = 0; j < 5; j++)
		cout << b[j] << " ";
	cout << endl;

	cout << "Zeros, Negatives, Unsorted: " << endl;
	for(int k = 0; k < 5; k++)
		cout << c[k] << " ";
	cout << endl << endl;


	/* Merge Sort */
	int d[] = {1, 2, 3, 4, 5}; //Already sorted
	int e[] = {5, 4, 3, 2, 1}; //Backwards
	int f[] = {-2, -5, 0, 2, 5}; //Zero and negatives, unsorted

	Sortings<int, intintCompare>::merge(d, 5);	
	Sortings<int, intintCompare>::merge(e, 5);	
	Sortings<int, intintCompare>::merge(f, 5);	

	cout << "MERGE SORT" << endl << endl;
	cout << "Already sorted: " << endl;
	for(int i = 0; i < 5; i++)
		cout << d[i] << " ";
	cout << endl;

	cout << "Backwards: " << endl;
	for(int j = 0; j < 5; j++)
		cout << e[j] << " ";
	cout << endl;

	cout << "Zeros, Negatives, Unsorted: " << endl;
	for(int k = 0; k < 5; k++)
		cout << f[k] << " ";
	cout << endl << endl;


	/* Shell Sort */
	int g[] = {1, 2, 3, 4, 5}; //Already sorted
	int h[] = {5, 4, 3, 2, 1}; //Backwards
	int i[] = {-2, -5, 0, 2, 5}; //Zero and negatives, unsorted

	Sortings<int, intintCompare>::shell(g, 5);	
	Sortings<int, intintCompare>::shell(h, 5);	
	Sortings<int, intintCompare>::shell(i, 5);	

	cout << "SHELL SORT" << endl << endl;
	cout << "Already sorted: " << endl;
	for(int i = 0; i < 5; i++)
		cout << g[i] << " ";
	cout << endl;

	cout << "Backwards: " << endl;
	for(int j = 0; j < 5; j++)
		cout << h[j] << " ";
	cout << endl;

	cout << "Zeros, Negatives, Unsorted: " << endl;
	for(int k = 0; k < 5; k++)
		cout << i[k] << " ";
	cout << endl << endl;
	
	return 0;
}
