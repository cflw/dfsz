#include "游戏常量.h"
#include "子弹_射线激光.h"
#include "游戏.h"
namespace 东方山寨 {
//==============================================================================
// 扩展-射线激光
//==============================================================================
struct C射线激光::S段信息 {
	int v序号;
	float v中心;
	S消失段 *v指针;
	bool operator <(const S段信息 &p) const {
		return v中心 < p.v中心;
	}
};
//常量
const float C射线激光::c消失段半长度 = 16;
const float C射线激光::c宽度缩放速度 = 1.f / 60.f;
const float C射线激光::c预警线宽度 = 0.1f;
const float C射线激光::c炸弹无敌时间 = 0.5f;
//接口
void C射线激光::f接口_初始化() {
	m开始段 = -1;
	m炸弹无敌 = 0;
	m出现.f初始化();
	m消失.f初始化();
	m标志[e变化_数量] = true;
	//长宽
	m缩放.x = 0;
	m缩放.y = 0;
	m目标.x = (m初始化_长 <= 0) ? (c框架范围r / m子弹属性->fg显示x()) : m初始化_长;
	m目标.y = (m初始化_宽 <= 0) ? 1 : m初始化_宽;
}
void C射线激光::f接口_参数初始化(const S子弹参数 &a) {
	C子弹::f接口_参数初始化(a);
	f初始化_长宽(a.m长宽.x, a.m长宽.y);
}
void C射线激光::f接口_计算() {
	const float v过秒 = m游戏速度->fg秒();
	//运动
	t向量2 v移动速度 = m速度 * v过秒;
	float &v目标长度 = m目标.x;
	float &v实际长度 = m缩放.x;
	if (v实际长度 < v目标长度) {
		const float v缩放速度 = 1 / m子弹属性->fg显示x();
		if (v目标长度 - v实际长度 > v缩放速度) {
			v实际长度 += v缩放速度;
		} else {
			v实际长度 = v目标长度;
		}
	}
	const float &v目标宽度 = m标志[e预警线] ? c预警线宽度 : m目标.y;
	float &v实际宽度 = m缩放.y;
	if (v实际宽度 != v目标宽度) {
		v实际宽度 = 数学::f线性渐变(v实际宽度, v目标宽度, c宽度缩放速度);
	}
	if (m标志[e移动]) {
		m坐标 += v移动速度;
	}
	f基础_计算方向();
	//炸弹无敌
	if (m炸弹无敌 > 0) {
		m炸弹无敌 -= v过秒;
	}
	//出现&消失
	m出现.f计算();
	if (m消失.fi消失()) {
		m消失.f计算();
		if (m消失.fi已经消失()) {
			f对象_销毁();
			return;
		}
	}
	//消失段计算
	f消失段_排序();
	const float v总长 = f扩展_g总长();
	if (m开始段 >= 0) {
		const float v段速度 = m速度.fg大小() * v过秒;
		//处理开始段的范围
		S消失段 &v这段 = ma消失段[m开始段];
		v这段.v范围.m小 += v段速度;
		if (v这段.v范围.fg直径() <= 0) {
			f消失段_销毁(v这段, -1);
		}
		//处理所有段
		int v这段序号 = m开始段;
		int v上段序号 = -1;
		while (v这段序号 >= 0) {
			S消失段 &v这段 = ma消失段[v这段序号];
			v这段.v消失.f计算();
			//消失段的运动
			v这段.v范围.fs移动(v段速度);
			float &v这段小位置 = v这段.v范围.m小;
			if (v这段小位置 >= v总长) {
				f消失段_销毁(v这段, v上段序号);
			}
			float &v这段大位置 = v这段.v范围.m大;
			if (v这段大位置 > v总长) {
				v这段大位置 = v总长;
			}
			//和上一段的交互
			if (v上段序号 >= 0) {
				S消失段 &v上段 = ma消失段[v上段序号];
				if (v上段.v范围.fi相交(v这段.v范围)) {
					v上段.v范围.m大 += v段速度;
					v这段.v范围.m小 -= v段速度;
					if (v上段.v消失.fi已经消失() && v这段.v消失.fi已经消失()) {
						v上段.v范围.fs合并(v这段.v范围);
						f消失段_销毁(v这段, v上段序号);
					}
				}
			}
			//准备下个段
			if (v这段.f对象_i使用()) {
				v上段序号 = v这段序号;
			}
			v这段序号 = v这段.v下个段;
		}
	}
}
void C射线激光::f接口_更新() {
	typedef C子弹顶点::C直线::S顶点 t顶点;
	f消失段_排序();
	const float v显示长度 = f扩展_g总长();
	//定义节点
	C子弹顶点::C直线::ta顶点 va节点;
	va节点.reserve(f消失段_数量() + 3);
	//添加节点
	auto f添加节点0 = [&](float a位置, float a消失) {
		va节点.push_back(t顶点{a位置, a消失});
	};
	f添加节点0(0, 0);
	f添加节点0(v显示长度, 1);
	auto f添加节点1 = [&](float a位置, float a消失) {
		if (a位置 > 0 && a位置 < v显示长度) {
			f添加节点0(a位置, a消失);
		}
	};
	f添加节点1(v显示长度 - c消失段半长度, 0);
	for (auto &v消失段 : f循环_消失段()) {
		const float &v消失 = v消失段.v消失.m帧;
		const float v小 = v消失段.v范围.fg小();
		f添加节点1(v小, 0);
		const float v大 = v消失段.v范围.fg大();
		f添加节点1(v大, 0);
		const float v半径 = v消失段.v范围.fg半径();
		if (v半径 <= c消失段半长度) {
			f添加节点1(v消失段.v范围.fg中心(), v半径 / c消失段半长度 * v消失);
		} else {
			f添加节点1(v小 + c消失段半长度, v消失);
			f添加节点1(v大 - c消失段半长度, v消失);
		}
	};
	auto f顶点比较 = [](const t顶点 &a0, const t顶点 &a1)->bool {
		return a0.m位置 < a1.m位置;
	};
	std::sort(va节点.begin(), va节点.end(), f顶点比较);
	auto f赋消失 = [](t顶点 &a点, float a消失) {
		float &v消失 = a点.m消失;
		v消失 = std::max<float>(v消失, a消失);
	};
	//如果一个消失段的消失节点在其它消失段中,重新计算消失
	for (auto &v消失段 : f循环_消失段()) {
		const float v小位置 = v消失段.v范围.fg小();
		const auto v开始节点 = std::upper_bound(va节点.begin(), va节点.end(), t顶点{v小位置, 0}, f顶点比较);
		const float v大位置 = v消失段.v范围.fg大();
		const auto v结束节点 = std::lower_bound(va节点.begin(), va节点.end(), t顶点{v大位置, 0}, f顶点比较);
		const float &v段消失 = v消失段.v消失.m帧;
		const float v半径 = v消失段.v范围.fg半径();
		if (v半径 <= c消失段半长度) {
			const float v中心 = v消失段.v范围.fg中心();
			for (auto v迭代器 = v开始节点; v迭代器 != v结束节点; ++v迭代器) {
				auto &v节点 = *v迭代器;
				const float &v节点位置 = v节点.m位置;
				const float v中心消失 = v半径 / c消失段半长度 * v段消失;
				if (v节点位置 <= v中心) {
					const float v消失 = 数学::f插值2<float, float>(v小位置, 0, v中心, v中心消失, v节点位置);
					f赋消失(v节点, v消失);
				} else {
					const float v消失 = 数学::f插值2<float, float>(v中心, v中心消失, v大位置, 0, v节点位置);
					f赋消失(v节点, v消失);
				}
			}
		} else {
			for (auto v迭代器 = v开始节点; v迭代器 != v结束节点; ++v迭代器) {
				auto &v节点 = *v迭代器;
				const float &v节点位置 = v节点.m位置;
				const float v小位置0 = v小位置 + c消失段半长度;
				const float v大位置0 = v大位置 - c消失段半长度;
				if (v节点位置 < v小位置0) {
					const float v消失 = 数学::f插值2<float, float>(v小位置, 0, v小位置0, v段消失, v节点位置);
					f赋消失(v节点, v消失);
				} else if (v节点位置 > v大位置0) {
					const float v消失 = 数学::f插值2<float, float>(v大位置0, v段消失, v大位置, 0, v节点位置);
					f赋消失(v节点, v消失);
				} else {
					f赋消失(v节点, v段消失);
				}
			}
		}
	};
	auto f位置转换 = 数学::C范围变换计算<float>{{0, v显示长度}, {0, 1}};
	for (auto &v节点 : va节点) {
		v节点.m位置 = f位置转换(v节点.m位置);
	}
	ma节点 = std::move(va节点);
	//准备图形数据
	const float v出现帧 = m出现.m帧 * (m缩放.y / m目标.y * 0.5f + 0.5f);
	const int v节点数量 = ma节点.size();
	C子弹顶点::C直线 v直线顶点{this, v节点数量};
	v直线顶点.m标志[C子弹顶点::e位置] = true;
	v直线顶点.m中心.m出现 = v出现帧;
	v直线顶点.m中心.m坐标 = f扩展_g中点();
	m图形数据 = m绘制->f生成直线(v直线顶点, ma节点);
}
void C射线激光::f接口_显示() const {
	m绘制->f绘制图形数据(m图形数据);
}
void C射线激光::f接口_自机判定(C自机与子弹判定 &a判定) {
	if (m缩放.y <= 0.1f) {
		return;
	}
	const t向量2 v方位 = f基础_到点方位(a判定.fg自机坐标());
	if (v方位.x < 0) {
		return;
	}
	const float v半径 = m子弹属性->fg判定y(m缩放.y);
	if (a判定.f子弹_提交判定(t圆形{f扩展_g点(v方位.x), v半径})) {
		bool vw有效 = true;
		for (auto &v消失段 : f循环_消失段()) {
			if (v消失段.v范围.fi范围内(v方位.x)) {
				vw有效 = false;
				break;
			}
		}
		if (vw有效) {
			a判定.f子弹_判定有效();
			if (a判定.f子弹_i擦弹()) {
				f基础_擦弹();
				if (a判定.f子弹_i碰撞()) {
					f消失段_新建(v方位.x);
				}
			}
		}
	}
}
bool C射线激光::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	if (m炸弹无敌 > 0) {
		return false;
	}
	const float c细分程度 = 12;
	const float v长 = m子弹属性->fg显示x(m缩放.x);
	if (a判定.f子弹_提交判定(f扩展_取固定端点(0.5f, v长), v长 / 2)) {
		const float v半径 = m子弹属性->fg判定y(m缩放.y);
		float v开始位置 = v长, v结束位置 = 0;
		bool v真 = false;
		std::vector<float> v判定位置组;
		for (float v位置 = 0; v位置 <= v长; v位置 += c细分程度) {
			const t向量2 v点 = f扩展_取固定端点(v位置);
			if (a判定.f子弹_提交判定(v点, v半径)) {
				v真 = true;
				if (v位置 < v开始位置) {
					v开始位置 = v位置;
				}
				if (v结束位置 < v位置) {
					v结束位置 = v位置;
				}
				//是否在消失范围外
				bool v范围外 = true;
				for (auto &v消失段 : f循环_消失段()) {
					if (v范围外 && v消失段.v范围.fi范围内(v位置)) {
						v范围外 = false;
					}
				};
				if (v范围外) {
					v判定位置组.push_back(v位置);
				}
			}
		}
		if (v真) {
			f消失段_新建((v开始位置 + v结束位置) / 2, v结束位置 - v开始位置);
			for (auto &v位置 : v判定位置组) {
				if (v位置 > 0)
					const t向量2 v道具点 = f扩展_取固定端点(v位置);
			}
			m炸弹无敌 = c炸弹无敌时间;
			return true;
		}
	}
	return false;
}
//初始化
void C射线激光::f初始化_长宽(float a长, float a宽) {
	m初始化_长 = a长;
	m初始化_宽 = a宽;
}
//动作
void C射线激光::f动作_消失(bool a) {
	if (a) {
		m消失.f消失();
	} else {
		f对象_销毁();
	}
}
void C射线激光::f动作_预警线(bool a) {
	m标志[e预警线] = a;
}
//扩展
t向量2 C射线激光::f扩展_取固定端点(float a, float a长) {
	return m坐标 + t向量2::fc方向r(a长 * a, m方向);
}
float C射线激光::f扩展_g总长() const {
	return m子弹属性->fg显示x(m缩放.x) * 2;
}
t向量2 C射线激光::f扩展_g中点() const {
	const float v显示长度 = m子弹属性->fg显示x(m缩放.x);
	return m坐标 + t向量2::fc方向r(v显示长度, m方向);
}
t向量2 C射线激光::f扩展_g远点() const {
	const float v显示长度 = m子弹属性->fg显示x(m缩放.x);
	return m坐标 + t向量2::fc方向r(v显示长度, m方向) * 2;
}
t向量2 C射线激光::f扩展_g点(float a位置) const {
	return m坐标 + t向量2::fc方向r(a位置, m方向);
}
//消失段
void C射线激光::f消失段_新建(float a位置, float a半径) {
	const float v半径 = (a半径 <= c消失段半长度) ? c消失段半长度 : a半径;
	ma消失段.f新建(1, [&](S消失段 &a, int i) {
		a.v序号 = i;
		a.v下个段 = m开始段;
		a.v范围.fs中心半径(a位置, v半径);
		if (a.v范围.m小 < 0) {
			a.v范围.m小 = 0;
		}
		a.v消失.f初始化(0);
		a.v消失.f消失();
		a.f对象_使用();
		m开始段 = i;
	});
	m标志[e变化_排序] = true;
	m标志[e变化_数量] = true;
	m标志[e变化_循环] = true;
}
void C射线激光::f消失段_销毁(S消失段 &p段, int p前) {
	int &v引用这个段 = (p前 < 0) ? m开始段 : ma消失段[p前].v下个段;
	const int &v下个段 = p段.v下个段;
	if (v下个段 >= 0) {
		v引用这个段 = v下个段;
	} else {
		v引用这个段 = -1;
	}
	p段.f对象_销毁();
	m标志[e变化_数量] = true;
	m标志[e变化_循环] = true;
}
void C射线激光::f消失段_排序() {
	auto vw排序 = m标志[e变化_排序];
	if (!vw排序) {
		return;
	}
	vw排序 = false;
	if (m开始段 < 0) {
		return;
	}
	std::vector<S段信息> va段信息;
	for (auto &v消失段 : f循环_消失段()) {
		S段信息 v信息;
		v信息.v序号 = v消失段.v序号;
		v信息.v中心 = v消失段.v范围.fg中心();
		v信息.v指针 = &v消失段;
		va段信息.push_back(v信息);
	}
	std::sort(va段信息.begin(), va段信息.end());
	auto &&vi数量 = m标志[e变化_数量];
	auto &&vi循环 = m标志[e变化_循环];
	int *v指 = &m开始段;
	for (auto &v信息 : va段信息) {
		S消失段 *const &vp这段 = v信息.v指针;
		if (*v指 != v信息.v序号) {
			*v指 = v信息.v序号;
			vi循环 = true;
		}
		v指 = &vp这段->v下个段;
	}
	*v指 = -1;
}
int C射线激光::f消失段_数量() {
	auto &&vi数量 = m标志[e变化_数量];
	if (vi数量) {
		int v新数量 = 0;
		int v段 = m开始段;
		while (v段 >= 0) {
			++v新数量;
			v段 = ma消失段[v段].v下个段;
		}
		m数量 = v新数量;
	}
	return m数量;
}
循环::C零散<std::vector<C射线激光::S消失段>> &C射线激光::f循环_消失段() {
	auto &&vi循环 = m标志[e变化_循环];
	if (vi循环) {
		std::vector<int> va序号;
		int v段 = m开始段;
		while (v段 >= 0) {
			va序号.push_back(v段);
			v段 = ma消失段[v段].v下个段;
		}
		m循环缓存_消失段 = 循环::C零散<std::vector<C射线激光::S消失段>>{ma消失段, va序号};
	}
	return m循环缓存_消失段;
}
}	//namespace 东方山寨