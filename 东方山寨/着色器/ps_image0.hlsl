#include "image.hlsli"
struct PS_IMAGE {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
	float alpha : ALPHA;
};
float4 ps_image(PS_IMAGE i) : SV_TARGET{
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
