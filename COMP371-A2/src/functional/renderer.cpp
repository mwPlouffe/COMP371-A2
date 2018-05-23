#include "renderer.h"

//this class renders by Object or by vao
//it is the "driving force" behind this assignment

Renderer::Renderer(GLuint shader, GLuint shadowShader)
{
	shaderID = shader;
	shadowShaderID = shadowShader;
}
void Renderer::init(Window::Window *w, Camera *c)
{
	std::cout << "MESSAGE: Starting renderer initialisation" << std::endl;
	//set the view, model, and projection matrices
	setContextSize(w);
	viewMatrix = c->init(this->shaderID);
	perspectiveMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)contextWidth / (GLfloat)contextHeight, 0.1f, 500.0f);
	
	modelMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f));
	
	//find the corresponding uniforms in the shaders
	modelFrameID = glGetUniformLocation(shaderID, "model_matrix");
	viewFrameID = glGetUniformLocation(shaderID, "view_matrix");
	perspectiveFrameID = glGetUniformLocation(shaderID, "projection_matrix");
	if (modelFrameID == -1 || viewFrameID == -1 || perspectiveFrameID == -1)
	{
		throw GLException("Renderer::init -> Could not locate Shader attribute(s). Shaders are not correctly linked.");
	}
	//although this instance is a broadcaster, we can simply broadcast its data using its own broadcast method, no need to register it
	
	
	setDepthTesting();
	std::cout << "MESSAGE: Renderer initialised Successfully" << std::endl;
}
void  Renderer::broadcast(void)
{
	//broadcast all the registered uniforms to the shader
	//done for each class that can broadcast data
	std::map<std::string, Broadcaster*>::iterator i;
	for (i = broadcasters.begin(); i != broadcasters.end(); i++)
	{
		i->second->broadcast();
	}
	//broadcast (read re-load to the GPU) the new data to the shaders
	glUniformMatrix4fv(modelFrameID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(perspectiveFrameID, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUniformMatrix4fv(viewFrameID,1,GL_FALSE,glm::value_ptr(viewMatrix));
}
void Renderer::update(Window *w)
{
	//render the contents stored in the buffer
	//10 is the boolean value associated with the shadow debug key
	broadcast();

	glfwSwapBuffers(w->glWindow());
	
	//check if there are any events to process
	glfwPollEvents();
}
void Renderer::setContextSize(Window::Window *w)
{
	//return the size of the frame buffer
	glfwGetFramebufferSize(w->glWindow(), &contextWidth, &contextHeight);
}
void Renderer::clear() const
{
	//clears the colour buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void Renderer::setDepthTesting(void)
{
	//enables depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
void Renderer::clearContext()
{
	//unbinds any currently bound VAO
	glBindVertexArray(0);
}
void Renderer::bindSquare(void)
{
	
	//hard-coded vertices to create a square from 3 triangles
	std::vector<GLfloat> vertices =
	{
		0.0f, 0.0f, -5.0f,
		0.0f, 1.0f, -5.0f,
		1.0f, 1.0f, -5.0f,
		1.0f, 0.0f, -5.0f
	};
	
	//the indices needed to properly render that shader
	std::vector<GLuint> indices =
	{
		3,2,1,
		1,0,3
	};
	std::vector<GLfloat> colours =
	{
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
	};
	Object *ret = new Object(vertices, indices, colours);
	ret->init();
	ret->DRAW_MODE = GL_TRIANGLES;
	bind(ret, GL_STATIC_DRAW, "square");
	std::cout << "MESSAGE: Renderer::bindSquare Successful" << std::endl;
}
void Renderer::bindCube(void)
{
	std::cout << "MESSAGE: Renderer::bindCube Successfully" << std::endl;
	std::vector<GLfloat> vertices =
	{
		//front vertices
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		
		//back vertices
		0.0f, 0.0f,	 1.0f,
		0.0f, 1.0f,	 1.0f,
		1.0f, 1.0f,  1.0f,
		1.0f, 0.0f,	 1.0f,
	};
	
	std::vector<GLuint> indices =
	{
		//front face
		3,2,1,
		1,0,3,
		//back face
		7,6,5,
		5,4,7,
		//left face
		2,6,5,
		5,1,2,
		//right face
		0,4,7,
		7,3,0,
		//top face
		7,6,2,
		2,3,7,
		//bottom face
		0,1,5,
		5,4,0,
	};
	
	std::vector<GLfloat> colours =
	{
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
	};
	Object *ret = new Object(vertices, indices, colours);
	ret->init();
	ret->DRAW_MODE = GL_TRIANGLES;
	bind(ret, GL_STATIC_DRAW, "cube");
	std::cout << "MESSAGE: Renderer::bindCube Successful" << std::endl;
}
void Renderer::bindAxis(void)
{
	std::vector <GLfloat> vertices =
	{
			-3.0f, 4.0f, -3.0f,
			-2.0f, 4.0f, -3.0f,
			-3.0f, 5.0f, -3.0f,
			-3.0f, 4.0f, -2.0f
	};
	//render as edges specifically
	std::vector<GLuint> indices =
	{
		0,1,
		0,2,
		0,3
	};
	
	std::vector<GLfloat> colours =
	{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f
	};
	
	Object *ret = new Object(vertices, indices, colours);
	ret->init();
	ret->DRAW_MODE = GL_LINES;
	bind(ret, GL_STATIC_DRAW, "axis");
	std::cout << "MESSAGE: Renderer::bindAxis Successful\n\tYellow = +y-axis\n\tGreen  = +x-axis" << std::endl;
}
void Renderer::draw(void)
{
	std::map<std::string, Object*>::iterator i;
	
	for (i = objectList.begin(); i != objectList.end(); i++)
	{
		drawElements(i->second->vao, i->second->DRAW_MODE, i->second->indexSize());
	}
}
void Renderer::drawArrays(GLuint vao, GLenum DRAW_TYPE, int vertexCount)
{
	//draw using the vertex ordering
	glBindVertexArray(vao);
	glDrawArrays(DRAW_TYPE, 0, vertexCount);
	clearContext();
}
void Renderer::drawElements(GLuint vao, GLenum DRAW_TYPE, int indexCount)
{
	//draw using an ibo
	glBindVertexArray(vao);
	glDrawElements(DRAW_TYPE, indexCount, GL_UNSIGNED_INT, nullptr);
	clearContext();
}
void Renderer::bind(Object *obj,GLenum DRAW_TYPE, std::string identifier)
{
	if (objectList.find(identifier) != objectList.end())
	{
		std::cout << "WARNING: Non-unique identifier \"" << identifier << "\". This could result in unusual behaviour" << std::endl;
	}

	//sends the data from a renderable object the the GPU
	GLuint vao, vbo, ibo, nbo, cbo;
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, obj->vertexSize() * sizeof(GLfloat), &(obj->vertexList())[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	glGenBuffers(1,&nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, obj->normalSize() * sizeof(GLfloat), &(obj->normalList())[0], GL_STATIC_DRAW);
		
	//this location must be different than the one used for the vertices
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1,&cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, obj->colourSize() * sizeof(GLfloat), &(obj->colourList())[0], GL_STATIC_DRAW);
	
	//this location must be different than the one used for the vertices and the normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	
	glGenBuffers(1,&ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->indexSize() * sizeof(GLuint), &(obj->pointIndex())[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	//instead of returning the vao, the object stores the vao its data is bound to
	std::cout << "\tMESSAGE: Renderer::bind Successful" << std::endl;
	obj->vao = vao;
	objectList[identifier] = obj;
	std::cout << "\tMESSAGE: Object \"" << identifier << "\" Registered Successfully" << std::endl;
}
void Renderer::bindTexture(std::string key, Texture *tex)
{
	//generate a vbo for the texture coordinates
	//TODO
}
void Renderer::transformViewMatrix(glm::mat4 transform)
{
	//transform the view matrix
	viewMatrix = transform * viewMatrix;
}
void Renderer::transformModelMatrix(glm::mat4 transform)
{
	//transform the model matrix
	modelMatrix = transform * modelMatrix;
}
void Renderer::transformProjectionMatrix(glm::mat4 transform)
{
	//transform the perspective matrix
	perspectiveMatrix = transform * perspectiveMatrix;
}
void Renderer::registerBroadcaster(Broadcaster *b, std::string identifier)
{
	
	if (broadcasters.find(identifier) != broadcasters.end())
	{
		std::cout << "WARNING: Non-unique identifier \"" << identifier << "\". This could result in unusual behaviour" << std::endl;
	}
	
	broadcasters[identifier] = b;
	std::cout << "\tMESSAGE: Broadcaster Registered \"" << identifier << "\"" << std::endl;
}
ShadowMap& Renderer::genShadowMap(void)
{
	GLuint dfbo;
	glGenFramebuffers(1, &dfbo);
	glBindFramebuffer(GL_FRAMEBUFFER, dfbo);
	//create the shadow map and bind it to the frame buffer
	ShadowMap *sm = new ShadowMap(GL_TEXTURE_2D, GL_DEPTH_COMPONENT, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);
	sm->init(dfbo);
	glBindFramebuffer(GL_FRAMEBUFFER, dfbo);
	//now set the viewport to the size of the texture
	glViewport(0, 0, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);
	
	//now let's generate that depth map
	
	glClear(GL_DEPTH_BUFFER_BIT);
	
	//we need a special broadcast method here for the light-modelspace-transform
	
	//we need to get the light from the 
	PointLight *light;
	if ( broadcasters.find("light") == broadcasters.end())
	{
		std::cout << "WARNING: No lights found, cannot generate shadows" <<std::endl;
		return *sm;
	}
	
	glUseProgram(shadowShaderID);
	light = dynamic_cast<PointLight*>(broadcasters.find("light")->second);
	
	GLuint lightViewID, lightProjectionID, lightModelID;
	
	lightViewID = glGetUniformLocation(shadowShaderID,"light_view_matrix");
	lightProjectionID = glGetUniformLocation(shadowShaderID, "light_projection_matrix");
	lightModelID = glGetUniformLocation(shadowShaderID, "light_model_matrix");
	
	if (lightViewID == -1 || lightProjectionID == -1 || lightModelID == -1)
	{
		throw GLException("ERROR: There was an unexpected problem initialising the shadowing shader matrices");
	}
	
	glUniformMatrix4fv(lightViewID, 1, GL_FALSE,
					   glm::value_ptr(glm::lookAt(light->location(), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f))));
	
	glUniformMatrix4fv(lightProjectionID, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	
	
	glUniformMatrix4fv(lightModelID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	glBindFramebuffer(GL_FRAMEBUFFER, dfbo);
	glBindTexture(GL_TEXTURE_2D, sm->tex);
	this->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glDeleteFramebuffers(GL_FRAMEBUFFER, &dfbo);
	return *sm;
	
	//memory leak in here caused by continually generating new shadowmaps and frame buffers for the GPU to deal with
}
void Renderer::render(void)
{
	ShadowMap map = genShadowMap();
	glViewport(0, 0, contextWidth, contextHeight);
	this->clear();
	glUseProgram(shaderID);
	broadcast();
	glBindTexture(GL_TEXTURE_2D, map.tex);
	GLuint tex = glGetUniformLocation(shaderID, "shadow_map");
	GLuint lightViewID = glGetUniformLocation(shaderID,"light_view_matrix");
	GLuint lightProjectionID = glGetUniformLocation(shaderID, "light_projection_matrix");
	
	if (tex == -1 || lightProjectionID == -1 || lightViewID == -1)
	{
		//throw GLException("ERROR: The shadow Map could not be found in the shaders. Exiting");
		std::cout << "ERROR: The shadow Map could not be found in the shaders."  << std::endl;
	}
	PointLight *light;
	if ( broadcasters.find("light") == broadcasters.end())
	{
		std::cout << "WARNING: No lights found, cannot generate shadows" <<std::endl;
		return;
	}
	light = dynamic_cast<PointLight*>(broadcasters.find("light")->second);
	
	glUniform1i(tex,map.tex);
	glm::mat4 lightViewMat = glm::lookAt(light->location(), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f));
	
	glUniformMatrix4fv(lightViewID, 1, GL_FALSE,
					   glm::value_ptr(lightViewMat));
	
	glUniformMatrix4fv(lightProjectionID, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	draw();
	glDeleteTextures(1, &(map.tex));
	
	//memory leak in here caused by not deleting the textures after completion
}




