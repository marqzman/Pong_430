#ifndef BOARD_H
#define BOARD_H





/*
struct paddle {
	int dir;		// Not really needed if the potentiometer determines position instead of acceleration
	int x;
}; */

/*
struct board {
	struct ball myBall1;
	struct paddle myPaddle1;
};*/

Ball makeBall(int x, int y) {
	Ball temp;
	temp.dir = UP;
	temp.x = x;
	temp.y = y;

	return temp;
}

/*
struct paddle makePaddle(int x) {
	struct paddle temp;
	temp.x = x;

	return temp;
}*/

#endif
