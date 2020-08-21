#include "数学_运动.h"
#include "计算.h"
#include "游戏.h"
#include "游戏常量.h"
namespace 东方山寨 {
//运动
const t向量2 &C复杂运动::fg坐标() const {
	return m坐标;
}
const t向量2 &C复杂运动::fg速度() const {
	return m速度;
}
void C复杂运动::fs速度(const t向量2 &a速度) {
	m速度 = a速度;
	mf运动 = nullptr;
}
void C复杂运动::fs运动(const tf复杂运动 &af运动) {
	mf运动 = af运动;
	m运动时间 = 0;
}
float C复杂运动::fg移动方向x() const {
	return 数学::f取符号<float>(m速度.x);
}
float C复杂运动::fg移动方向y() const {
	return 数学::f取符号<float>(m速度.y);
}
bool C复杂运动::fi运动时间内(float a时间) const {
	return m运动时间 < a时间;
}
float C复杂运动::f剩余运动时间(float a时间) const {
	return a时间 - m运动时间;
}
void C复杂运动::f计算运动(float a过秒) {
	if (mf运动) {
		m速度 = mf运动(*this);
	}
	m运动时间 += a过秒;
	计算::f基本运动计算(m坐标, m速度, a过秒);
}
void C复杂运动::f直接移动(const t向量2 &a目标, float a时间) {
	m速度 = 计算::f到目标速度(m坐标, a目标, a时间);
}
void C复杂运动::f运动_速度(const t向量2 &a速度, float a时间) {
	if (a时间 > 0) {
		fs运动(F直线速度(a速度, a时间));
	} else {
		fs速度(a速度);
	}
}
void C复杂运动::f运动_限时移动到(const t向量2 &a目标, float a时间, float a平滑开始, float a平滑结束) {
	if (a平滑开始 != 0 || a平滑结束 != 0) {
		f运动_平滑移动到(a目标, a时间, a平滑开始, a平滑结束);
	} else {
		fs运动(F目标坐标(a目标, a时间));
	}
}
void C复杂运动::f运动_限速移动到(const t向量2 &a目标, float a速度, float a平滑开始, float a平滑结束) {
	if (a平滑开始 != 0 || a平滑结束 != 0) {
		const float v时间 = a目标.fg大小() / a速度;
		f运动_平滑移动到(a目标, v时间, a平滑开始, a平滑结束);
	} else {
		fs运动(F目标坐标(a目标, m坐标.f到点距离(a目标) / a速度));
	}
}
void C复杂运动::f运动_限时移动过(const t向量2 &a目标, float a时间, float a平滑开始) {
	if (a平滑开始 != 0) {
		f运动_平滑移动过(a目标, a时间, a平滑开始);
	} else {
		fs速度((a目标 - m坐标) / a时间);
	}
}
void C复杂运动::f运动_限速移动过(const t向量2 &a目标, float a速度, float a平滑开始) {
	if (a平滑开始 != 0) {
		const float v时间 = a目标.fg大小() / a速度;
		f运动_平滑移动过(a目标, v时间, a平滑开始);
	} else {
		fs速度(t向量2::fc方向r(a速度, m坐标.f到点方向r(a目标)));
	}
}
void C复杂运动::f运动_平滑移动到(const t向量2 &a目标, float a总时间, float a平滑开始, float a平滑结束) {
	const float v方向 = m坐标.f到点方向r(a目标);
	const float v距离 = m坐标.f到点距离(a目标);
	const float v均速时间 = a总时间 - a平滑开始 - a平滑结束;
	const float v速度 = v距离 / (0.5f * a平滑开始 + 0.5f * a平滑结束 + v均速时间);
	fs运动(F平滑移动到(t向量2::fc方向r(v速度, v方向), a总时间, a平滑开始, a平滑结束));
}
void C复杂运动::f运动_平滑移动过(const t向量2 &a目标, float a总时间, float a平滑开始) {
	const float v方向 = m坐标.f到点方向r(a目标);
	const float v距离 = m坐标.f到点距离(a目标);
	const float v均速时间 = a总时间 - a平滑开始;
	const float v速度 = v距离 / (0.5f * a平滑开始 + v均速时间);
	fs运动(F平滑移动过(t向量2::fc方向r(v速度, v方向), a总时间, a平滑开始));
}
void C复杂运动::f运动_相对横坐标随机移动(float a横坐标, float a横平均, float a横浮动, float a纵平均, float a纵浮动) {
	constexpr float c移动总时间 = 1.5f;
	constexpr float c移动开始 = 0.5f;
	constexpr float c移动结束 = 0.5f;
	auto v引擎 = C游戏::fg内容().f工厂_随机数引擎();
	const auto v纵分布 = std::uniform_real_distribution<float>(a纵平均 - a纵浮动, a纵平均 + a纵浮动);
	const float v纵位置0 = v纵分布(v引擎);
	const float v纵差 = v纵位置0 - m坐标.y;
	const float v纵位置1 = (abs(v纵差) > a横平均) ? (m坐标.y + 数学::f取符号(v纵差) * a横平均) : v纵位置0;
	if (a横坐标 == m坐标.x) {
		const auto v横分布 = std::uniform_real_distribution<float>(-a横平均, a横平均);
		const float v横移动 = v横分布(v引擎);
		const float v横位置 = m坐标.x + v横移动;
		f运动_平滑移动到({ v横位置, v纵位置1 }, c移动总时间, c移动开始, c移动结束);
	} else {
		const auto v横分布 = std::uniform_real_distribution<float>(a横平均 - a横浮动, a横平均 + a横浮动);
		const float v横移动 = v横分布(v引擎);
		const float v横位置 = m坐标.x + 数学::f取符号(a横坐标 - m坐标.x) * v横移动;
		f运动_平滑移动到({ v横位置, v纵位置1 }, c移动总时间, c移动开始, c移动结束);
	}
}
//==============================================================================
// 运动
//==============================================================================
tf复杂运动 C复杂运动::F直线速度(const t向量2 &a速度, float a时间) {
	return [=](const C复杂运动 &a运动)->t向量2 {
		return a运动.fi运动时间内(a时间) ? a速度 : t向量2::c零;
	};
}
tf复杂运动 C复杂运动::F目标坐标(const t向量2 &a目标, float a时间) {
	return [=](const C复杂运动 &a运动)->t向量2 {
		const float v剩余时间 = a运动.f剩余运动时间(a时间);
		const t向量2 v坐标差 = a目标 - a运动.m坐标;
		return (v剩余时间 >= c帧秒<float>) ? (v坐标差 / v剩余时间) : v坐标差;
	};
}
tf复杂运动 C复杂运动::F平滑移动到(const t向量2 &a最高速度, float a总时间, float a平滑开始, float a平滑结束) {
	const float v均速结束点 = a总时间 - a平滑结束;
	assert(a总时间 - a平滑开始 - a平滑结束 >= 0);	//均速运动时间要大于0
	return [=](const C复杂运动 &a运动)->t向量2 {
		const float v运动时间 = a运动.m运动时间;
		if (v运动时间 < a平滑开始) {	//平滑开始
			return 数学::f插值<t向量2>(t向量2::c零, a最高速度, v运动时间 / a平滑开始);
		} else if (v运动时间 < v均速结束点) {	//均速
			return a最高速度;
		} else if (v运动时间 < a总时间) {	//平滑结束
			return 数学::f插值<t向量2>(a最高速度, t向量2::c零, (v运动时间 - v均速结束点) / a平滑结束);
		} else {	//停止移动
			return t向量2::c零;
		}
	};
}
tf复杂运动 C复杂运动::F平滑移动过(const t向量2 &a最高速度, float a总时间, float a平滑开始) {
	assert(a总时间 - a平滑开始 >= 0);
	return [=](const C复杂运动 &a运动)->t向量2 {
		const float v运动时间 = a运动.m运动时间;
		if (v运动时间 < a平滑开始) {
			return 数学::f插值<t向量2>(t向量2::c零, a最高速度, v运动时间 / a平滑开始);
		} else {
			return a最高速度;
		}
	};
}

}	//namespace 东方山寨