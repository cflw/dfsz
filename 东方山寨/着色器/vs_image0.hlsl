#include "image.hlsli"
struct VS_IMAGE {
	float2 pos : POSITION;
	float2 tex : TEXCOORD;
	float alpha : ALPHA;
};
struct PS_IMAGE {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
	float alpha : ALPHA;
};
PS_IMAGE vs_image(VS_IMAGE i) {
	PS_IMAGE o;
	o.pos = setposition(i.pos);
	o.tex = i.tex;
	o.alpha = i.alpha;
	return o;
}
