#include <stdio.h>
#include <stdlib.h>
#include "pingpong.h"

// operating system check

task_t Pang, Peng, Ping, Pong, Pung ;

void Body (void * arg)
{
   int i,j ;

   printf ("%s INICIO em %4d ms\n", (char *) arg, systime()) ;

   for (i=0; i<40000; i++)
      for (j=0; j<40000; j++) ;

   printf ("%s FIM    em %4d ms\n", (char *) arg, systime()) ;
   task_exit (0) ;
}

int main (int argc, char *argv[])
{
   int i,j ;

   pingpong_init () ;

   printf ("Main INICIO em %4d ms\n", systime()) ;

   task_create (&Pang, Body, "    Pang") ;
   task_create (&Peng, Body, "        Peng") ;
   task_create (&Ping, Body, "            Ping") ;
   task_create (&Pong, Body, "                Pong") ;
   task_create (&Pung, Body, "                    Pung") ;

   for (i=0; i<20000; i++)
      for (j=0; j<40000; j++) ;

   printf ("Main FIM    em %4d ms\n", systime()) ;
   task_exit (0);

   exit (0) ;
}
