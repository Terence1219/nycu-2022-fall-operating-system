#include<iostream>
#include <queue>
#include <vector>

using namespace std;

int FIFO(int frame,int number, int ref_str[]);
int LRU(int frame,int number, int ref_str[]);
int LFU(int frame,int number, int ref_str[]);
int farthest(vector<int> inframe, int lastuse[]);
int least_freq(vector<int> inframe, int freq[], int firstin[]);

int main()
{
    int frame, number;
    cin >> frame;
    cin >> number;

    int ref_str[number];
    for(int i=0;i<number;i++)
        cin >> ref_str[i];

    cout << FIFO(frame,number,ref_str) << '\n';
    cout << LRU(frame,number,ref_str) << '\n';
    cout << LFU(frame,number,ref_str);

    return 0;
}

int FIFO(int frame,int number, int ref_str[])
{
    int space = frame, current = 0, pagefault = 0;
    queue<int> inframe;
    bool in[20] = {false};

    while(current < number)
    {
        if(space > 0)
        {
            if(!in[ref_str[current]])
            {
                inframe.push(ref_str[current]);
                in[ref_str[current]] = true;
                space--;
                pagefault++;
            }          
        }
        else
        {
            if(!in[ref_str[current]])
            {
                in[inframe.front()] = false;
                inframe.pop();
                inframe.push(ref_str[current]);
                in[ref_str[current]] = true;
                pagefault++;
            }           
        }
        current++;
    }
    return pagefault;
}

int LRU(int frame,int number, int ref_str[])
{
    int space = frame, current = 0, pagefault = 0;
    vector<int> inframe;
    int lastuse[20];
    bool in[20] = {false};

    while(current < number)
    {
        if(space > 0)
        {
            if(!in[ref_str[current]])
            {
                inframe.push_back(ref_str[current]);
                lastuse[ref_str[current]] = current;
                in[ref_str[current]] = true;
                space--;
                pagefault++;
            }  
            else 
               lastuse[ref_str[current]] = current;     
        }
        else
        {
            if(!in[ref_str[current]])
            {
                int replaced = farthest(inframe, lastuse);
                in[inframe[replaced]] = false;
                inframe[replaced] = ref_str[current];
                in[ref_str[current]] = true;
                lastuse[ref_str[current]] = current;
                pagefault++;
            }
            else
                lastuse[ref_str[current]] = current;        
        }
        current++;
    }
    return pagefault;
}

int LFU(int frame,int number, int ref_str[])
{
    int space = frame, current = 0, pagefault = 0;
    vector<int> inframe;
    int firstin[20] = {0}, freq[20] = {0};
    bool in[20] = {false};

    while(current < number)
    {
        if(space > 0)
        {
            if(!in[ref_str[current]])
            {
                inframe.push_back(ref_str[current]);
                firstin[ref_str[current]] = current;
                in[ref_str[current]] = true;
                freq[ref_str[current]]++;
                space--;
                pagefault++;
            }  
            else 
                freq[ref_str[current]]++;                   
        }
        else
        {
            if(!in[ref_str[current]])
            {
                int replaced = least_freq(inframe, freq, firstin);
                in[inframe[replaced]] = false;
                freq[inframe[replaced]] = 0;
                inframe[replaced] = ref_str[current];
                in[ref_str[current]] = true;
                firstin[ref_str[current]] = current;
                freq[ref_str[current]]++;
                pagefault++;
            }
            else
                freq[ref_str[current]]++;
        }
        current++;
    }
    return pagefault;
}

int farthest(vector<int> inframe, int lastuse[])
{
    int least = lastuse[inframe[0]], idx=0;
    for(int i=1;i<inframe.size();i++)
    {
        if(least > lastuse[inframe[i]])
        {
            least = lastuse[inframe[i]];   
            idx = i;
        }
    }
    return idx;
}

int least_freq(vector<int> inframe, int freq[], int firstin[])
{
    int least = freq[inframe[0]], idx=0;

    for(int i=1;i<inframe.size();i++)
    {
        if(least > freq[inframe[i]])
        {
            least = freq[inframe[i]];   
            idx = i;       
        }
        else if (least == freq[inframe[i]])
        {
            if(firstin[inframe[idx]] > firstin[inframe[i]])
                idx = i;
        }
    }
    return idx;
}