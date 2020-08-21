#include "敌机扩展.h"
namespace 东方山寨 {
const S敌机属性 C敌机扩展生命::c属性{.m判定半径 = c判定半径 };
C敌机扩展生命::C敌机扩展生命(C敌机 &a敌机, bool a目标无敌):
	m目标(&a敌机), 
	m源头(dynamic_cast<C敌机扩展生命*>(&a敌机) ? static_cast<C敌机扩展生命&>(a敌机).m源头 : &a敌机),
	m目标无敌(a目标无敌) {
}
void C敌机扩展生命::f接口_计算() {
	m坐标 = m目标->m坐标;	//在并行计算中可能有问题
}
bool C敌机扩展生命::f接口_玩家子弹判定(C敌机与玩家子弹判定 &a判定) {
	const t向量2 &v坐标 = m源头->m坐标;
	const float &v半径 = c判定半径;
	return a判定.f敌机_提交判定(t圆形(v坐标, v半径));
}
void C敌机扩展生命::f接口_初始化() {
	m目标->m标志[e无敌] = m目标无敌;
}
void C敌机扩展生命::f接口_击破() {
	m目标->m标志[e无敌] = false;
}
}	//namespace 东方山寨