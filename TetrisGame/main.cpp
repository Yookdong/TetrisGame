#include "Header.h"

#define INTERVAL 1.0/60.0 // 60FPS 기준으로 한 것

int main()
{
	srand(time(0));

	showConsoleCursor(false); // 화면의 콘솔 커서 끄기

	// clock() 프로그램 시작부터 함수가 실행된 시점의 시간을 구한다. CLOCKS_PER_SEC 는 보통 1000 이다.
	float prev = (float)clock() / CLOCKS_PER_SEC;

	Display* DisPlay = new Display;

	GameEngine* GameManger = new GameEngine;
	GameManger->Init(); // 게임 초기 설정

	while (true)
	{
		float currenttime = (float)clock() / CLOCKS_PER_SEC;
		// prev 에서 clock 함수가 실행된 시점과 currentrime 에서 실행된 시점을 빼주면 while 문이 한 번 돌아간 시간이 계산이 되는 것이다.

		float deltatime = currenttime - prev;

		if (deltatime < INTERVAL)
		{
			continue; // 한 프레임보다 빠르면 while 문을 다시 돌려 시간을 맞춘다. -> 60 프레임보다 빠르다는 것
		}
		prev = currenttime; // 갱신을 해주는 것

		// printf("%d : %.3f\n", CLOCKS_PER_SEC, currenttime); // 정확히 한 프레임마다 출력이 되는것을 알 수 있다.

		bool left = keyState('a');
		bool right = keyState('d');
		bool down = keyState('s');
		bool rotate = keyState('w');

		if (left) // 이 조건문 자체를 bool 을 파라미터 값으로 받는 함수로 변경하기
		{
			// 왼쪽으로 블럭 이동
			GameManger->Next(deltatime,'a');
		}
		else if (right)
		{
			GameManger->Next(deltatime, 'd');
		}
		else if (down)
		{
			GameManger->Next(deltatime, 's');
		}
		else if (rotate)
		{
			GameManger->Next(deltatime, 'w');
		}
		else
		{
			// 이동하지 않고 그냥 떨어지게
			GameManger->Next(deltatime, 0);
		}

		// 화면 출력
		GameManger->MakeDisplayData();
		DisPlay->draw();

		// 게임 상태 판별
		if (GameManger->CurrentState == GameState::GAMEOVER) break;
	}
}
