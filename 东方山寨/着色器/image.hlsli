struct VS_IMAGE {
	float2 pos : POSITION;
	float2 tex : TEXCOORD;
	float alpha : ALPHA;
};
struct PS_IMAGE {
	float4 pos : SV_POSITION;
	float2 pos0 : POSITION0;
	float2 tex : TEXCOORD;
	float alpha : ALPHA;
};