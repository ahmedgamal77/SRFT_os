

#include <iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct SRTF_Process {
	string id; // Process ID 
	int bt; // Burst Time 
	int at; // Arrival Time
	int rmt; // remaning time
	int wt; // waiting time 


	SRTF_Process(string i, int b, int a) {
		id = i;
		bt = b;
		at = a;
		rmt = b;
		wt = 0;



	}
};
void SRTF(vector<string>&id, vector<int>&burst, vector<int>&arival, vector<int> &start, vector<SRTF_Process> &v);

bool cmp(SRTF_Process A, SRTF_Process B) {
	if (A.bt != B.bt)
		return A.bt < B.bt;
	else
		return A.at < B.at;
}

void SRTF_Gantt_Chart(vector<SRTF_Process> &sr, vector<int> &ids);

float SRTF_Waiting_time(vector<SRTF_Process> &sr);
float SRTF_Turn_Around(vector<SRTF_Process> &sr);
int main()
{
	vector<SRTF_Process> sr;
	vector<string> ids = { "p1","p2","p3","p4","p5" };
	vector<int>burst = { 10,5,3,6,3 };
	vector<int>arrival = { 0,1,2,24,25 };
	vector<int> start;

	//the main function take 4 vectors 
	SRTF(ids, burst, arrival, start, sr);
	//functions to calculate turn around & waiting times
	for (int i = 0; i < ids.size(); i++) {
		cout << "ID : " << ids[i] << " //Time :" << burst[i]  << " //Gap :" << arrival[i]<<" //start: "<<start[i] << endl;
	}
	//cout<<"turn around time: "<<SRTF_Turn_Around(sr)<<endl;
	//cout<<"waiting time"<<SRTF_Waiting_time(sr)<<endl;


}

void SRTF_Gantt_Chart(vector<SRTF_Process> &sr, vector<string> &ids)
{


	int time = 0, flag = 0, num = sr.size();
	while (flag != 1)
	{
		flag = 1;

		for (int i = 0; i < sr.size(); i++) {

			if (sr[i].rmt > 0 && sr[i].at <= time) {

				//cout << "At " << time << " : process NO. :" << sr[i].id << endl;
				ids.push_back(sr[i].id);
				sr[i].rmt--;
				flag = 0;
				if (sr[i].rmt == 0) {
					num--;
				}


				for (int j = 0; j < sr.size(); j++) {
					if (j != i && sr[j].at <= time && sr[j].rmt > 0) {
						sr[j].wt++;
					}

				}
				break;


			}

		}
		if (num != 0 && flag == 1) {
			flag = 0;
			ids.push_back("-1");
			for (int j = 0; j < sr.size(); j++) {
				if (sr[j].at <= time && sr[j].rmt > 0) {
					sr[j].wt++;
				}

			}

		}
		time++;




	}
	//cout << "the processes take " << time-1 << endl;






}
float SRTF_Waiting_time(vector<SRTF_Process> &sr) {

	int total = 0;
	for (int i = 0; i < sr.size(); i++) {

		total += sr[i].wt;




	}

	//cout<<"avg waiting time" << (1.0*total / sr.size())<<endl;
	return (1.0*total / sr.size());


}
float SRTF_Turn_Around(vector<SRTF_Process> &sr) {

	int total = 0;
	for (int i = 0; i < sr.size(); i++) {

		total += sr[i].wt + sr[i].bt;




	}

	return (1.0*total / sr.size());
}


void SRTF(vector<string>&id, vector<int>&burst, vector<int>&arival, vector<int> &start, vector<SRTF_Process> &v) {
	vector<string>time_line;
	//to put the input in SRFT vector 

	for (int i = 0; i < id.size(); i++) {
		
		v.push_back(SRTF_Process(id[i], burst[i], arival[i]));
	}
	id.clear();
	burst.clear();
	arival.clear();

	sort(v.begin(), v.end(), cmp);
	SRTF_Gantt_Chart(v, time_line);
	int  gap = 0, time = 0;
	string lastid = time_line[0];

	time_line.push_back("-1");
	for (int i = 0; i < time_line.size(); i++) {

		if (time_line[i] == lastid) {
			if (time_line[i] != "-1") {
				time++;
			}
			else if (time_line[i] == "-1") {
				gap++;
			}
		}
		else if (time_line[i] != lastid) {
			if (lastid !="-1" && time_line[i] != "-1") {
				id.push_back(lastid);
				burst.push_back(time);
				arival.push_back(gap);
				lastid = time_line[i];
				time = 1;
				gap = 0;
			}
			else if (lastid != "-1" && time_line[i] == "-1") {
				id.push_back(lastid);
				burst.push_back(time);
				arival.push_back(gap);
				lastid = time_line[i];
				time = 0;
				gap = 1;
			}
			else if (lastid == "-1") {
				lastid = time_line[i];
				time = 1;
			}

		}







	}
	int sta = 0;
	for (int i = 0; i < burst.size(); i++) {
		sta += arival[i];
		start.push_back(sta);
		sta += burst[i];
	}








}
