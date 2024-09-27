#include<iostream>
using namespace std;


class Process
{
    public:
    int process_id;
    int arrival_time;
    int burst_time;
    int turn_around_time;
    int completion_time;
    int waiting_time;
    Process(int pid,int at,int bt){
        this->process_id = pid;
        this->arrival_time = at;
        this->burst_time = bt;
        this->turn_around_time = 0;
        this->completion_time = 0;
        this->waiting_time = 0;
    }
    Process(){};
};


void display_table(Process p_arr[], int n);
void sjf_scheduling(Process *p_arr, int n);


int main(){
    int n = 4;
    Process p1 = Process(1,0,2);
    Process p2 = Process(2,1,2);
    Process p3 = Process(3,5,3);
    Process p4 = Process(4,6,4);
    Process p_arr[4] = {p1,p2,p3,p4};
    
    display_table(p_arr,4);
    sjf_scheduling(p_arr,4);
    display_table(p_arr,4);

    return 0;
}

void sjf_scheduling(Process *processes,int n){
    int time = 0;

    //sort processes on basis of arrival time
    for (int i = 0; i < n; i++)
    {
        Process temp;
        for (int j = i+1; j < n; j++)
        {
            if (processes[j].arrival_time <= processes[i].arrival_time)
            {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    //calculating times
    for (int i = 0; i < n; i++)
    {
        //handling idle condition
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        time += processes[i].burst_time;
        processes[i].completion_time = time;
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    }
    
}

void display_table(Process *p_arr, int n){
    cout<<"\nProcess Table "<<endl;
    cout<<"PId "<<"AT  "<<"BT  "<<"CT  "<<"TAT  "<<"WT"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<p_arr[i].process_id<<"   "<<p_arr[i].arrival_time<<"   "<<p_arr[i].burst_time<<"    "<<p_arr[i].completion_time<<"   "<<p_arr[i].turn_around_time<<"    "<<p_arr[i].waiting_time<<endl;
    }
    
}