#include "windows.hlsli"
#include "tint.hlsli"
float4 ps_tint(PS_TINT i) : SV_TARGET {
	if (isoutframe(i.pos0)) {
		discard;
	}
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