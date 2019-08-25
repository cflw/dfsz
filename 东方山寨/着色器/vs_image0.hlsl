#include "windows.hlsli"
#include "image.hlsli"
PS_IMAGE vs_image(VS_IMAGE i) {
	PS_IMAGE o;
	o.pos = setposition(i.pos);
	o.pos0 = i.pos;
	o.tex = i.tex;
	o.alpha = i.alpha;
	return o;
}
