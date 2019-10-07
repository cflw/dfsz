#include <cflw数学_平面几何.h>
#include "子弹_大子弹.h"
#include "子弹图形接口.h"
namespace 东方山寨 {
//==============================================================================
// 扩展-大子弹
//==============================================================================
//常量
const float C大子弹::c细分半径 = 32.f / 3.f;
const float C大子弹::c细分直径 = c细分半径 * 2;
C属性数组<std::vector<bool>> C大子弹::ma节点判定;
//构造函数
C大子弹::C大子弹(float a长, float a宽) :
	m初始化_长{a长}, m初始化_宽{a宽} {
}
//接口
void C大子弹::f接口_初始化() {
	m出现.f初始化();
	//长宽
	m缩放.x = m初始化_长;
	m缩放.y = m初始化_宽;
	const float v判定长 = m子弹属性->fg显示x(m缩放.x);
	const float v判定宽 = m子弹属性->fg显示y(m缩放.y);
	m长数 = v判定长 / c细分半径;
	m宽数 = v判定宽 / c细分半径;
	assert(m子弹属性->fi圆形() ? (m长数 == m宽数) : true);
	m数量 = m长数 * m宽数;
	assert(m数量 >= 1);
	//计算节点判定
	const int v节点判定标识 = ((int&)v判定长 >> 1) ^ (int&)v判定宽;	//随便哈希
	if (ma节点判定.fi不存在(v节点判定标识)) {
		std::vector<bool> va节点判定;
		va节点判定.resize(m数量);
		using tf判定 = std::function<bool(const t向量2 &)>;
		const auto f判定 = m子弹属性->fi圆形() ? 
			tf判定([v圆形 = t圆形{{0, 0}, m子弹属性->fg判定x(m缩放.x)}](const t向量2 &a坐标)->bool {
				return 数学::f圆形相交判定(v圆形, {a坐标, c细分半径});
			}) : 
			tf判定([v矩形 = t旋转矩形{{0, 0}, m子弹属性->fg判定(m缩放), 0}](const t向量2 &a坐标)->bool {
				return 数学::f圆形旋转矩形相交判定({a坐标, c细分半径}, v矩形);
			});
		for (int i = 0; i != m数量; ++i) {
			va节点判定[i] = f判定(f节点_g相对坐标(i));
		}
		ma节点判定.f添加(v节点判定标识, va节点判定);
	}
	//给节点赋值
	auto &va节点判定 = ma节点判定.fg数据(v节点判定标识);
	ma节点.resize(m数量);
	int i = 0;
	for (auto &v节点 : ma节点) {
		v节点.m序号 = (i++);
		v节点.m消失.f初始化();
		const bool vw判定 = va节点判定[v节点.m序号];
		v节点.m标志[e判定] = vw判定;
		v节点.m标志[e道具] = vw判定;
	}
}
void C大子弹::f接口_参数初始化(const S子弹参数 &a) {
	C子弹::f接口_参数初始化(a);
	f初始化_长宽(a.m长宽.x, a.m长宽.y);
}
void C大子弹::f接口_计算() {
	//渐变&消失
	m出现.f计算();
	bool v全部消失 = true;
	for (auto &v节点 : ma节点) {
		v节点.m消失.f计算();
		if (v节点.m消失.fi还没消失()) {
			v全部消失 = false;
		}
	}
	if (v全部消失) {
		f对象_销毁();
		return;
	}
	//移动
	f基础_计算运动();
	f基础_计算方向();
}
void C大子弹::f接口_更新() {
	C子弹顶点::C网格::ta顶点 va原始顶点{ma节点.size()};
	bool v没有消失 = true;
	for (int i = 0; i != m数量; ++i) {
		auto &v节点 = f扩展_取节点(i);
		auto &v原始顶点 = va原始顶点[i];
		v原始顶点.m消失 = v节点.m消失.m帧;
		if (v节点.m消失.fi消失()) {
			v没有消失 = false;
		}
	}
	if (/*v没有消失*/ false) {
		//画完整的子弹
		C子弹顶点::C点 v子弹顶点{this};
		v子弹顶点.m中心.m出现 = m出现.m帧;
		v子弹顶点.m中心.m消失 = 0;
		m绘制->f生成点(m图形数据, v子弹顶点);
	} else {
		//画细分的子弹
		C子弹顶点::C网格 v子弹顶点{this, m长数, m宽数};
		v子弹顶点.m中心.m出现 = m出现.m帧;
		m绘制->f生成网格(m图形数据, v子弹顶点, va原始顶点);
	}
}
void C大子弹::f接口_显示() const {
	m绘制->f绘制图形数据(m图形数据);
}
void C大子弹::f接口_自机判定(C自机与子弹判定 &a判定) {
	if (m出现.fi正在出现()) {
		return;
	}
	if (m子弹属性->fi圆形()) {
		const t圆形 v圆形(m坐标, m子弹属性->fg判定x(m缩放.x));
		a判定.f子弹_提交判定(v圆形);
	} else {
		const t旋转矩形 v矩形(m坐标, m子弹属性->fg判定(m缩放), m方向);
		a判定.f子弹_提交判定(v矩形);
	}
	if (a判定.f子弹_i擦弹()) {
		const int v节点序号 = f节点_g坐标对应序号(a判定.fg自机坐标());
		auto &v节点 = f扩展_取节点(v节点序号);
		if (v节点.m消失.fi存在()) {//判定成立
			a判定.f子弹_判定有效();
			if (a判定.f子弹_i碰撞()) {
				f扩展_节点消失(v节点序号);
			}
		}
	}
}
bool C大子弹::f接口_i在窗口外() {//跟普通子弹一样
	const float v半径 = m子弹属性->fg显示x(m缩放.x);
	return C边界::c窗口.f外边判断(m坐标, v半径);
}
bool C大子弹::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	auto f产生道具 = [&](S节点 &a节点) {
		auto vi道具 = a节点.m标志[e道具];
		if (vi道具) {
			vi道具 = false;
			a判定.f子弹_产生道具(f节点_g坐标(a节点.m序号), m速度);
		}
	};
	C复杂形状 v形状 = C复杂形状::fc最大圆(m坐标, m子弹属性->fg判定(m缩放), t向量2::c一);
	if (a判定.f子弹_提交判定(v形状.m坐标, v形状.m半尺寸.x)) {
		bool v真 = false;
		for (int i = 0; i != m数量; ++i) {
			S节点 &v节点 = f扩展_取节点(i);
			if (v节点.m消失.fi全消失()) {
				continue;
			}
			const t向量2 v节点坐标 = f节点_g坐标(i);
			if (a判定.f子弹_提交判定(v节点坐标, c细分半径)) {
				f扩展_节点消失(i);
				f产生道具(v节点);
				for (auto &v节点 : f循环_周围(i)) {
					f产生道具(v节点);
				}
				v真 = true;
			}
		}
		return v真;
	} else {
		return false;
	}
}
//初始化
void C大子弹::f初始化_长宽(float a长, float a宽) {
	m初始化_长 = a长;
	m初始化_宽 = a宽 <= 0 ? a长 : a宽;
}
//动作
void C大子弹::f动作_消失(bool a) {
	if (a) {
		for (auto &v节点 : ma节点) {
			v节点.m消失.f消失(1);
			v节点.m标志[e道具] = false;
		};
	} else {
		f对象_销毁();
	}
}
//扩展
C大子弹::S节点 &C大子弹::f扩展_取节点(int a序号) {
	assert(a序号 >= 0 && a序号 < m数量);
	return ma节点[a序号];
}
const C大子弹::S节点 &C大子弹::f扩展_取节点(int a序号) const {
	assert(a序号 >= 0 && a序号 < m数量);
	return ma节点[a序号];
}
std::pair<int, int> C大子弹::f扩展_计算限制长宽(int a长, int a宽) {
	const int v长 = 数学::f夹取<int>(a长, 0, m长数 - 1);
	const int v宽 = 数学::f夹取<int>(a宽, 0, m宽数 - 1);
	return {v长, v宽};
}
void C大子弹::f扩展_节点消失(int a序号) {
	auto &v节点 = f扩展_取节点(a序号);
	assert(v节点.m消失.fi存在());
	v节点.m消失.f消失(4);
	v节点.m标志.reset();
	for (auto &v节点 : f循环_周围(a序号)) {
		if (v节点.m标志[e判定]) {
			v节点.m标志.reset();
			v节点.m消失.f增加消失(0.5f);
		} else {
			v节点.m消失.f消失();
		}
	}
	//如果消失节点向外的节点没有判定时也要消失
	const t向量2 v消失节点坐标 = f节点_g相对坐标(a序号);
	const float v消失节点距离 = v消失节点坐标.fg大小();
	const float v单位距离 = t圆形{v消失节点坐标, c细分半径}.f垂直于中线到切线距离(t向量2::c零) / v消失节点距离;
	if (v消失节点距离 >= m子弹属性->fg判定x(m缩放.x) - c细分直径) {	//消失的节点要靠近判定边缘
		std::vector<int> va节点序号;
		va节点序号.reserve(m数量 / 8);
		const float v方向 = v消失节点坐标.fg方向r();
		const 数学::S直线2 v直线 = 数学::S直线2::fc点向(t向量2::c零, v方向);
		for (int i = 0; i != m数量; ++i) {
			S节点 &v节点 = f扩展_取节点(i);
			const t向量2 m坐标 = f节点_g相对坐标(i);
			if (数学::C角度计算<float>::c弧度.f夹角(v方向, m坐标.fg方向r()) >= 数学::c半π<float>) {
				continue;
			}
			const float v这节点距离 = m坐标.fg大小();
			if (v这节点距离 > v消失节点距离 && v直线.f到点距离(m坐标) <= v这节点距离 * v单位距离 + c细分直径) {
				va节点序号.push_back(i);
			}
		}
		std::sort(va节点序号.begin(), va节点序号.end(), [this](int a0, int a1)->bool {
			return f节点_g相对坐标(a0).fg大小() < f节点_g相对坐标(a1).fg大小();
		});
		for (auto &v节点序号 : va节点序号) {
			auto &v节点 = f扩展_取节点(v节点序号);
			const t向量2 m坐标 = f节点_g相对坐标(v节点序号);
			if (v消失节点距离 >= m坐标.fg大小()) {
				continue;
			}
			if (v节点.m标志[e判定]) {
				break;
			} 
			const float v这节点距离 = m坐标.fg大小();
			v节点.m标志.reset();
			v节点.m消失.f消失(c细分直径 / (v直线.f到点距离(m坐标) + c细分半径));	//越靠近直线越透明,加细分半径是为了防止÷0异常
		}
	}
	f扩展_节点消失检查();
}
void C大子弹::f扩展_节点消失检查() {
	bool v全部消失 = true;
	for (auto &v节点 : ma节点) {
		if (v节点.m标志[e判定] && v节点.m消失.fi存在()) {
			v全部消失 = false;
			break;
		}
	}
	if (v全部消失) {
		for (auto &v节点 : ma节点) {
			v节点.m消失.f消失();
		}
	}
}
//节点属性
int C大子弹::f节点_g一维序号(int a长, int a宽) {
	const auto [v长, v宽] = f扩展_计算限制长宽(a长, a宽);
	return v长 + v宽 * m长数;
}
std::pair<int, int> C大子弹::f节点_g二维序号(int a) {
	const int v宽0 = a / m长数;
	const int v长0 = a % m长数;
	const auto [v长1, v宽1] = f扩展_计算限制长宽(v长0, v宽0);
	return {v长1, v宽1};
}
t向量2 C大子弹::f节点_g相对坐标(int a序号) {
	auto f计算偏移 = [](int i, int n)->float {
		return t位置计算::f右到中(i, n - 1) * c细分直径;
	};
	const auto v序号 = f节点_g二维序号(a序号);
	const float v长偏移 = f计算偏移(v序号.first, m长数);
	const float v宽偏移 = f计算偏移(v序号.second, m宽数);
	return t向量2{v长偏移, v宽偏移};
}
t向量2 C大子弹::f节点_g坐标(int a序号) {
	return m坐标 + f节点_g相对坐标(a序号).f旋转r(m方向);
}
int C大子弹::f节点_g坐标对应序号(const t向量2 &a坐标) {
	auto f计算序号 = [](float p, int n)->int {
		return (int)t位置计算::f中到右(p / c细分直径, (n - 1));
	};
	const t向量2 v方位 = m坐标.f到点方位r(a坐标, m方向);
	const int v序号 = f节点_g一维序号(f计算序号(v方位.x, m长数), f计算序号(v方位.y, m宽数));
	return v序号;
}
float C大子弹::f节点_g相对方向(int a序号) {
	auto f计算偏移 = [](int i, int n)->float {
		return t位置计算::f右到中(i, n - 1);
	};
	const auto [v长, v宽] = f节点_g二维序号(a序号);
	const float v长偏移 = f计算偏移(v长, m长数);
	const float v宽偏移 = f计算偏移(v宽, m宽数);
	return t向量2{v长偏移, v宽偏移}.fg方向r();
}
float C大子弹::f节点_g方向(int a序号) {
	return f节点_g相对方向(a序号) + m方向;
}
std::vector<C大子弹::S节点> &C大子弹::f循环_所有() {
	return ma节点;
}
循环::C零散<std::vector<C大子弹::S节点>> &C大子弹::f循环_周围(int a序号) {
	if (m循环缓存_周围节点序号 != a序号) {
		m循环缓存_周围节点序号 = a序号;
		const auto [v长序号, v宽序号] = f节点_g二维序号(a序号);
		std::vector<int> va序号;
		va序号.reserve(8);
		static const std::pair<int, int> va偏移[] = {
			{1, 0},
			{-1, 0},
			{0, 1},
			{0, -1},
			{1, 1},
			{-1, 1},
			{1, -1},
			{-1, -1}
		};
		for (const auto &[v长偏移, v宽偏移] : va偏移) {
			const int xx = v长序号 + v长偏移;
			if (xx >= 0 && xx < m长数) {
				const int yy = v宽序号 + v宽偏移;
				if (yy >= 0 && yy < m宽数) {
					const int v序号 = f节点_g一维序号(xx, yy);
					va序号.push_back(v序号);
				}
			}
		}
		m循环缓存_周围节点循环 = 循环::C零散<std::vector<C大子弹::S节点>>(ma节点, std::move(va序号));
	}
	return m循环缓存_周围节点循环;
}
}	//namespace 东方山寨