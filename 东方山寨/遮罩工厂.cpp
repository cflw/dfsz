#include "遮罩工厂.h"
namespace 东方山寨 {
//实现
void C遮罩工厂::C实现::f初始化_数组(C对象数组<I遮罩> &aa遮罩) {
	ma遮罩 = &aa遮罩;
}
bool C遮罩工厂::C实现::fi有空() {
	return ma遮罩->fi有空();
}
void C遮罩工厂::C实现::f产生遮罩(const std::shared_ptr<I遮罩> &a遮罩) {
	a遮罩->m计数指针 = &ma遮罩->m计数;
	a遮罩->f事件_初始化();
	a遮罩->f对象_使用();
	ma遮罩->f添加(a遮罩);
}
//工厂
C遮罩工厂::C遮罩工厂(C实现 &a实现):
	m实现(&a实现) {
}
C遮罩工厂::~C遮罩工厂() {
}
}	//namespace 东方山寨