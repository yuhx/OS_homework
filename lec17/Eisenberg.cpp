#include <pthread.h>
#include <iostream>
#define MAXTHREAD 10
using namespace std;

enum pstate {IDLE, WAITING, ACTIVE};
pstate flags[MAXTHREAD];
int turn;

void *main_thread(void *arg) 
{
	int id = *((int*)(&arg));
	bool stop;
	do
	{
		flags[id] = WAITING;
		int index = turn;
		while (index != id)
		{
			if (flags[index] != IDLE)
			{
				index = turn;
			}
			else
			{
				index = (index + 1) % MAXTHREAD;
			}
		}
		flags[id] = ACTIVE;
		stop = true;
		for (int i = 0; i < MAXTHREAD; i ++)
		{
			if ((flags[i] == ACTIVE) && (i != id))
			{
				stop = false;
			}
		}
		stop = stop && ((turn == id) || flags[turn] == IDLE);
	}
	while (!stop);

	turn = id;
	printf("Process %d enter\n", turn);
	//CS
	for (int i = 0; i < MAXTHREAD; i ++)
	{
		printf("%d", flags[i]);
	}
	printf("\n");
	int index = (turn + 1) % MAXTHREAD;
	while (flags[index] == IDLE)
	{
		index = (index + 1) % MAXTHREAD;
	}
	printf("Process %d exit\n\n", turn);
	turn = index;
	flags[id] = IDLE;

	return NULL;
}

int main()
{
	for (int i = 0; i < MAXTHREAD; i ++)
	{
		flags[i] = IDLE;
	}
	turn = 0;

	pthread_t tid[MAXTHREAD];
	for (int i = 0; i < MAXTHREAD; i ++)
	{
		pthread_create(&tid[i], NULL, main_thread, (void *)i);
	}
	for (int i = 0; i < MAXTHREAD; i ++)
	{
		pthread_join(tid[i], NULL);
	}
	return 0;
}