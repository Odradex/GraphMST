#pragma once
class List
{
private:
	struct point
	{
		int value = 0;
		int start, end;
		int index = 0;
		point* next;
	};
	int size = 0;
	point* head;
	point* current;
public:
	void AddEdge(int start, int end, int value)
	{
		
	}
};

