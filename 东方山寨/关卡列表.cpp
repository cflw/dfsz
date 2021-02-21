#include "关卡列表.h"
#include "关卡.h"
namespace 东方山寨 {
std::vector<C关卡 *> &C关卡列表::fg列表() {
	static std::vector<C关卡 *> va关卡 = {
		&fg关卡(E关卡::e一),
		&fg关卡(E关卡::e二),
		//&fg关卡(E关卡::e三),
		//&fg关卡(E关卡::e四),
		//&fg关卡(E关卡::e五),
		//&fg关卡(E关卡::e六),
	};
	return va关卡;
}
C关卡 &C关卡列表::fg关卡(E关卡 a关卡) {
	const std::wstring v关卡名 = ca关卡[(int)a关卡];
	return C关卡管理::fg关卡(v关卡名);
}
}	//namespace 东方山寨