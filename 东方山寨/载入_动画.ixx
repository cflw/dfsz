export module 东方山寨.载入.动画;
import 东方山寨.载入.内部;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import "程序.h";
import "游戏.h";
import "标识.h";
import "图形引擎.h";
import "图形资源工厂.h";
import "游戏_名称标识.h";
import "动画接口.h";
import "动画.h";
import "道具动画.h";
namespace 东方山寨::载入 {
void C内部载入::f动画() {
	struct S内置动画属性 {
		E动画 m动画标识;
		I工厂<I动画> *m动画对象;
	};
	const S内置动画属性 v内置动画表[] = {
		{E动画::e静态, new C简单工厂<I动画>},
		{E动画::e道具, new C简单工厂<I动画, C道具动画>},
	};
	auto &va动画扩展 = C游戏::g资源.fg动画();
	for (auto &v : v内置动画表) {
		va动画扩展.f添加((int)v.m动画标识, v.m动画对象);
	}
}
}	//namespace 东方山寨::载入
namespace 东方山寨::xml {
void C载入::f动画(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	auto &va动画 = C游戏::g资源.fg动画();
	int v主标识 = -1;
	for (const t节点 &v动画节点 : a参数.m根.child(L"数据").children(L"动画")) {
		v主标识 = v动画节点.attribute(L"标识").as_int(v主标识 + 1);
		const std::wstring v动画名称 = v动画节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v动画名称, v主标识, true);
		C角色动画::S属性 v属性;
		const float v变化速度 = v动画节点.child(L"变化速度").text().as_float(8);
		const float v循环速度 = v动画节点.child(L"循环速度").text().as_float(8);
		auto f解析动作 = [&](C角色动画::S属性::S动画方向 &a结构, const t节点 &a动作节点) {
			a结构.m顶点偏移 = a动作节点.child(L"顶点偏移").text().as_int();
			const int v循环帧数 = a动作节点.child(L"循环帧数").text().as_int();
			assert(v循环帧数);	//必需指定循环帧数
			const int v开始帧数 = a动作节点.child(L"开始帧数").text().as_int();
			a结构.m循环位置 = v开始帧数;
			a结构.m帧数 = v开始帧数 + v循环帧数;
			a结构.m变化速度 = a动作节点.child(L"变化速度").text().as_float(v变化速度) / c计算频率<float>;
			a结构.m循环速度 = a动作节点.child(L"循环速度").text().as_float(v循环速度) / c计算频率<float>;
			a结构.m镜像 = a动作节点.child(L"镜像").text().as_bool(false);
		};
		for (const t节点 &v动作节点 : v动画节点.children(L"动作")) {
			const std::wstring_view v方向 = v动作节点.attribute(L"方向").as_string();
			if (v方向 == L"正常") {
				f解析动作(v属性.m正常, v动作节点);
			} else if (v方向 == L"左移") {
				f解析动作(v属性.m左移, v动作节点);
			} else if (v方向 == L"右移") {
				f解析动作(v属性.m右移, v动作节点);
			}
		}
		va动画.f添加(v名称标识1, new C角色动画::C工厂(std::make_shared<C角色动画::S属性>(v属性)));
	}
}
}	//namespace 东方山寨::xml