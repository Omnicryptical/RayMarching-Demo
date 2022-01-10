#version 330 core
in vec2 fPosition;
in vec3 cPosition;
in mat4 cDirection;
in float fTime;
out vec3 color;

float sphere_sdf(in vec3 p, in vec3 c, float r)
{
	return length(p - c) - r;
}

float cube_sdf(in vec3 p, in vec3 c, float r)
{
	return length(max(abs(p-c)-r, 0.0));
}

vec2 world_dst(in vec3 p){
    float s1 = sphere_sdf(p, vec3(3.0*cos(fTime), 0.0,-10.0+3.0*sin(fTime)), 3.0);
    float s2 = cube_sdf(p, vec3(0.0, 5.5*cos(fTime),-10.0+2.5*sin(fTime)), 1.0);
    float s3 = sphere_sdf(p, vec3(3.0*sin(-fTime-1.5), 0.0,-10.0+3.0*cos(-fTime-1.5)), 3.0);

    float color = 0.0;
    if (s2 < s1 && s2 < s3){
        color = 1.0;
    }

    return vec2(min(min(s1, s2), s3), color);
}

vec3 get_norm(in vec3 p)
{
    const vec3 ss = vec3(0.001, 0.0, 0.0);

    float gradient_x = world_dst(p + ss.xyy).x - world_dst(p - ss.xyy).x;
    float gradient_y = world_dst(p + ss.yxy).x - world_dst(p - ss.yxy).x;
    float gradient_z = world_dst(p + ss.yyx).x - world_dst(p - ss.yyx).x;

    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

    return normalize(normal);
}


void main() {
    vec3 pos = vec3(fPosition, -1.0);
    vec3 light = vec3(10.0*sin(fTime), 10.0*cos(fTime), -1.0);
    vec2 dist = world_dst(pos);

	color = vec3(0.0, 0.05, 0.1);

    vec3 dir = (vec4(normalize(pos), 1.0f)).xyz;

    for (int i = 0; i < 55; ++i){
        pos = pos + dir*dist.x;
        dist = world_dst(pos);

        if (dist.x < 0.001) {
            vec3 lightdir = normalize(light-pos);
            vec3 n = get_norm(pos);

            float intensity = max(0.0, dot(n, lightdir));

            if (dist.y < 1){
                color = vec3(1.0, 0.0, 0.0)*intensity;
            }
            if (dist.y >= 1){
                color = vec3(0.0, 0.0, 1.0)*intensity;
            }

            break;
        }
    }
}
