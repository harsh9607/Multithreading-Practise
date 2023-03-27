// Using the atomic keyword 
// use k++ or k+=1 but not k = k+1 or ++k
// See atomic class definition at cpp reference for more 

#include<iostream>
#include<thread>
#include<atomic>
#include<mutex>
#include<vector>

using namespace std;


static atomic_int k = 0;

void incrementor()
{

	cout << " thread id " << std::this_thread::get_id() << " is ";
	cout << "Reading k = " << k << endl;
	k=k+1;

}

int main()
{
	vector<std::thread> myThreads;
	int x = 50000;
	for (int i = 0; i < x; i++)
	{
		myThreads.push_back(std::thread(incrementor));
	}
	for (int i = 0; i < x; i++)
	{
		myThreads[i].join();
	}

	cout << " k = " << k << endl;
	if (k != x)
	{
		cout << "We just suffered Data race ! \n";
	}

	return 0;
}

