version #440

layout(location=0) in vec4 inPos;
uniform vec2 delta;
layout(location=1) in vec4 inColor;
out vec4 fragColor;

void main(void)
{
	vec4 totalOffset = vec4(delta.x,, delta.y, 0.0,0.0);
	gl_position = inPos+totalOffset;
	fragColor = inColor;
}