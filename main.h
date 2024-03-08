#pragma once
#include "strategy.h"

namespace NAVIGATION
{
	class Navigator//������
	{
	public:
		Navigator();
		bool process(const int& h_type_, const int& algo_type_);

	public:
		vector<Node*> result_nodes;//���·��
		unique_ptr<GridMapBase> grid_map_ptr;//��ͼ����ָ��
		unique_ptr<StrategyBase> strategy_ptr;//ȫ�ֹ滮����ָ��
	};
}//end of namespace NAVIGATION