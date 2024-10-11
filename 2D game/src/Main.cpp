#include "core/Window_Manager.h"
#include "GL_Render/Render.h"
#include "GL_Render/Shader.h"
#include "GL_Render/Camera.h"
#include "GL_Render/Ssbo.h"

Render render;
Shader shader;
Windows window;
WindowSettings windset;
Ssbo ssbo;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::mat4 to_mat4() const
	{
		glm::mat4 m = glm::translate(glm::mat4(1.0f), position);
		m *= glm::mat4_cast(glm::quat(rotation));
		m = glm::scale(m, scale);
		return m;
	}
};

static float RandomFloat(float min, float max) {
	return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min);
}

class Player {
public:
	Player() = default;
	Transform transform;
	float speed = 10.0f;
};
Player player;

struct Enemy {
	Enemy() = default;
	Transform transform;
};

int main() 
{
	window.CreateWindow(windset.width = 1920, windset.height = 1080, "Wave shooter");
	shader.Load("vertexShader.vert","FragmentShader.frag");

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(window.glDebugOutput, nullptr);

	//Plane 1
	std::vector<Vertex> vertices =
	{
		{glm::vec3(0.5f, 0.5f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, 0.0f)}
	};

	std::vector<uint16_t> indices =
	{
		3, 1, 0,
		3, 2, 1
	};
	
	Render::Mesh mesh = render.CreateMesh(vertices, indices);
	Render::Mesh multimesh = render.CreateMultiMesh(vertices, indices);
	
	glm::vec2 cameraPosition = glm::vec2(0.0f, 0.0f);
	float aspectRatio = static_cast<float>(windset.width) / windset.height; 
	float zoom = 100.0f; 

	Camera camera(cameraPosition, aspectRatio, zoom);

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	std::vector<Enemy> enemies(10);
	for (Enemy& enemy : enemies) {
		enemy.transform.position.x = RandomFloat(-10, 10);
		enemy.transform.position.y = RandomFloat(-10, 10);
	}
	GLsizeiptr bufferSize = enemies.size() * sizeof(glm::mat4);
	ssbo.SSBObuffer(bufferSize, 0);

	std::vector<glm::mat4> enemyTransforms(enemies.size());
	for (size_t i = 0; i < enemies.size(); ++i) {
	enemyTransforms[i] = enemies[i].transform.to_mat4();
	}

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4f, 0.7f, 0.2f, 1.0f);

		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) 
		{
			double fps = double(nbFrames) / (currentTime - lastTime);
			printf("%f ms/frame | FPS: %f\n", 1000.0 / fps, fps);
			nbFrames = 0;
			lastTime = currentTime;
		}

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		window.processInput(window);

		shader.Use();
		
		glm::mat4 projectionmatrix = camera.ReturnProjection(windset.width, windset.height);
		glm::mat4 viewmatrix = camera.ReturnView();
		camera.Updatecamera(player.transform.position);

		ssbo.updateSSBO(bufferSize, enemyTransforms.data(),0);

		shader.SetMat4("Projection", projectionmatrix);
		shader.SetMat4("View",       viewmatrix);
		shader.SetMat4("Transforms", player.transform.to_mat4());
		shader.SetVec3("color",      color);

		shader.SetBool("SwitchState", false);
		render.DrawMesh(mesh.vao, indices);

		shader.SetBool("SwitchState", true);
		render.DrawMultiMesh(multimesh.vao, indices, enemies.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
	ssbo.clear();
}

void Windows::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		player.transform.position.y += player.speed * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		player.transform.position.y -= player.speed * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		player.transform.position.x -= player.speed * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		player.transform.position.x += player.speed * deltaTime;
	}
}