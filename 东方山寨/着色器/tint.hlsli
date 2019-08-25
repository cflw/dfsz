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
	float2 pos0 : POSITION0;
	float2 tex : TEXCOORD;//Œ∆¿Ìuv
};