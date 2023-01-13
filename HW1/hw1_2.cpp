#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid;
    cout << "Main Process ID : " << getpid() << endl;

    pid = fork(); //fork 1
    
    if(pid == 0)
    {
        cout << "Fork 1. I'm the child " << getpid() << ", my parents is " << getppid() << ".\n";

        pid = fork(); //fork2 
        if(pid>0)
          wait(NULL);
        else if(pid == 0)
        {
            cout << "Fork 2. I'm the child " << getpid() << ", my parents is " << getppid() << ".\n";

            pid = fork(); //fork 3
            if(pid > 0)
              wait(NULL);
            else if(pid == 0)
              cout << "Fork 3. I'm the child " << getpid() << ", my parents is " << getppid() << ".\n"; 
        }
    }
    else if(pid > 0)
    {
        wait(NULL);
        pid = fork(); //fork 4
        if(pid == 0)
          cout << "Fork 4. I'm the child " << getpid() << ", my parents is " << getppid() << ".\n";
        else if(pid > 0)
        {
          wait(NULL); 
          pid = fork(); //fork 6
          if(pid > 0)
            wait(NULL);
          else if(pid == 0)
            cout << "Fork 6. I'm the child " << getpid() << ", my parents is " << getppid() << ".\n";

        }
          
        
        
        pid = fork(); //fork 5
        if(pid > 0)
          wait(NULL);
        else if(pid == 0)
          cout << "Fork 5. I'm the child " << getpid() << ", my parents is " << getppid() << ".\n"; 
        
          
                 
    }
    else
        printf("Error!");
       
    return 0;
}