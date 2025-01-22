#include "b_model.h"

model_triangle* mt_from_obj(const char* filename, size_t* vertex_count)
{
	char file_path[MAX_FILEPATH];
	sprintf(file_path, DIR_MODELS "/%s", filename);

	FILE* src = fopen(file_path, "r");
	if (!src)
	{
		LOG_ERR("Could not read file with path %s", file_path);
		perror(file_path);
		return NULL;
	}

	// Raw obj data
	dynarr_t* vertices  = dynarr_init(vec3);
	dynarr_t* texcoords = dynarr_init(vec2);
	dynarr_t* normals   = dynarr_init(vec3);

	// Triangles list
	dynarr_t* tris      = dynarr_init(model_triangle);

	// Reading lines
	char line[MAX_BUFFER];
	char* token = NULL;
	char name[128];
	while (fgets(line, MAX_BUFFER, src))
	{
		token = strtok(line, " ");

		if (!strcmp(token, "o"))
		{
			// Reading name
			token = strtok(NULL, " ");
			size_t name_len = strlen(token);
			memcpy(name, token, name_len);
			name[name_len - 1] = '\0';
			LOG_MSG("Reading model with name: %s", name);
		}
		else if (!strcmp(token, "v"))
		{
			// Reading vertices
			vec3 vert;
			for (uch i = 0; i < 3; ++i)
			{
				token = strtok(NULL, " ");
				vert[i] = atof(token);
			};
			dynarr_add(vertices, vert);
		}
		else if (!strncmp(token, "vt", 2))
		{
			// Reading texcoords
			vec2 tc;
			for (uch i = 0; i < 2; ++i)
			{
				token = strtok(NULL, " ");
				tc[i] = atof(token);
			};
			dynarr_add(texcoords, tc);
		}
		else if (!strncmp(token, "vn", 2))
		{
			// Reading normals
			vec3 nrm;
			for (uch i = 0; i < 3; ++i)
			{
				token = strtok(NULL, " ");
				nrm[i] = atof(token);
			};
			dynarr_add(normals, nrm);
		}
		else if (!strcmp(token, "f"))
		{
			model_triangle face = {};
			// Reading faces
			for (uch i = 0; i < 3; ++i)
			{
				// Vertices index
				// Texcoord index
				// Normal index
				int vi = 0, ti = 0, ni = 0;
				token = strtok(NULL, " ");
				sscanf(token, "%d/%d/%d", &vi, &ti, &ni);

				vec3 position = {};
				vec2 texcoord = {};
				vec3 normal   = {};
				dynarr_at(vertices, position, vi - 1);
				dynarr_at(texcoords, texcoord, ti - 1);
				dynarr_at(normals, normal, ni - 1);

				face.vertices[i] = (model_vertex){
				    {position[0], position[1], position[2]},
				    {texcoord[0], texcoord[1]},
				    {normal[0], normal[1], normal[2]}
                };
			};
			// Push model vertex to list
			dynarr_add(tris, &face);			
		}
	};
	// Close file
	fclose(src);

	// Allocate memory for output data
	model_triangle* mts = malloc(tris->length * sizeof(model_triangle));
	// Place Model triangles to new memory location
	memcpy(mts, tris->data, tris->length * sizeof(model_triangle));

	*vertex_count = tris->length * 3;

	LOG_MSG("Vertex count: %lu", *vertex_count);

	// Free memory
	dynarr_release(vertices);
	dynarr_release(texcoords);
	dynarr_release(normals);
	dynarr_release(tris);

	return mts;
};

mesh_t* mesh_from_mt(model_triangle* tris,
					 size_t vertex_count)
{
	mesh_t* m = create_mesh();
	mesh_add_buffer(m, tris, sizeof(model_vertex) * 3 * vertex_count);
	mesh_add_attribute(
		m, 0, 3, sizeof(float) * 8, 0);
	mesh_add_attribute(
	    m, 0, 2, sizeof(float) * 8, offsetof(model_vertex, texcoord));
	mesh_add_attribute(
	    m, 0, 3, sizeof(float) * 8, offsetof(model_vertex, normal));
	m->vertices_count = vertex_count;
	return m;
}

entity_t entity_init(mesh_t* m, GLuint texture)
{
	return (entity_t){
	    .mesh     = m,
	    .texture  = texture,
	    .scale    = {1.0, 1.0, 1.0},
	    .poistion = {},
	    .rotation = {},
	    .color    = {1.0, 1.0, 1.0, 1.0},
	};
};

void mt_print(model_triangle* mt, size_t count)
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
