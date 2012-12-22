#include <iostream>
#include <stdlib.h>
#include <cmath>

#define N 12

using namespace std;

/*
* program to write a counterpoint piece of music given an input
* Mappings are s.t. middle c -> 49
*/

int calcNote(int lastNote, int note[], int iter);

int main()
{
  srand48(12);
  int note[N], i;
  note[0] = 14;
  cout << "initialised" << endl;
  cout << note[0] << " ";
  for(i=1; i<N; ++i)
  {
    note[i] = calcNote(note[i-1],  note, i);
    cout << note[i] << " ";
  }

  cout << endl;

}

int calcNote(int lastNote, int note[], int iter)
{
  int newNote, interval, sign, complete;
  complete = 0;

  while(0 == complete)
  {
    interval = (int) (8*drand48());
    sign = 0;

    if(6 == interval) // not allowed jumps of 6
    {
      complete = 0;
    }
    else if(5 == interval) //can only allow e->c' || a->f'
    {
      if(2 != abs(lastNote%7) || 5 != abs(lastNote%7))
      {
        complete = 0;
      }
      else
      {
        sign = 1;
        complete = 1;
      }
    }
    /*Can't have any f->b combos*/
    else  if(3 == abs(lastNote%7)) //=f
    {
      if(3 == interval) // ensure no f->b (+3)
      {
        sign = 1; // the sign won't change now
        interval = interval *(-1); 
      }
      if(4 == interval) // ensure no f'->b (-4)
      {
        sign = 1; // the sign won't change now
      }
      complete = 1;
    }
    else if(6 == abs(lastNote%7)) //=b
    {
      if(3 == interval) // ensure no b b->f (-3)
      {
        sign = 1; // the sign won't change now
      }
      if(4 == interval) // ensure no b->f' (+4)
      {
        interval = interval *(-1); 
        sign = 1; // the sign won't change now
      }
      complete = 1;
    }
    else
    {
      complete = 1;
    }

    if(sign != 1 && drand48() > 0.5)
    {
      interval = interval * (-1);
    }
    if(lastNote+interval > note[0]+9 || lastNote+interval < note[0]-9)
    {
      complete = 0;
    }
    if((7 == abs(interval) || 0 == abs(interval)) && abs(note[iter-2]%7) == abs(lastNote%7))
    {
      complete = 0;
    }
  }
  newNote = lastNote + interval;
  return newNote;
  
}
