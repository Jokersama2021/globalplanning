#pragma once
#include <queue>
#include <cmath>
#include "grid_map.h"

using std::priority_queue, std::pair;

namespace NAVIGATION
{
	enum HType//H��������
	{
		Euclidean,//ŷʽ����
		Manhattan,//�����پ���
		Chebyshev //�б�ѩ�����
	};

	enum AlgoType//�㷨����
	{
		Dijkstra,
		BFS,
		AStar
	};

	class StrategyBase //���Ը���
	{
	public:
		virtual bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) = 0;//�������̣����麯��
	};

	class Astar : public StrategyBase//Astar����
	{
	public:
		Astar(const int& h_type_, const int& algo_type_);
		bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) override;//����map�����result_nodes_output 
		int heuristicDis(const Node& node1, const Node& node2);//��������
		void calCost(const Node& current_node, Node& next_node, const Node& end_node);//�������
		void printResult(const vector<Node*>& result_nodes);//��ӡ���
		void drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time);//�������ƽڵ�
		void drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes);//���ƽ��

	public:
		priority_queue<Node> open_queue;//open��С���ѣ����Զ�����Сֵ��Ϊ�Ѷ���ʡȥ������Сfֵ�Ĺ��� //��ΪҪ�������Բ���ָ��
		unordered_set<Node*> open_set;//open��Ҫ�߱����ٲ��ҹ��ܣ���unordered_setά������open_queue����ͬ��	
		unordered_set<Node*> close_set;//close��Ҳ����̽�����Ľڵ�

		int h_type = HType::Manhattan;//Ĭ�Ͼ���Ϊ�����پ���
		int algo_type = AlgoType::AStar;//Ĭ���㷨ΪAstar
		int final_length = 0;//����·������
		int step_len = 0;//��������
	};
}//end of namespace NAVIGATION