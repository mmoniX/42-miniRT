# 42-miniRT

This is a join project (minimalistic) based on "Ray Tracing" methods of graphic. We use "MLX42" library instead of Forty-two's allowed "MinilibX" library, as it's a bit outdated.

basic ray-tracing rendering:

render_scene
│
├── for each pixel
│   ├── generate_ray
│   │   └── calculate direction based on camera and pixel
│   ├── trace_ray(ray, depth=0)
│   │   ├── find_closest_intersection
│   │   │   └── test ray-object intersections
│   │   ├── if no hit → return background
│   │   ├── compute normal at hit point
│   │   ├── compute lighting (diffuse/specular/shadows)
│   │   ├── if reflective
│   │   │   └── trace_ray(reflected_ray, depth+1)
│   │   ├── if transparent
│   │   │   └── trace_ray(refracted_ray, depth+1)
│   │   └── combine colors
│   └── set_pixel color
└── save_image_to_file
