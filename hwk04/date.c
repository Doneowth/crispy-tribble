#include "types.h"
#include "user.h"
#include "date.h"

void 
display()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	printf(1,"%d",r.month);
	printf(1,"/%d",r.day);
	printf(1,"/%d",r.year);
	printf(1," ");
	printf(1,"%d",r.hour);
	printf(1,":%d",r.minute);
	printf(1,":%d\n",r.second);
}

int 
main(int argc, char **argv) 
{
    if (argc == 1)
        display();

    exit(); //don’t use return
}