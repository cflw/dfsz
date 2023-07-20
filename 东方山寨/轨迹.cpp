#include "游戏常量.h"
#include "轨迹.h"
namespace 东方山寨 {
void C轨迹::f添加坐标(const t向量2 &a坐标) {
	ma坐标.push_front(a坐标);
	if (ma坐标.size() > c计算频率<size_t>) {
		ma坐标.pop_back();
	}
}
void C轨迹::f填充坐标(const t向量2 &a坐标) {
	constexpr size_t c总数量 = c计算频率<size_t>;
	std::deque<t向量2> va坐标(c总数量, a坐标);
	ma坐标.swap(va坐标);
}
const t向量2 &C轨迹::fg当前坐标() const {
	return ma坐标.front();
}
t向量2 C轨迹::fg未来坐标(float a秒) const {
	return fg当前坐标() + fg平均速度(a秒) * a秒;
}
t向量2 C轨迹::fg平均速度(float a秒) const {
	constexpr size_t c总数量 = c计算频率<size_t>;
	const float v帧 = std::floor(a秒 * c计算频率<float>);
	const size_t v帧数 = (size_t)v帧;
	const auto vp开始 = ma坐标.begin();
	if (v帧数 <= 1) {	//小于1帧,取瞬间速度
		return *vp开始 - *(vp开始 + 1);
	} else if (v帧数 >= c总数量) {	//大于1秒
		const t向量2 v坐标差 = ma坐标.front() - ma坐标.back();
		return v坐标差;
	} else {	//1帧~1秒之间
		const t向量2 &v后坐标 = *(vp开始 + v帧数);
		const t向量2 v坐标差 = ma坐标.front() - v后坐标;
		return v坐标差 / a秒;
	}
}
void C实时轨迹::f记录坐标(const t向量2 &a坐标) {
	f添加坐标(a坐标);
}
void C移动轨迹::f记录坐标(const t向量2 &a坐标) {
	if (ma坐标.empty()) {
		ma坐标.push_front(a坐标);
		return;
	}
	if (ma坐标.front() == a坐标) {
		return;
	}
	f添加坐标(a坐标);
}

}	//namespace 东方山寨