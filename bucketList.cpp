// Author: Chris Kau
// CECS 325-02
// Bucket List (Prog 5)
// Due 3/25/2024
// I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.
#include <ostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int globalSwapCount = 0;
class Bucket{
	private:
		vector<int> v;
	public:
		Bucket(){}	
		void generate(int size, int min, int max)
		{
			for(int i = 0; i < size; i++)
			{
				v.push_back(rand() % (max-min+1) + min);
			}
		}

		void merge(Bucket buck)
		{
			vector<int> b;
			for(int idx = 0; idx < buck.size(); idx ++)
			{
				b.push_back(buck.atIndex(idx));
			}
			vector<int> temp;
			int i = 0,j = 0;
			while(i < size() && j < buck.size())
			{
				if(v[i] <= b[j])
				{
					temp.push_back(v[i]);
					i++;
				}else{
					temp.push_back(b[j]);
					j++;
				}
			}

			//we dont check i < size() because we only use merge() for the end bucket, and the end bucket size will always be >= b.size()
			while(j < buck.size())
			{
				temp.push_back(b[j]);
				j++;
			}
			v = temp;
		}

		int atIndex(int idx)
		{
			return v[idx];
		}

		void sort()
		{
			for(int i = 0; i < size() - 1; i++)
			{
				for(int j = 0; j < size() - i - 1; j++)
				{
					if (v[j] > v[j+1])
					{
						swap(v[j],v[j+1]);
						globalSwapCount++;
					}
				}
			}
		}
	
		int size()
		{
			return v.size();
		}	


};

int main(int argc, char *argv[])
{
	srand(time(0)); //sets seed for rand() function
	
	int bucketCount = stoi(argv[1]);
	int bucketSize = stoi(argv[2]);
	int bucketMin = stoi(argv[3]);
	int bucketMax = stoi(argv[4]);
	cout << "Bucket Count:" << bucketCount << endl;	
	cout << "Bucket Size:" << bucketSize << endl;
	cout << "Bucket Min Value:" << bucketMin << endl;
	cout << "Bucket Max Value:" << bucketMax << endl;

	vector<Bucket> list; //create empty Bucket vector
	Bucket *bptr; //create a pointer to Bucket class
	
	for(int i = 0; i < bucketCount; i++)
	{
		bptr = new Bucket; //allocating new Bucket object
		bptr->generate(bucketSize, bucketMin, bucketMax); //Bucket::generate
		list.push_back(*bptr); //pushing Bucket onto list
	}
	for(auto it = list.begin(); it != list.end(); it++) //iterating through the entire list
	{
		it->sort(); //Bucket::sort
	}
	Bucket endGame; //create an empty Bucket to merge ALL buckets stored in list variable
	
	while(list.size() > 0)
	{
		endGame.merge(list[0]);//merge first bucket in list into endGame
		list.erase(list.begin()); //erase the first bucket in the list
	}
	//writes out all the numbers in endGame bucket to a file
	fstream out("bucketList.out", ios::out);
	for(int i = 0; i < endGame.size(); i++)
	{
		out << endGame.atIndex(i) << endl;
	}

	cout << "Global Swap Count:" << globalSwapCount << endl;
	cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n";
	return 0;
	

}

