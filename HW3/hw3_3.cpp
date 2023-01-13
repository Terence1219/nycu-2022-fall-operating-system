# include <iostream>
# include <queue>
using namespace std;

void RR(int n,int arrival[],int burst[], int q);
void output(int n,int burst[],int turnaround[]);

int main()
{
    int n,q;
    cin >> n;
    int arrival[n],burst[n];
    for(int i = 0 ; i < n ; i++)
        cin >> arrival[i];
    for(int i = 0 ; i < n ; i++)
        cin >> burst[i];
    cin >> q;

    RR(n,arrival,burst,q);

    return 0;
}

void RR(int n,int arrival[],int burst[], int q)
{
    int time = 0, count = 0, processing;
    int turnaround_time[n],burst_save[n];
    queue<int> waiting,FCFS;

    for(int i = 0 ; i < n ; i++) //copy burst array
        burst_save[i] = burst[i];

    waiting.push(count); //process1 in waiting queue
    time = arrival[count];
    count++;
    
    while(1)
    {    
        while(waiting.empty()) //Waiting queue is empty, but there will have a process enter the queue
        {
            time++;
            if(time == arrival[count] && count < n) //new process arrive in waiting queue
            {
                waiting.push(count);
                count++;
            }
        }
        processing = waiting.front(); //execute the process in waiting queue
        waiting.pop();

        int processing_time = 0; //execution time
        while(processing_time < q) 
        {
                                
            burst[processing]--;
            time++;

            if(time == arrival[count] && count < n) //new process arrive in waiting queue
            {
                waiting.push(count);
                count++;
            }

            if(burst[processing] == 0) //the process has finished
            {
                turnaround_time[processing] = time - arrival[processing]; // calculate turnaround time
                break;
            }
            processing_time++;
                      
        }
        if(burst[processing] > 0) //put the unfinished process into FCFS queue
            FCFS.push(processing);

        if(waiting.empty() && !FCFS.empty())
        {
            processing = FCFS.front(); //execute the process in FCFS queue
            FCFS.pop();
            while(waiting.empty())
            {
                burst[processing]--;
                time++;

                if(time == arrival[count] && count < n) //new process arrive in waiting queue, current process in FCFS
                {
                    waiting.push(count);
                    count++;
                    FCFS.push(processing);
                }

                if(burst[processing] == 0) //the process has finished
                {
                    turnaround_time[processing] = time - arrival[processing]; // calculate turnaround time
                    if(!FCFS.empty())
                    {
                        processing = FCFS.front(); 
                        FCFS.pop();
                    }
                    else
                        break;
                }
            }
        }

        if((waiting.empty() && FCFS.empty()) && count == n)
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