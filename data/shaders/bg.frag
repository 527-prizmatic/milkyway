uniform vec2 uRes;
uniform int uTime;
uniform sampler2D texture;

float lerp(float _a, float _b, float _t) {
	if (_t < 0) return _a;
	else if (_t > 1) return _b;
	else return (_b - _a) * _t + _a;
}

float clamp(float _a, float _l, float _u) {
	if (_a < _l) return _l;
	else if (_a > _u) return _u;
	else return _a;
}

void main() {
	vec2 px = gl_TexCoord[0].xy;
	vec4 clr = texture2D(texture, px);
	float time = uTime / 20.;
	vec2 uv = gl_FragCoord / uRes;

	float posY = gl_FragCoord.y / uRes.y;
	float posYnew = clamp(posY * 3., 0., 1.);
	vec3 newclr = vec3(clr.r * posYnew, clr.g * posYnew, clr.b);

	newclr.b *= 1.25;
	newclr.r *= 0.75;

	if (uTime % 4 == 0) newclr.rgb *= 0.95;

	newclr.g += 0.05 * clamp(1 - (cos(time * 5. + uv.y * 200.) + 0.97), 0., 1.) * sin((uv.y + uv.x) * 3.14);
	newclr.b += 0.1 * clamp(1 - (cos(time * 2. + uv.y * 200.) + 0.97), 0., 1.)  * sin((uv.y + uv.x) * 3.14);


	gl_FragColor = vec4(newclr, 1.);
}