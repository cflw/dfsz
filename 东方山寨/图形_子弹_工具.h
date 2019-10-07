#include "数学包含.h"
namespace 东方山寨::画子弹工具 {
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
}	//namespace 东方山寨::画子弹工具