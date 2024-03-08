#include "main.h"
//using namespace NAVIGATION;

namespace NAVIGATION
{
	Navigator::Navigator()
	{
		Node start_node(6, 5, NodeType::start);//�������
		Node end_node(28, 40, NodeType::end);//�����յ�
		grid_map_ptr = make_unique<GridMap>(start_node, end_node);
		system("pause");
	}

	bool Navigator::process(const int& h_type_, const int& algo_type_)
	{
		strategy_ptr = make_unique<Astar>(h_type_, algo_type_);//�����滮����������ָ��ָ���������
		return strategy_ptr->search(grid_map_ptr, result_nodes);
	}
}//end of namespace NAVIGATION

int main()
{
	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);// easyx��ʼ����ͬʱ����ͼ�δ��ں������

	unique_ptr<NAVIGATION::Navigator> navigator_ptr = make_unique<NAVIGATION::Navigator>();//������������
	if (navigator_ptr->process(NAVIGATION::HType::Manhattan, NAVIGATION::AlgoType::AStar))
	{
		cout << "�������" << endl;
	}

	system("pause");
	closegraph();//�رջ�ͼ����
	return 0;
}