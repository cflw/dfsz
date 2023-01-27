#include "玩家成绩.h"
#include "数学包含.h"
#include "游戏常量.h"
namespace 东方山寨 {
//==============================================================================
// 各种值
//==============================================================================
//分数值
void C分数值::f计算() {
	m显示值 = 数学::f倍数渐变<long long>(m显示值, m实际值, 0.1f, 1, 100000);
}
void C分数值::f加分(long long p) {
	m实际值 += p;
}
//吸收值
const float C吸收值::c减少速度 = 50.f * c帧秒<float>;
const float C吸收值::c上限 = 130.f;
C吸收值::operator int() const {
	return (int)m值;
}
void C吸收值::f计算() {
	m值 -= c减少速度;
	if (m值 < 0) {
		m值 = 0;
	} else if (m值 > c上限) {
		m值 -= c减少速度;
	}
	if (m值 >= 100) {

	}
}
void C吸收值::f加() {

}
void C吸收值::f满() {
	m值 = c上限;
}
//难度
}	//namespace 东方山寨