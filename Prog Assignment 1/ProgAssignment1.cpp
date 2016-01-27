#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Idea is to have my schedule program able to read text file that has 10000 jobs
// URL for the text file are as follows: http://spark-public.s3.amazonaws.com/algo2/datasets/jobs.txt

// Program must be able to read between space and process the different entries as weight and length

// Use greedy algorithm method to schedule jobs in decreasing order of the difference(weight - length)

// If 2 jobs have equal difference(weight - length), should schedule the job with higher weight first
// Weight = priority of the job, the higher the number the higher the priority

// Length = number of hours taken

// Report the sum of weighted completion times of the resulting schedule that is generated. Positive integer.

// !!!!!Test for a smaller sample size. The segmentation fault error could be because the data is too huge.!!!!!
// !!!!!Or check the theory whether adding from behind is causing the segmennantion fault, if so sort in decending order of the diff
// between weight - length then if values are even after that use weight to check which one gets higher priority!!!

// Create Job Object
struct Job
{
	string JobName;
	int weight;
	int length;
	int diff;
	Job* next;
};
int initcounter()
{
	int counter = 0;
	return counter;
};
int startcounter(int counter)
{
	counter++;
	return counter;
};
int difference(int weight, int length)
{
	int temp;
	temp = weight - length;
	return temp;
};

/*Job* entry(int d, int w, int l, int count)
{
	Job* newnode = new Job;
	newnode->JobName = "Job " + std::to_string(count);
	newnode->weight = w;
	newnode->length = l;
	newnode->diff = d;
	return newnode;
};*/


/*********************************************/
/*               Main Function               */
/*********************************************/

int main()
{	
	// variable declaration
	int weight2, length2, diff2, totalJobs, count;
	Job* head = NULL;
	count = initcounter();
	string line;
	
	ifstream infile("/Users/alnurfaisal/Desktop/jobs.txt");

	if(infile.is_open())
	{
		// get the total amount of jobs from the first line

		std::getline(infile, line);

		// convert the amount of jobs to integer
		istringstream i(line);
		i >> totalJobs;
			
		// reads weight and length from second line onwards and calculate the difference. Store the difference and weight to an job object.
		while(infile >> weight2 >> length2)
		{
			Job* curr = head;
			Job* pre = NULL;
			Job* nex = NULL;

			//Job* newJob = new Job;
			diff2 = difference(weight2, length2);

			// new fresh entry to the joblist
			if(curr == NULL)
			{
				count = startcounter(count);
				Job* newnode = new Job;
				newnode->JobName = "Job " + std::to_string(count);
				newnode->weight = weight2;
				newnode->length = length2;
				newnode->diff = diff2;
				//newJob = entry(diff, weight, length, count);
				head = newnode;
			}
			// sort the array data from the biggest to the smallest using a sorting algorithm. Will sort using difference and include weight
			// if values of both are the same so whichever weight is havier between the 2 similar difference will get higher priority on the job list
			
			// add on to existing joblist
			else
			{
				// will search for the right position according to the decreasing order before linking the pointer to new entry
				//newJob = entry(diff, weight, length, count);

				count = startcounter(count);
				Job* newnode2 = new Job;
				newnode2->JobName = "Job " + std::to_string(count);
				newnode2->weight = weight2;
				newnode2->length = length2;
				newnode2->diff = diff2;
				
				while (curr != NULL)
				{
					if(curr->diff <= newnode2->diff)
					{
						break;

					}
					else
					{
						pre = curr;
						curr = curr->next;
					}

				}
				// node is inserted behind
				if(curr->diff == newnode2->diff && curr->weight > newnode2->weight)
				{
					if(curr->next == NULL)
					{
						curr->next = newnode2;
						newnode2->next = NULL;
					}
					else
					{
						nex = curr->next;
						curr->next = newnode2;
						newnode2->next = nex;
					}
				}
				// node is inserted infront
				else
				{
					if(curr == head)
					{
						newnode2->next = head;
						head = newnode2;
					}
					else
					{
						newnode2->next = curr;
						pre->next = newnode2;
					}

				}
				
			}

		}
		// use totalJobs as refrence to count the number of entries after the first entry. Check whether there is 10000 jobs as per declared.
		if(infile.eof())
		{
			if(totalJobs == count)
			{
				cout << "There are 10,000 total jobs as declared." << endl;
			}
			else
			{
				cout << "The total number of jobs are less than 10,000." << endl;
			}
		}
	}
	else
	{
		cout << "File could not be opened." << endl;
	}

	// Output of job schedule according to decending order

	Job* currpass = head;
	int index = 1;
	int total = 0;
	int a, b;
	if(currpass == NULL)
	{
		cout << "List was not sucessfully generated." << endl;
	}
	else
	{
		cout << "List of schedule jobs in decreasing order according to priority using difference of (weight - length)." << endl;
		cout << "----\t-------\t------\t------\t----------------------------" << endl;
		cout << "Rank\tJob No.\tWeight\tLength\tDifference" << endl;
		cout << "----\t-------\t------\t------\t----------------------------" << endl;
		while(currpass != NULL)
		{

			cout << index << "\t";
			cout << currpass->JobName << "\t";
			cout << currpass->weight << "\t";
			cout << currpass->length << "\t";
			cout << currpass->diff << endl;
			cout << endl;
			a = currpass->weight;
			b = currpass->length;
			total += a * b; 
			index++;
			currpass = currpass->next;
		}

		cout << "The total sum of the weighted completion times is " << total << endl;
	}	

	return 0;


}