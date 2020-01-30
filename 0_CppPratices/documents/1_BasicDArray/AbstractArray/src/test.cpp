
#include <iostream>
#include "DArray.h"

int main()
{
	DArray a;
	a.InsertAt(0, 2.1);
	a.Display();

	a.PushBack(3.0);
	a.PushBack(3.1);
	a.PushBack(3.2);
	a.Display();

	a.DeleteAt(0);
	a.Display();
	a.InsertAt(0, 4.1);
	a.Display();

	DArray b;
	b.PushBack(21);
	b.Display();
	b.DeleteAt(0);
	b.Display();
	b.PushBack(22);
	b.SetSize( 5 );
	b.Display();

	DArray c(5, 3.4);
	c.PushBack(5.5);
	c.Display();
	c.SetSize( 10 );
	c.Display();

	DArray d;

	for(int i=0; i<17; i++)
	{
		d.PushBack(i);
		d.Display();
	}
	return 0;
}