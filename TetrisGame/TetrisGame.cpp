#include "Header.h"

int main()
{
	float prev = (float)clock() / CLOCKS_PER_SEC;
	// clock() 프로그램 시작부터 함수가 실행된 시점의 시간을 구한다. CLOCKS_PER_SEC 는 보통 1000 이다.

	while (true)
	{
		float currenttime = (float)clock() / CLOCKS_PER_SEC;
		// prev 에서 clock 함수가 실행된 시점과 currentrime 에서 실행된 시점을 빼주면 while 문이 한 번 돌아간 시간이 계산이 되는 것이다.
		float deltatime = currenttime - prev;	
	}
}
