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
#define MIN_LENGTH 0   //0-27����

#define DIRECT_LEFT -1   //�����һ
#define DIRECT_RIGHT 1    //���Ҽ�һ

#define ANT_NUM 5  //���ϵ�����

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
	//���ϳ���ľ������ �߳�����true
	bool IsOut()
	{
		if(position <= MIN_LENGTH || position >= MAX_LENGTH)
			return true;
		else
			return false;
	}
	//�����ƶ�����
	void Walk()
	{
		if(!IsOut())
			position = position + direction * step;
	}
	//�����Ƿ�������һ������ ��������true
	bool IsEncounter(Ant *ant)
	{
		return (ant->position == this->position);
	}
	//�ı����ϵ�ǰ������
	void ChangeDistation()
	{
		direction = -1 * direction;
	}
	static const int step = 1; //����ǰ��һ��.
private:
	int position; 	     //���ϵĳ�ʼλ��
	int direction;   //���ϵ�ǰ������
	
};
/**
* ��Ϊ��5ֻAnt���������֮����32�����.�պ���5λ����������ʾ,
* ���Ϊ0���ʾAnt��0�ķ����� ���Ϊ1,���ʾ��27�ķ�����
* 
* ע:��ͨ��Ant�Ĺ��캯�����ó�ʼֵʱ,ͨ�����˰�0�޸ĳ���-1.
**/

void GetDirections(int seed,int ret[ANT_NUM])
{
	ret[0] = seed % 2;
	ret[1] = seed / 2 % 2;
	ret[2] = seed / 4 % 2;
	ret[3] = seed / 8 % 2;
	ret[4] = seed / 16 % 2;
}
//���϶���ȥ��
bool IsAllOut(Ant *ant[ANT_NUM])
{
	for(int i = 0;i < ANT_NUM;i++)
	{
		if(!ant[i]->IsOut())
			return false;
	}
	return true;
}

//���������������
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
	
	int time = 0; //ʱ��
	int maxTime = 0;
	int minTime = MAX_LENGTH;
	//��32�����
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
		cout<<"�� "<<i<<"�������"<<direct[0]<<" "<<direct[1]<<" "<<direct[2]<<" "
			<<direct[3]<<" "<<direct[4]<<"  time = "<<time<<endl;	
		if(time >= maxTime)
			maxTime = time;
		if(time <= minTime)
			minTime = time;
		time = 0;
	}
	cout<<"�ʱ��Ϊ�� "<<maxTime<<" ���ʱ��Ϊ�� "<<minTime<<endl;
	system("pause");
	return 0;
}