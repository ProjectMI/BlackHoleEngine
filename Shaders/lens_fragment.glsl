#version 330 core
out vec4 FragColor;

in vec2 vLocal;

uniform sampler2D uBackgroundTex;
uniform vec2  uScreenSize;     
uniform vec2  uCenterUV;       
uniform float uOpacity;        
uniform float uBlendStrength;  
uniform float uDistortionK;    
uniform float uFeather;        
uniform float uDiskRadiusWS;   // полный радиус диска (EventHorizonRadius)
uniform float uBHRadiusWS;     // радиус горизонта BH->GetRadius()

void main()
{
    vec2 uv = gl_FragCoord.xy / uScreenSize;
    float r = length(vLocal); // нормированный радиус [0..1]

    // радиус горизонта событий в нормализованных координатах
    float r_h = uBHRadiusWS / uDiskRadiusWS;

    // вне диска
    if (r > 1.0 + uFeather) discard;

    // внутри горизонта событий -> чёрное
    if (r < r_h) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // мягкая кромка у внешней границы
    float mask = 1.0 - smoothstep(1.0 - uFeather, 1.0 + uFeather, r);

    // направление от центра в экранных координатах
    vec2 dir = normalize(uv - uCenterUV);

    // коэффициент искажения: 0 у r_h, макс. у края
    float t = smoothstep(r_h, 1.0, r);
    float strength = uDistortionK * t;

    vec2 sampleUV = uv + dir * strength;

    vec4 baseCol = texture(uBackgroundTex, uv);
    vec4 bentCol = texture(uBackgroundTex, sampleUV);

    float w = mask * clamp(uBlendStrength, 0.0, 1.0);
    vec4 col = mix(baseCol, bentCol, w);

    col.a *= uOpacity;
    FragColor = col;
}
