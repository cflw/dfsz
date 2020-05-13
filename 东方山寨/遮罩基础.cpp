#include "遮罩基础.h"
#include "基础_数组计数.h"
namespace 东方山寨 {
//形状接口
bool I遮罩形状::f判定_点(const t向量2 &) const {
	return false;
}
bool I遮罩形状::f判定_圆形(const t圆形 &) const {
	return false;
}
//遮罩接口
void I遮罩::f对象_使用() {
	m计数指针->f加计数();
	m标志[e使用] = true;
	m标志[e动作] = true;
}
void I遮罩::f对象_销毁() {
	f事件_销毁();
	m计数指针->f加计数();
	m标志[e使用] = false;
}
bool I遮罩::f对象_i使用() {
	return m标志[e使用];
}
bool I遮罩::f判定_点(const t向量2 &a) const {
	return f接口_g形状().f判定_点(a);
}
bool I遮罩::f判定_圆形(const t圆形 &a) const {
	return f接口_g形状().f判定_圆形(a);
}
void I遮罩::f遮罩_敌机(C敌机 &) {
}
void I遮罩::f遮罩_自机(C自机 &) {
}
void I遮罩::f遮罩_子机(C子机 &) {
}
void I遮罩::f遮罩_道具(C道具 &) {
}
void I遮罩::f动作_结束() {
	m标志[e动作] = false;
	f对象_销毁();
}
}	//namespace 东方山寨