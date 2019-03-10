cbuffer global : register(b0) {
	float2 windows;	//���ڰ�ߴ�
	float2 frame;	//�߿��ߴ�
}
Texture2D tx : register(t0);
SamplerState sam : register(s0);
struct P2F {
	float4 color : SV_TARGET;
	float depth : SV_DEPTH;
};
float4 setposition(float2 pos) {
	float4 v;
	v.x = pos.x / windows.x;
	v.y = pos.y / windows.y;
	v.z = 0;
	v.w = 1;
	return v;
}
//=============================================================================
// ��ͼ
//=============================================================================
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
//=============================================================================
// ��ɫ��ͼ
//=============================================================================
struct VS_COLORIMAGE {
	float2 pos : POSITION;
	float4 color0 : COLOR0;
	float4 color1 : COLOR1;
	float2 tex : TEXCOORD;
};
struct PS_COLORIMAGE {
	float4 pos : SV_POSITION;
	float4 color0 : COLOR0;
	float4 color1 : COLOR1;
	float2 tex : TEXCOORD;//����uv
};
PS_COLORIMAGE vs_colorimage(VS_COLORIMAGE i) {
	PS_COLORIMAGE o;
	o.pos = setposition(i.pos);
	o.color0 = i.color0;
	o.color1 = i.color1;
	o.tex = i.tex;
	return o;
}
float4 ps_colorimage(PS_COLORIMAGE i) : SV_TARGET {
	float4 tex = tx.Sample(sam, i.tex);
	if (tex.z <= 0) {
		discard;
	}
	float4 t = i.color0 * tex.x;
	float4 b = i.color1 * tex.y;
	float a = t.a + b.a;
	if (a <= 0) {
		discard;
	}
	float4 o = b + t;
	o = lerp(o, t, tex.x);
	o.a = a * tex.z;
	return o;
}