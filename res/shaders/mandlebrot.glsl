uniform float screenWidth;
uniform float screenHeight;
uniform int maxIteration;
uniform float scale;
uniform float xOff;
uniform float yOff;


float x = (gl_FragCoord.x / screenWidth) * scale - 1.7 + (xOff / 25.0);
float y = (gl_FragCoord.y / screenHeight) * scale - 1.0 + (yOff / 25.0);

void main()
{
	vec2 c = vec2(x, y);
	int iteration = 0;
	float colorScaling = 0.0;

	for(int i = 0; i < maxIteration; i++)
	{
		if(x*x + y*y > 2.0*2.0) break;

		float xtemp = x*x - y*y + c.x;
		y = 2.0*x*y + c.y;
		x = xtemp;
		iteration++;
		colorScaling++;
	}

	if(iteration == maxIteration)
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	else
		gl_FragColor = vec4(0.72 - 1.0 / colorScaling, 0.25 - 1.0 / colorScaling, 0.06 - 1.0 / colorScaling, 1.0);
}
