#include "windows.hlsli"
#include "tint.hlsli"
PS_TINT vs_tint(VS_TINT i) {
	PS_TINT o;
	o.pos = setposition(i.pos);
	o.pos0 = i.pos;
	o.color0 = i.color0;
	o.color1 = i.color1;
	o.tex = i.tex;
	return o;
}
