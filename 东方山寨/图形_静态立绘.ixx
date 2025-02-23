export module 东方山寨.图形.静态立绘;
export import "基础_数组指针.h";
export import "图形包含.h";
export import "图形基础.h";
export import "图形缓冲.h";
export import "图形管线接口.h";
export import "图形引擎.h";
export import 东方山寨.对话基础;
export import 东方山寨.图形.对话立绘;
export import "图形_画图片.h";
import <ranges>;
import "程序.h";
import "游戏.h";
import "图形工厂.h";
export namespace 东方山寨 {
constexpr size_t c最大立绘图层数 = 2;
class C静态立绘管线;
struct S静态立绘属性;
using tp静态立绘 = const S静态立绘属性 *;
//==============================================================================
// 静态立绘类
//==============================================================================
//结构
struct S静态立绘组件 {
	t属性指针<S纹理> m纹理;
	t属性指针<S顶点矩形> m矩形;	//载入时计算，表示组件的位置
	t向量2 m偏移;	//载入时保存,表示组件偏移位置
};
struct S静态立绘属性 {
	struct S表情映射 {
		t属性指针<S静态立绘组件> ma组件[c最大立绘图层数];	//设置成某个表情时, 每一个图层对应的纹理
	};
	using ta表情映射 = std::map<E立绘表情, S表情映射>;
	ta表情映射 ma表情映射;
	float m缩放 = 1;	//载入时保存,表示组件缩放
	E对话方向 m方向 = E对话方向::e从左向右;
};
//立绘
class C静态对话立绘 : public I对话立绘 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:	//部分代码可以和 C画图片 复用,以后重构
		void f显示() const override;
		void f画组件(const S静态立绘组件 &) const;
		C静态立绘管线 *m图形管线 = nullptr;
		const S静态立绘组件 *ma组件[c最大立绘图层数];
		t向量2 m坐标;
		float m缩放x = 1;	//用来翻转
		float m透明度 = 0;
	};
	using t图形缓冲 = C图形缓冲;
	C静态对话立绘(const S静态立绘属性 &);
	void f接口_初始化(const S图形参数 &);
	void f接口_更新() override;
	void f接口_改变表情(E立绘表情) override;
	float fg显示方向() const;
