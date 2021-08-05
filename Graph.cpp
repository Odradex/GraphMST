#include "Graph.h"
/*
CPP-файл класса Graph содержит 
определения обьявленных в нем методов и свойств
*/
void Graph::Clear()
{
	edges.clear();
	path.clear();
	visited.clear();
	nodes.clear();
	for (size_t i = 0; i < nodeAmount; i++)
		for (size_t j = 0; j < nodeAmount; j++)
			matrix[i][j] = 0;

	nodeAmount = 0;
}

int Graph::AddNode(Point^ p)
{
	if (nodeAmount >= 52)
	{
		MessageBox::Show("Вы добавили максимальное количество вершин", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return 0;
	}

	nodes.push_back(Node{ p->X, p->Y, false, (char)(nodeAmount + (nodeAmount < 26 ? 65 : 71)) });

	++nodeAmount;
	return 0;
}
int Graph::detectNode(Point^ p)
{
	for (int i = 0; i < nodeAmount; i++)
		if (abs(nodes[i].X - p->X) < nRad && abs(nodes[i].Y - p->Y) < nRad)
			return i;

	return -1;
}
void Graph::DrawGraph(Graphics^ g, bool drawValues, Brush^ valuesBrush, bool drawTree)
{
	Font^ nodeFont = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
	Brush^ nodeBrush = Brushes::WhiteSmoke;
	System::String^ t = gcnew System::String("H");
	Pen^ chosenPen = drawTree ? gcnew System::Drawing::Pen(Color::Green, 3) : gcnew System::Drawing::Pen(Color::Red, 3);
	Pen^ defaultPen = drawTree ? gcnew System::Drawing::Pen(Color::DimGray, 3) : gcnew System::Drawing::Pen(Color::Blue, 3);
	for (Edge e : edges)
	{
		g->DrawLine((e.selected && drawTree) ? chosenPen : defaultPen, GetNodePosition(e.startNode), GetNodePosition(e.endNode));
		if (drawValues)
			g->DrawString(e.value + "", nodeFont, valuesBrush, float(nodes[e.endNode].X + nodes[e.startNode].X) / 2, float(nodes[e.endNode].Y + nodes[e.startNode].Y) / 2 + 4);
	}
	for (size_t i = 0; i < nodeAmount; i++)
	{
		g->DrawEllipse((!nodes[i].selected || drawTree) ? chosenPen : defaultPen, nodes[i].X - nRad, nodes[i].Y - nRad, nRad * 2, nRad * 2);
	}
	for (size_t i = 0; i < nodeAmount; i++)
	{
		t = "H";
		t = t->Replace('H', nodes[i].letter);

		g->FillEllipse(nodeBrush, nodes[i].X - nRad + 1.5, nodes[i].Y - nRad + 1.5, float(nRad * 2 - 3), float(nRad * 2 - 3));
		g->DrawString(t, nodeFont, Brushes::Black, nodes[i].X - nRad / 2, nodes[i].Y - nRad / 2);
	}
}
void Graph::AddEdge(int start, int end, int tbTag)
{
	Edge temp;
	temp.endNode = end;
	temp.startNode = start;
	temp.id = tbTag;
	temp.value = 0;

	edges.push_back(temp);
}

void Graph::UpdateEdge(int tag, int value)
{
	for (int i = 0; i < edges.size(); i++)
		if (edges[i].id == tag)
		{
			edges[i].value = value;
			matrix[edges[i].startNode][edges[i].endNode] = value;
			matrix[edges[i].endNode][edges[i].startNode] = value;
		}
}
void Graph::SetNodeSelect(int i, bool key) { nodes[i].selected = key; }

int Graph::GetMatrixElem(int x, int y) { return matrix[x][y]; }
Point Graph::GetNodePosition(int i) { return Point(nodes[i].X, nodes[i].Y); }
int Graph::GetNodeAmount() { return nodeAmount; }
Node Graph::GetNode(int i) { return nodes[i]; }
std::vector<Edge> Graph::GetEdges() { return edges; }
char Graph::GetNodeLetter(int i) { return nodes[i].letter; }
int Graph::GetMinWeight()
{
	int temp = 0;
	for (Edge p : path)
		temp += p.value;
	return temp;
}
int Graph::UpdateValue(int x, int y, int value)
{
	if (matrix[x][y] == 0)
		return -1;

	matrix[x][y] = value;
	matrix[y][x] = value;

	for (size_t i = 0; i < edges.size(); i++)
		if ((edges[i].endNode == x && edges[i].startNode == y) || (edges[i].endNode == y && edges[i].startNode == x))
		{
			edges[i].value = value;
			return edges[i].id;
		}
	return -1;
}

void Graph::Save(System::IO::StreamWriter^ out)
{
	out->WriteLine("Node amount = " + nodeAmount);

	out->WriteLine("[nodePositions]");
	for (Node n : nodes)
		out->WriteLine(n.X + ";" + n.Y);

	out->WriteLine("[matrix]");
	for (size_t i = 0; i < nodeAmount; i++)
	{
		for (size_t j = 0; j < nodeAmount; j++)
		{
			out->Write(matrix[i][j] + "\t");
		}
		out->WriteLine();
	}

}
void Graph::Load(System::IO::StreamReader^ in)
{
	this->Clear();
	System::String^ line;
	while ((line = in->ReadLine()) != nullptr)
	{
		if (line->Contains("Node amount"))
		{
			nodeAmount = System::Convert::ToInt32(line->Replace("Node amount = ", ""));
			nodes.reserve(nodeAmount);
		}
		if (line == "[matrix]")
		{
			for (size_t i = 0; i < nodeAmount; i++)
			{
				line = in->ReadLine();
				for (size_t j = 0; j < nodeAmount; j++)
					matrix[i][j] = System::Convert::ToInt32(line->Split('\t')[j]);
			}
			for (size_t i = 0; i < nodeAmount; i++)
			{
				for (size_t j = i; j < nodeAmount; j++)
				{
					if (matrix[i][j] > 0)
					{
						edges.push_back(Edge{ (int)i, (int)j, (int)matrix[i][j], (int)(edges.size() + 1), true });
						nodes[i].selected = true;
						nodes[j].selected = true;
					}
				}
			}
		}
		if (line == "[nodePositions]")
			for (size_t i = 0; i < nodeAmount; i++)
			{
				line = in->ReadLine();
				this->AddNode(Point(System::Convert::ToInt32(line->Split(';')[0]), System::Convert::ToInt32(line->Split(';')[1])));
				nodes[i].letter = (char)i + (i < 26 ? 65 : 71);
				nodeAmount--;
			}
	}
}

bool Graph::CheckNodesConnection()
{
	visited.clear();
	for (Node n : nodes)
		visited.push_back(false);

	return dfs(0, visited) == nodeAmount? true : false;
}
int Graph::dfs(int u, std::vector<bool>& visited)
{
	int visitedVertices = 1;
	visited[u] = true; // помечаем вершину как пройденную

	for (size_t n = 0; n < nodeAmount; n++)
		if (CheckEdgeExistence(n, u) && !visited[n]) //проверяем, не находились ли мы ранее в выбранной вершине
			visitedVertices += dfs(n, visited);

	return visitedVertices;
}
	
bool Graph::CheckEdgeExistence(int start, int end)
{
	for (Edge e : edges)
		if ((e.startNode == start && e.endNode == end) || (e.startNode == end && e.endNode == start))
			return true;
	return false;
}

Edge Graph::findMinEdge(int n, std::vector<bool> visited)
{
	Edge min;
	min.value = INF;
	for (size_t i = 0; i < edges.size(); i++)
		if (edges[i].value <= min.value && !(visited[edges[i].endNode] && visited[edges[i].startNode]) && (edges[i].endNode == n ^ edges[i].startNode == n))
		{
			min = edges[i];
		}
	return min;
}
void Graph::KraskalsMethod()
{
	visited.clear(); //Очищаем массив посещенных граней
	path.clear(); //Удаляем старый каркас
	for (size_t i = 0; i < edges.size(); i++)
	{
		edges[i].selected = false;
		visited.push_back(false);
	}

	Edge min; //Минимальная грань
	min.value = INF;
	std::vector<int> group = { 0 };
	for (size_t i = 0; i < nodeAmount; i++)
	{
		group.push_back(0);
	}
	int groupCounter = 0;
	while (path.size() < nodeAmount - 1)
	{
		min.value = INF;
		for (Edge e : edges) //Находим минимальную грань
			if (min.value >= e.value && !visited[e.id - 1])
			{
				min = e;
			}
		visited[min.id - 1] = true;
		if ((group[min.endNode] == group[min.startNode]) && group[min.startNode] == 0)
		{
			groupCounter++;
			group[min.endNode] = group[min.startNode] = groupCounter;
			path.push_back(min);
		}
		else if (group[min.endNode] * group[min.startNode] == 0)
		{
			if (group[min.endNode] == 0)
				group[min.endNode] = group[min.startNode];
			else
				group[min.startNode] = group[min.endNode];
			path.push_back(min);
		}
		else
		{
			if (group[min.endNode] == group[min.startNode])
			{
				if (path.size() == nodeAmount - 2)
				{
					//path.push_back(min);
					continue;
				}
				continue;
			}
			int temp1 = group[min.startNode], temp2 = group[min.endNode];
			for (int i = 0; i < nodeAmount; i++)
				if (group[i] == temp1 || group[i] == temp2)
					group[i] = group[min.endNode];
			path.push_back(min);
		}
	}

	for (size_t e = 0; e < edges.size(); e++)
		for (size_t i = 0; i < path.size(); i++)
			if (edges[e].id == path[i].id)
				edges[e].selected = true;

}
void Graph::PrimaMethod()
{
	path.clear();
	visited.resize(nodeAmount);
	for (size_t i = 0; i < edges.size(); i++)
		edges[i].selected = false;

	for (size_t i = 0; i < nodeAmount; i++)
		visited[i] = false;

	visited[0] = true;

	Edge min, temp;
	min.value = INF;
	while (path.size() < nodeAmount - 1)
	{
		min.value = INF;
		for (int i = 0; i < nodeAmount; i++)
		{
			temp = findMinEdge(i, visited);
			if (visited[i] && min.value > temp.value)
			{
				min = temp;
			}
		}
		visited[min.endNode] = true;
		visited[min.startNode] = true;
		path.push_back(min);
	}
	path.resize(nodeAmount - 1);
	

	for (size_t e = 0; e < edges.size(); e++)
		for (size_t i = 0; i < path.size(); i++)
			if (edges[e].id == path[i].id)
				edges[e].selected = true;
}