#pragma once
#include <boost/rational.hpp>
namespace 东方山寨 {
class C分数值 {
public:
	void f计算();
	void f加分(long long);
public:
	long long m实际值 = 0;
	long long m显示值 = 0;
};
class C吸收值 {
public:
	static const float c减少速度;
	static const float c上限;
	operator int() const;
	void f计算();
	void f加();
	void f满();
public:
	float m值 = 0;
};
struct S玩家成绩 {
	long long m得分;
	boost::rational<int> m残机;
	boost::rational<int> m炸弹;
	boost::rational<int> m火力;
	int m最大点;
	int m擦弹;
	C吸收值 m吸收;
};
}	//namespace 东方山寨