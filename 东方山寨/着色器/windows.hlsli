cbuffer cb0 : register(b0) {
	float2 g_windows;	//´°¿Ú°ë³ß´ç
	float2 g_frame;	//¿ò¼Ü°ë³ß´ç,×ÜÊÇ640*480
}
Texture2D tx : register(t0);
SamplerState sam : register(s0);
float4 setposition(float2 pos) {
	float4 v;
	v.x = pos.x / g_windows.x;
	v.y = pos.y / g_windows.y;
	v.z = 0;
	v.w = 1;
	return v;
}
bool isinframe(float2 pos) {
	return abs(pos.x) < g_frame.x && abs(pos.y) < g_frame.y;
}
bool isoutframe(float2 pos) {
	return abs(pos.x) >= g_frame.x || abs(pos.y) >= g_frame.y;
}