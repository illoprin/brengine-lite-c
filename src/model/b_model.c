#include "b_model.h"

model_triangle* mt_from_obj(const char* filename, unsigned* vertex_count)
{
	return NULL;
}

void mt_print(model_triangle* mt, unsigned count)
{
	uch v_index = 0;
	for (unsigned i = 0; i < count * 3; ++i)
	{
		v_index = i % 3;
		model_triangle t = *(mt + (i / 3));
		if (v_index == 0)
			putchar('\n');
		printf("Position: %.2f %.2f %.2f Texcoord: %.2f %.2f Normal: %.2f %.2f %.2f\n",
			t.vertices[v_index].position[0], t.vertices[v_index].position[1], t.vertices[v_index].position[2],
			t.vertices[v_index].texcoord[0], t.vertices[v_index].position[1],
			t.vertices[v_index].normal[0], t.vertices[v_index].normal[1], t.vertices[v_index].normal[2]);
	}
}
