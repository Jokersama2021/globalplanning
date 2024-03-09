#pragma once
#include <iostream>
#include <graphics.h>
#include <ctime>
#include <assert.h>
#include <vector>
#include <unordered_set>
#include "config.h"

using std::cout, std::endl; 
using std::vector, std::unordered_set, std::unique_ptr, std::make_unique;

namespace NAVIGATION
{
	enum NodeType//命令行打印
	{
		normal,
		start,
		end,
		obs,
		result_way,
	};

	class Node
	{
	public:
		Node() = default;
		Node(const int& r, const int& c, const int& type = NodeType::normal);//有参构造，传入行和列，默认为普通节点
		void drawNode() const;//绘制节点

		bool operator<(const Node& other_node) const { return this->f > other_node.f; }//重载<，用于创建小顶堆的优先队列

	public:
		int row = 0;
		int col = 0;

		int f = 0;//该点的综合代价
		int g = 0;//起点到该点的累计代价
		int h = 0;//该点到终点的启发代价

		int node_type = NodeType::normal;
		Node* parent_node = nullptr;//结果节点的父节点
	};

	class GridMapBase//栅格地图父类
	{
	public:
		bool GridMapInit(const Node& start, const Node& end);//地图初始化，输入起点，终点
		void printMap();//打印地图
		void drawMap();//绘制地图
		bool outOfMap(const Node& node);//node是否超出地图边界
		virtual void addObs() = 0;//添加障碍物

	public:
		vector<vector<Node>> grid_map;//地图的结构
		Node* start_node = nullptr;//起点
		Node* end_node = nullptr;//终点
		unordered_set<Node*> obs_nodes;//障碍物
	};

	class GridMap : public GridMapBase//栅格地图，通过多态可以在同样规格的地图中实现不同起点终点、不同障碍物位置
	{
	public:
		GridMap(const Node& start, const Node& end);//地图初始化
		void addObs() override;//添加障碍物
	};
}