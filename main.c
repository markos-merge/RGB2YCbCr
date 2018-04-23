/*
 * main.c
 *
 *  Created on: Apr 22, 2018
 *      Author: markos
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void RGB2YCbCr_Ciml(unsigned char r[64], unsigned char g[64], unsigned char b[64],
		char y[64], char cb[64] , char cr[64] );

void RGB2YCbCr(unsigned char r[64], unsigned char g[64], unsigned char b[64],
		char y[64], char cb[64] , char cr[64] );

int main()
{
	int i ;
	unsigned char r[64], g[64], b[64];
	char y[64],cb[64],cr[64],yy[64],ccb[64],ccr[64];
	short resy[64], rescb[64],rescr[64];
	srand(time(NULL));
	float ta,tc;
	clock_t start,end;

	for(i = 0; i < 64; i++)
	{
		r[i] = rand()%255;
		b[i] = rand()%255;
		g[i] = rand()%255;
	}
	start = clock();
	RGB2YCbCr_Ciml(r,g,b,y,cb,cr);
	end = clock();
	tc = (float)(end - start) / CLOCKS_PER_SEC;
	start =clock();
	RGB2YCbCr(r,g,b,yy,ccb,ccr);
	end = clock();
	ta = (float)(end - start) / CLOCKS_PER_SEC;
	for(i = 0; i <64 ;i ++)
	{
		resy[i] = abs(y[i]-yy[i]);
		rescb[i] = abs(cb[i]-ccb[i]);
		rescr[i] = abs(cr[i]-ccr[i]);
//		printf("%d ",resy[i]);
	}

	printf("\n C implementation  %f\n Asm implementation %f\n",tc,ta);
	return 0;




}

void RGB2YCbCr_Ciml(unsigned char r[64], unsigned char g[64], unsigned char b[64],
		char y[64], char cb[64] , char cr[64]  )
{

short _r,_g,_b;
unsigned char i = 0;
for( i = 0; i < 64; i++)
{
		_b = b[i];
		_g = g[i];
		_r = r[i];
		y[i] = ((77*_r+150*_g+29*_b)>>8)-128;
		cb[i] = ((-43*_r-85*_g+128*_b)>>8);
		cr[i] = ((128*_r-107*_g-21*_b)>>8);
	}
}
