cbuffer cb0 : register(b0) {
	float3 g_eyepos;
	float4 g_fogcolor;
	float g_fogstart;
	float g_fogrange;
}
Texture2D tx : register(t0);
SamplerState sam : register(s0);
struct PS_STAGE {
	float4 pos0 : SV_POSITION;
	float3 pos1 : POSITION;
	float2 tex : TEXCOORD;
};
float4 ps_stage(PS_STAGE i) : SV_TARGET {
	float4 v = tx.Sample(sam, i.tex);

	const float d = distance(g_eyepos, i.pos1);
	if (d > g_fogstart) {
		const float s = saturate((d - g_fogstart) / g_fogrange);
		v = lerp(v, g_fogcolor, s);
	}

	return v;
}