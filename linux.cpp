#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>

bool isPrime(int number)
{
   bool prime = true;

   if(number <= 1)
   {
      prime = false;
   }
   else{
      for(int i = 2; i * i <= number; i++)
      {
         if(number % i == 0)
         {
            prime = false;
            break;
         }
      }
   }

   return prime;
}

#define MSGSIZE 16

int main()
{
   char buff[MSGSIZE];
   int fds[10][2];

   pid_t proc;

   for(int i=0; i<10; i++){
      pipe(fds[i]);
   }

    for(int i = 0; i < 10; i++)
    {
        proc = fork();
        if(proc == 0)
        {
            for(int j = i * 1000; j < (i+1) * 1000; j++)
            {
               if(isPrime(j))
               {
                  write(fds[i][1], std::to_string(j).c_str() , MSGSIZE);
               }
            }
            close(fds[i][1]);
            return 0;
        }
    }
   
   if(proc > 0)
   {

      for(int i = 0; i < 10; i++)
      {
         close(fds[i][1]);
      }
      
      bool ok = true;
      while (ok)
      {
         ok = false;
         for(int i = 0; i < 10; i++)
         {
            if(read(fds[i][0],buff,MSGSIZE) > 0)
            {
               std::cout<<buff<<std::endl;
               ok = true;
            }
            else
            {
               close(fds[i][0]);
            }
         }
      }
   }
   
   return 0;
}