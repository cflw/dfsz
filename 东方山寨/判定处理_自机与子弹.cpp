#include "判定处理_自机与子弹.h"
#include "自机.h"
namespace 东方山寨 {
//--------------------------------------------------------------------------------
// 自机与子弹判定
//--------------------------------------------------------------------------------
void C自机与子弹判定::f绑定自机(C自机 *a自机) {
	m自机 = a自机;
	m擦弹数 = 0;
	m碰撞点 = m自机->fg判定点();
	m擦弹点 = m自机->fg擦弹点();
}
int C自机与子弹判定::f子弹_提交判定(const t圆形 &a圆形) {
	m判定结果 = 0;
	if (数学::f圆形相交判定(m擦弹点, a圆形)) {
		m判定结果 |= e擦弹;
		if (数学::f圆形相交判定(m碰撞点, a圆形)) {
			m判定结果 |= e碰撞;
		}
	}
	return m判定结果;
}
int C自机与子弹判定::f子弹_提交判定(const t旋转矩形 &a矩形) {
	m判定结果 = 0;
	if (数学::f圆形旋转矩形相交判定(m擦弹点, a矩形)) {
		m判定结果 |= e擦弹;
		if (数学::f圆形旋转矩形相交判定(m碰撞点, a矩形)) {
			m判定结果 |= e碰撞;
		}
	}
	return m判定结果;
}
void C自机与子弹判定::f子弹_判定有效() {
	if (f子弹_i擦弹()) {
		f擦弹成立处理();
		if (f子弹_i碰撞()) {
			f碰撞成立处理();
		}
	}
}
bool C自机与子弹判定::f子弹_i碰撞() const {
	return m判定结果 & e碰撞;
}
bool C自机与子弹判定::f子弹_i擦弹() const {
	return m判定结果 & e擦弹;
}
const t向量2 &C自机与子弹判定::fg自机坐标() const {
	return m自机->m坐标;
}
void C自机与子弹判定::f碰撞成立处理() {
	if (!m自机->fi无敌()) {
		m自机->f中弹();
	}
}
void C自机与子弹判定::f擦弹成立处理() {
	++m擦弹数;
}

}