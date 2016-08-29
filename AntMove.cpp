#include "stdafx.h"


using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cassert>
#include <errno.h>
#include<vector>
/*************************************************/
/* ------------------------------------------>   */
/* 0                                        27   */
/*************************************************/
#define MAX_LENGTH 27
#define MIN_LENGTH 0   //0-27长度

#define DIRECT_LEFT -1   //向左减一
#define DIRECT_RIGHT 1    //向右加一

#define ANT_NUM 5  //蚂蚁的数量

class Ant
{
public:
	Ant(int position,int direction)
	{
		this->position = position;
		if(direction == DIRECT_RIGHT)
		{
			this->direction = DIRECT_RIGHT;
		}
		else
		{
			this->direction = DIRECT_LEFT;
		}
	}
	~Ant(){}
	//蚂蚁出了木棒了嘛 走出返回true
	bool IsOut()
	{
		if(position <= MIN_LENGTH || position >= MAX_LENGTH)
			return true;
		else
			return false;
	}
	//蚂蚁移动函数
	void Walk()
	{
		if(!IsOut())
			position = position + direction * step;
	}
	//蚂蚁是否遇到另一个蚂蚁 遇到返回true
	bool IsEncounter(Ant *ant)
	{
		return (ant->position == this->position);
	}
	//改变蚂蚁的前进方向
	void ChangeDistation()
	{
		direction = -1 * direction;
	}
	static const int step = 1; //蚂蚁前进一步.
private:
	int position; 	     //蚂蚁的初始位置
	int direction;   //蚂蚁的前进方向
	
};
/**
* 因为有5只Ant，所以组合之后有32种组合.刚好用5位二进制来表示,
* 如果为0则表示Ant往0的方向走 如果为1,则表示往27的方向走
* 
* 注:在通过Ant的构造函数设置初始值时,通过过滤把0修改成了-1.
**/

void GetDirections(int seed,int ret[ANT_NUM])
{
	ret[0] = seed % 2;
	ret[1] = seed / 2 % 2;
	ret[2] = seed / 4 % 2;
	ret[3] = seed / 8 % 2;
	ret[4] = seed / 16 % 2;
}
//蚂蚁都出去了
bool IsAllOut(Ant *ant[ANT_NUM])
{
	for(int i = 0;i < ANT_NUM;i++)
	{
		if(!ant[i]->IsOut())
			return false;
	}
	return true;
}

//处理蚂蚁相遇情况
void DealEncounter(Ant *ant[ANT_NUM])
{
	for(int i = 0;i < ANT_NUM;i++)
	{
		for(int j = i + 1;j < ANT_NUM;j++)
		{
			if(ant[i]->IsEncounter(ant[j]))
			{
				ant[i]->ChangeDistation();
				ant[j]->ChangeDistation();
			}
		}
	}
}
int main()
{
	int iniPos[ANT_NUM] = {3, 7, 11, 17, 23};
	Ant *ant[ANT_NUM] = {NULL};
	int direct[ANT_NUM];
	
	int time = 0; //时间
	int maxTime = 0;
	int minTime = MAX_LENGTH;
	//共32中情况
	for(int i = 0;i < 32;i++)
	{
		GetDirections(i,direct);
		//cout<<"direct:"<<direct[0]<<" "<<direct[1]<<" "<<direct[2]<<" "
		//	<<direct[3]<<" "<<direct[4]<<" "<<endl;
		for(int j = 0;j < ANT_NUM;j++)
		{
			ant[j] = new Ant(iniPos[j],direct[j]);	
		}			
		while(!IsAllOut(ant))
		{
			for(int k = 0;k < ANT_NUM;k++)
				if(!ant[k]->IsOut())
					ant[k]->Walk();
			time++;
			DealEncounter(ant);
		}
		cout<<"第 "<<i<<"种情况："<<direct[0]<<" "<<direct[1]<<" "<<direct[2]<<" "
			<<direct[3]<<" "<<direct[4]<<"  time = "<<time<<endl;	
		if(time >= maxTime)
			maxTime = time;
		if(time <= minTime)
			minTime = time;
		time = 0;
	}
	cout<<"最长时间为： "<<maxTime<<" 最短时间为： "<<minTime<<endl;
	system("pause");
	return 0;
}