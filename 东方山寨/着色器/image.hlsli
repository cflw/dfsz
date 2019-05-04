cbuffer global : register(b0) {
	float2 windows;	//´°¿Ú°ë³ß´ç
	float2 frame;	//±ß¿ò°ë³ß´ç
}
Texture2D tx : register(t0);
SamplerState sam : register(s0);
float4 setposition(float2 pos) {
	float4 v;
	v.x = pos.x / windows.x;
	v.y = pos.y / windows.y;
	v.z = 0;
	v.w = 1;
	return v;
}