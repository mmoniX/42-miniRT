# trace_ray Function – Raytracing Steps

The `trace_ray()` function determines what color a given ray sees in the scene. Here’s a breakdown of what the function should do.

---

## 1. Normalize the Ray Direction
- Ensure the direction vector of the ray is normalized.
- Required for consistent intersection calculations.

---

## 2. Initialize Closest Intersection Tracking
- Keep track of the nearest object hit by the ray.
  - Closest distance (`t`)
  - Hit object type (sphere, plane, cylinder)
  - Hit position, surface normal, color, etc.

---

## 3. Intersect Ray with All Scene Objects
- Loop over each type of object (sphere, plane, cylinder, etc.).
- For each object:
  - Call its specific intersection function.
  - Check if the intersection is closer than the current closest.
  - If so, update the closest hit data.

---

## 4. If No Hit: Return Background Color
- If the ray does not hit anything:
  - Return a default color (e.g., black or sky blue).

---

## 5. Compute Surface Normal at Hit Point
- Needed for lighting calculations.
- Varies by object type (e.g., for a sphere it's the normalized vector from center to hit point).

---

## 6. Compute Lighting (Phong or Lambert)
- Use the hit position and surface normal to compute lighting.
  - **Ambient** lighting (constant)
  - **Diffuse** lighting (depends on angle to light)
  - (Optional) **Specular** lighting (for highlights)
- Check for shadows:
  - Cast a ray from hit point toward light.
  - If blocked by any object, skip diffuse/specular.

---

## 7. Combine Color Components
- Final color = ambient + diffuse (+ optional specular).
- Clamp the RGB values to [0, 255] range.

---

## 8. Return Final Color
- Return the resulting `t_col` or RGB color from this pixel's ray.



t_col tray_race(t_mrt *mrt)
{
	mrt->light.position = vector_normalization(&mrt->light.position);
	//others logic
}


