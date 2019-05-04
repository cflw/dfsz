#include "image.hlsli"
struct VS_TINT {
	float2 pos : POSITION;
	float4 color0 : COLOR0;
	float4 color1 : COLOR1;
	float2 tex : TEXCOORD;
};
struct PS_TINT {
	float4 pos : SV_POSITION;
	float4 color0 : COLOR0;
	float4 color1 : COLOR1;
	float2 tex : TEXCOORD;//Œ∆¿Ìuv
};
PS_TINT vs_tint(VS_TINT i) {
	PS_TINT o;
	o.pos = setposition(i.pos);
	o.color0 = i.color0;
	o.color1 = i.color1;
	o.tex = i.tex;
	return o;
}
