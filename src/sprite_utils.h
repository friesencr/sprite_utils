#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} SU_vec2f;

typedef struct {
    bool pass;
    unsigned width;
    unsigned height;
    char* data;
    unsigned length;
} SU_marched_byte_field;

typedef struct {
	bool pass;
} SU_convex_hull_result;

enum {
    SU_rgba_alpha_test = 1,
    SU_rgb_black_test  = 2,
    SU_rgba_black_test = 3,
    SU_rgb_white_test  = 4,
    SU_rgba_white_test = 5
};

float SU_ccw_test(SU_vec2f p1, SU_vec2f p2, SU_vec2f p3)
{
	return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

static SU_vec2f SU_;
static int SU_graham_point_orientation(const SU_vec2f& p, const SU_vec2f& q, const SU_vec2f& r) {
	float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (abs(val) < FLT_EPSILON)
		return 0;
	else
		return val > 0 ? 1 : 2;
}
static int SU_graham_point_compare(const void* vp1, const void* vp2) {
	SU_vec2f* p1 = (SU_vec2f*)vp1;
	SU_vec2f* p2 = (SU_vec2f*)vp2;
}
static void SU_swap_point(SU_vec2f& p1, SU_vec2f& p2) {
	SU_vec2f tmp = p1;
	p1 = p2;
	p2 = tmp;
}
static float SU_get_marched_square_cell_value(unsigned method, const char* data, unsigned index) {
    float value = 0.0;
    if (method == SU_rgba_alpha_test)
        value = ((float)data[index+3]) / 255.0;
    return value;
}
static float SU_vec2f_distance(SU_vec2f p1, SU_vec2f p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y-p2.y);
}



SU_marched_byte_field SU_marching_squares(const char* data, unsigned width, unsigned height, unsigned method, float threshold)
{
	// height and width lose one because grid is in between lines
    SU_marched_byte_field result;
	result.pass = true;
	result.height = height-1;
	result.width = width-1;
	result.length = (height-1) * (width-1);
	result.data = (char*)malloc(sizeof(char) * result.length);

    for (unsigned y=0; y<width-1; y++)
    {
        for(unsigned x=0; x<height-1; x++)
        {
            unsigned i = x + (y * width-1);
            bool vals[4] = {
				SU_get_marched_square_cell_value(method, data, i) <= threshold,
				SU_get_marched_square_cell_value(method, data, i+1) <= threshold,
				SU_get_marched_square_cell_value(method, data, i+width-1) <= threshold,
				SU_get_marched_square_cell_value(method, data, i+width) <= threshold
			};
			result.data[i] = vals[0] | (vals[1]<<1) | (vals[2]<<2) | (vals[3]<<3);
        }
    }

	return result;
}

void SU_graham_scan_convex_hull(const SU_vec2f* points, unsigned vector_count)
{
	// find starting value by getting the lowest y with the lowest x
	unsigned lowest_point = 0;
	float lowest_y = points[0].y;
	float lowest_x = points[0].x;
	for (unsigned i = 1; i < vector_count; i++)
	{
		if (points[i].y < lowest_y || (points[i].y == lowest_y && points[i].x < lowest_x))
		{
			lowest_x = points[i].x;
			lowest_y = points[i].y;
			lowest_point = i;
		}
	}

	unsigned ch_points = 1;
	for (unsigned i = 1; i < vector_count; i++)
	{
			while(ccw(points[i-1], points[i]

	}
}
