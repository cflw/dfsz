#pragma once
#include <functional>
#include <boost/rational.hpp>
namespace 东方山寨 {
using tf难度 = std::function<float(float)>;
//e=简单 h=困难 t=折磨 t6=折磨6
namespace 难度 {
constexpr float c简单 = 1;
constexpr float c普通 = 2;
constexpr float c困难 = 3;
constexpr float c疯狂 = 4;
constexpr float c折磨 = 5;
constexpr float c折磨2 = 6;
constexpr float c折磨3 = 7;
constexpr float c折磨4 = 8;
constexpr float c折磨5 = 9;
constexpr float c折磨6 = 10;
//计算
bool f单调(float e, float h, float t, float t6);	//难度函数在x∈[1,+∞)必需单调递增或单调递减
tf难度 F一次(float e, float t6);
tf难度 F二次(float e, float t, float t6);
//tf难度 F四次(float e, float h, float t, float t6);
//tf难度 F指数(float e, float t, float t6);
//tf难度 F反(float e, float t, float t6);
tf难度 F线性插值(float e, float h, float t, float t6);	//插值
}	//namespace 难度
//控制
class C难度 {
public:
	void f增加难度(const boost::rational<int> &);
	void f增加难度_最大点(int 最大点);
	void f减少难度();	//自机挂掉时调用
	float fg基础难度() const;	//只返回整数
	float fg动态难度() const;
	int m基础难度 = 1;
	int m增加难度 = 0;	//单位1/100 0000
};
}	//namespace 东方山寨