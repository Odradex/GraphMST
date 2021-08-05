#pragma once
#include <math.h>
#include <vector>
#include <Windows.h>
#define INF 100000
#define nRad 15
using namespace System::Drawing;
using namespace System::Windows::Forms;

struct Node //Структура для хранения вершины
{
	int X; //X-координата вершины
	int Y; //Y-координата вершины
	bool selected = false; //Связанность вершины
	char letter = 'A'; //Отображаемый символ
};
struct Edge //Структура для хранения граней
{
	int startNode, endNode; //Начальная и конечная вершины
	int value; //Вес ребра
	int id = 0; //Номер ребра
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
	int nodeAmount; //Количество вершин в графе
	std::vector<Edge> edges; //Хранилище граней
	std::vector<Edge> path; //Хранилище каркаса
	std::vector<Node> nodes; //Хранилище вершин
	std::vector<bool> visited; //Хранилище посещенных граней/вершин
	int matrix[52][52] = { 0 }; //Матрица

public:
	Graph() // Конструктор
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
	void Clear(); //Обнуление всех данных
	int AddNode(Point^ p); //Добавление новой вершины с указанными координатами
	int detectNode(Point^ p); //Ищет вершину по указанным координатам и возвращает ее номер
	void DrawGraph(Graphics^ g, bool drawValues = false, Brush^ valuesBrush = Brushes::Black, bool drawTree = false); //Рисует граф на заданном элементе

	void AddEdge(int start, int end, int tbTag); //Связывает гранью две вершины
	void UpdateEdge(int tag, int value); //Обновляет грань новым значением (весом)

	void SetNodeSelect(int i, bool key); //Устанавливает "связанность" вершины.

	int GetMatrixElem(int x, int y); //Возвращает элемент матрицы
	Point GetNodePosition(int i); //Возврашает координаты вершины
	int GetNodeAmount(); //Возврашает количество вершин
	Node GetNode(int i); //Возврашает вершину с указанным номером
	std::vector<Edge> GetEdges(); //Возврашает список граней
	char GetNodeLetter(int i); //Возврашает символ вершины с указанным номером
	int GetMinWeight(); //Возврашает минимальный вес графа

	int UpdateValue(int x, int y, int value); //Обновление значения в матрице и грани

	void Save(System::IO::StreamWriter^ out); //Сохранение графа в текстовый файл
	void Load(System::IO::StreamReader^ in); //Загрузка графа из текстового файла

	bool CheckNodesConnection(); //Проверка связанности графа
	int dfs(int u, std::vector<bool> &visited); //Обход графа в глубину
	bool CheckEdgeExistence(int start, int end); //Проверка существования грани между 2 вершинами

	Edge findMinEdge(int n, std::vector<bool> visited); //Нахождение грани с минимальным весом, связанной с заданой вершиной
	void KraskalsMethod(); //Находжение каркаса графа методом Краскала
	void PrimaMethod(); //Находжение каркаса графа методом Прима
};

