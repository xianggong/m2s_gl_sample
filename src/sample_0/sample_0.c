#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define WINDOW_TITLE_PREFIX "test-shader"


int current_width = 800;
int current_height = 600;
int window_handle = 0;

int frame_count;

GLuint vertex_shader_id;
GLuint fragment_shader_id;
GLuint program_id;
GLuint vao_id;
GLuint vbo_id;
GLuint color_buffer_id;
GLuint tf_buffer_id;

const GLchar *vertex_shader =
	"#version 130\n"

	"layout(location=0) in vec4 in_Position;\n"
	"layout(location=1) in vec4 in_Color;\n"
	"out vec4 ex_Color;\n"

	"void main(void)\n"
	"{\n"
	"	gl_Position = in_Position;\n"
	"	ex_Color = in_Color;\n"
	"}\n";


const GLchar *fragment_shader =
	"#version 130\n"

	"in vec4 ex_Color;\n"
	"out vec4 out_Color;\n"

	"void main(void)\n"
	"{\n"
	"	out_Color = ex_Color;\n"
	"}\n";


void initialize(int argc, char* argv[]);
void init_window(int argc, char **argv);
void resize_function(int Width, int Height);
void render_function(void);
void idle_function();
void timer_function(int value);
void cleanup_function(void);
void create_vbo(void);
void destroy_vbo(void);
void create_shaders(void);
void destroy_shaders(void);

int main (int argc, char* argv[])
{
	initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void initialize(int argc, char* argv[])
{
	GLenum GlewInitResult;

	/* GLUT */
	init_window(argc, argv);

	/* GLEW */
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK)
	{
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(1);
	}

	/* OpenGL information */
	printf("INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	create_shaders();
	create_vbo();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void init_window(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
			GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(current_width, current_height);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	window_handle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if (window_handle < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(resize_function);
	glutDisplayFunc(render_function);
	glutIdleFunc(idle_function);
	glutTimerFunc(0, timer_function, 0);
	glutCloseFunc(cleanup_function);

}

void resize_function(int Width, int Height)
{
	current_width = Width;
	current_height = Height;
	glViewport(0, 0, current_width, current_height);
}

void render_function(void)
{
	/* New frame */
	frame_count++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tf_buffer_id);

	glEnable(GL_RASTERIZER_DISCARD);
	glBeginTransformFeedback(GL_TRIANGLES);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	glEndTransformFeedback();
	glDisable(GL_RASTERIZER_DISCARD);

	glBindBuffer(GL_ARRAY_BUFFER, tf_buffer_id);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tf_buffer_id);

	float *pos = (float *)glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_WRITE);

	int i;
	if (pos != NULL)
	{
		for (i = 0; i < 3; ++i)
		{
			printf("Vertex #%d\n", i);
			printf("    Color: \t%f %f %f %f\n", pos[8 * i], pos[8 * i + 1], pos[8 * i + 2], pos[8 * i + 3]);
			printf("    Pos: \t%f %f %f %f\n", pos[8 * i + 4], pos[8 * i + 5], pos[8 * i + 6], pos[8 * i + 7]);
		}
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void idle_function()
{
	glutPostRedisplay();
}

void timer_function(int value)
{
	if (value)
	{
		char *s = malloc(512 + strlen(WINDOW_TITLE_PREFIX));
		sprintf(s, "%s: %d FPS @ %d x %d",
			WINDOW_TITLE_PREFIX, frame_count * 4,
			current_width, current_height);

		glutSetWindowTitle(s);
		free(s);
	}

	frame_count = 0;
	glutTimerFunc(250, timer_function, 1);
}

void cleanup_function(void)
{
	destroy_shaders();
	destroy_vbo();
}

void create_vbo(void)
{
	GLfloat vertices[] = {
		-0.8f, -0.8f, 0.0f, 1.0f,
		0.0f, 0.8f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f, 1.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	GLenum error_check_value = glGetError();

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &color_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &tf_buffer_id);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tf_buffer_id);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STREAM_DRAW);

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		fprintf(stderr, "error: could not create VBO: %s\n",
				gluErrorString(error_check_value));
		exit(1);
	}
}

void destroy_vbo(void)
{
	GLenum error_check_value = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &color_buffer_id);
	glDeleteBuffers(1, &vbo_id);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao_id);

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		fprintf(stderr, "error: could not create VBO: %s\n",
				gluErrorString(error_check_value));
		exit(1);
	}

}

void create_shaders(void)
{
	GLenum error_check_value = glGetError();

	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_shader, NULL);
	glCompileShader(vertex_shader_id);

	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_shader, NULL);
	glCompileShader(fragment_shader_id);

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);

	const char* varyings[2] = { "ex_Color", "gl_Position" };
	glTransformFeedbackVaryings(program_id, 2, varyings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(program_id);
	glUseProgram(program_id);

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		fprintf(stderr, "error: %s: %s\n",
				__FUNCTION__,
				gluErrorString(error_check_value));
		exit(1);
	}
}


void destroy_shaders(void)
{
	GLenum error_check_value = glGetError();

	glUseProgram(0);

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(fragment_shader_id);
	glDeleteShader(vertex_shader_id);

	glDeleteProgram(program_id);

	error_check_value = glGetError();
	if (error_check_value != GL_NO_ERROR)
	{
		fprintf(stderr, "error: %s: %s\n",
				__FUNCTION__,
				gluErrorString(error_check_value));
		exit(1);
	}
}

