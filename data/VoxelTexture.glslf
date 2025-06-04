#version 150 
#extension GL_EXT_gpu_shader4 : enable
#pragma debug(on)
uniform mat4x4 worldviewproj_matrix, invView,viewMat;
//in float isItGlass;
uniform vec2 windowSize; // set per frame?
vec3 CalcCameraSpacePosition()
{
    vec4 ndcPos;
    ndcPos.xy = ((gl_FragCoord.xy / windowSize.xy) * 2.0) - 1.0;
    ndcPos.z = (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far) /
        (gl_DepthRange.far - gl_DepthRange.near);
    ndcPos.w = 1.0;
    
    vec4 clipPos = ndcPos / gl_FragCoord.w;
    
    return vec3(worldviewproj_matrix * clipPos);
}

float ATLAS_WIDTH = 1024.0;
float TEXTURE_WIDTH = 128.0;
float RATIO =  (TEXTURE_WIDTH) / ATLAS_WIDTH;

uniform sampler2D Atlas;
uniform vec4 diffuse, specular, ambient, lightPos, emissive, attenuation;
uniform float shininess;
in vec3 normal;
//in vec3 iVrt;
out vec4 FragColor;
uniform mat4x4 worldViewProj;
struct IOStruct {
 vec4 textureAtlasOffset;
 vec3 worldPosition;
 float glass;
 float water;
 float lava;
 float stained_glass;
 vec4 vertex;
 vec4 color;
 bool inView;
 bool isGrass;
 bool isWater;
 vec2 rendering_stuff;
 vec3 vPos3;
 vec3 normal;
};
in IOStruct gsOutput;

#define GOREAL float
float _get3d_vecdistref(vec3 p, vec3 y) {
		GOREAL c_x = p.x-y.x;
		GOREAL c_y = p.y-y.y;
		GOREAL c_z = p.z-y.z;
		return sqrt((c_x*c_x)+(c_y*c_y)+(c_z*c_z));
}



float rand( vec2  co)
{
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
float i_rand(int i) {
    return rand(vec2(0,i));
}
float noise3f(in vec3 p)
{
  ivec3 ip = ivec3(floor(p));
  vec3 u = fract(p);
  u = u*u*(3.0-2.0*u);

  int n = ip.x + ip.y*57 + ip.z*113;

  float res = mix(mix(mix(i_rand(n+(0+57*0+113*0)),
                          i_rand(n+(1+57*0+113*0)),u.x),
                      mix(i_rand(n+(0+57*1+113*0)),
                          i_rand(n+(1+57*1+113*0)),u.x),u.y),
                 mix(mix(i_rand(n+(0+57*0+113*1)),
                          i_rand(n+(1+57*0+113*1)),u.x),
                      mix(i_rand(n+(0+57*1+113*1)),
                          i_rand(n+(1+57*1+113*1)),u.x),u.y),u.z);

  return 1.0 - res*(1.0/1073741824.0);
}

vec4 fx(vec4 x)
{
      x.r=(noise3f(vec3(x.r,x.g,x.b)));
      x.g=(noise3f(vec3(x.r,x.g,x.b)));
      x.b=(noise3f(vec3(x.r,x.g,x.b)));
      x.a=(noise3f(vec3(x.r,x.g,x.b)));
      return x;
}




uniform vec4 cameraPos;
void main()
{
//if(glass != isItGlass)
//FragColor = vec4(0,0,0,1);
//return;
float LOD;
  float dist = _get3d_vecdistref(cameraPos.xyz,gsOutput.worldPosition.xyz);
  if(dist < 10) LOD = 0;
  else if(dist < 15) LOD = 1;
  else if(dist < 20) LOD = 2;
  else if(dist < 30) LOD = 3;
  else if(dist < 40) LOD = 4;
  else if(dist < 70) LOD = 5;
  else LOD = 6;


	vec2 uv = vec2(0.0, 0.0);
	vec3 wp = gsOutput.worldPosition.xyz - vec3(0.5,0.5,0.5);
	// ddx then ddy gives back positive normals for all the positive faces
	vec3   worldNormal = cross(dFdx(wp.xyz), dFdy(wp.xyz));
	worldNormal = normalize(worldNormal);
    
    vec4 textureOff = gsOutput.textureAtlasOffset;

    
   if(worldNormal.x > 0.5) {
      uv = fract(vec2(-wp.z, wp.y));
   }
   if(worldNormal.x < -0.5) {
      uv = fract(vec2(wp.z, wp.y));
    }
   if(worldNormal.y > 0.5){
      uv = fract(vec2(wp.x,-wp.z));
   }
   if(worldNormal.y < -0.5){ 
      uv = fract(vec2(wp.x, wp.z));
   }
   if(worldNormal.z > 0.5){
      uv = fract(vec2(wp.x, wp.y));
   }
   if(worldNormal.z < -0.5){
      uv = fract(vec2(-wp.x,wp.y));
   }
   TEXTURE_WIDTH = TEXTURE_WIDTH/( LOD+1);
ATLAS_WIDTH = ATLAS_WIDTH/( LOD+1);
   uv = uv* (TEXTURE_WIDTH-1);//(2+LOD));
   textureOff*=TEXTURE_WIDTH;
   textureOff.y += TEXTURE_WIDTH-1;
   textureOff.x += uv.x;
   textureOff.y -= uv.y;
   textureOff = textureOff/ATLAS_WIDTH;
   FragColor = textureLod(Atlas, textureOff.xy,LOD);
   if(gsOutput.glass != 0) {
	if(FragColor.rgb == vec3(0,0,0)) FragColor.a = .15;
	else FragColor.a = .25;

   }
   if(gsOutput.stained_glass != 0) {
	if(FragColor.rgb == vec3(0,0,0)) FragColor.a = .15;
	else FragColor.a = .45;
   }
   /*
   Meh, this only works for 1 light, produces a lot of extra blackness, and blah blah.
   Need to do something like a lightmap.
		 const vec3 lightColor = vec3(1.0, 1.0, 1.0);

		//vec4 PE = viewMat*(vec4(gsOutput.worldPosition, 1.0));
		vec3 P = gsOutput.worldPosition.xyz;
		vec3 N = normal.xyz;
		dist = length(lightPos.xyz-P);
		vec3 amb = lightColor*vec3(0.2,0.2,0.2);
		
		if(dist < attenuation.x && attenuation.x >0)  {
			float att = 1.0 / (attenuation.y+(attenuation.z*dist)+(attenuation.w*(dist*dist)));
			vec3 LD = normalize(lightPos.xyz-P);
			vec3 diffuseReflection = att 
				* vec3(diffuse) * lightColor
				* max(0.0, dot(N, LD));
			
			vec3 specularReflection;
			vec3 VD;
			{
				//vec4 TMP = (invView * vec4(0.0,0.0,0.0,1.0));
			//	TMP = TMP-vec4(P,1);
				VD = normalize(-P);
			}
			
		//	if (dot(N, LD) < 0.0) // light source on the wrong side?
		//	{
		//		  specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
		//	}
		//	else // light source on the right side
		//	{
				  specularReflection = att * vec3(specular) * lightColor 
					* pow(max(0.0, dot(reflect(-LD, N), VD)), shininess);
		//	}
 
			FragColor.xyz = mix(FragColor.xyz,amb + diffuseReflection + specularReflection, .5);
		} else { 
				FragColor.xyz = mix(FragColor.xyz,amb,.5);
		}
	*/
   //FragColor = FragColor*ambient_light;//mix(FragColor,ambient_light, lessThan(FragColor,ambient_light));
   
return;
} 
