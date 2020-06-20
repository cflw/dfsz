#include "边框形状.h"
#include "边框常量.h"
namespace 东方山寨::边框 {
//==============================================================================
// 矩形边框
//==============================================================================
static const t矩形 c标准矩形 = t矩形::fc原点半尺寸(c边框范围x, c边框范围y);
const C矩形 C矩形::c标准 = C矩形(c标准矩形);
const C矩形 C矩形::c窗口 = C矩形(t矩形::fc原点半尺寸(c框架范围x, c框架范围y));
//构造
C矩形::C矩形():
	m矩形(c标准矩形) {
}
C矩形::C矩形(const t矩形 &a矩形):
	m矩形(a矩形) {
}
//边框
bool C矩形::f判断(const t向量2 &a坐标, float a外偏移) const {
	return f左边判断(a坐标, a外偏移) || f右边判断(a坐标, a外偏移) || f上边判断(a坐标, a外偏移) || f下边判断(a坐标, a外偏移);
}
int C矩形::f反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移, int a次数) const {
	if (a次数 <= 0) {
		return 0;
	}
	const int v左右 = f左右反弹(a坐标, a速度, a外偏移) ? 1 : 0;
	if (v左右 >= a次数) {
		return v左右;
	}
	const int v上下 = f上下反弹(a坐标, a速度, a外偏移) ? 1 : 0;
	return v左右 + v上下;
}
int C矩形::f限制(t向量2 &a坐标, float a外偏移, int a次数) const {
	if (a次数 <= 0) {
		return 0;
	}
	const int v左右 = f左右限制(a坐标, a外偏移) ? 1 : 0;
	if (v左右 >= a次数) {
		return v左右;
	}
	const int v上下 = f上下限制(a坐标, a外偏移) ? 1 : 0;
	return v左右 + v上下;
}
void C矩形::f显示(const S画边框参数 &a) const {
	const float v左内 = m矩形.fg左();
	const float v左外 = v左内 - c边框宽度;
	const float v右内 = m矩形.fg右();
	const float v右外 = v右内 + c边框宽度;
	const float v上内 = m矩形.fg上();
	const float v上外 = v上内 + c边框宽度;
	const float v下内 = m矩形.fg下();
	const float v下外 = v下内 - c边框宽度;
	a.m画图形.f填充矩形(t矩形::fc左上右下(v右内, v上外, v右外, v下外));	//右
	a.m画图形.f填充矩形(t矩形::fc左上右下(v左外, v上外, v左内, v下外));	//左
	a.m画图形.f填充矩形(t矩形::fc左上右下(v左内, v上外, v右内, v上内));	//上
	a.m画图形.f填充矩形(t矩形::fc左上右下(v左内, v下内, v右内, v下外));	//下
}
//判断
bool C矩形::f左边判断(const t向量2 &a坐标, float a外偏移) const {
	return a坐标.x < m矩形.fg左() - a外偏移;
}
bool C矩形::f右边判断(const t向量2 &a坐标, float a外偏移) const {
	return a坐标.x > m矩形.fg右() + a外偏移;
}
bool C矩形::f上边判断(const t向量2 &a坐标, float a外偏移) const {
	return a坐标.y > m矩形.fg上() + a外偏移;
}
bool C矩形::f下边判断(const t向量2 &a坐标, float a外偏移) const {
	return a坐标.y < m矩形.fg下() - a外偏移;
}
//限制
bool C矩形::f左边限制(t向量2 &a坐标, float a外偏移) const {
	const float v边界 = m矩形.fg左() - a外偏移;
	if (a坐标.x < v边界) {
		a坐标.x = v边界;
		return true;
	} else {
		return false;
	}
}
bool C矩形::f右边限制(t向量2 &a坐标, float a外偏移) const {
	const float v边界 = m矩形.fg右() + a外偏移;
	if (a坐标.x > v边界) {
		a坐标.x = v边界;
		return true;
	} else {
		return false;
	}
}
bool C矩形::f上边限制(t向量2 &a坐标, float a外偏移) const {
	const float v边界 = m矩形.fg上() + a外偏移;
	if (a坐标.y > v边界) {
		a坐标.y = v边界;
		return true;
	} else {
		return false;
	}
}
bool C矩形::f下边限制(t向量2 &a坐标, float a外偏移) const {
	const float v边界 = m矩形.fg下() - a外偏移;
	if (a坐标.y < v边界) {
		a坐标.y = v边界;
		return true;
	} else {
		return false;
	}
}
bool C矩形::f左右限制(t向量2 &a坐标, float a外偏移) const {
	return f左边限制(a坐标, a外偏移) || f右边限制(a坐标, a外偏移);
}
bool C矩形::f上下限制(t向量2 &a坐标, float a外偏移) const {
	return f上边限制(a坐标, a外偏移) || f下边限制(a坐标, a外偏移);
}
//反弹
bool C矩形::f左边反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移) const {
	const float v边界 = m矩形.fg左() - a外偏移;
	if (a坐标.x < v边界) {
		std::tie(a坐标, a速度) = 物理::f反弹运动x(a坐标, a速度, v边界);
		return true;
	} else {
		return false;
	}
}
bool C矩形::f右边反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移) const {
	const float v边界 = m矩形.fg右() + a外偏移;
	if (a坐标.x > v边界) {
		std::tie(a坐标, a速度) = 物理::f反弹运动x(a坐标, a速度, v边界);
		return true;
	} else {
		return false;
	}
}
bool C矩形::f上边反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移) const {
	const float v边界 = m矩形.fg上() + a外偏移;
	if (a坐标.y > v边界) {
		std::tie(a坐标, a速度) = 物理::f反弹运动y(a坐标, a速度, v边界);
		return true;
	} else {
		return false;
	}
}
bool C矩形::f下边反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移) const {
	const float v边界 = m矩形.fg下() - a外偏移;
	if (a坐标.y < v边界) {
		std::tie(a坐标, a速度) = 物理::f反弹运动y(a坐标, a速度, v边界);
		return true;
	} else {
		return false;
	}
}
bool C矩形::f左右反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移) const {
	return f左边反弹(a坐标, a速度, a外偏移) || f右边反弹(a坐标, a速度, a外偏移);
}
bool C矩形::f上下反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移) const {
	return f上边反弹(a坐标, a速度, a外偏移) || f下边反弹(a坐标, a速度, a外偏移);
}
//==============================================================================
// 圆形边框
//==============================================================================
static const t圆形 c标准圆形 = t圆形(t向量2::c零, c边框范围y);
const C圆形 C圆形::c标准 = C圆形(c标准圆形);
C圆形::C圆形() :
	m圆形(c标准圆形) {
}
C圆形::C圆形(const t圆形 &a圆形) :
	m圆形(a圆形) {
}
//边框
bool C圆形::f判断(const t向量2 &a坐标, float a外偏移) const {
	const float v边界 = m圆形.m半径 + a外偏移;
	const float v距离 = m圆形.m坐标.f到点距离(a坐标);
	return v距离 > v边界;
}
int C圆形::f反弹(t向量2 &a坐标, t向量2 &a速度, float a外偏移, int a次数) const {
	if (a次数 <= 0) {
		return 0;
	}
	const float v边界 = m圆形.m半径 + a外偏移;
	const float v距离 = m圆形.m坐标.f到点距离(a坐标);
	if (v距离 > v边界) {
		std::tie(a坐标, a速度) = 物理::f反弹运动_圆形(a坐标, a速度, t圆形::fc坐标半径(m圆形.m坐标, v边界));
		return 1;
	}
	return 0;
}
int C圆形::f限制(t向量2 &a坐标, float a外偏移, int a次数) const {
	if (a次数 <= 0) {
		return 0;
	}
	const float v边界 = m圆形.m半径 + a外偏移;
	const float v距离 = m圆形.m坐标.f到点距离(a坐标);
	if (v距离 > v边界) {
		const float v方向 = m圆形.m坐标.f到点方向r(a坐标);
		a坐标 = m圆形.m坐标 + t向量2::fc方向r(v边界, v方向);
		return 1;
	}
	return 0;
}
void C圆形::f显示(const S画边框参数 &a) const {
	const float v半径 = m圆形.m半径 + c边框宽度 * 0.5f;
	a.m画图形.f绘制圆形(t圆形(m圆形.m坐标, v半径));
}
}	//namespace 东方山寨