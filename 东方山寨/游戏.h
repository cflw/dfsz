#pragma once
#include <random>
#include <wrl.h>
#include <cflw数学_随机.h>
#include "数学包含.h"
#include "基础.h"
#include "基础_对象工厂.h"
#include "基础_对象数组.h"
#include "基础_属性数组.h"
#include "基础_扩展数组.h"
namespace 东方山寨 {
using Microsoft::WRL::ComPtr;
typedef std::mt19937 t随机数引擎;
//==============================================================================
// 类
//==============================================================================
class C游戏;
struct S游戏设置;
class C图形引擎;
class I游戏输入;
class C音频引擎;
class C随机数工厂;
//关卡
class C关卡脚本;
class C关卡控制;
class C王战控制;
class I关卡;
class C抬显控制;
//子弹
class C子弹;
class C子弹制造机;
//敌机
class C敌机制造机;
class C敌机;
struct S敌机属性;
//玩家子弹
class C玩家子弹;
class C玩家子弹制造机;
class C玩家子弹发射器;
class C玩家炸弹发射管理;
//玩家
class C玩家;
class C自机;
class I子机移动;
class C难度;
//道具
class C道具;
class C道具制造机;
//遮罩
class I遮罩;
class C遮罩工厂;
class I边框;
//属性
struct S子弹属性;
struct S自机属性;
struct S子机属性;
struct S道具属性;
struct S玩家子弹属性;
//扩展
class C玩家炸弹;
//图形
class I图形;
class C图形工厂;
class I图形管线;
class I动画;
class C纹理工厂;	//包含头文件"图形_资源工厂.h"
class C顶点矩形工厂;
class C模型工厂;
class C静态立绘管理;
//其它资源
class C取文本;
//==============================================================================
// 游戏
//==============================================================================
class C游戏 {
private:
	class C实现;
	class C资源;
public:
	C游戏();
	~C游戏();
	//
	void f初始化_图形接口(C图形引擎 &);
	void f初始化_音频接口(C音频引擎 &);
	void f初始化_在载入结束();
	void f销毁();	//程序结束时清理
	void f开始();	//总的开始,进入游戏前调用
	void f结束();	//总的结束,回到主菜单前调用
	void f计算();
	void f更新();
	void f显示() const;
	void f推进随机数();
public:	//公开控制
	class C内容 {	//全局控制游戏的类
		friend C游戏;
	public:
		//变量
		C游戏速度 &fg游戏速度() const;
		C对象数组<C子弹> &fg子弹数组() const;
		C对象数组<C敌机> &fg敌机数组() const;
		t随机数引擎 &fg随机数引擎() const;
		C自机 &fg自机() const;
		C关卡控制 &fg关卡控制() const;
		C王战控制 &fg王战控制() const;
		C抬显控制 &fg抬显控制() const;
		C难度 &fg难度() const;
		C玩家 &fg玩家() const;
		const I边框 &fg边框() const;
		const C玩家炸弹发射管理 &fg炸弹发射管理() const;
		//工厂
		const C子弹制造机 &f工厂_子弹() const;
		const C敌机制造机 &f工厂_敌机() const;
		const C玩家子弹制造机 &f工厂_玩家子弹() const;
		const C道具制造机 &f工厂_道具() const;
		const C遮罩工厂 &f工厂_遮罩() const;
		template<typename t> auto f工厂_随机数f(t &&, unsigned long long 推进 = 0) const;
		t随机数引擎 f工厂_随机数引擎(unsigned long long 推进  = 0) const;	//为了保证回放正确,推进值必须是编程阶段就确定的常量
		//游戏中
		void f游戏_切换边框(const I边框 &);
		void f游戏_结束游戏();	//结束关卡回到标题画面
		void f游戏_通关菜单();	//结束关卡弹出菜单
	private:
		C实现 *m实现 = nullptr;
	};
	class C取资源 {	//专门取资源的类
		friend C游戏;
	public:
		C游戏速度 &fg游戏速度() const;
		C属性数组<S子弹属性> &fg子弹属性() const;
		C属性数组<S自机属性> &fg自机属性() const;
		C属性数组<S子机属性> &fg子机属性() const;
		C属性数组<S道具属性> &fg道具属性() const;
		C属性数组<S玩家子弹属性> &fg玩家子弹属性() const;
		C属性数组<S敌机属性> &fg敌机属性() const;
		C扩展数组<I工厂<C玩家子弹发射器>> &fg玩家发射() const;
		C扩展数组<I工厂<I子机移动>> &fg子机移动() const;
		C扩展数组<I工厂<I动画>> &fg动画() const;
		C静态立绘管理 &fg静态立绘() const;
		std::map<std::wstring, int> &fg名称标识() const;
		int fc随机标识() const;
		int fg标识(const std::wstring &) const;
		C对象数组<I图形> &fg图形数组() const;
		C图形工厂 &f工厂_图形();
		template<typename t> auto f工厂_随机数f(t &&, unsigned long long 推进  = 0) const;
		t随机数引擎 f工厂_随机数引擎(unsigned long long 推进  = 0) const;	//用于图形,所以推进值可以随便取值
	private:
		C资源 *m资源 = nullptr;
	};
	static void fs游戏输入(I游戏输入 &);	//开始游戏前设置
	static void fs游戏设置(const S游戏设置 &);	//开始游戏前设置
	static C内容 &fg内容();
	static C取资源 &fg资源();
	static C图形引擎 &fg图形();
	static C音频引擎 &fg音频();
	static I游戏输入 &fg游戏输入();
	static C内容 g内容;
	static C取资源 g资源;
private:	//内部控制
	static C资源 &fg内部资源();
	static std::unique_ptr<C实现> mp实现;
	static std::unique_ptr<C资源> mp资源;
};
//==============================================================================
// 模板实现
//==============================================================================
template<typename t> auto C游戏::C内容::f工厂_随机数f(t &&a分布, unsigned long long a推进) const {
	return std::bind(a分布, f工厂_随机数引擎(a推进));
}
template<typename t> auto C游戏::C取资源::f工厂_随机数f(t &&a分布, unsigned long long a推进) const {
	return std::bind(a分布, f工厂_随机数引擎(a推进));
}
}	//namespace 东方山寨