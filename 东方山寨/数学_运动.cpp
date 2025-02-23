#include "数学_运动.h"
#include "游戏.h"
#include "游戏常量.h"
import 东方山寨.计算;
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
	m运动时间 += a过秒;
	if (mf运动) {
		m速度 = mf运动(*this);
	}
	计算::f基本运动计算(m坐标, m速度, a过秒);
}
void C复杂运动::f直接移动(const t向量2 &a目标, float a时间) {
	m速度 = 计算::f到目标速度(m坐标, a目标, a时间);
}
void C复杂运动::f运动_结束() {
	mf运动 = nullptr;
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
void C复杂运动::f运动_随机移动到(const t向量2 &a目标, const t向量2 &a移动, const t向量2 &a浮动) {
	constexpr float c移动总时间 = 1.5f;
	constexpr float c移动开始 = 0.5f;
	constexpr float c移动结束 = 0.5f;
	auto f计算目标位置 = [](float a当前0, float a目标0, float a移动0, float a浮动0, int a随机推进)->float {
		auto v引擎 = C游戏::fg内容().f工厂_随机数引擎(a随机推进);
		if (a当前0 == a目标0) {
			auto v分布 = std::uniform_real_distribution<float>(-a移动0, a移动0);
			const float v移动 = v分布(v引擎);
			const float v目标 = a当前0 + v移动;
			return v目标;
		} else {
			auto v分布 = std::uniform_real_distribution<float>(a移动0 - a浮动0, a移动0 + a浮动0);
			const float v移动 = v分布(v引擎);
			const float v目标 = a当前0 + 数学::f取符号(a目标0 - a当前0) * v移动;
			return v目标;
		}
	};
	const float v目标x = f计算目标位置(m坐标.x, a目标.x, a移动.x, a浮动.x, 0x328d);
	const float v目标y = f计算目标位置(m坐标.y, a目标.y, a移动.y, a浮动.y, 0x4fa0);
	f运动_平滑移动到({v目标x, v目标y}, c移动总时间, c移动开始, c移动结束);
}
void C复杂运动::f运动_圆周运动(bool a顺时针, float a时间, float a圈数) {
	const float v方向 = m速度.fg方向r();
	const float v角速度 = 数学::c二π<float> *(a顺时针 ? -1 : 1) / a时间 * a圈数;
	const float v线速度 = m速度.fg大小();
	const float v半径 = 计算::f圆周运动半径(v线速度, v角速度);
	const float v到圆心方向 = (a顺时针 ? -1 : 1) * 数学::c半π<float> + v方向;
	const t向量2 v圆心 = m坐标 + t向量2::fc方向r(v半径, v到圆心方向);
	const float v起点方向 = v到圆心方向 + 数学::cπ<float>;
	fs运动(F圆周运动(v圆心, v半径, v起点方向, v角速度));
}
void C复杂运动::f运动_圆周运动(const t向量2 &a圆心, float a半径, float a起点方向, bool a顺时针, float a时间, float a周数) {
	const float v角速度 = 数学::c二π<float> * (a顺时针 ? -1 : 1) / a时间 / a周数;
	fs运动(F圆周运动(a圆心, a半径, a起点方向, v角速度));
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
tf复杂运动 C复杂运动::F圆周运动(const t向量2 &a圆心, float a半径, float a起点方向, float a角速度) {
	return [=](const C复杂运动 &a运动)->t向量2 {
		const float v运动时间 = a运动.m运动时间;
		const float v目标方向 = a起点方向 + a角速度 * v运动时间;
		const t向量2 v目标坐标 = a圆心 + t向量2::fc方向r(a半径, v目标方向);
		return (v目标坐标 - a运动.fg坐标()) * c计算频率<float>;
	};
}
}	//namespace 东方山寨