#include "常量.h"
#include "图形_抬显.h"
#include "敌机基础.h"
#include "游戏.h"
#include "关卡效果.h"
namespace 东方山寨 {
//=============================================================================
// 标题
//=============================================================================
C关卡标题::C关卡标题(const S关卡标题 &p) {
	//格式
	auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
	二维::S文本格式参数 v文本格式;
	v文本格式.m字体 = c文本字体;
	v文本格式.m字号 = c大字号;
	v文本格式.m水平对齐 = DWRITE_TEXT_ALIGNMENT_CENTER;
	//文本
	std::wstring v文本 = p.m场景 + L"\n" + p.m标题;
	//创建布局
	m布局 = v文本工厂.fc文本布局(v文本, v文本格式);
	m布局->SetFontSize(c小字号, {0, p.m场景.size() + 1});
}
void C关卡标题::f接口_计算() {
	f计算_生命();
}
void C关卡标题::f接口_显示() const {
	auto &v画文本 = C游戏::fg图形().fg画文本();
	v画文本.fs区域(t向量2{0, 100});
	v画文本.fs颜色(t颜色::c白);
	v画文本.fs透明度(数学::f等腰梯形插值<float>(0, 1, 1.f / m寿命, fg生命百分比()));
	v画文本.f绘制文本布局(m布局.Get());
}

//=============================================================================
// 总血条
//=============================================================================
C总血条::C总血条(int p):
	m总数(p), m当前(p),
	m显示(0), m实际(1) {
	assert(p > 0);
	const auto &v二维 = C游戏::fg图形().m二维;
	m渲染目标 = v二维->fg渲染目标();
	m画笔 = v二维->fc纯色画笔(t颜色(0, 1, 0, 1));
}
void C总血条::f接口_更新() {
	auto &v图形 = C游戏::fg图形();
	const float v渲染秒 = v图形.fg渲染秒();
	if (m实际 != m显示) {
		m显示 = 数学::f线性渐变<float>(m显示, m实际, c变化速度 * v渲染秒);
	}
}
void C总血条::f接口_显示() const {
	auto &v图形 = C游戏::fg图形();
	const auto &v渲染目标 = v图形.fg二维渲染目标();
	const auto &v坐标计算 = v图形.fg二维坐标计算();
	const float v每段长度 = c总长度 / (float)m总数;
	const float v显示右 = c左 + c总长度 * m显示;
	for (int i = 0; i < m总数; ++i) {
		const float v左 = c左 + (float)i * v每段长度;
		if (v左 > v显示右) {
			break;
		}
		const float v右 = v左 + v每段长度 - c间隔;
		if (v右 > v显示右) {
			v渲染目标->FillRectangle(v坐标计算.f矩形_左上右下(v左, c外边框范围y, v显示右, c边框范围y), m画笔.Get());
			break;
		} else {
			v渲染目标->FillRectangle(v坐标计算.f矩形_左上右下(v左, c外边框范围y, v右, c边框范围y), m画笔.Get());
		}
	}
}
bool C总血条::f接口_i可销毁() const {
	return m当前 == 0 && m显示 == 0;
}
void C总血条::f减一() {
	--m当前;
	m实际 = (float)m当前 / (float)m总数;
}
//=============================================================================
// 分血条
//=============================================================================
const 数学::S颜色 C分血条::c颜色(1, .5f, .5f, 1);
C分血条::C分血条(const C敌机 &p敌机):
	m敌机(&p敌机),
	m实际(p敌机.m生命值.fg百分比()),
	m显示(0) {
	assert(p敌机.f对象_i使用());
	const auto &v二维 = C游戏::fg图形().fg二维();
	m渲染目标 = v二维.fg渲染目标();
	m画笔 = v二维.fc纯色画笔(t颜色(1, .5f, .5f, 0.8f));
}
void C分血条::f接口_计算() {
	mi更新 = true;
	if (m敌机) {
		if (m敌机->f对象_i使用()) {
			if (m敌机->m生命值.m当前 > 0) {
				m实际 = m敌机->m生命值.fg百分比();
			} else {
				m实际 = 0;
			}
			if (m坐标 != m敌机->m坐标) {
				m坐标 = m敌机->m坐标;
				mi更新 = false;
			}
		} else {
			m敌机 = nullptr;
		}
	}
}
void C分血条::f接口_更新() {
	auto &v图形 = C游戏::fg图形();
	const float v渲染秒 = v图形.fg渲染秒();
	if (m实际 != m显示) {
		m显示 = 数学::f线性渐变<float>(m显示, m实际, c变化速度 * v渲染秒);
		mi更新 = false;
	}
	//更新对象
	if (mi更新) {
		return;
	}
	auto &v二维 = v图形.fg二维();
	auto &v坐标计算 = v二维.fg坐标计算();
	m外圈 = v坐标计算.f圆形(m坐标, c外圈);
	m内圈 = v坐标计算.f圆形(m坐标, c内圈);
	m几何 = v二维.fc路径几何();
	auto v修改 = v二维.f修改路径几何(m几何);
	v修改.f圆弧(m坐标, c半径, 数学::c半π<float>, 数学::c二π<float> * m显示, false);
	mi更新 = true;
}
void C分血条::f接口_显示() const {
	if (m敌机 && m敌机->f对象_i使用()) {
		m渲染目标->DrawEllipse(m外圈, m画笔.Get());
		m渲染目标->DrawEllipse(m内圈, m画笔.Get());
		m渲染目标->DrawGeometry(m几何.Get(), m画笔.Get(), c线宽);
	}
}
bool C分血条::f接口_i可销毁() const {
	return m敌机 == nullptr;
}
//=============================================================================
// 弹幕时间
//=============================================================================
const t颜色 C弹幕时间::c正常颜色 = t颜色(1,1,1,1);
const t颜色 C弹幕时间::c急促颜色0 = t颜色(1, 0.5f, 0, 1);
const t颜色 C弹幕时间::c急促颜色1 = t颜色(1, 0, 0, 1);
C弹幕时间::C弹幕时间(const float &p):
	m实际(p), m显示(0){
	auto &v二维 = C游戏::fg图形().fg二维();
	m画笔 = v二维.fc纯色画笔(c正常颜色);
	//文本
	二维::S文本格式参数 v格式;
	v格式.fs字号(c字号);
	v格式.fs水平对齐(二维::E文本水平对齐::e中);
	v格式.fs垂直对齐(二维::E文本垂直对齐::e上);
	auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
	m格式 = v文本工厂.fc文本格式(v格式);
}
void C弹幕时间::f接口_更新() {
	if (m显示 != m实际) {
		const float v整数差 = floor(m显示) - floor(m实际);
		const float v渲染秒 = C游戏::fg图形().fg渲染秒();
		if (m实际 < 10 && v整数差 > 0) {
			m画笔->SetColor(二维::C类型转换::f颜色((m实际 > c王战倒计时1) ? c急促颜色0 : c急促颜色1));
			m透明度 = 1;
		} else {
			m透明度 = 数学::f线性渐变<float>(m透明度, c透明度, c透明度速度 * v渲染秒);
			m画笔->SetOpacity(m透明度);
		}
		m显示 = m实际;
		auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
		if (m显示 < 1000) {
			m布局 = v文本工厂.fc文本布局_小数(m显示, 2, m格式.Get());
		} else {
			m布局 = v文本工厂.fc文本布局(L"∞", m格式.Get());
		}
	}
}
void C弹幕时间::f接口_显示() const {
	static const D2D1_POINT_2F c点 = C游戏::fg图形().fg二维坐标计算().f点(t向量2(0, c边框范围y + c边框厚度));
	auto v渲染目标 = C游戏::fg图形().fg二维渲染目标();
	v渲染目标->DrawTextLayout(c点, m布局.Get(), m画笔.Get());
}
void C弹幕时间::f动作_重置颜色() {
	//m画笔->SetColor(二维::C类型转换::f颜色(c正常颜色));
	if (m实际 >= 10) {
		m画笔->SetColor(二维::C类型转换::f颜色(c正常颜色));
	} else if (m实际 > 5) {
		m画笔->SetColor(二维::C类型转换::f颜色(c急促颜色0));
	} else {
		m画笔->SetColor(二维::C类型转换::f颜色(c急促颜色1));
	}
}
}	//namespace 东方山寨