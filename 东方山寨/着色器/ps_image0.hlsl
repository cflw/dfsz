#include "windows.hlsli"
#include "image.hlsli"
float4 ps_image(PS_IMAGE i) : SV_TARGET {
	if (i.alpha <= 0) {
		discard;
	}
	float4 o = tx.Sample(sam, i.tex);
	if (o.w <= 0) {
		discard;
	}
	o.a *= i.alpha;
	return o;
}
