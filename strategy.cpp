#include "strategy.h"

namespace NAVIGATION
{
	void delay(const int& time) //��ʱ��������λms
	{
		clock_t  now = clock();
		while (clock() - now < time)
		{

		}
	}

	Astar::Astar(const int& h_type_, const int& algo_type_) :h_type(h_type_), algo_type(algo_type_)
	{

	}

	bool Astar::search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes)//����map�����result_nodes
	{
		//��ʼ�����
		open_queue.emplace(*map->start_node);//������open����
		open_set.insert(map->start_node);//������open����
		Node* current_node = map->start_node;//���������Ϊ��ǰ��		

		//���õ����ƶ�����
		vector<pair<int, int>> move_step =
		{
			pair<int, int>(0, 1),
			pair<int, int>(0, -1),
			pair<int, int>(1, 0),
			pair<int, int>(-1, 0),
			pair<int, int>(-1, 1),
			pair<int, int>(-1, -1),
			pair<int, int>(1, -1),
			pair<int, int>(1, 1),
		};

		//��������
		while (!open_queue.empty())
		{
			//��ǰ��Ĵ���
			int r = open_queue.top().row;//����
			int c = open_queue.top().col;//����
			current_node = &map->grid_map[r][c];//��ǰ�ڵ��ƶ���f��С���¸��ڵ�
			cout << "current_node->f = " << current_node->f << ", current_node->r = " << r << ", current_node->c = " << c << endl;

			//����close��
			setfillcolor(YELLOW);//�����ɫ
			drawNodeStep(map->start_node, map->end_node, current_node, DELAYTIME_SEARCH);

			open_queue.pop();//�ѵ�ǰ���Ƴ�����
			open_set.erase(current_node);//�ѵ�ǰ���Ƴ�����
			close_set.insert(current_node);//����close��

			//�ѵ����յ�Ĵ���
			if (current_node == map->end_node)//����ѵ����յ�
			{
				final_length = current_node->g;//��¼��·������

				//����ָ���������result_nodes
				while (current_node->parent_node)
				{
					current_node->node_type = NodeType::result_way;//��������
					result_nodes.emplace_back(current_node);//������
					current_node = current_node->parent_node;//�򸸽ڵ��ƶ�
				}
				reverse(result_nodes.begin(), result_nodes.end());//��ת
				cout << "Astar�����ɹ�" << endl;

				//�ָ�����յ�����ͣ�Ϊ�������д�ӡЧ��
				map->start_node->node_type = NodeType::start;
				map->end_node->node_type = NodeType::end;

				//���չʾ				
				printResult(result_nodes);
				map->printMap();
				drawResult(map->start_node, map->end_node, result_nodes);
				return true;
			}

			//һ������
			for (auto it = move_step.begin(); it != move_step.end(); it++)
			{
				Node node_tmp(r + it->first, c + it->second);//��ȡ�¸��ڵ�λ��
				if (map->outOfMap(node_tmp))//��������߽磬������
				{
					continue;
				}
				Node* next_node = &map->grid_map[node_tmp.row][node_tmp.col];//���û���磬�򴴽��¸��ڵ�ָ�룬ָ��node_tmpλ�����ڵĽڵ�		
				if (close_set.find(next_node) != close_set.end() 
					|| map->obs_nodes.find(next_node) != map->obs_nodes.end())//�߹��������ϰ��������
				{
					continue;
				}

				step_len = abs(it->first) == abs(it->second) ? XLEN : LEN;//�����������������б�߾���XLEN��������������Ҿ���LEN��
				if (open_set.find(next_node) != open_set.end())//����Ѿ���open����
				{
					if (current_node->g + step_len < next_node->g)//����ۼӵ�gֵС�����е�gֵ
					{
						calCost(*current_node, *next_node, *map->end_node);
						next_node->parent_node = current_node;//�������ӹ�ϵ
					}
				}
				else//�������open���У������open��
				{
					calCost(*current_node, *next_node, *map->end_node);
					next_node->parent_node = current_node;//�������ӹ�ϵ

					open_queue.emplace(*next_node);//����open��
					open_set.insert(next_node);//����open��

					//����open��
					setfillcolor(LIGHTCYAN);//�����ɫ
					drawNodeStep(map->start_node, map->end_node, next_node, DELAYTIME_SEARCH);
				}
			}
		}

		//����ʧ�ܵĴ���
		cout << "Astar����ʧ��" << endl;
		drawResult(map->start_node, map->end_node, result_nodes);
		return false;
	}

	int Astar::heuristicDis(const Node& node1, const Node& node2)//��������
	{
		if (h_type == HType::Euclidean)//ŷʽ����
		{
			return hypot(node1.col - node2.col, node1.row - node2.row) * LEN;
		}
		else if (h_type == HType::Manhattan)//�����پ���
		{
			return (abs(node1.col - node2.col) + abs(node1.row - node2.row)) * LEN;
		}
		else if (h_type == HType::Chebyshev)//�б�ѩ����룬Ҳ�����̾���
		{
			int len_col = abs(node1.col - node2.col);
			int len_row = abs(node1.row - node2.row);
			int x_step = min(len_col, len_row);
			int res_step = abs(len_col - len_row);
			return x_step * XLEN + res_step * LEN;
		}
		return 0;
	}

	void Astar::calCost(const Node& current_node, Node& next_node, const Node& end_node)//�������
	{
		next_node.g = current_node.g + step_len;//����gֵ
		next_node.h = heuristicDis(next_node, end_node);//����hֵ
		if (algo_type == AlgoType::Dijkstra)
		{
			next_node.h = 0;
		}
		else if (algo_type == AlgoType::BFS)
		{
			next_node.g = 0;
		}
		next_node.f = next_node.g + next_node.h;//����fֵ
		cout << "f = " << next_node.f << ", g = " << next_node.g << ", h = " << next_node.h << endl;
	}

	void Astar::printResult(const vector<Node*>& result_nodes)//��ӡ���
	{
		cout << "·��������" << result_nodes.size() << endl;
		cout << "̽��������" << close_set.size() << endl;
		cout << "·�����ȣ�" << final_length << endl;

		for (const auto& result_node : result_nodes)
		{
			cout << "(" << result_node->row << ", " << result_node->col << "), "
				<< "f: " << result_node->f << ", "
				<< "g: " << result_node->g << ", "
				<< "h: " << result_node->h << endl;
		}
	}

	void Astar::drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time)//�������ƽڵ�
	{
		if (node != start && node != end)//�ܿ�����յ�
		{
			BeginBatchDraw();
			node->drawNode();
			delay(time);
			EndBatchDraw();
		}
	}

	void Astar::drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes)//���ƽ��
	{
		setfillcolor(GREEN);//�����ɫ
		for (const auto& result_node : result_nodes)
		{
			drawNodeStep(start, end, result_node, DELAYTIME_RESULT);
		}
	}
}//end of namespace NAVIGATION