#version 330 core

layout(location = 0) in vec2 Position;

out vec2 fPosition;
out vec3 cPosition;
out mat4 cDirection;
out float fTime;

uniform vec3 u_cPos;
uniform mat4 u_cDir;
uniform float u_time;

void main() 
{
	fPosition = vec2(Position.x, Position.y);
    fTime = u_time;
    cPosition = u_cPos;
    cDirection = u_cDir;
	gl_Position = vec4(Position.x, Position.y, -1.0, 1.0);
}
