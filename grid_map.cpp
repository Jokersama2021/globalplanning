#include "grid_map.h"

namespace NAVIGATION
{
	Node::Node(const int& r, const int& c, const int& type)
		:row(r), col(c), node_type(type)//�вι��죬�����к���
	{

	}

	void Node::drawNode() const//���ƽڵ�
	{
		int left = ORIX + col * LEN;
		int right = left + LEN;
		int top = ORIY + row * LEN;
		int bottom = top + LEN;
		fillrectangle(left, top, right, bottom);
	}

	bool GridMapBase::GridMapInit(const Node& start, const Node& end)//��ͼ��ʼ����������㣬�յ�
	{
		if (outOfMap(start) || outOfMap(end))
		{
			cout << "�����յ㳬����ͼ�߽�" << endl;
			return false;
		}

		//������ͼ
		for (int i = 0; i < ROWS; i++)//��ÿ�й�������
		{
			vector<Node> row_tmp;//ÿ��
			for (int j = 0; j < COLS; j++) //����ÿ��
			{
				Node node_tmp(i, j);
				row_tmp.emplace_back(node_tmp);
			}
			grid_map.emplace_back(row_tmp);
		}

		//��������յ�
		grid_map[start.row][start.col].node_type = NodeType::start; //�޸�����յ�����
		grid_map[end.row][end.col].node_type = NodeType::end;
		start_node = &grid_map[start.row][start.col];//ָ���Ӧ��λ��
		end_node = &grid_map[end.row][end.col];
		return true;
	}

	void GridMapBase::printMap()//��ӡ��ͼ
	{
		cout << "��ͼ������" << ROWS << ", ��ͼ������" << COLS << endl;
		cout << "���������" << start_node->row
			<< "�� ���������" << start_node->col
			<< "�� �յ�������" << end_node->row
			<< "�� �յ�������" << end_node->col << endl;

		//���ڵ����ʹ�ӡ������������д���
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (grid_map[i][j].node_type == NodeType::normal)
				{
					cout << "  ";
				}
				else
				{
					cout << grid_map[i][j].node_type << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	void GridMapBase::drawMap()
	{
		setbkcolor(WHITE);    //���ñ�����ɫ
		setlinecolor(BLACK);    //���ñ߿���ɫ
		setlinestyle(PS_SOLID, 2);	//�����ߵ���ʽΪʵ��2px
		cleardevice();

		BeginBatchDraw();
		setfillcolor(WHITE);//����ɫ
		for (int i = 0; i < ROWS; i++)//��ÿ�л��Ƴ�������ͼ
		{
			for (int j = 0; j < COLS; j++)//����ÿ��
			{
				grid_map[i][j].drawNode();
			}
		}

		//����յ�
		setfillcolor(RED);//����ɫ
		start_node->drawNode();//�������

		setfillcolor(BLUE);//�����ɫ
		end_node->drawNode();//�����յ�

		setfillcolor(BROWN);//����ɫ
		for (const auto& obs_node : obs_nodes)
		{
			obs_node->drawNode();//�����ϰ���
		}
		EndBatchDraw();
	}

	bool GridMapBase::outOfMap(const Node& node)
	{
		return (node.col < 0 || node.col >= COLS || node.row < 0 || node.row >= ROWS);
	}

	GridMap::GridMap(const Node& start, const Node& end)//��ͼ��ʼ����������㣬�յ�
	{
		assert(GridMapInit(start, end));//��ʼ�� //����
		addObs();//����ϰ���
		printMap();//��ӡ
		drawMap();//����
	}

	void GridMap::addObs()
	{
		Node* node_tmp;

		for (int i = 2; i < 17; i++)//��
		{
			node_tmp = &grid_map[5][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

		for (int i = 2; i < 17; i++)//��
		{
			node_tmp = &grid_map[12][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//��
		{
			node_tmp = &grid_map[19][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//��
		{
			node_tmp = &grid_map[23][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//��
		{
			node_tmp = &grid_map[30][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//��
		{
			node_tmp = &grid_map[37][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

		for (int i = 27; i < 42; i++)//��
		{
			node_tmp = &grid_map[5][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 27; i < 42; i++)//��
		{
			node_tmp = &grid_map[19][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 27; i < 42; i++)//��
		{
			node_tmp = &grid_map[30][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

		for (int i = 5; i < 13; i++)//��
		{
			node_tmp = &grid_map[i][16];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 23; i < 31; i++)//��
		{
			node_tmp = &grid_map[i][16];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 12; i < 19; i++)//��
		{
			node_tmp = &grid_map[i][2];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 30; i < 38; i++)//��
		{
			node_tmp = &grid_map[i][2];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 5; i < 19; i++)//��
		{
			node_tmp = &grid_map[i][27];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 5; i < 19; i++)//��
		{
			node_tmp = &grid_map[i][41];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 5; i < 19; i++)//��
		{
			node_tmp = &grid_map[i][41];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 22; i < 30; i++)//��
		{
			node_tmp = &grid_map[i][27];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 22; i < 38; i++)//��
		{
			node_tmp = &grid_map[i][41];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

	}

}//end of namespace NAVIGATION