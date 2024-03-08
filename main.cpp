#include "main.h"
//using namespace NAVIGATION;

namespace NAVIGATION
{
	Navigator::Navigator()
	{
		Node start_node(6, 5, NodeType::start);//创建起点
		Node end_node(28, 40, NodeType::end);//创建终点
		grid_map_ptr = make_unique<GridMap>(start_node, end_node);
		system("pause");
	}

	bool Navigator::process(const int& h_type_, const int& algo_type_)
	{
		strategy_ptr = make_unique<Astar>(h_type_, algo_type_);//创建规划方法，父类指针指向子类对象
		return strategy_ptr->search(grid_map_ptr, result_nodes);
	}
}//end of namespace NAVIGATION

int main()
{
	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);// easyx初始化，同时创建图形窗口和命令窗口

	unique_ptr<NAVIGATION::Navigator> navigator_ptr = make_unique<NAVIGATION::Navigator>();//创建导航任务
	if (navigator_ptr->process(NAVIGATION::HType::Manhattan, NAVIGATION::AlgoType::AStar))
	{
		cout << "导航完成" << endl;
	}

	system("pause");
	closegraph();//关闭绘图窗口
	return 0;
}