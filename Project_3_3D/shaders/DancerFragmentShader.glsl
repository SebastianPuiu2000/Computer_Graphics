#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

uniform vec3 light_position[9];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int number_lights;
uniform vec3 object_color[9];

uniform vec3 light_direction;
uniform vec3 spot_light_position[4];
uniform vec3 spot_light_color[4];

// Output
layout(location = 0) out vec4 out_color;


void main()
{

    float light_radius = 0.82;

    vec3 color;

    vec3 L;
    vec3 V;
    vec3 H;
    vec3 R;

    float ambient_light;

    float diffuse_light;

    float specular_light;

    float light;

    // zona de calcul a iluminarii ce provine de la bucatile de podea alaturate dansatorului
    for(int i = 0; i < number_lights; i++) {
    
        L = normalize( light_position[i] - world_position );

        V = normalize( eye_position - world_position );

        H = normalize( L + V );

        R = normalize (reflect (-L, world_normal));

        ambient_light = 0;

        diffuse_light = (material_kd + 0.3) *  max (dot(world_normal,L), 0);

        specular_light = 0;

 
        if (diffuse_light > 0)
        {
            specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
        }


        light = ambient_light;
        
        float d = distance(light_position[i], world_position);

        float at_factor = 0;
        
        if(d < light_radius) {
            at_factor = pow(light_radius - d, 2);
        }

        light = at_factor * (diffuse_light + specular_light);
    
        color += object_color[i] * light;

    }



    // zona de calcul a iluminarii ce provine de la reflectoarele alaturate dansatorului
    for(int i = 0; i < 4; i++) {
    
        L = normalize( spot_light_position[i] - world_position );

        V = normalize( eye_position - world_position );

        H = normalize( L + V );

        R = normalize (reflect (-L, world_normal));

        ambient_light = 0;

        diffuse_light = material_kd *  max (dot(world_normal,L), 0);

        specular_light = 0;

        light = 0;


        if (diffuse_light > 0)
        {
            specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
        }


        float angle = 30;
        float cut_off = radians(angle);
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(cut_off);

        if (spot_light > spot_light_limit) {
            
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = pow(linear_att, 2);

            light = ambient_light + light_att_factor * (diffuse_light + specular_light);
        }

        color += spot_light_color[i] * light;

    }

    out_color = vec4(color, 1);
}
