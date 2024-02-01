#version 330 core
out vec4 FragColor;

in vec2 Pos;

uniform vec2 ScreenResolution;
uniform float Time;

vec3 palette(in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d) {
    return a + b*cos( 6.28318*(c*t+d) );
}

vec3 palette_1(in float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(2.0, 1.0, 0.0);
    vec3 d = vec3(0.50, 0.20, 0.25);

    return palette(t, a, b, c, d);
}

void main() {
    vec2 uv = Pos;
    uv.x *= ScreenResolution.x / ScreenResolution.y;
    vec2 uv0 = uv;
    vec3 finalColour = vec3(0.0);
    float time_s = Time / 1000;

    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        float dist = length(uv) * exp(-length(uv0));
        vec3 colour = palette_1(length(uv0) + i*0.4 + time_s*0.4);

        dist = sin(dist * 8 + time_s) / 8;
        dist = abs(dist);

        dist = pow(0.008 / dist, 2);

        finalColour += colour *= dist;
    }

    FragColor = vec4(finalColour, 1.0);
}
