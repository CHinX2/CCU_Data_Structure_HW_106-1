//==============================
// Homework 3 - 1
//==============================
// 3-dimentional maze of the size 𝑋×𝑌×𝑍
// path() : search a path from (0,0,0) to (X-1,Y-1,Z-1)
// use move[dir].vert and move[dir].horiz to store the direction of the next move
//==============================
// belongs to CHinX2@20171114
//==============================
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
	int vert; //vertical 垂直(Y)
	int horiz; //horizontal 水平(X)
	int depth; //depth 深度(Z)
}mv;

int x, y, z; //store the size of maze
int maze[MAX][MAX][MAX];
int travers[MAX][MAX][MAX];
int check = 0;
int totalStep;

void dfs(mv* move,int now,int lx,int ly,int lz)
{
	int nx, ny, nz; //now position
	int kx, ky, kz;
	kx = ky = kz = -1;
	if (lx == x - 1 && ly == y - 1 && lz == z - 1)check = 1;
	travers[lx][ly][lz] = 1;

	if (lx == 0)kx = 0;
	if (ly == 0)ky = 0;
	if (lz == 0)kz = 0;

	for (nx = lx + kx; nx < x; nx++)
	{
		for (ny = ly + ky; ny < y ; ny++)
		{
			for (nz = lz + kz; nz < z; nz++)
			{
				if (maze[nx][ny][nz] == 0 && travers[nx][ny][nz] == 0)
				{
					printf("%d %d %d -> %d %d %d\n", lx,ly,lz, nx,ny,nz);
					if (check == 0 && nz-lz<2 && ny-ly<2 && nx-lx<2)
					{
						move[now].horiz = nx - lx;
						move[now].vert = ny - ly;
						move[now].depth = nz - lz;
						now++;
						totalStep = now;
						dfs(move, now, nx, ny, nz);
					}
				}
			}
		}
	}
}

void path(mv* move)
{
	int nx, ny, nz; //now position
	nx = ny = nz = 0;
	int i;
	for (i = 0; i < totalStep; i++)
	{
		nx += move[i].horiz;
		ny += move[i].vert;
		nz += move[i].depth;
		printf("%d %d %d\n", nx, ny, nz);
	}
}

int main()
{
	int bx, by, bz;
	bx = by = bz = 0;
	mv move[200];
	move[0].vert = 0;
	move[0].horiz = 0;
	move[0].depth = 0;
	int nowM = 1;

	/*set the size of maze*/
	printf("Please input the X, Y, Z values of the 3-d maze :\n");
	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &z);

	memset(maze, 0, x*y*z);
	memset(travers, 0, x*y*z);

	/*set the barriers in the maze*/
	printf("Please inpue the barriers' position(x y z), each put in one line :\n");
	printf("To end the input, please enter -1-1-1\n");
	do {
		scanf("%d%d%d", &bx, &by, &bz);
		if (maze[bx][by][bz]==0) {
			maze[bx][by][bz] = 1;
		}
		else {
			printf("Fatal input!\n");
			continue;
		}
	} while (bx >= 0 && by >= 0 && bz >= 0);

	if (maze[0][0][0] == 1)printf("There is no available path.\n");
	else {
		dfs(move,nowM,0,0,0);
		if(check==1)path(move);
		else {
			printf("There is no available path.\n");
		}
	}

	return 0;
}
