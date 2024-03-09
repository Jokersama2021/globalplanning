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
	enum NodeType//�����д�ӡ
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
		Node(const int& r, const int& c, const int& type = NodeType::normal);//�вι��죬�����к��У�Ĭ��Ϊ��ͨ�ڵ�
		void drawNode() const;//���ƽڵ�

		bool operator<(const Node& other_node) const { return this->f > other_node.f; }//����<�����ڴ���С���ѵ����ȶ���

	public:
		int row = 0;
		int col = 0;

		int f = 0;//�õ���ۺϴ���
		int g = 0;//��㵽�õ���ۼƴ���
		int h = 0;//�õ㵽�յ����������

		int node_type = NodeType::normal;
		Node* parent_node = nullptr;//����ڵ�ĸ��ڵ�
	};

	class GridMapBase//դ���ͼ����
	{
	public:
		bool GridMapInit(const Node& start, const Node& end);//��ͼ��ʼ����������㣬�յ�
		void printMap();//��ӡ��ͼ
		void drawMap();//���Ƶ�ͼ
		bool outOfMap(const Node& node);//node�Ƿ񳬳���ͼ�߽�
		virtual void addObs() = 0;//����ϰ���

	public:
		vector<vector<Node>> grid_map;//��ͼ�Ľṹ
		Node* start_node = nullptr;//���
		Node* end_node = nullptr;//�յ�
		unordered_set<Node*> obs_nodes;//�ϰ���
	};

	class GridMap : public GridMapBase//դ���ͼ��ͨ����̬������ͬ�����ĵ�ͼ��ʵ�ֲ�ͬ����յ㡢��ͬ�ϰ���λ��
	{
	public:
		GridMap(const Node& start, const Node& end);//��ͼ��ʼ��
		void addObs() override;//����ϰ���
	};
}