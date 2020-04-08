
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

void SRFT_Gantt_Chart(vector<SRTF_Process> &sr);

void SRFT_Waiting_time(vector<SRTF_Process> &sr);
int main()
{
	vector<SRTF_Process> sr;
	
	sr.push_back(SRTF_Process(1,8,0));
	sr.push_back(SRTF_Process(2, 4, 1));
	sr.push_back(SRTF_Process(3, 9, 2));
	sr.push_back(SRTF_Process(4, 5, 3));

	SRTF_Arrange(sr);
	SRFT_Gantt_Chart(sr);
	SRFT_Waiting_time(sr);


}
void SRTF_Arrange(vector<SRTF_Process> & srft) {

	sort(srft.begin(), srft.end(), cmp);

}
void SRFT_Gantt_Chart(vector<SRTF_Process> &sr) {

	int time = 0, flag = 0;
	while (flag!=1)
	{	
		flag = 1;
		
		for (int i = 0; i < sr.size(); i++) {

			if (sr[i].at <= time && sr[i].rmt > 0) {

				cout << "At " << time << " : processes NO. :" << sr[i].id << endl;
				sr[i].rmt--;
				flag = 0;
				
				for (int j = 0; j < sr.size(); j++) {
					if (j != i && sr[j].at<=time && sr[j].rmt>0) {
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
void SRFT_Waiting_time(vector<SRTF_Process> &sr) {
	int total = 0;
	for (int i = 0; i < sr.size(); i++) {

		total += sr[i].wt;




	}
	cout << " total waiting time = " << (1.0*total / sr.size()) << endl;


}