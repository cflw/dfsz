export module 东方山寨.脚本;
//标准库
//export import std;
//基础
export import "游戏.h";
export import "基础.h";
//子弹
export import "标识.h";
export import "子弹基础.h";
export import "子弹制造机.h";

export import "子弹_普通子弹.h";
export import "子弹_直线激光.h";
export import "子弹_曲线激光.h";
export import "子弹_大子弹.h";
export import "子弹_连续子弹.h";
export import "子弹_射线激光.h";
//敌机
export import "敌机基础.h";
export import "敌机制造机.h";
export import "敌机扩展.h";
export import "敌机模板.h";
export import 东方山寨.敌机图形模板;
//道具
export import "道具.h";
export import "道具制造机.h";
//遮罩
export import "遮罩基础.h";
export import "遮罩形状.h";
export import "遮罩工厂.h";
export import "边框形状.h";
//图形
import "图形引擎.h";
export import "图形工厂.h";
export import 东方山寨.图形.抬显;
export import 东方山寨.图形.抬显模板;
export import "图形_三维.h";
export import 东方山寨.图形.对话框;
export import 东方山寨.图形.对话立绘;
export import 东方山寨.图形.静态立绘;
export import "图形_背景.h";
//关卡
export import 东方山寨.关卡;
export import "场景.h";
export import 东方山寨.对话控制;
export import 东方山寨.对话脚本;
export import 东方山寨.王战;
export import 东方山寨.关卡标识;
export import 东方山寨.关卡工厂;
export import 东方山寨.关卡练习;
export import 东方山寨.关卡效果;
//玩家
export import "玩家.h";
export import "轨迹.h";
import 东方山寨.玩家炸弹发射;
//其它
export import 东方山寨.计算;
export import "取文本.h";
export import 东方山寨.难度;
export import 东方山寨.基础_计时器;
export import 东方山寨.图形_符卡立绘函数;
export import 东方山寨.图形_符卡立绘模板;
export import 东方山寨.文本管理;
export namespace 东方山寨 {
using t子弹工厂 = C子弹制造机;
using t敌机工厂 = C敌机制造机;
using t图形工厂 = C图形工厂;
using tp子弹工厂 = std::shared_ptr<C子弹制造机>;
using tp敌机工厂 = std::shared_ptr<C敌机制造机>;
using tp图形工厂 = std::shared_ptr<C图形工厂>;
using 工具::C计次器;
//实用函数
namespace 脚本 {
//游戏资源
tp敌机属性 fg敌机样式(const std::wstring &);
//图形资源
tp模型 fg模型(const std::wstring &);
tp纹理 fg纹理(const std::wstring &);
tp静态立绘 fg静态立绘(const std::wstring &);
//随机
std::function<float()> F随机数(unsigned long long 推进 = 0);
std::function<float()> F边框随机x(unsigned long long 推进 = 0);
std::function<float()> F边框随机y(unsigned long long 推进 = 0);
std::function<float()> F圆周随机(unsigned long long 推进 = 0);
//内容
void f全屏清弹(const t向量2 &坐标 = t向量2::c零, float 最大半径 = 600, bool 产生道具 = false);
float fg动态难度();
t向量2 fg自机坐标();
t向量2 fg自机速度(float 秒 = 1);	//平均速度
std::shared_ptr<C敌机> f王入场(E敌机, const t向量2 &开始, const t向量2 &结束);
std::shared_ptr<C敌机> f王入场(const std::wstring &, const t向量2 &开始, const t向量2 &结束);
void f掉落道具(const t道具组 &, const t向量2 &坐标, const t向量2 &速度 = t向量2::c零);
//模板
template<typename t> auto F均匀随机(t a, t b, unsigned long long a推进 = 0) {
	if constexpr (std::is_integral_v<t>) {
		return C游戏::fg内容().f工厂_随机数f(std::uniform_int_distribution<t>(a, b), a推进);
	} else if constexpr (std::is_floating_point_v<t>) {
		return C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<t>(a, b), a推进);
	} else {
		return C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<t>(a, b), a推进);
	}
}
}	//namespace 脚本
}	//namespace 东方山寨
module: private;
namespace 东方山寨::脚本 {
//==============================================================================
// 资源
//==============================================================================
tp敌机属性 fg敌机样式(const std::wstring &a名称) {
	const auto &va敌机属性 = C游戏::fg资源().fg敌机属性();
	return va敌机属性[a名称];
}
tp模型 fg模型(const std::wstring &a名称) {
	static auto &va模型 = C游戏::fg图形().fg模型();
	return va模型[a名称];
}
tp纹理 fg纹理(const std::wstring &a名称) {
	static auto &va纹理 = C游戏::fg图形().fg纹理();
	return va纹理[a名称];
}
tp静态立绘 fg静态立绘(const std::wstring &a名称) {
	static auto &va静态立绘 = C游戏::fg资源().fg静态立绘();
	return va静态立绘.ma属性[a名称];
}
//==============================================================================
// 内容
//==============================================================================
std::function<float()> F随机数(unsigned long long a推进) {
	return F均匀随机<float>(0, 1, a推进);
}
std::function<float()> F边框随机x(unsigned long long a推进) {
	return F均匀随机<float>(-c边框范围x, c边框范围x, a推进);
}
std::function<float()> F边框随机y(unsigned long long a推进) {
	return F均匀随机<float>(-c边框范围y, c边框范围y, a推进);
}
std::function<float()> F圆周随机(unsigned long long a推进) {
	return F均匀随机<float>(0, 数学::c二π<float>, a推进);
}
void f全屏清弹(const t向量2 &a坐标, float a半径, bool a道具) {
	return C游戏::fg内容().fg炸弹发射管理().f全屏清弹(a坐标, a半径, a道具);
}
float fg动态难度() {
	const auto &v难度 = C游戏::fg内容().fg难度();
	return v难度.fg动态难度();
}
t向量2 fg自机坐标() {
	return C游戏::g内容.fg自机().m坐标;
}
t向量2 fg自机速度(float a秒) {
	return C游戏::g内容.fg玩家().m轨迹.fg平均速度(a秒);
}
std::shared_ptr<C敌机> f王入场(E敌机 a敌机, const t向量2 &a开始, const t向量2 &a结束) {
	const auto &v敌机工厂 = C游戏::fg内容().f工厂_敌机();
	t敌机参数 v敌机参数;
	v敌机参数.fs坐标(a开始);
	v敌机参数.fs移动到_时间(a结束, 1);
	v敌机参数.m样式 = (int)a敌机;
	auto v敌机 = v敌机工厂.f产生王(v敌机参数);
	图形模板::f分血条(*v敌机);
	auto &v王战 = C游戏::fg内容().fg王战控制();
	v王战.fs王(v敌机);
	return v敌机;
}
std::shared_ptr<C敌机> f王入场(const std::wstring &a名称, const t向量2 &a开始, const t向量2 &a结束) {
	const auto &v敌机属性 = C游戏::fg资源().fg敌机属性();
	const auto &v敌机工厂 = C游戏::fg内容().f工厂_敌机();
	t敌机参数 v敌机参数;
	v敌机参数.fs坐标(a开始);
	v敌机参数.fs移动到_时间(a结束, 1);
	v敌机参数.m样式 = v敌机属性[a名称];
	auto v敌机 = v敌机工厂.f产生王(v敌机参数);
	图形模板::f分血条(*v敌机);
	auto &v王战 = C游戏::fg内容().fg王战控制();
	v王战.fs王(v敌机);
	return v敌机;
}
void f掉落道具(const t道具组 &a道具组, const t向量2 &a坐标, const t向量2 &a速度) {
	const auto &v工厂 = C游戏::fg内容().f工厂_道具();
	t道具参数 v参数;
	v参数.m坐标 = a坐标;
	v参数.m速度 = a速度;
	v工厂.f产生道具(v参数, a道具组);
}
}	//namespace 东方山寨::脚本