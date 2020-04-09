#include "Application.hpp"

Application::Application()
{
}

void Application::run()
{
	mainWindow = Window(800, 600);
	mainWindow.init();

	std::vector<unsigned int> indices = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	std::vector <Vertex> vertices = {
		{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(0.0f, -1.0f, 1.0f),  glm::vec2(0.5f, 0.0f)},
		{glm::vec3(1.0f, -1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.5f, 1.0f)}
	};

	auto obj1 = std::make_unique<Mesh>(vertices, indices);
	meshList.push_back(std::move(obj1));

	auto obj2 = std::make_unique<Mesh>(vertices, indices);
	meshList.push_back(std::move(obj2));

	shader.createFromFiles(vShader, fShader);
	shaderList.push_back(shader);

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);

	metalTexture = Texture("Textures/metal.png");
	metalTexture.load();

	mainLight = Light(1.0f, 1.0f, 1.0f, 1.0f);

	update();
}

void Application::update()
{
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GLuint uniformAmbientIntensity = 0, uniformAmbientColour = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;
	while (!mainWindow.getShouldColse())
	{
		GLfloat currentTime = glfwGetTime(); 
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();
		camera.keyControl(mainWindow, deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].use();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectionLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformAmbientColour = shaderList[0].getAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].getAmbientIntensityLocation();

		mainLight.use(uniformAmbientIntensity, uniformAmbientColour);
		
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		metalTexture.use();
		meshList[0]->render();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		model = glm::rotate(model, 180 * TO_RADIANS, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->render();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
}

Application::~Application()
{
}
