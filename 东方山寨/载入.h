#pragma once
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <filesystem>
#include <memory>
namespace 东方山寨 {
struct S载入参数 {
	const boost::property_tree::wptree &m树;
	const std::filesystem::path &m路径;
};
class C载入 {
public:
	typedef std::unique_ptr<boost::property_tree::wptree> tp树;
	typedef boost::property_tree::wptree t树;
	typedef void(*tf载入数据)(const S载入参数 &);
	static std::map<int, tf载入数据> g载入函数;
	static void f汇总(const S载入参数 &);
	static void f子弹(const S载入参数 &);
	static void f图形(const S载入参数 &);
	static void f动画(const S载入参数 &);
	static void f自机(const S载入参数 &);
	static void f敌机(const S载入参数 &);
	static void f子机(const S载入参数 &);
	static void f子机位置(const S载入参数 &);
	static void f玩家子弹(const S载入参数 &);
	static void f玩家发射(const S载入参数 &);
	static void f纹理列表0(const S载入参数 &);
	static void f模型列表0(const S载入参数 &);
	static void f声音列表0(const S载入参数 &);
	static void f声音列表1(const S载入参数 &);
	static void f文本(const S载入参数 &);
};
class C内部载入 {
public:
	static void f道具();
	static void f画子弹();
	static void f子机();
	static void f玩家子弹();
	static void f玩家子弹发射();
	static void f动画();
	static void f模型();
};
}