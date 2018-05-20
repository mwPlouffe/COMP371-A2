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
	ShaderProgram *ambient	= new ShaderProgram("./include/shaders/shadow.vert", "./include/shaders/shadow.frag");
	Camera *camera			= new Camera (glm::vec3(0.0f,0.0f,-25.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	Renderer *renderer;
	PointLight *light = new PointLight();
	Object *test;

	
	
	
	try
	{
		window->init();
		window->registerCallbacks();
		
		ambient->init();
		ambient->enable();
		
		renderer = new Renderer(ambient->program());
		renderer->init(window, camera);
		
		camera->init(ambient->program());
		
		light->init(ambient->program());
		
		test = new Object("./include/objectfiles/teapot.obj");
		//test->pointIndex();
		test->uniformColour();
		test->init();
		
	}
	catch(GLFWException &ex)
	{
		std::cout << "ERROR: " << ex.what() << std::endl;
		return -1;
	}
	catch(GLException &ex)
	{
		std::cout << "ERROR: " << ex.what() << std::endl;
		//return -1;
	}
	renderer->bind(light, GL_STATIC_DRAW);
	glPointSize(24);
	renderer->bind(test, GL_STATIC_DRAW);
	GLuint vao = renderer->bindCube();
	while (! window->closed())
	{
		renderer->clear();
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		
		renderer->drawElements(light->vao, GL_POINTS, light->indexSize());
		renderer->drawElements(test->vao, GL_TRIANGLES, test->indexSize());
		renderer->drawElements(vao, GL_TRIANGLES, 48);
		renderer->transformModelMatrix( camera->updateModel(window->keyPressed) );
		camera->broadcast();
		light->broadcast();
		renderer->update(window);
		
	}
	
	
	
	/* shadows are working (provisionally, I think that my low polygon cube is having weird shading effects, simply by there being fewer vertices to use)
	 TODO: implement the object-loader and load in some models to test
	 TODO: implement the shadowing mapping
			-requires textures
			-requires framebuffers
	 */

}
