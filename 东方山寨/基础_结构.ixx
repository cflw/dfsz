export module 东方山寨.基础.结构;
export import "数学包含.h";
export namespace 东方山寨 {
struct S运动 {
	t向量2 m坐标;
	t向量2 m速度;
	void f初始化_运动(const t向量2 &a坐标, const t向量2 &a速度) noexcept;
	void f计算_运动(float a过秒) noexcept;
};
struct S生命 {	//记录寿命和存活时间
	float m寿命;	//固定
	float m生命 = 0;	//存活的时间
	void f初始化_生命(float 寿命) noexcept;
	void f计算_生命(float 过秒) noexcept;
	float fg生命百分比() const noexcept;
	float fg反生命百分比() const noexcept;
	bool fi死亡() const noexcept;
	void fs剩余生命(float) noexcept;
	float fg剩余生命() const noexcept;
	float fg渐变(float 时间 = 1) const noexcept;	//计算渐变值,渐入0->1,渐出1->0
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
//==============================================================================
// 运动
//==============================================================================
void S运动::f初始化_运动(const t向量2 &a坐标, const t向量2 &a速度) noexcept {
	m坐标 = a坐标;
	m速度 = a速度;
}
void S运动::f计算_运动(float a过秒) noexcept {
	m坐标 += m速度 * a过秒;
}
//==============================================================================
// 生命
//==============================================================================
void S生命::f初始化_生命(float a寿命) noexcept {
	m寿命 = a寿命;
	m生命 = 0;
}
void S生命::f计算_生命(float a过秒) noexcept {
	m生命 += a过秒;
}
float S生命::fg生命百分比() const noexcept {
	return m生命 / m寿命;
}
float S生命::fg反生命百分比() const noexcept {
	return 1 - fg生命百分比();
}
bool S生命::fi死亡() const noexcept {
	return m生命 >= m寿命;
}
void S生命::fs剩余生命(float a寿命) noexcept {
	m寿命 = m生命 + a寿命;
}
float S生命::fg剩余生命() const noexcept {
	return m寿命 - m生命;
}
float S生命::fg渐变(float a时间) const noexcept {
	const float v渐入 = (m生命 > a时间) ? 1 : (m生命 / a时间);
	const float v剩余生命 = fg剩余生命();
	const float v渐出 = (v剩余生命 > a时间) ? 1 : (v剩余生命 / a时间);
	return std::min(v渐入, v渐出);
}
}	//namespace 东方山寨