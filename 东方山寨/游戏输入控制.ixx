module;
#include "程序实现.h"
export module 东方山寨.游戏输入控制;
import 东方山寨.图形_帧速率;
export import 东方山寨.游戏输入;
import 东方山寨.游戏输入_录像;
import 东方山寨.游戏录像管理;
export namespace 东方山寨 {
class C游戏输入控制 {
public:
	C游戏输入控制(C程序实现 &a实现, C输入引擎 &a输入, C游戏录像管理 &a录像管理):
		mp实现(&a实现),
		mp输入(&a输入),
		mp录像管理(&a录像管理) {
	}
	I游戏输入 &fg游戏输入(E游戏输入 a游戏输入) {
		auto &vp游戏输入 = ma游戏输入[(int)a游戏输入];
		if (!vp游戏输入) {
			switch (a游戏输入) {
			case E游戏输入::e直接: {
				vp游戏输入 = std::make_unique<C游戏输入>(*mp输入);
				break;
			}
			case E游戏输入::e录像: {
				auto v录像 = std::make_unique<C游戏输入_录像>(*mp输入, mp实现->m画帧速率->m计算);
				v录像->mp录像 = &mp录像管理->f新建录像();
				vp游戏输入 = std::move(v录像);
				break;
			}
			case E游戏输入::e回放:
				//vp游戏输入 = std::make_unique<C游戏输入_回放>(m输入);
				break;
			}
		}
		return *vp游戏输入;
	}
	C程序实现 *mp实现 = nullptr;
	C输入引擎 *mp输入 = nullptr;
	C游戏录像管理 *mp录像管理 = nullptr;
	std::unique_ptr<I游戏输入> ma游戏输入[(int)E游戏输入::c数量];
};
}	//namespace 东方山寨