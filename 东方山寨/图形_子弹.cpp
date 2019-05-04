#include "图形_子弹.h"
#include "子弹基础.h"
#include "图形引擎.h"
#include "程序.h"
namespace 东方山寨 {
//==============================================================================
// 工具
//==============================================================================
namespace 画子弹工具 {
class F固定位置 {
public:
	F固定位置(int a数量) :
		v数量((float)(a数量 - 1)) {
	}
	float operator ()(int i) const {
		return (float)i / v数量;
	}
private:
	const float v数量;
};
class F曲线方向 {
public:
	F曲线方向(float a方向) :
		m前方向{a方向}, m后方向{a方向} {
	}
	float operator ()(const t向量2 &a中, const t向量2 &a后) {
		if (&a中 != &a后) {
			m前方向 = m后方向;
			if (a中 != a后) {
				m后方向 = a后.f到点方向r(a中);
			}
			return 数学::C角度计算<float>::c弧度.f平均(m前方向, m后方向);
		} else {	//最后一个
			return m前方向;
		}
	}
private:
	float m前方向, m后方向;
};
}	//namespace 画子弹工具
//==============================================================================
// 顶点
//==============================================================================
struct C画子弹_顶点::S顶点 {
	t向量2 m坐标;
	t颜色 m颜色[2];
	t向量2 m纹理;
};
class C画子弹_顶点::C图形数据 : public I子弹图形数据 {
public:
	template<typename t>
	static t *f分配(std::unique_ptr<t[]> &a指针, size_t &a数量, size_t &a大小, size_t a) {
		a指针 = std::make_unique<t[]>(a);
		a数量 = a;
		a大小 = sizeof(t) * a;
		return a指针.get();
	}
	t顶点 *f分配顶点(size_t a顶点数量) {
		return f分配(m顶点, m顶点数量, m顶点大小, a顶点数量);
	}
	t索引 *f分配索引(size_t a索引数量) {
		return f分配(m索引, m索引数量, m索引大小, a索引数量);
	}
	tf顶点 F顶点() {
		return std::bind(&C画子弹_顶点::C图形数据::f分配顶点, this, std::placeholders::_1);
	}
	tf索引 F索引() {
		return std::bind(&C画子弹_顶点::C图形数据::f分配索引, this, std::placeholders::_1);
	}
	std::unique_ptr<t顶点[]> m顶点;
	std::unique_ptr<t索引[]> m索引;
	size_t m顶点数量, m索引数量;
	size_t m顶点大小, m索引大小;
	const C子弹 *m子弹;
};
//画子弹顶点赋值
class C画子弹_顶点::C顶点赋值 {
public:
	const C子弹 *m子弹;
	const S子弹属性 *m属性;
	S顶点 *m顶点;
	t颜色 m颜色[2];
	C顶点赋值(const C子弹 *a子弹) :
		m子弹(a子弹), m属性(a子弹->m子弹属性) {
	}
	void fs顶点(S顶点 *p顶点) {
		m顶点 = p顶点;
	}
	void fs颜色(const t颜色 &a颜色0, const t颜色 &a颜色1, float a出现, float a消失) {
		const float v颜色插值 = sqrt(a消失 * 2);
		const float v出现透明 = a出现;
		const float v消失透明 = 1 - sqrt(a消失);
		const float v总透明 = v出现透明 * v消失透明;
		m颜色[0] = a颜色0;
		m颜色[0].a *= v总透明;
		for (int i = 0; i != 3; ++i) {
			m颜色[1].m值[i] = 数学::f插值(a颜色1.m值[i], a颜色0.m值[i], v颜色插值);
		}
		m颜色[1].a = a颜色0.a * v总透明;
	}
	void fs颜色(const t颜色 *const *a颜色, float a出现, float a消失) {
		fs颜色(*a颜色[0], *a颜色[1], a出现, a消失);
	}
	void fs颜色(const t颜色 *a颜色, float a出现, float a消失) {
		fs颜色(a颜色[0], a颜色[1], a出现, a消失);
	}
	//给坐标赋值的第1步(必需)
	void f坐标1_位置(const t向量2 &a位置) {
		auto &v顶点 = m属性->m顶点.m指针[(int)m子弹->m动画帧];
		m顶点->m坐标.x = m子弹->m缩放.x * v顶点.fg坐标x(a位置.x);
		m顶点->m坐标.y = m子弹->m缩放.y * v顶点.fg坐标y(a位置.y);
	}
	//给坐标赋值的第2步(可选)
	void f坐标2_出现(float a出现) {
		m顶点->m坐标 *= sqrt(a出现);
	}
	//给坐标赋值的第3步(必需)
	void f坐标3_子弹() {
		m顶点->m坐标.fs旋转r(m子弹->m方向);
		m顶点->m坐标 += m子弹->m坐标;
	}
	void f坐标3_自定义(const t向量2 &a坐标, float a方向) {
		m顶点->m坐标.fs旋转r(a方向);
		m顶点->m坐标 += a坐标;
	}
	//纹理&颜色
	void f纹理(const t向量2 &a位置) {
		assert(a位置.x >= c左 && a位置.x <= c右);
		auto &v顶点 = m属性->m顶点.m指针[(int)m子弹->m动画帧];
		m顶点->m纹理.x = v顶点.fg纹理x(a位置.x);
		m顶点->m纹理.y = v顶点.fg纹理y(a位置.y);
	}
	void f颜色() {
		m顶点->m颜色[0] = m颜色[0];
		m顶点->m颜色[1] = m颜色[1];
	}
};
//画子弹
C画子弹_顶点::C画子弹_顶点(C图形引擎 &a引擎, 三维::C三维 &a三维) : m渲染控制(&a三维.fg渲染控制()), m缓存(a三维) {
	三维::S图形管线参数 v图形管线;
	三维::C顶点格式 v顶点格式;
	v顶点格式.f添加(三维::C顶点格式::e位置, 2);
	v顶点格式.f添加(三维::C顶点格式::e颜色, 4);
	v顶点格式.f添加(三维::C顶点格式::e颜色, 4);
	v顶点格式.f添加(三维::C顶点格式::e纹理, 2);
	v图形管线.fs输入布局(v顶点格式);
	auto &v着色器工厂 = a引擎.fg着色器工厂();
	着色器::tp着色器 vs, ps;
	v着色器工厂.f读取着色器(vs, C程序::f计算路径(L"~/shader/vs_tint0.cso").c_str());
	v着色器工厂.f读取着色器(ps, C程序::f计算路径(L"~/shader/ps_tint0.cso").c_str());
	v图形管线.fs顶点着色器(着色器::fc跨度(vs));
	v图形管线.fs像素着色器(着色器::fc跨度(ps));
	const auto &v渲染状态 = a三维.fg渲染状态();
	v图形管线.fs光栅化(v渲染状态.m光栅化.m显示隐藏面.Get());
	v图形管线.fs混合(v渲染状态.m混合.m开启透明.Get());
	v图形管线.fs深度模板(v渲染状态.m深度模板.m总是覆盖.Get());
	a三维.f创建图形管线(m图形管线, v图形管线);
	m缓存.m顶点缓冲.f初始化(sizeof(S顶点), c顶点缓存数量);
	m缓存.m索引缓冲.f初始化(sizeof(WORD), c索引缓存数量);
	m缓存.mf刷新回调 = [this]() {
		f自动准备();
		m渲染控制->fs纹理(0, m纹理.Get());
	};
	m采样器 = v渲染状态.m采样器.m图案;
	m常量缓冲 = a引擎.fg二维常量缓冲();
}
void C画子弹_顶点::f准备() {
	m纹理 = nullptr;
	m渲染控制->fs图形管线(*m图形管线);
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->fs采样器(0, m采样器.Get());
	m渲染控制->fs常量缓冲v(0, m常量缓冲.Get());
}
void C画子弹_顶点::f刷新() {
	m缓存.f刷新();
}
void C画子弹_顶点::f绘制点(const C子弹顶点::C点 &a顶点信息) {
	f生成点0(a顶点信息, F分配顶点(), F分配索引());
	f最后画子弹(a顶点信息.m子弹);
}
void C画子弹_顶点::f绘制直线(const C子弹顶点::C直线 &a顶点信息, const C子弹顶点::C直线::ta顶点 &a顶点数组) {
	f生成直线0(a顶点信息, a顶点数组, F分配顶点(), F分配索引());
	f最后画子弹(a顶点信息.m子弹);
}
void C画子弹_顶点::f绘制曲线(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a顶点数组) {
	f生成曲线0(a顶点信息, a顶点数组, F分配顶点(), F分配索引());
	f最后画子弹(a顶点信息.m子弹);
}
void C画子弹_顶点::f绘制连续点(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a顶点数组) {
	f生成连续点0(a顶点信息, a顶点数组, F分配顶点(), F分配索引());
	f最后画子弹(a顶点信息.m子弹);
}
void C画子弹_顶点::f绘制网格(const C子弹顶点::C网格 &a顶点信息, const C子弹顶点::C网格::ta顶点 &a顶点数组) {
	f生成网格0(a顶点信息, a顶点数组, F分配顶点(), F分配索引());
	f最后画子弹(a顶点信息.m子弹);
}
tp子弹图形数据 C画子弹_顶点::f生成点(const C子弹顶点::C点 &a顶点信息) {
	auto v数据 = std::make_shared<C图形数据>();
	f生成点0(a顶点信息, v数据->F顶点(), v数据->F索引());
	v数据->m子弹 = a顶点信息.m子弹;
	return v数据;
}
tp子弹图形数据 C画子弹_顶点::f生成直线(const C子弹顶点::C直线 &a顶点信息, const C子弹顶点::C直线::ta顶点 &a顶点数组) {
	auto v数据 = std::make_shared<C图形数据>();
	f生成直线0(a顶点信息, a顶点数组, v数据->F顶点(), v数据->F索引());
	v数据->m子弹 = a顶点信息.m子弹;
	return v数据;
}
tp子弹图形数据 C画子弹_顶点::f生成曲线(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a顶点数组) {
	auto v数据 = std::make_shared<C图形数据>();
	f生成曲线0(a顶点信息, a顶点数组, v数据->F顶点(), v数据->F索引());
	v数据->m子弹 = a顶点信息.m子弹;
	return v数据;
}
tp子弹图形数据 C画子弹_顶点::f生成连续点(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a顶点数组) {
	auto v数据 = std::make_shared<C图形数据>();
	f生成连续点0(a顶点信息, a顶点数组, v数据->F顶点(), v数据->F索引());
	v数据->m子弹 = a顶点信息.m子弹;
	return v数据;
}
tp子弹图形数据 C画子弹_顶点::f生成网格(const C子弹顶点::C网格 &a顶点信息, const C子弹顶点::C网格::ta顶点 &a顶点数组) {
	auto v数据 = std::make_shared<C图形数据>();
	f生成网格0(a顶点信息, a顶点数组, v数据->F顶点(), v数据->F索引());
	v数据->m子弹 = a顶点信息.m子弹;
	return v数据;
}
void C画子弹_顶点::f绘制图形数据(const tp子弹图形数据 &a数据) {
	const C图形数据 &v数据 = (C图形数据&)(*a数据);
	f画子弹(*v数据.m子弹, v数据.m顶点.get(), v数据.m顶点大小, v数据.m索引.get(), v数据.m索引大小);
}
void C画子弹_顶点::f最后画子弹(const C子弹 *a子弹) {
	f画子弹(*a子弹, m顶点空间.m指针, sizeof(S顶点) * m顶点空间.m需要数量, m索引空间.m指针, sizeof(WORD) * m索引空间.m需要数量);
}
void C画子弹_顶点::f画子弹(const C子弹 &a子弹, const void *a顶点指针, size_t a顶点大小, const void *a索引指针, size_t a索引大小) {
	三维::tp纹理 v目标纹理 = *a子弹.m子弹属性->m纹理;
	if (m纹理 != v目标纹理) {
		m缓存.f刷新();
		m纹理 = v目标纹理;
	}
	m缓存.f复制(a顶点指针, a顶点大小, a索引指针, a索引大小);
}
//索引
int C画子弹_顶点::f计算索引数量(int a宽, int a高) {
	return a宽 * a高 * 6;
}
void C画子弹_顶点::f自动索引_长条(int a长度, const tf索引 &af索引) {
	/*顶点顺序
	0	2	4	...
	1	3	5	...
	*/
	const int v索引数 = f计算索引数量(a长度);
	t索引 *v索引指针 = af索引(v索引数);
	const t索引 c基础索引[] = {
		0, 2, 1,
		2, 3, 1
	};
	for (int i = 0; i != a长度; ++i) {
		const int v索引序号 = i * 6;
		const int v顶点序号 = i * 2;
		for (int j = 0; j != 6; ++j) {
			v索引指针[v索引序号 + j] = v顶点序号 + c基础索引[j];
		}
	}
}
void C画子弹_顶点::f自动索引_网格(int a宽, int a高, const tf索引 &af索引) {
	/*顶点顺序
	0	1	2
	3	4	5
	6	7	8
	*/
	const int v索引数 = f计算索引数量(a宽, a高);
	t索引 *v索引指针 = af索引(v索引数);
	const int v单行顶点数 = a宽 + 1;
	const int v单行索引数 = a宽 * 6;
	for (int v行 = 0; v行 != a高; ++v行) {
		for (int v列 = 0; v列 != a宽; ++v列) {
			/*索引顺序
			0	1			3
			2			5	4
			*/
			const int v顶点基础序号 = v行 * v单行顶点数 + v列;
			const int v索引基础序号 = v行 * v单行索引数 + v列 * 6;
			v索引指针[v索引基础序号 + 0] = v顶点基础序号;
			v索引指针[v索引基础序号 + 1] = v顶点基础序号 + 1;
			v索引指针[v索引基础序号 + 2] = v顶点基础序号 + v单行顶点数;
			v索引指针[v索引基础序号 + 3] = v顶点基础序号 + 1;
			v索引指针[v索引基础序号 + 4] = v顶点基础序号 + v单行顶点数 + 1;
			v索引指针[v索引基础序号 + 5] = v顶点基础序号 + v单行顶点数;
		}
	}
}
//生成图形数据
void C画子弹_顶点::f生成点0(const C子弹顶点::C点 &a顶点信息, const tf顶点 &af顶点, const tf索引 &af索引) {
	const float v出现 = a顶点信息.m中心.m出现;
	const t颜色 *const v子弹颜色 = a顶点信息.m子弹->m颜色;
	C顶点赋值 v赋值{a顶点信息.m子弹};
	v赋值.fs颜色(v子弹颜色, v出现, a顶点信息.m中心.m消失);
	S顶点 *const v子弹顶点 = af顶点(4);
	auto f = [&](S顶点 &a修改顶点, const t向量2 &a位置) {
		v赋值.fs顶点(&a修改顶点);
		v赋值.f坐标1_位置(a位置);
		v赋值.f坐标2_出现(v出现);
		v赋值.f坐标3_子弹();
		v赋值.f纹理(a位置);
		v赋值.f颜色();
	};
	f(v子弹顶点[0], t向量2(c左, c上));
	f(v子弹顶点[1], t向量2(c左, c下));
	f(v子弹顶点[2], t向量2(c右, c上));
	f(v子弹顶点[3], t向量2(c右, c下));
	f自动索引_长条(1, af索引);
}
void C画子弹_顶点::f生成直线0(const C子弹顶点::C直线 &a顶点信息, const C子弹顶点::C直线::ta顶点 &a顶点数组, const tf顶点 &af顶点, const tf索引 &af索引) {
	const t向量2 &v中心坐标 = a顶点信息.m中心.m坐标;
	const float v出现 = a顶点信息.m中心.m出现;
	const int v数量 = a顶点信息.m数量;
	const bool vi位置 = a顶点信息.m标志[C子弹顶点::e位置];
	const C子弹 *const v子弹 = a顶点信息.m子弹;
	const float v子弹方向 = v子弹->m方向;
	const t颜色 *const v子弹颜色 = v子弹->m颜色;
	C顶点赋值 v赋值{v子弹};
	S顶点 *const v子弹顶点 = af顶点(v数量 * 2);
	auto f = [&](S顶点 &a修改顶点, const t向量2 &a位置) {
		v赋值.fs顶点(&a修改顶点);
		v赋值.f坐标1_位置(a位置);
		v赋值.f坐标2_出现(v出现);
		v赋值.f坐标3_自定义(v中心坐标, v子弹方向);
		v赋值.f纹理(a位置);
		v赋值.f颜色();
	};
	const 画子弹工具::F固定位置 f位置{v数量};
	for (unsigned int i = 0; i != v数量; ++i) {
		const C子弹顶点::C直线::t顶点 &v点 = a顶点数组[i];
		const float v位置x = (vi位置) ? v点.m位置 : f位置(i);
		v赋值.fs颜色(v子弹颜色, v出现, v点.m消失);
		f(v子弹顶点[i * 2], t向量2(v位置x, c上));
		f(v子弹顶点[i * 2 + 1], t向量2(v位置x, c下));
	}
	f自动索引_长条(v数量 - 1, af索引);
}
void C画子弹_顶点::f生成曲线0(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a顶点数组, const tf顶点 &af顶点, const tf索引 &af索引) {
	const float v中心出现 = a顶点信息.m中心.m出现;
	const bool vi出现 = a顶点信息.m标志[C子弹顶点::e出现];
	const bool vi颜色 = a顶点信息.m标志[C子弹顶点::e颜色];
	const int v数量 = a顶点信息.m数量;
	const t颜色 *const v子弹颜色 = a顶点信息.m子弹->m颜色;
	C顶点赋值 v赋值{a顶点信息.m子弹};
	const int v顶点数量 = v数量 * 2;
	S顶点 *v子弹顶点 = af顶点(v顶点数量);
	auto f节点 = [&](S顶点 &a修改顶点, const t向量2 &a坐标, float a位置x, float a位置y, float a方向) {
		v赋值.fs顶点(&a修改顶点);
		v赋值.f坐标1_位置({c中, a位置y});
		v赋值.f坐标2_出现(v中心出现);
		v赋值.f坐标3_自定义(a坐标, a方向);
		v赋值.f纹理({a位置x, a位置y});
		v赋值.f颜色();
	};
	const 画子弹工具::F固定位置 f位置{v数量};
	画子弹工具::F曲线方向 f方向{a顶点信息.m子弹->m方向};
	int i = 0;
	for (auto &v : 循环::C前后<const C子弹顶点::C曲线::ta顶点>{a顶点数组}) {
		const C子弹顶点::C曲线::t顶点 &v这点 = *v.m这;
		//颜色
		const float v出现 = vi出现 ? v这点.m出现 : v中心出现;
		if (vi颜色) {
			v赋值.fs颜色(v这点.m颜色, v出现, v这点.m消失);
		} else {
			v赋值.fs颜色(v子弹颜色, v出现, v这点.m消失);
		}
		//方向
		const float v方向 = f方向(v.m这->m坐标, v.m后->m坐标);
		//赋值
		const float v位置x = 1 - f位置(i++);
		f节点(v子弹顶点[0], v这点.m坐标, v位置x, c上, v方向);
		f节点(v子弹顶点[1], v这点.m坐标, v位置x, c下, v方向);
		v子弹顶点 += 2;
	}
	f自动索引_长条(v数量 - 1, af索引);
}
void C画子弹_顶点::f生成连续点0(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a顶点数组, const tf顶点 &af顶点, const tf索引 &af索引) {
	const float v中心出现 = a顶点信息.m中心.m出现;
	assert(v中心出现 >= 0);
	const bool vi位置 = a顶点信息.m标志[C子弹顶点::e位置];
	const bool vi出现 = a顶点信息.m标志[C子弹顶点::e出现];
	const bool vi颜色 = a顶点信息.m标志[C子弹顶点::e颜色];
	const bool vi环 = a顶点信息.m标志[C子弹顶点::e环];
	const int v数量 = a顶点信息.m数量;
	const int v补充数量 = vi环 ? 1 : 2;
	const t颜色 *const v子弹颜色 = a顶点信息.m子弹->m颜色;
	C顶点赋值 v赋值{a顶点信息.m子弹};
	const int v顶点数量 = (v数量 + v补充数量) * 2;
	S顶点 *v子弹顶点 = af顶点(v顶点数量);
	auto f头尾节点 = [&](S顶点 &a修改顶点, const t向量2 &a坐标, const t向量2 &a位置, float a方向) {
		v赋值.fs顶点(&a修改顶点);
		const t向量2 v位置 = t向量2{a位置.y, a位置.x};
		v赋值.f坐标1_位置(v位置);
		v赋值.f坐标2_出现(v中心出现);
		v赋值.f坐标3_自定义(a坐标, a方向);
		v赋值.f纹理(v位置);
		v赋值.f颜色();
	};
	auto f中间节点 = [&](S顶点 &a修改顶点, const t向量2 &a坐标, float a位置y, float a方向) {
		v赋值.fs顶点(&a修改顶点);
		const t向量2 v位置 = t向量2{a位置y, c中};
		v赋值.f坐标1_位置(v位置);
		v赋值.f坐标2_出现(v中心出现);
		v赋值.f坐标3_自定义(a坐标, a方向);
		v赋值.f纹理(v位置);
		v赋值.f颜色();
	};
	const unsigned int v末尾 = v数量 - 1;
	float v前方向 = 0, v后方向 = 0, v头方向 = 0;
	t颜色 v头颜色[2];
	for (int i = 0; i != v数量; ++i) {
		const C子弹顶点::C曲线::t顶点 &v这点 = a顶点数组[i];
		//颜色
		const float v出现 = vi出现 ? v这点.m出现 : v中心出现;
		const float v消失 = v这点.m消失;
		assert(v出现 >= 0);
		assert(v消失 >= 0);
		if (vi颜色) {
			v赋值.fs颜色(v这点.m颜色, v出现, v消失);
		} else {
			v赋值.fs颜色(v子弹颜色, v出现, v消失);
		}
		//区分头尾中间
		if (i == 0) {	//头
			v后方向 = v这点.m坐标.f到点方向r(a顶点数组[i + 1].m坐标);
			if (vi环) {	//是环,计算末尾节点到头部节点的方向
				const C子弹顶点::C曲线::t顶点 &v尾点 = a顶点数组[v末尾];
				v前方向 = v尾点.m坐标.f到点方向r(v这点.m坐标);
				const float v方向 = 数学::C角度计算<float>::c弧度.f平均(v前方向, v后方向) + 数学::c半π<float>;
				f中间节点(v子弹顶点[0], v这点.m坐标, c上, v方向);
				f中间节点(v子弹顶点[1], v这点.m坐标, c下, v方向);
				v子弹顶点 += 2;
				v头颜色[0] = v赋值.m颜色[0];
				v头颜色[1] = v赋值.m颜色[1];
				v头方向 = v方向;
			} else {	//不是环
				const float v方向 = v后方向 + 数学::c半π<float>;
				f头尾节点(v子弹顶点[0], v这点.m坐标, {c左, c上}, v方向);
				f头尾节点(v子弹顶点[1], v这点.m坐标, {c左, c上}, v方向);
				f中间节点(v子弹顶点[2], v这点.m坐标, c上, v方向);
				f中间节点(v子弹顶点[3], v这点.m坐标, c下, v方向);
				v子弹顶点 += 4;
			}
		} else if (i == v末尾) {	//尾
			if (vi环) {	//是环
				const C子弹顶点::C曲线::t顶点 &v头点 = a顶点数组[0];
				v后方向 = v这点.m坐标.f到点方向r(v头点.m坐标);
				const float v方向 = 数学::C角度计算<float>::c弧度.f平均(v前方向, v后方向) + 数学::c半π<float>;
				f中间节点(v子弹顶点[0], v这点.m坐标, c上, v方向);
				f中间节点(v子弹顶点[1], v这点.m坐标, c下, v方向);
				//头
				v赋值.m颜色[0] = v头颜色[0];
				v赋值.m颜色[1] = v头颜色[1];
				f中间节点(v子弹顶点[2], v头点.m坐标, c上, v头方向);
				f中间节点(v子弹顶点[3], v头点.m坐标, c下, v头方向);
				v子弹顶点 += 4;
			} else {	//不是环
				const float v方向 = v前方向 + 数学::c半π<float>;
				f中间节点(v子弹顶点[0], v这点.m坐标, c上, v方向);
				f中间节点(v子弹顶点[1], v这点.m坐标, c下, v方向);
				f头尾节点(v子弹顶点[2], v这点.m坐标, {c右, c上}, v方向);
				f头尾节点(v子弹顶点[3], v这点.m坐标, {c右, c下}, v方向);
				v子弹顶点 += 4;
			}
		} else {	//中间
			v后方向 = v这点.m坐标.f到点方向r(a顶点数组[i + 1].m坐标);
			const float v方向 = 数学::C角度计算<float>::c弧度.f平均(v前方向, v后方向) + 数学::c半π<float>;
			f中间节点(v子弹顶点[0], v这点.m坐标, c上, v方向);
			f中间节点(v子弹顶点[1], v这点.m坐标, c下, v方向);
			v子弹顶点 += 2;
		}
		//循环结束处理
		v前方向 = v后方向;
	}
	f自动索引_长条(v数量 + v补充数量 - 1, af索引);
}
void C画子弹_顶点::f生成网格0(const C子弹顶点::C网格 &a网格信息, const C子弹顶点::C网格::ta顶点 &a顶点数组, const tf顶点 &af顶点, const tf索引 &af索引) {
	const int v原始宽 = a网格信息.m宽;
	const int v原始高 = a网格信息.m高;
	assert(v原始宽 * v原始高 <= a顶点数组.size());
	const float v中心出现 = a网格信息.m中心.m出现;
	const int v宽 = v原始宽 + 1;
	const int v高 = v原始高 + 1;
	const bool vi坐标 = a网格信息.m标志[C子弹顶点::e坐标];
	const bool vi颜色 = a网格信息.m标志[C子弹顶点::e颜色];
	const t颜色 *const v子弹颜色 = a网格信息.m子弹->m颜色;
	const 画子弹工具::F固定位置 f位置x{v宽};
	const 画子弹工具::F固定位置 f位置y{v高};
	C顶点赋值 v赋值{a网格信息.m子弹};
	const int v顶点数量 = v宽 * v高;
	S顶点 *const v子弹顶点 = af顶点(v顶点数量);
	//赋值函数
	auto f遍历输入顶点周围的原始顶点 = [&](int i, int j, const std::function<void(int, int)> &pf) {
		static const std::pair<int, int> va位置[] = {
			{-1, -1},
		{-1, 0},
		{0, -1},
		{0, 0}
		};
		for (auto &v位置 : va位置) {
			const int x = v位置.first + i;
			if (x < 0) {
				continue;
			} else if (x >= v原始宽) {
				continue;
			}
			const int y = v位置.second + j;
			if (y < 0) {
				continue;
			} else if (y >= v原始高) {
				continue;
			}
			pf(x, y);
		}
	};
	std::function<void(int, int)> vf顶点赋值;
	if (vi坐标) {	//坐标,消失
		vf顶点赋值 = [&](int i, int j) {
			//计算平均值
			int v计数 = 0;
			t向量2 v总向量;
			float v总消失 = 0;
			f遍历输入顶点周围的原始顶点(i, j, [&](int i, int j) {
				const int v序号 = i + j * a网格信息.m宽;
				const C子弹顶点::C网格::t顶点 &v点 = a顶点数组[v序号];
				v总向量 += v点.m坐标;
				v总消失 += v点.m消失;
				++v计数;
			});
			//赋值
			const int v序号 = i + j * v宽;
			const t向量2 v位置{f位置x(i), f位置y(j)};
			v赋值.fs顶点(&v子弹顶点[v序号]);
			v赋值.fs颜色(v子弹颜色, v中心出现, v总消失 / v计数);
			v赋值.f坐标1_位置(v总向量 / (float)v计数);
			v赋值.f坐标2_出现(v中心出现);
			v赋值.f坐标3_子弹();
			v赋值.f纹理(v位置);
			v赋值.f颜色();
		};
	} else {	//消失
		vf顶点赋值 = [&](int i, int j) {
			//计算平均值
			int v计数 = 0;
			float v总消失 = 0;
			f遍历输入顶点周围的原始顶点(i, j, [&](int i, int j) {
				const int v序号 = i + j * a网格信息.m宽;
				const C子弹顶点::C网格::t顶点 &v点 = a顶点数组[v序号];
				v总消失 += v点.m消失;
				++v计数;
			});
			//赋值
			const int v序号 = i + j * v宽;
			const t向量2 v位置{f位置x(i), f位置y(j)};
			v赋值.fs顶点(&v子弹顶点[v序号]);
			v赋值.fs颜色(v子弹颜色, v中心出现, v总消失 / v计数);
			v赋值.f坐标1_位置(v位置);
			v赋值.f坐标2_出现(v中心出现);
			v赋值.f坐标3_子弹();
			v赋值.f纹理(v位置);
			v赋值.f颜色();
		};
	}
	//赋值循环
	for (int j = 0; j != v高; ++j) {
		for (int i = 0; i != v宽; ++i) {
			vf顶点赋值(i, j);
		}
	}
	f自动索引_网格(v原始宽, v原始高, af索引);
}
C画子弹_顶点::tf顶点 C画子弹_顶点::F分配顶点() {
	return [this](int a数量)->t顶点* {
		return m顶点空间.f分配(a数量);
	};
}
C画子弹_顶点::tf索引 C画子弹_顶点::F分配索引() {
	return [this](int a数量)->t索引* {
		return m索引空间.f分配(a数量);
	};
}
//==============================================================================
// 线条
//==============================================================================
C画子弹_线条::C画子弹_线条(二维::C二维 &a二维) : m画图(a二维.fc画图形()) {

}
void C画子弹_线条::f准备() {

}
void C画子弹_线条::f刷新() {

}
void C画子弹_线条::f绘制点(const C子弹顶点::C点 &a点) {
	const C子弹 *const v子弹 = a点.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	t颜色 v颜色 = v子弹->m颜色[0];
	v颜色.a = f计算透明度(a点.m中心.m出现, a点.m中心.m消失);
	m画图->fs颜色(v颜色);
	const t向量2 v判定 = v子弹属性->fg判定(v子弹->m缩放);
	const float &v子弹方向 = v子弹->m方向;
	const t向量2 &v子弹坐标 = v子弹->m坐标;
	if (v判定.x == v判定.y) {
		m画图->f绘制圆形(t圆形(v子弹坐标, v判定.x));
	} else {
		m画图->f绘制旋转矩形(t旋转矩形(v子弹坐标, v判定, v子弹方向));
	}
}
void C画子弹_线条::f绘制直线(const C子弹顶点::C直线 &a直线信息, const C子弹顶点::C直线::ta顶点 &a数组) {
	const C子弹 *const v子弹 = a直线信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const float vx = v子弹属性->fg显示x(v子弹->m缩放.x);
	const float vy = v子弹属性->fg显示y(v子弹->m缩放.y);
	auto f坐标 = [v子弹方向 = v子弹->m方向, v子弹坐标 = v子弹->m坐标](float px, float py)->t向量2 {
		return t向量2(px, py).f旋转r(v子弹方向) + v子弹坐标;
	};
	const float &v子弹方向 = v子弹->m方向;
	const t向量2 &v子弹坐标 = v子弹->m坐标;
	const t向量2 v左上 = t向量2(-vx, vy).f旋转r(v子弹方向) + v子弹坐标;
	const t向量2 v左下 = t向量2(-vx, -vy).f旋转r(v子弹方向) + v子弹坐标;
	const t向量2 v右上 = t向量2(vx, vy).f旋转r(v子弹方向) + v子弹坐标;
	const t向量2 v右下 = t向量2(vx, -vy).f旋转r(v子弹方向) + v子弹坐标;
	//画边
	t颜色 v颜色 = v子弹->m颜色[0];
	m画图->fs颜色(v颜色);
	m画图->f绘制线条(t线段(v左上, v左下));
	m画图->f绘制线条(t线段(v左上, v右上));
	m画图->f绘制线条(t线段(v右上, v右下));
	m画图->f绘制线条(t线段(v左下, v右下));
	//画节点
	const int v数量 = (int)a数组.size();
	数学::C范围变换计算<float> f范围变换{{0, (float)(v数量 - 1)}, {-vx, vx}};
	for (int i = 0; i != v数量; i++) {
		v颜色.a = f计算透明度(a直线信息.m中心.m出现, a数组[i].m消失);
		m画图->fs颜色(v颜色);
		m画图->f绘制圆形(t圆形(f坐标(f范围变换(i), 0), vy));
	}
}
void C画子弹_线条::f绘制曲线(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a数组) {
	const C子弹 *const v子弹 = a顶点信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const float vx = v子弹属性->fg显示x(v子弹->m缩放.x);
	const float v半径 = v子弹属性->fg显示y(v子弹->m缩放.y);
	画子弹工具::F曲线方向 f方向{v子弹->m方向};
	for (auto &v : 循环::C前后<const C子弹顶点::C曲线::ta顶点>{a数组}) {
		const float v方向 = f方向(v.m这->m坐标, v.m后->m坐标);
		const t向量2 v移动 = t向量2::fc方向r(v半径, v方向 + 数学::c半π<float>);
		m画图->f绘制线条(t线段(v.m这->m坐标 + v移动, v.m这->m坐标 - v移动));
		if (!v.fw前()) {
			m画图->f绘制线条(t线段(v.m前->m坐标 + v移动, v.m这->m坐标 + v移动));
			m画图->f绘制线条(t线段(v.m前->m坐标 - v移动, v.m这->m坐标 - v移动));
		}
	}
}
void C画子弹_线条::f绘制连续点(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a数组) {
	const C子弹 *const v子弹 = a顶点信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const float vx = v子弹属性->fg显示x(v子弹->m缩放.x);
	const float v半径 = v子弹属性->fg显示y(v子弹->m缩放.y);
	t颜色 v颜色 = a顶点信息.m子弹->m颜色[0];
	m画图->fs颜色(v颜色);
	auto f画两点之间的线 = [&](const t向量2 &p0, const t向量2 &p1) {
		const float v方向 = p0.f到点方向r(p1);
		const t向量2 v移动 = t向量2::fc方向r(v半径, v方向 + 数学::c半π<float>);
		m画图->f绘制线条(t线段(p0 + v移动, p1 + v移动));
		m画图->f绘制线条(t线段(p0 - v移动, p1 - v移动));
	};
	for (auto &v : 循环::C前后<const C子弹顶点::C曲线::ta顶点>{a数组}) {
		const t向量2 &v这坐标 = v.m这->m坐标;
		m画图->f绘制圆形(t圆形(v这坐标, v半径));
		if (!v.fw前()) {
			f画两点之间的线(v.m前->m坐标, v这坐标);
		}
	}
	if (a顶点信息.m标志[C子弹顶点::e环]) {
		f画两点之间的线(a数组.back().m坐标, a数组.front().m坐标);
	}
}
void C画子弹_线条::f绘制网格(const C子弹顶点::C网格 &p网络信息, const C子弹顶点::C网格::ta顶点 &a数组) {
	const C子弹 *const v子弹 = p网络信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const t向量2 v显示 = v子弹属性->fg显示(v子弹->m缩放);
	const float v宽数 = (float)p网络信息.m宽;
	const float v高数 = (float)p网络信息.m高;
	const float v半宽 = v显示.x / (float)p网络信息.m宽;
	const float v半高 = v显示.y / (float)p网络信息.m高;
	const float v半径 = (v半宽 + v半高) / 2;
	const float v全宽 = v半宽 * 2;
	const float v全高 = v半高 * 2;
	//画线
	const t向量2 &m坐标 = v子弹->m坐标;
	const float &v方向 = v子弹->m方向;
	t颜色 v颜色 = p网络信息.m子弹->m颜色[0];
	m画图->fs颜色(v颜色);
	m画图->f绘制旋转矩形(t旋转矩形(m坐标, v显示, v方向));
	//画圆
	数学::C二维序号计算<int> f序号{p网络信息.m宽};
	for (int y = 0; y != p网络信息.m高; ++y) {
		const float v位置y = t位置计算::f右到中(y, v高数 - 1) * v全高;
		for (int x = 0; x != p网络信息.m宽; ++x) {
			const float v位置x = t位置计算::f右到中(x, v宽数 - 1) * v全宽;
			v颜色.a = f计算透明度(p网络信息.m中心.m出现, a数组[f序号(y, x)].m消失);
			m画图->fs颜色(v颜色);
			m画图->f绘制圆形(t圆形(t向量2{v位置x, v位置y}.f旋转r(v方向) + m坐标, v半径));
		}
	}
}
tp子弹图形数据 C画子弹_线条::f生成点(const C子弹顶点::C点 &) {
	return nullptr;
}
tp子弹图形数据 C画子弹_线条::f生成直线(const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) {
	return nullptr;
}
tp子弹图形数据 C画子弹_线条::f生成曲线(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) {
	return nullptr;
}
tp子弹图形数据 C画子弹_线条::f生成连续点(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) {
	return nullptr;
}
tp子弹图形数据 C画子弹_线条::f生成网格(const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) {
	return nullptr;
}
void C画子弹_线条::f绘制图形数据(const tp子弹图形数据 &) {
}
float C画子弹_线条::f计算透明度(float a出现, float a消失) {
	return a出现 * (1 - a消失);
}
}	//namespace 东方山寨