public:
	const S静态立绘属性 *m属性 = nullptr;
	const S静态立绘属性::S表情映射 *m表情映射 = nullptr;
};
//建造机
class C静态立绘建造机 : public C图形建造机<C静态对话立绘, C静态对话立绘::C图形缓冲> {
public:
	C静态立绘建造机() = default;
	C静态立绘建造机(const S静态立绘属性 &);
	void f接口_建造图形(t过程 &) const override;
	const S静态立绘属性 *m属性 = nullptr;
};
//管理资源
class C静态立绘管理 {
public:
	C静态立绘管理();
	~C静态立绘管理();
	void f编译(const C属性数组<S纹理> &, const C属性数组<S顶点矩形> &);
	C属性数组<S静态立绘组件> ma组件;
	C属性数组<S静态立绘属性> ma属性;
};
//==============================================================================
// 静态立绘管线
//==============================================================================
//支持星莲船之后的正作的立绘
struct VS_CHARACTER1 {
	t向量2 m位置;
	t向量2 m纹理[c最大立绘图层数];
	float m透明度 = 0;
	//float x0;	//不使用
};
//在构造函数中初始化使得派生类难以重写整个初始化过程。以后改掉。
class C静态立绘管线 : public C画图片管线 {
public:
	C静态立绘管线(C图形引擎 &, 三维::C三维 &);
	~C静态立绘管线();
	void f准备() override;
	void f刷新() override;
private:
	三维::tp深度模板 m深度模板;
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
//==============================================================================
// 静态立绘图形管线
//==============================================================================
C静态立绘管线::C静态立绘管线(C图形引擎 &a引擎, 三维::C三维 &a三维):
	C画图片管线(a引擎, a三维) {
	三维::S深度模板参数 v深度模板参数 = m渲染状态->m深度模板参数.m模板比较;
	v深度模板参数.fs深度部分(m渲染状态->m深度模板参数.m总是覆盖);
	v深度模板参数.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	v深度模板参数.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	v深度模板参数.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	v深度模板参数.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER;
	v深度模板参数.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	v深度模板参数.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	v深度模板参数.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	v深度模板参数.BackFace.StencilFunc = D3D11_COMPARISON_GREATER;
	a三维.fg设备()->CreateDepthStencilState(&v深度模板参数, &m深度模板);
}
C静态立绘管线::~C静态立绘管线() {
}
void C静态立绘管线::f准备() {
	m渲染控制->fs顶点着色器(m顶点着色器.Get());
	m渲染控制->fs像素着色器(m像素着色器.Get());
	m渲染控制->fs输入布局(m输入布局.Get());
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->fs采样器(0, m渲染状态->m采样器.m纹理.Get());
	m渲染控制->fs光栅化(m渲染状态->m光栅化.m显示隐藏面.Get());
	m渲染控制->fs混合(m渲染状态->m混合.m开启透明.Get());
	//m渲染控制->fs深度模板(m渲染状态->m深度模板.m总是覆盖.Get());
	m渲染控制->fs深度模板(m深度模板.Get());
	m渲染控制->fs模板参考值(0x01);
	m渲染控制->fs常量缓冲(0, m常量缓冲.Get());
}
void C静态立绘管线::f刷新() {
	m缓冲.f刷新();
}
//==============================================================================
// 静态立绘图形缓冲
//==============================================================================
void C静态对话立绘::C图形缓冲::f显示() const {
	for (const S静态立绘组件 *v组件 : ma组件 | std::views::reverse) {
		if (v组件) {
			f画组件(*v组件);
		}
	}
}
void C静态对话立绘::C图形缓冲::f画组件(const S静态立绘组件 &a组件) const {
	//复制自 C画图片::f画图片,以后重构
	//顶点
	VS_IMAGE v顶点[4];
	const S顶点矩形 &v矩形 = *a组件.m矩形;
	auto f赋顶点 = [&](VS_IMAGE &a顶点, int x, int y) {
		//坐标
		const float v坐标x = v矩形.m坐标[x] * m缩放x;
		const float v坐标y = v矩形.m坐标[y];
		a顶点.m坐标.x = v坐标x + m坐标.x;
		a顶点.m坐标.y = v坐标y + m坐标.y;
		//纹理
		a顶点.m纹理.x = v矩形.m纹理[x];
		a顶点.m纹理.y = v矩形.m纹理[y];
		//透明度
		a顶点.m透明度 = m透明度;
		};
	f赋顶点(v顶点[0], 0, 1);	//左上
	f赋顶点(v顶点[1], 2, 1);	//右上
	f赋顶点(v顶点[2], 0, 3);	//左下
	f赋顶点(v顶点[3], 2, 3);	//右下
	//索引
	static const WORD v索引[] = {
		0, 1, 2,
		1, 3, 2
	};
	//复制
	const S纹理 &v纹理 = *a组件.m纹理;
	m图形管线->f自动准备();
	m图形管线->fs纹理(v纹理.m纹理);
	m图形管线->f绘制(v顶点, v索引);
}
//==============================================================================
// 静态立绘图形对象
//==============================================================================
C静态对话立绘::C静态对话立绘(const S静态立绘属性 &a属性):
	m属性(&a属性) {
}
void C静态对话立绘::f接口_初始化(const S图形参数 &a参数) {
	I对话立绘::f接口_初始化(a参数);
	C图形缓冲 *const v缓冲 = (C图形缓冲 *)m图形缓冲;
	v缓冲->m图形管线 = C游戏::fg图形().fg图形管线<C静态立绘管线>(E图形管线::e静态立绘);
	f接口_改变表情(E立绘表情::e无);
}
void C静态对话立绘::f接口_更新() {
	const float v渲染秒 = C游戏::fg图形().fg渲染秒();
	const float v速度 = v渲染秒 * c动画速度;
	C图形缓冲 *const v缓冲 = (C图形缓冲 *)m图形缓冲;
	const size_t v数量 = std::size(m表情映射->ma组件);
	for (size_t i = 0; i != v数量; ++i) {
		v缓冲->ma组件[i] = m表情映射->ma组件[i].m指针;
	}
	v缓冲->m坐标 = fg显示坐标();
	v缓冲->m缩放x = fg显示方向();
	v缓冲->m透明度 = 数学::f线性渐变<float>(v缓冲->m透明度, fg显示透明度(), v速度);
}
void C静态对话立绘::f接口_改变表情(E立绘表情 a表情) {
	if (auto vp表情 = m属性->ma表情映射.find(a表情); vp表情 != m属性->ma表情映射.end()) {
		m表情映射 = &vp表情->second;
	}
	//表情不存在则写告警日志,以后写
}
float C静态对话立绘::fg显示方向() const {
	return m方向 == m属性->m方向 ? 1 : -1;
}
//==============================================================================
// 静态立绘图形建造机
//==============================================================================
C静态立绘建造机::C静态立绘建造机(const S静态立绘属性 &a属性):
	m属性(&a属性) {
}
void C静态立绘建造机::f接口_建造图形(t过程 &a过程) const {
	a过程.f建造图形<C静态对话立绘>(*m属性);
}
//==============================================================================
// 静态立绘资源管理
//==============================================================================
C静态立绘管理::C静态立绘管理() {
}
C静态立绘管理::~C静态立绘管理() {
}
void C静态立绘管理::f编译(const C属性数组<S纹理> &aa纹理, const C属性数组<S顶点矩形> &aa矩形) {
	for (auto &v组件 : ma组件.ma数据) {
		aa纹理.f编译(v组件.m纹理);
		aa矩形.f编译(v组件.m矩形);
	}
	for (auto &v属性 : ma属性.ma数据) {
		for (auto &[_, v表情] : v属性.ma表情映射) {
			for (auto &v组件 : v表情.ma组件) {
				ma组件.f编译(v组件);
			}
		}
	}
}
}	//namespace 东方山寨