// Using  Lock Guard C++11 ; Removes the fuzz of locking and unlocking the mutex manually
// It also handles cases of exceptions , makes our code cleaner elegant and RAII principles 
// Its a wrapper around the mutex; automatically unlocks when scope is over;
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std; 

std::mutex MUTEX ;
static int k = 0; 

void incrementor()
{  
	std::lock_guard<std::mutex>my_lock_guard(MUTEX);
	    // Critical section 
		cout << " thread id " << std::this_thread::get_id()<<" is ";
		cout << "Reading k = " << k << endl;
		k = k + 1;
	
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

