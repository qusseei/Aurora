#include <stdio.h>
int main()
{
	float score;
	int Class;
	
	while(scanf("%f",&score),score<0|score>100)
	{
		printf("%s\n","Wrong Score");
	}

	Class = (int)(score/10);
	if(Class == 10)
		Class = 9;
	else if(Class < 6)
		Class = 5;
	else
		Class = Class;

	switch(Class)
	{
		case 9:printf("A\n");break;
		case 8:printf("B\n");break;
		case 7:printf("C\n");break;
		case 6:printf("D\n");break;
		case 5:printf("E\n");break;
		default:printf("Wrong\n");break;
	}
	return 0;
}