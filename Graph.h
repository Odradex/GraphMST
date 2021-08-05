#pragma once
#include <math.h>
#include <vector>
#include <Windows.h>
#define INF 100000
#define nRad 15
using namespace System::Drawing;
using namespace System::Windows::Forms;

struct Node //��������� ��� �������� �������
{
	int X; //X-���������� �������
	int Y; //Y-���������� �������
	bool selected = false; //����������� �������
	char letter = 'A'; //������������ ������
};
struct Edge //��������� ��� �������� ������
{
	int startNode, endNode; //��������� � �������� �������
	int value; //��� �����
	int id = 0; //����� �����
	bool selected = false; //

	Edge() : startNode(0), endNode(0), value(0), id(0), selected(false)  {}
	Edge(int start, int end, int value, int id, bool selected)
		: startNode(start), endNode(end), value(value), id(id), selected(selected) {}
	~Edge() {}
	Edge operator=(Edge e)
	{
		startNode = e.startNode;
		endNode = e.endNode;
		value = e.value;
		id = e.id;
		selected = e.selected;
		return *this;
	}
};
class Graph
{
private:
	int nodeAmount; //���������� ������ � �����
	std::vector<Edge> edges; //��������� ������
	std::vector<Edge> path; //��������� �������
	std::vector<Node> nodes; //��������� ������
	std::vector<bool> visited; //��������� ���������� ������/������
	int matrix[52][52] = { 0 }; //�������

public:
	Graph() // �����������
	{
		nodeAmount = 0;
	}
	~Graph()
	{
		edges.clear();
		path.clear();
		visited.clear();
		nodes.clear();
		nodeAmount = 0;
	}
	void Clear(); //��������� ���� ������
	int AddNode(Point^ p); //���������� ����� ������� � ���������� ������������
	int detectNode(Point^ p); //���� ������� �� ��������� ����������� � ���������� �� �����
	void DrawGraph(Graphics^ g, bool drawValues = false, Brush^ valuesBrush = Brushes::Black, bool drawTree = false); //������ ���� �� �������� ��������

	void AddEdge(int start, int end, int tbTag); //��������� ������ ��� �������
	void UpdateEdge(int tag, int value); //��������� ����� ����� ��������� (�����)

	void SetNodeSelect(int i, bool key); //������������� "�����������" �������.

	int GetMatrixElem(int x, int y); //���������� ������� �������
	Point GetNodePosition(int i); //���������� ���������� �������
	int GetNodeAmount(); //���������� ���������� ������
	Node GetNode(int i); //���������� ������� � ��������� �������
	std::vector<Edge> GetEdges(); //���������� ������ ������
	char GetNodeLetter(int i); //���������� ������ ������� � ��������� �������
	int GetMinWeight(); //���������� ����������� ��� �����

	int UpdateValue(int x, int y, int value); //���������� �������� � ������� � �����

	void Save(System::IO::StreamWriter^ out); //���������� ����� � ��������� ����
	void Load(System::IO::StreamReader^ in); //�������� ����� �� ���������� �����

	bool CheckNodesConnection(); //�������� ����������� �����
	int dfs(int u, std::vector<bool> &visited); //����� ����� � �������
	bool CheckEdgeExistence(int start, int end); //�������� ������������� ����� ����� 2 ���������

	Edge findMinEdge(int n, std::vector<bool> visited); //���������� ����� � ����������� �����, ��������� � ������� ��������
	void KraskalsMethod(); //���������� ������� ����� ������� ��������
	void PrimaMethod(); //���������� ������� ����� ������� �����
};

