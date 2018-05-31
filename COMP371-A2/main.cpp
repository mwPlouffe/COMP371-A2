//
//  main.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-16.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "main.h"

int main(void)
{
	Window *window			= new Window("COMP371: Assignment 2: 27532733", 800, 800);
	ShaderProgram *ambient	= new ShaderProgram("./include/shaders/light.vert", "./include/shaders/light.frag");
	ShaderProgram *shadows  = new ShaderProgram("./include/shaders/shadow.vert", "./include/shaders/shadow.frag");
	Camera *camera			= new Camera (glm::vec3(0.0f,100.0f,500.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	Renderer *renderer;
	Object *teddy;
	Object *teddy1;
	Light *light;
	HeightMap *floor;
	HeightMap *wall;
	
	std::vector<GLfloat> vertices;
	for (int x = -1 * DEFAULT_WIDTH/2; x < DEFAULT_WIDTH/2; x++)
	{
		for (int y = -25; y < DEFAULT_HEIGHT - 25; y++)
		{
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(-150.0);
		}
	}
	
	try
	{
		//start up the window and register the callbacks to it (static member functions)
		window->init();
		window->registerCallbacks();
		
		//start the shaders, and enable the lighting one by default
		shadows->init();
		ambient->init();
		ambient->enable();
		
		//start the renderer engine
		renderer = new Renderer(ambient->program(),shadows->program());
		//it needs the window and camera data to start up
		renderer->init(window, camera);
		
		//add it a directionallight, and initialise it with the shader data
		light = new PointLight(0.3f, 0.4f, 0.7f, glm::vec3(1.0f,0.f,0.f), glm::vec3(0.f,100.f,0.01f), glm::vec3(1.f,0.00014f,0.000007f));
		
		light->init(ambient->program());
		//set the projection matrix to something that can be seen
		dynamic_cast<PointLight*>(light)->setProjectionMatrix(glm::ortho(-256.0f, 256.0f, -256.0f, 256.0f, -1.0f, 1000.0f));

		//add in the teddy bear
		teddy = new Object("./include/objectfiles/teddy.obj");
		teddy->init();
		teddy->uniformColour(glm::vec3(129.0/256, 70.0/256, 43.0/256));	//the bear is brown
		teddy->DRAW_MODE = GL_TRIANGLES;	//use triangles to draw the bear
		teddy->move(glm::rotate(glm::mat4(), 180.f, glm::vec3(1.0f,0.0f,1.0f)));
		teddy->move(glm::translate(glm::mat4(), glm::vec3(0.f, -10.2f, 0.f)));
		
		//add another teddy bear
		teddy1 = new Object("./include/objectfiles/teddy.obj");
		teddy1->init();
		teddy1->uniformColour(glm::vec3(129.0/256, 70.0/256, 43.0/256));	//the bear is brown
		teddy1->DRAW_MODE = GL_TRIANGLES;	//use triangles to draw the bear
		teddy1->move(glm::scale(glm::mat4(), glm::vec3(1.5f)));
		teddy1->move(glm::translate(glm::mat4(), glm::vec3(0.f, 5.f, 100.f)));
		
		//add in a plane, orient the normals
		floor = new HeightMap();
		floor->init();
		floor->orientNormals(glm::vec3(0.0f, -1.0f, 0.0f));
		floor->uniformColour(glm::vec3(1.0f));
		floor->DRAW_MODE = GL_TRIANGLES;
		
		//add in a plane that acts as the wall, then orient the normals
		wall = new HeightMap(vertices, DEFAULT_WIDTH, DEFAULT_HEIGHT);
		wall->init();
		wall->orientNormals(glm::vec3(0.0f,0.0f,-1.0f));
		wall->uniformColour(glm::vec3(1.0f));
		wall->DRAW_MODE = GL_TRIANGLES;
		
		//bind them to the renderer so that they can be drawn
		renderer->bind(teddy, GL_STATIC_DRAW, "teddy");
		renderer->bind(teddy1, GL_STATIC_DRAW, "teddy1");
		renderer->bind(floor, GL_STATIC_DRAW, "floor");
		renderer->bind(wall, GL_STATIC_DRAW, "wall");
		renderer->bind(dynamic_cast<Object*>(light), GL_STATIC_DRAW, "light");
		renderer->bindAxis();
		
		//register the broadcasters with the renderer so that they can send the needed data to the shaders
		renderer->registerBroadcaster(camera, "camera");
		renderer->registerBroadcaster(light, "light");
	}
	catch(GLFWException &ex)
	{
		std::cout << "ERROR: " << ex.what() << std::endl;
		return -1;
	}
	catch(GLException &ex)
	{
		std::cout << "ERROR: " << ex.what() << std::endl;
		return -1;
	}
	glPointSize(24);
	bool isMovingLight = false;
	bool isPressed[3] = {false,false,false};
	while (! window->closed())
	{
		//toggles the control authority between the camera and the light on a button press, handles held down presses with an additional flag
		if (glfwGetKey(window->glWindow(), GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS && isPressed[0] == false)
		{
			isMovingLight = !isMovingLight;
			isPressed[0] = true;
		}
		//untoggles when the key is release
		if (glfwGetKey(window->glWindow(), GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE && isPressed[0] == true)
		{
			isPressed[0] = false;
		}
		//adjusts the bias, hold down to decrease
		if (glfwGetKey(window->glWindow(), GLFW_KEY_MINUS) == GLFW_PRESS || isPressed[1] == true)
		{
			renderer->updateBias(-0.0005);
			isPressed[1] = true;
		}
		//check for the button not being pressed anymore
		if (glfwGetKey(window->glWindow(), GLFW_KEY_MINUS) == GLFW_RELEASE)
		{
			isPressed[1] = false;
		}
		//adjusts the bias, hold down to increase
		if (glfwGetKey(window->glWindow(), GLFW_KEY_EQUAL) == GLFW_PRESS || isPressed[2] == true)
		{
			renderer->updateBias(0.0005);
			isPressed[2] = true;
		}
		//check that the button is no longer pressed so that the bias updates stop
		if (glfwGetKey(window->glWindow(), GLFW_KEY_EQUAL) == GLFW_RELEASE)
		{
			isPressed[2] = false;
		}
		
		if (isMovingLight == true)
		{
			dynamic_cast<PointLight*>(light)->update(window->keyPressed);
		}
		else
		{
			renderer->transformViewMatrix(camera->update(window->keyPressed) );
		}
			//tell the object to move in the scene by the specified transformation
			teddy->move( glm::rotate(glm::mat4(), 0.1f, glm::vec3(0.f,0.01f,0.f))  );
			
			renderer->render();
			renderer->update(window);
	}
	free(wall);
	free(floor);
	free(camera);
	free(light);
	free(window);
	
	free(teddy1);
	free(teddy);
	free(ambient);
	free(shadows);
	free(renderer);
}
