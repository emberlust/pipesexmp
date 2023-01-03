#include <process.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

bool isPrime(int number)
{
   bool prime = true;

   if(number == 1)
   {
      return false;
   }

   for(int i = 2; i * i <= number; i++)
   {
      if(number % i == 0)
      {
         prime = false;
         break;
      }
   }
   return prime;
}

int main(int argc, char *argv[])
{

   //daca nu sunt argumente, procesul este considerat parinte
   if(argc == 1)
   {
      //buffer pentru cititrea outputului
      char   psBuffer[128];
      //pipeurile aferente proceselor
      FILE   *pPipe[10];

      //offset pentru intervale
      int offset = 1000;

      //pregatirea celor 10 procese
      for(int i = 0; i < 10; i++)
      {

         //pregatirea comenzii ce va fi executata de popen
         std::string prog = argv[0];
         std::string arg1;

         if(i == 0)  arg1 = std::to_string(i + 1);
         else arg1 = std::to_string(i * offset + 1);

         std::string arg2 = std::to_string((i + 1) * offset);

         std::string command = "\"" + prog + "\"" + " " + arg1 +  " " + arg2;

         //deschiderea unui nou pipe
         pPipe[i] = _popen(command.c_str(),"rt");
      }

      //testeaza daca mai sunt pipeuri deschide
      bool canRead = true;
      while (canRead == true)
      {
         canRead = false;
         //citeste fiecare pipe
         for(int i = 0; i < 10; i++)
         {
            //daca pipeul este deschis, afiseaza output si seteaza variabila pe true pentru a mai incerca alta citire
            if(fgets(psBuffer, 128, pPipe[i]) != nullptr)
            {
               canRead = true;
               puts(psBuffer);
            }
         }
      }
   }
   //in cazul unui proces copil, verifica numerele din interval
   else
   {
      int a = atoi(argv[1]);
      int b = atoi(argv[2]);
      for(int i = a; i < b; i++)
      {
         if(isPrime(i))
         {
            std::cout<<i<<std::endl;
         }
      }
   }   
   return 0;
}