#include "project.h"
#include "engine.h"
#include "object.h"

Delegate<> Engine::onOpenGLInit;
Delegate<> Engine::onOpenGLDraw;
Delegate<> Engine::onOpenGLTerminate;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);

const static std::pair<int, int> res = { 800, 600 };

int Engine::Go()
{
	std::cout << "Initializing...\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(res.first, res.second, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// print device info
	//const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
	//const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model

	//std::cout << "OpenGL device:\n";
	//std::cout << "Vender: " << (const char*)vendor << "\n";
	//std::cout << "Renderer: " << (const char*)renderer << "\n";

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << "Initialized OpenGL...\n";
	onOpenGLInit.Broadcast();

	Mesh::Create();

	// Render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// Rendering commands here...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		onOpenGLDraw.Broadcast();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved, etc...)
		// ----------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "Terminating OpenGL...\n";
	onOpenGLTerminate.Broadcast();
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resized window! Width: " << width << " Height: " << height << "\n";
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}