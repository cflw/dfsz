#include "游戏常量.h"
#include "边框常量.h"
#include "数学包含.h"
#include "日志.h"
namespace 东方山寨 {
float C日志::S日志::fg透明度() const {
	return std::min<float>(m出现, 1 - m消失);
}
C日志::C日志(二维::C二维 &a二维):
	m画文本(a二维.fc画文本()) {
	二维::C文本工厂 v文本工厂;
	v文本工厂.f初始化();
	二维::S文本格式参数 v格式;
	v格式.fs字号(12);
	v格式.fs水平对齐(二维::E文本水平对齐::e左);
	v格式.fs垂直对齐(二维::E文本垂直对齐::e下);
	m画文本->m格式 = v文本工厂.fc文本格式(v格式);
}
void C日志::f添加(E级别 a级别, const std::wstring &a文本) {
	S日志 v日志;
	v日志.m时间 = 时间::fg现在();
	v日志.m级别 = a级别;
	v日志.m文本 = a文本;
	ma日志.push_back(v日志);
	m显示位置y -= c行距;
}
void C日志::f计算() {
	constexpr float c渐变速度 = 4;
	constexpr float c渐变秒 = c帧秒<float> * c渐变速度;
	int i = 0;
	const int v数量 = ma日志.size();
	const int v消失 = v数量 - 5;
	for (S日志 &v日志 : ma日志) {
		v日志.m出现 += c帧秒<float>;
		if (i < v消失) {
			v日志.m消失 += c渐变秒;
		} else if (v日志.m出现 >= 5) {
			v日志.m消失 += c帧秒<float>;	//慢慢消失
		}
		++i;
	}
	//清除过期日志
	while (!ma日志.empty()) {
		const S日志 &v日志 = ma日志.front();
		if (v日志.m消失 >= 1) {
			ma日志.pop_front();
		} else {
			break;
		}
	}
	m显示位置y = 数学::f倍数渐变<float>(m显示位置y, -c框架范围y, 0.01f, c帧秒<float>);
}
void C日志::f显示() const {
	float v显示位置y = m显示位置y;
	//从后住前
	for (auto v = ma日志.crbegin(); v != ma日志.crend(); ++v) {
		const S日志 &v日志 = *v;
		const float v透明度 = v日志.fg透明度();
		m画文本->fs颜色({1, 1, 1, v透明度});
		m画文本->fs区域(-c框架范围x, v显示位置y);
		m画文本->f绘制文本(v日志.m文本);
		v显示位置y += c行距;
	}
}
}