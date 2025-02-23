export module 东方山寨.载入.图形管线;
import 东方山寨.载入.内部;
import "程序.h";
import "图形引擎.h";
import "图形管线接口.h";
import "图形_三维.h";
import "图形_画图片.h";
import 东方山寨.图形.静态立绘;
import "图形_子弹_线条.h";
import "图形_子弹_顶点.h";
namespace 东方山寨::载入 {
void C内部载入::f图形管线() {
	C图形引擎 &v图形 = C程序::fg图形();
	auto &va图形管线 = v图形.fg图形管线数组();
	va图形管线.f构造<C画图片管线>((int)E图形管线::e图片, v图形, *v图形.m三维);
	va图形管线.f构造<C画子弹_顶点>((int)E图形管线::e子弹正常, v图形, *v图形.m三维, false);
	va图形管线.f构造<C画子弹_顶点>((int)E图形管线::e子弹高光, v图形, *v图形.m三维, true);
	va图形管线.f构造<C画子弹_线条>((int)E图形管线::e子弹线条, *v图形.m二维);
	va图形管线.f构造<C画三维管线>((int)E图形管线::e三维场景, v图形, *v图形.m三维);
	va图形管线.f构造<C静态立绘管线>((int)E图形管线::e静态立绘, v图形, *v图形.m三维);
}
}	//namespace 东方山寨::载入