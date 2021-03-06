attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;
uniform 	mat4 	u_matWorld;
uniform 	float 	u_alpha;
uniform		float   u_mCurrentFrame;
uniform		float   u_mFrameCount;

varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	v_uv = vec2(a_uv.x / u_mFrameCount + u_mCurrentFrame / u_mFrameCount ,a_uv.y);
}
   