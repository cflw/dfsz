export module 东方山寨.图形.抬显;
export import "图形包含.h";
export import "图形基础.h";
export import "图形缓冲.h";
export import "边框常量.h";
export import 东方山寨.王战;
import "程序常量.h";
import "游戏常量.h";
import "游戏.h";
import "图形引擎.h";
import "敌机基础.h";
import 东方山寨.抬显;
export namespace 东方山寨 {
class C敌机;
struct S关卡标题;
class C符卡控制;
class C王战时间控制;
constexpr float c抬显最大透明度 = 0.8f;
constexpr float c抬显最小透明度 = 0.5f;
constexpr float c抬显透明度速度 = (c抬显最大透明度 - c抬显最小透明度) * 2.f;
constexpr float c血条透明度 = 0.6f;
//==============================================================================
// 血条
//==============================================================================
class C总血条 : public I图形 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp渲染目标 m渲染目标;
		二维::tp纯色画笔 m画笔;
		int m总数;
		float m显示;	//百分比
	};
	static constexpr float c变化速度 = 0.5f;
	static constexpr float c线宽 = 4;
	static constexpr float c间隔 = 2;	//每段之间留一点空白
	static constexpr float c左 = -c边框范围x;
	static constexpr float c右 = c边框范围x + c间隔;
	static constexpr float c总长度 = 2 * c边框范围x + c间隔;
	using t图形缓冲 = C图形缓冲;
	C总血条(int);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_更新() override;
	bool f接口_i可销毁() const override;
	void f减一();
private:
	int m总数, m当前;
	float m显示 = 0, m实际 = 1;	//百分比
};
class C分血条 : public I图形 {	//圆形血条
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp渲染目标 m渲染目标;
		二维::tp纯色画笔 m画笔;
		二维::tp路径几何 m几何;
		二维::t椭圆 m外圈, m内圈;	//2个圈
		二维::t点2f m指针[2];	//指出当前血量
		bool mi可显示;
	};
	static constexpr float c变化速度 = 2.f;
	static constexpr float c半径 = 64;
	static constexpr float c线宽 = 4;
	static constexpr float c外圈 = c半径 + c线宽 / 2 + 2;
	static constexpr float c内圈 = c半径 - c线宽 / 2 - 2;
	using t图形缓冲 = C图形缓冲;
	C分血条(const C敌机 &, const t颜色 & = t颜色::c粉);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	bool f接口_i可销毁() const override;
	bool fi可显示() const;	//敌机存在才能显示
private:
	t向量2 m坐标;
	t颜色 m颜色;
	float m显示, m实际;	//百分比
	const C敌机 *m敌机;	//跟踪的对象
	bool mi更新 = false;	//是否需要更新图形缓冲二维对象
};
//==============================================================================
// 弹幕时间
//==============================================================================
class C弹幕时间 : public I图形 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp渲染目标 m渲染目标;
		二维::tp纯色画笔 m画笔;
		二维::tp文本布局 m布局;
		二维::tp文本格式 m格式;
	};
	static constexpr float c字号 = 二维::ca中文字号[二维::e一号];
	static constexpr float c小数字号 = c字号 * 0.6f;
	static const t颜色 c正常颜色, c急促颜色0, c急促颜色1;
	using t图形缓冲 = C图形缓冲;
	C弹幕时间(const C王战时间控制 &);	//必需是引用
	void f接口_初始化(const S图形参数 &) override;
	void f接口_更新() override;
	void f动作_重置颜色();	//每秒调用一次
	static const t颜色 &fg显示颜色(float 时间);	//根据倒计时 白->浅红->深红
