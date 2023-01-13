# include <iostream>
# include <algorithm> 
# include <deque>
using namespace std;

struct P
{
    int burst, arrival, turnaround, number;
};

void SRTF(int n,P process[]);
void output(int n,int burst[],int turnaround[]);
bool cmp (P i,P j) { return (i.burst<j.burst); }

int main()
{   
    int n;
    cin >> n;
    P process[n];
    for(int i = 0 ; i < n ; i++)
        cin >> process[i].arrival;
    for(int i = 0 ; i < n ; i++)
        cin >> process[i].burst;
    for(int i = 0 ; i < n ; i++)
        process[i].number = i;


    SRTF(n,process);

    return 0;
}

void SRTF(int n,P process[])
{
    int time, count = 0;
    P processing;
    int turnaround_time[n],burst_save[n];
    deque<P> waiting;

    for(int i = 0 ; i < n ; i++) //copy burst array
        burst_save[i] = process[i].burst;
   
    waiting.push_back(process[count]); //process1 in waiting queue
    time = process[count].arrival;
    count++;
    

    while(1)
    {    
        while(waiting.empty()) //Waiting queue is empty, but there will have a process enter the queue
        {
            time++;
            if(time == process[count].arrival && count < n) //new process arrive in waiting queue
            {
                waiting.push_back(process[count]);
                count++;
            }
        }

        sort(waiting.begin(), waiting.end(), cmp);;
        processing = waiting.front(); //execute the process in waiting queue
        waiting.pop_front();

        while(1) 
        {
              
            processing.burst--;
            time++;

            if(time == process[count].arrival && count < n) //new process arrive in waiting queue
            {
                if(process[count].burst<processing.burst)
                {
                    waiting.push_back(processing);
                    processing = process[count];
                    count++;
                }
              else
                {
                    waiting.push_back(process[count]);
                    count++;
                }
                
            }

            if(processing.burst == 0) //the process has finished
            {               
                turnaround_time[processing.number] = time - processing.arrival; // calculate turnaround time
                break;
            }
                 
        }

        if(waiting.empty() && count == n) //end if no new process will enter waiting queue and the queue is empty
            break;
   
    }
    
    output(n,burst_save,turnaround_time);
    
    return;   
}

void output(int n,int burst[],int turnaround[])
{
    int total_waiting = 0, total_turnaround = 0;
    for(int i = 0 ; i < n ; i++)
    {
        cout << turnaround[i]-burst[i] << " " << turnaround[i] <<'\n';
        total_waiting += turnaround[i]-burst[i];
        total_turnaround += turnaround[i];
    }

    cout << total_waiting << '\n' << total_turnaround;

    return;
}

