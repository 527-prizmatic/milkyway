uniform vec2 uPos;
uniform vec2 uRes;
uniform int uTime;
uniform sampler2D texture;

void main() {
	vec2 px = gl_TexCoord[0].xy;
	vec4 clr = texture2D(texture, px);
	vec2 uv = uPos / uRes;

	gl_FragColor = vec4(clr.r, clr.g, clr.b, clr.a * uv.y * 4);
}