private:
	const C王战时间控制 *m时间控制 = nullptr;
	float m显示;	//文本
	float m透明度 = c抬显最大透明度;
	bool mi重置颜色 = false;	//在更新时更新颜色
};
//==============================================================================
// 符卡文本,包含符卡名和分数
//==============================================================================
class C符卡文本 : public I图形 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp画文本 m画分数;
		二维::tp画文本 m画名称;
		二维::tp文本格式 m格式;
		std::wstring m显示分数;
		std::wstring m显示名称;
	};
	static constexpr float c字号 = 二维::ca中文字号[二维::e三号];
	static constexpr t颜色 c结束颜色 = t颜色(0, 1, 0, c抬显最大透明度);
	using t图形缓冲 = C图形缓冲;
	C符卡文本(const C符卡控制 &符卡控制);
	void f接口_初始化(const S图形参数 &);
	void f接口_更新() override;
	bool f接口_i可销毁() const override;
	void f动作_结束();
	const C符卡控制 *m符卡控制 = nullptr;
	int m显示分数 = 0;
	float m分数透明度 = c抬显最大透明度;
	float m名称透明度 = c抬显最大透明度;
	float m出现 = 0;
	bool mi刚消失 = false;
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
//==============================================================================
// 总血条
//==============================================================================
C总血条::C总血条(int a):
	m总数(a), m当前(a) {
	assert(a > 0);
}
void C总血条::f接口_初始化(const S图形参数 &a) {
	I图形::f接口_初始化(a);
	const auto &v二维 = C游戏::fg图形().m二维;
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	v图形缓冲.m渲染目标 = v二维->fg渲染目标();
	v图形缓冲.m画笔 = v二维->fc纯色画笔(t颜色(0, 1, 0, c血条透明度));
	v图形缓冲.m总数 = m总数;
	v图形缓冲.m显示 = 0;
}
void C总血条::f接口_更新() {
	auto &v图形 = C游戏::fg图形();
	const float v渲染秒 = v图形.fg渲染秒();
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	if (m实际 != m显示) {
		v图形缓冲.m显示 = m显示 = 数学::f线性渐变<float>(m显示, m实际, c变化速度 * v渲染秒);
	}
	v图形缓冲.m画笔->SetOpacity(c血条透明度 * C抬显控制::fg全局透明度());
}
bool C总血条::f接口_i可销毁() const {
	return m当前 == 0 && m显示 == 0;
}
void C总血条::f减一() {
	--m当前;
	m实际 = (float)m当前 / (float)m总数;
}
//图形缓冲
void C总血条::C图形缓冲::f显示() const {
	auto &v图形 = C游戏::fg图形();
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
			m渲染目标->FillRectangle(v坐标计算.f矩形_左上右下(v左, c外边框范围y, v显示右, c边框范围y), m画笔.Get());
			break;
		} else {
			m渲染目标->FillRectangle(v坐标计算.f矩形_左上右下(v左, c外边框范围y, v右, c边框范围y), m画笔.Get());
		}
	}
}
//==============================================================================
// 分血条
//==============================================================================
C分血条::C分血条(const C敌机 &a敌机, const t颜色 &a颜色):
	m敌机(&a敌机),
	m颜色(a颜色),
	m实际(a敌机.m生命值.fg百分比()),
	m显示(0) {
	assert(a敌机.f对象_i使用());
}
void C分血条::f接口_初始化(const S图形参数 &a) {
	I图形::f接口_初始化(a);
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	const auto &v二维 = C游戏::fg图形().fg二维();
	v图形缓冲.m渲染目标 = v二维.fg渲染目标();
	v图形缓冲.m画笔 = v二维.fc纯色画笔(m颜色);
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
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	if (m实际 != m显示) {
		m显示 = 数学::f线性渐变<float>(m显示, m实际, c变化速度 * v渲染秒);
		mi更新 = false;
	}
	v图形缓冲.mi可显示 = fi可显示();
	if (!v图形缓冲.mi可显示) {	//如果不用显示,只计算血条百分比,不更新二维对象
		return;
	}
	v图形缓冲.m画笔->SetOpacity(c血条透明度 * C抬显控制::fg全局透明度());
	//更新二维对象
	if (mi更新) {
		return;
	}
	auto &v二维 = v图形.fg二维();
	auto &v坐标计算 = v二维.fg坐标计算();
	v图形缓冲.m外圈 = v坐标计算.f圆形(m坐标, c外圈);
	v图形缓冲.m内圈 = v坐标计算.f圆形(m坐标, c内圈);
	v图形缓冲.m几何 = v二维.fc路径几何();
	auto v修改 = v二维.f修改路径几何(v图形缓冲.m几何);
	v修改.f圆弧(m坐标, c半径, 数学::c半π<float>, 数学::c二π<float> *m显示, false);
	const float v指针角度 = 数学::c半π<float> +数学::c二π<float> *m显示;
	v图形缓冲.m指针[0] = v坐标计算.f点(m坐标 + t向量2::fc方向r(c内圈, v指针角度));
	v图形缓冲.m指针[1] = v坐标计算.f点(m坐标 + t向量2::fc方向r(c外圈, v指针角度));
	mi更新 = true;
}
bool C分血条::f接口_i可销毁() const {
	return m敌机 == nullptr;
}
bool C分血条::fi可显示() const {
	return m敌机 && m敌机->f对象_i使用();
}
//图形缓冲
void C分血条::C图形缓冲::f显示() const {
	if (mi可显示) {
		m渲染目标->DrawEllipse(m外圈, m画笔.Get());
		m渲染目标->DrawEllipse(m内圈, m画笔.Get());
		m渲染目标->DrawGeometry(m几何.Get(), m画笔.Get(), c线宽);
		m渲染目标->DrawLine(m指针[0], m指针[1], m画笔.Get(), 2);
	}
}
//==============================================================================
// 弹幕时间
//==============================================================================
const t颜色 C弹幕时间::c正常颜色 = t颜色(1, 1, 1, c抬显最大透明度);
const t颜色 C弹幕时间::c急促颜色0 = t颜色(1, 0.5f, 0, c抬显最大透明度);
const t颜色 C弹幕时间::c急促颜色1 = t颜色(1, 0, 0, c抬显最大透明度);
C弹幕时间::C弹幕时间(const C王战时间控制 &a时间控制):
	m时间控制(&a时间控制), m显示(0) {
}
void C弹幕时间::f接口_初始化(const S图形参数 &a) {
	I图形::f接口_初始化(a);
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	auto &v二维 = C游戏::fg图形().fg二维();
	v图形缓冲.m渲染目标 = v二维.fg渲染目标();
	v图形缓冲.m画笔 = v二维.fc纯色画笔(c正常颜色);
	//文本
	二维::S文本格式参数 v格式;
	v格式.fs字号(c字号);
	v格式.fs水平对齐(二维::E文本水平对齐::e中);
	v格式.fs垂直对齐(二维::E文本垂直对齐::e上);
	auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
	v图形缓冲.m格式 = v文本工厂.fc文本格式(v格式);
}
void C弹幕时间::f接口_更新() {
	const float v显示 = m时间控制->fg显示倒计时();
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	if (m显示 != v显示) {
		const float v整数差 = floor(m显示) - floor(v显示);
		const float v渲染秒 = C游戏::fg图形().fg渲染秒();
		if (v显示 < 10 && v整数差 > 0) {
			const t颜色 &v颜色 = v显示 > c王战倒计时1 ? c急促颜色0 : c急促颜色1;
			v图形缓冲.m画笔->SetColor(二维::C类型转换::f颜色(v颜色));
			m透明度 = 1;
			mi重置颜色 = false;
		} else {
			m透明度 = 数学::f线性渐变<float>(m透明度, c抬显最小透明度, c抬显透明度速度 * v渲染秒);
		}
		if (mi重置颜色) {
			v图形缓冲.m画笔->SetColor(二维::C类型转换::f颜色(fg显示颜色(v显示)));
			mi重置颜色 = false;
		}
		v图形缓冲.m画笔->SetOpacity(m透明度);
		m显示 = v显示;
		auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
		if (m显示 < 1000) {
			v图形缓冲.m布局 = v文本工厂.fc文本布局_小数(m显示, 2, v图形缓冲.m格式.Get());
		} else {
			v图形缓冲.m布局 = v文本工厂.fc文本布局(L"∞", v图形缓冲.m格式.Get());
		}
	}
}
void C弹幕时间::f动作_重置颜色() {
	mi重置颜色 = true;
}
const t颜色 &C弹幕时间::fg显示颜色(float a时间) {
	if (a时间 >= 10) {
		return c正常颜色;
	} else if (a时间 > 5) {
		return c急促颜色0;
	} else {
		return c急促颜色1;
	}
}
//图形缓冲
void C弹幕时间::C图形缓冲::f显示() const {
	static const D2D1_POINT_2F c点 = C游戏::fg图形().fg二维坐标计算().f点(t向量2(0, c边框范围y + c边框宽度));
	m渲染目标->DrawTextLayout(c点, m布局.Get(), m画笔.Get());
}
//==============================================================================
// 符卡文字
//==============================================================================
C符卡文本::C符卡文本(const C符卡控制 &a符卡控制):
	m符卡控制(&a符卡控制) {
}
void C符卡文本::f接口_初始化(const S图形参数 &) {
	auto &v图形 = C游戏::fg图形();
	二维::S文本格式参数 v格式;
	v格式.fs字号(c字号);
	v格式.fs水平对齐(二维::E文本水平对齐::e右);
	v格式.fs垂直对齐(二维::E文本垂直对齐::e上);
	auto &v文本工厂 = v图形.fg文本工厂();
	const auto f赋画文本 = [&](std::shared_ptr<二维::C画文本> &a画文本, float a位置y) {
		a画文本 = v图形.fc画文本();
		a画文本->fs区域(t向量2(c边框范围x, a位置y));
		a画文本->fs颜色(t颜色(1, 1, 1, c抬显最大透明度));
		a画文本->fs格式(v文本工厂.fc文本格式(v格式).Get());
		};
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	f赋画文本(v图形缓冲.m画分数, c边框范围y);
	f赋画文本(v图形缓冲.m画名称, c边框范围y - c字号);
	v图形缓冲.m显示名称 = m符卡控制->fg名称();
}
void C符卡文本::f接口_更新() {
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	//计算
	const float v渲染秒 = C游戏::fg图形().fg渲染秒();
	if (m符卡控制) {
		m出现 += v渲染秒;	//出现
		const int v当前分数 = m符卡控制->fg当前分数();
		if (m显示分数 - v当前分数 >= m显示分数 / 4) {	//分数变化较大时分数变明显,当前阀值1/4
			m分数透明度 = c抬显最大透明度;
		}
		m显示分数 = v当前分数;
	} else {
		m出现 -= v渲染秒;	//消失
	}
	if (mi刚消失) {
		v图形缓冲.m画分数->fs颜色(t颜色(0, 1, 0, m分数透明度));
		v图形缓冲.m画名称->fs颜色(t颜色(0, 1, 0, m名称透明度));
		mi刚消失 = false;
	}
	if (m出现 < 0.5f) {
		const float v透明度 = 数学::f插值<float>(0, c抬显最大透明度, m出现 * 2);
		m分数透明度 = m名称透明度 = v透明度;
	} else if (m出现 < 2) {
		m分数透明度 = m名称透明度 = c抬显最大透明度;
	} else {
		m分数透明度 = 数学::f线性渐变<float>(m分数透明度, c抬显最小透明度, c抬显透明度速度 * v渲染秒);
		m名称透明度 = 数学::f线性渐变<float>(m名称透明度, c抬显最小透明度, c抬显透明度速度 * v渲染秒);
	}
	//更新缓冲
	v图形缓冲.m画分数->fs透明度(m分数透明度);
	v图形缓冲.m画名称->fs透明度(m名称透明度);
	v图形缓冲.m显示分数 = std::to_wstring(m显示分数);
}
bool C符卡文本::f接口_i可销毁() const {
	return !m符卡控制 && m分数透明度 <= 0;
}
void C符卡文本::f动作_结束() {
	m符卡控制 = nullptr;
	m出现 = 1;
	mi刚消失 = true;
}
void C符卡文本::C图形缓冲::f显示() const {
	m画分数->f绘制文本(m显示分数);
	m画名称->f绘制文本(m显示名称);
}
}	//namespace 东方山寨