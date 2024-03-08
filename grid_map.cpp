#include "grid_map.h"

namespace NAVIGATION
{
	Node::Node(const int& r, const int& c, const int& type)
		:row(r), col(c), node_type(type)//有参构造，传入行和列
	{

	}

	void Node::drawNode() const//绘制节点
	{
		int left = ORIX + col * LEN;
		int right = left + LEN;
		int top = ORIY + row * LEN;
		int bottom = top + LEN;
		fillrectangle(left, top, right, bottom);
	}

	bool GridMapBase::GridMapInit(const Node& start, const Node& end)//地图初始化，输入起点，终点
	{
		if (outOfMap(start) || outOfMap(end))
		{
			cout << "起点或终点超出地图边界" << endl;
			return false;
		}

		//构建地图
		for (int i = 0; i < ROWS; i++)//把每行构建成列
		{
			vector<Node> row_tmp;//每行
			for (int j = 0; j < COLS; j++) //构建每行
			{
				Node node_tmp(i, j);
				row_tmp.emplace_back(node_tmp);
			}
			grid_map.emplace_back(row_tmp);
		}

		//更新起点终点
		grid_map[start.row][start.col].node_type = NodeType::start; //修改起点终点类型
		grid_map[end.row][end.col].node_type = NodeType::end;
		start_node = &grid_map[start.row][start.col];//指向对应的位置
		end_node = &grid_map[end.row][end.col];
		return true;
	}

	void GridMapBase::printMap()//打印地图
	{
		cout << "地图行数：" << ROWS << ", 地图列数：" << COLS << endl;
		cout << "起点行数：" << start_node->row
			<< "， 起点列数：" << start_node->col
			<< "， 终点行数：" << end_node->row
			<< "， 终点列数：" << end_node->col << endl;

		//按节点类型打印，输出的命令行窗口
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
		setbkcolor(WHITE);    //设置背景颜色
		setlinecolor(BLACK);    //设置边框颜色
		setlinestyle(PS_SOLID, 2);	//设置线的样式为实线2px
		cleardevice();

		BeginBatchDraw();
		setfillcolor(WHITE);//填充白色
		for (int i = 0; i < ROWS; i++)//把每行绘制成整个地图
		{
			for (int j = 0; j < COLS; j++)//绘制每行
			{
				grid_map[i][j].drawNode();
			}
		}

		//起点终点
		setfillcolor(RED);//填充红色
		start_node->drawNode();//绘制起点

		setfillcolor(BLUE);//填充蓝色
		end_node->drawNode();//绘制终点

		setfillcolor(BROWN);//填充褐色
		for (const auto& obs_node : obs_nodes)
		{
			obs_node->drawNode();//绘制障碍物
		}
		EndBatchDraw();
	}

	bool GridMapBase::outOfMap(const Node& node)
	{
		return (node.col < 0 || node.col >= COLS || node.row < 0 || node.row >= ROWS);
	}

	GridMap::GridMap(const Node& start, const Node& end)//地图初始化，输入起点，终点
	{
		assert(GridMapInit(start, end));//初始化 //断言
		addObs();//添加障碍物
		printMap();//打印
		drawMap();//绘制
	}

	void GridMap::addObs()
	{
		Node* node_tmp;

		for (int i = 2; i < 17; i++)//行
		{
			node_tmp = &grid_map[5][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

		for (int i = 2; i < 17; i++)//行
		{
			node_tmp = &grid_map[12][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//行
		{
			node_tmp = &grid_map[19][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//行
		{
			node_tmp = &grid_map[23][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//行
		{
			node_tmp = &grid_map[30][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 2; i < 17; i++)//行
		{
			node_tmp = &grid_map[37][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

		for (int i = 27; i < 42; i++)//行
		{
			node_tmp = &grid_map[5][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 27; i < 42; i++)//行
		{
			node_tmp = &grid_map[19][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 27; i < 42; i++)//行
		{
			node_tmp = &grid_map[30][i];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

		for (int i = 5; i < 13; i++)//列
		{
			node_tmp = &grid_map[i][16];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 23; i < 31; i++)//列
		{
			node_tmp = &grid_map[i][16];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 12; i < 19; i++)//列
		{
			node_tmp = &grid_map[i][2];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 30; i < 38; i++)//列
		{
			node_tmp = &grid_map[i][2];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 5; i < 19; i++)//列
		{
			node_tmp = &grid_map[i][27];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 5; i < 19; i++)//列
		{
			node_tmp = &grid_map[i][41];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 5; i < 19; i++)//列
		{
			node_tmp = &grid_map[i][41];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 22; i < 30; i++)//列
		{
			node_tmp = &grid_map[i][27];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}
		for (int i = 22; i < 38; i++)//列
		{
			node_tmp = &grid_map[i][41];
			obs_nodes.insert(node_tmp);
			node_tmp->node_type = NodeType::obs;
		}

	}

}//end of namespace NAVIGATION