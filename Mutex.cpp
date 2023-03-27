// Using Mutex to prohibit Data race by restricting shared ownership of resource;
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std; 

std::mutex MUTEX ;
static int k = 0; 

void incrementor()
{  
	// Mutex is creating an  atomic block ! 
	MUTEX.lock();
	cout << " thread id " << std::this_thread::get_id()<<" is ";
	cout << "Reading k = " << k << endl;
	k = k + 1;
	MUTEX.unlock();
	// Mutex atomic block 
}

int main()
{
	vector<std::thread> myThreads; 
	int x = 10000; 
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

