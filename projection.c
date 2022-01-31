#include "fdf.h"
#include <math.h>

t_vec3d *define_vec3d_coord(t_vec3d *coord, float x, float y, float z)
{
	coord = malloc(sizeof(t_vec3d));
    coord->x = x;
    coord->y = y;
    coord->z = z;
    return (coord);
}

void    clean_4(t_mat4x4 *matrix)
{
    int i;
    int y;
    
    i = 0;
    while (i < 4)
    {
        y = 0;
        while (y < 4)
        {
           matrix->m[i][y] = 0;
           ++y;
        }
        ++i;
    }
}

void    multiply_matrix_vector(t_vec3d *in, t_vec3d *out, t_mat4x4 *mat)
{
    out->x = in->x * mat->m[0][0] + in->y * mat->m[1][0] + in->z * mat->m[2][0] + mat->m[3][0];
    out->y = in->x * mat->m[0][1] + in->y * mat->m[1][1] + in->z * mat->m[2][1] + mat->m[3][1];
    out->z = in->x * mat->m[0][2] + in->y * mat->m[1][2] + in->z * mat->m[2][2] + mat->m[3][2];
    float w = in->x * mat->m[0][3] + in->y * mat->m[1][3] + in->z * mat->m[2][3] + mat->m[3][3];
    
    if (w != 0.0)
    {
        out->x = out->x / w;
        out->y = out->y / w;
        out->z = out->z / w;
    }
}

t_mat4x4	*projection(t_mat4x4 *mat_proj, float fFov)
{
    float fNear = 0.1;
    float fFar = 2000.0;
    float fAspectRatio = 1000 / 1000;
    float fFovRad = 1.0 / tan(fFov * 0.5 / 180.0 * 3.14159);

    clean_4(mat_proj);

    mat_proj->m[0][0] = fAspectRatio * fFovRad;
    mat_proj->m[1][1] = fFovRad;
    mat_proj->m[2][2] = fFar / (fFar - fNear);
    mat_proj->m[3][2] = (-fFar * fNear) / (fFar - fNear);
    mat_proj->m[2][3] = 1.0;
    mat_proj->m[3][3] = 0.0;

    return (mat_proj);
}

t_vec3d	*project_point(t_mat4x4 *mat_proj, t_vec3d *coord)
{
    t_vec3d *projected_coord;

    // coord = define_vec3d_coord(coord, 1, 1, 100);
	projected_coord = NULL;
    projected_coord = define_vec3d_coord(projected_coord, 0, 0, 0);
    multiply_matrix_vector(coord, projected_coord, mat_proj);
	// free(coord);
    // scale into view
    projected_coord->x += 1.0;
    projected_coord->y += 1.0;
   
    projected_coord->x *= 0.5 * 1000;
    projected_coord->y *= 0.5 * 1000;
	return (projected_coord);
}
