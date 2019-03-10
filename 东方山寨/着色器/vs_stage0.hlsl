cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
struct VS_STAGE {
	float4 pos0 : POSITION0;
	float2 tex : TEXCOORD;
};
struct PS_STAGE {
	float4 pos0 : SV_POSITION;
	float3 pos1 : POSITION;
	float2 tex : TEXCOORD;
};
PS_STAGE vs_stage(VS_STAGE i) {
	PS_STAGE o;
	o.pos0 = i.pos0;
	o.pos0 = mul(o.pos0, g_world);
	o.pos1 = o.pos0.xyz;
	o.pos0 = mul(o.pos0, g_view);
	o.pos0 = mul(o.pos0, g_projection);
	o.tex = i.tex;
	return o;
}
