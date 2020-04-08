
#include "pch.h"
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct SRTF_Process {
	int id; // Process ID 
	int bt; // Burst Time 
	int at; // Arrival Time
	int rmt; // remaning time
	int wt; // waiting time 
	

SRTF_Process(int i , int b , int a) {
	id = i;
	bt = b;
	at = a;
	rmt = b;
	wt = 0;
	
	
	
}};
void SRTF_Arrange(vector<SRTF_Process> & srft);
bool cmp(SRTF_Process A, SRTF_Process B){
	if (A.bt != B.bt)
		return A.bt < B.bt;
	else
		return A.at < B.at;
}

void SRFT_Gantt_Chart(vector<SRTF_Process> &sr, vector<int> &ids);

float SRFT_Waiting_time(vector<SRTF_Process> &sr);
float SRFT_Turn_Around(vector<SRTF_Process> &sr);
int main()
{
	vector<int> ids;
	vector<SRTF_Process> sr;
	
	sr.push_back(SRTF_Process(1,8,0));
	sr.push_back(SRTF_Process(2, 4, 1));
	sr.push_back(SRTF_Process(3, 9, 2));
	sr.push_back(SRTF_Process(4, 5, 3));

	SRTF_Arrange(sr);
	SRFT_Gantt_Chart(sr,ids);
	SRFT_Waiting_time(sr);
	SRFT_Turn_Around(sr);

}
void SRTF_Arrange(vector<SRTF_Process> & srft) {

	sort(srft.begin(), srft.end(), cmp);

}
void SRFT_Gantt_Chart(vector<SRTF_Process> &sr, vector<int> &ids)
{

	int time = 0, flag = 0;
	while (flag!=1)
	{	
		flag = 1;
		
		for (int i = 0; i < sr.size(); i++) {

			if (sr[i].rmt > 0 && sr[i].at <= time) {
				
				//cout << "At " << time << " : process NO. :" << sr[i].id << endl;
				ids.push_back(sr[i].id);
				sr[i].rmt--;
				flag = 0;
				

				for (int j = 0; j < sr.size(); j++) {
					if (j != i && sr[j].at <= time && sr[j].rmt > 0) {
						sr[j].wt++;
					}

				}
				break;
				
				
			}

		}

		time++;




	}
	cout << "the processes take " << time-1 << endl;
	





}
float SRFT_Waiting_time(vector<SRTF_Process> &sr) {
	int total = 0;
	for (int i = 0; i < sr.size(); i++) {

		total += sr[i].wt;




	}

	//cout<<"avg waiting time" << (1.0*total / sr.size())<<endl;
	return (1.0*total / sr.size()) ;


}
float SRFT_Turn_Around(vector<SRTF_Process> &sr) {
	int total = 0;
		for (int i = 0; i < sr.size(); i++) {

			total += sr[i].wt+sr[i].bt;




		}
		cout<<"avg turn around time" << (1.0*total / sr.size())<<endl;
		return (1.0*total / sr.size());
}
