//
//  renderer.h
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-14.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef renderer_h
#define renderer_h

#include <vector>
#include <map>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "window.h"
#include "object.h"
#include "camera.h"
#include "texture.h"
#include "broadcaster.h"
#include "shadowMap.h"
#include "pointLight.h"
#include "directionalLight.h"

#define SHADOW_BUFFER_WIDTH		1024
#define SHADOW_BUFFER_HEIGHT	1024

//heart and soul of the engine
//keeps track of the MVP state, shaders, meshes and broadcasters
//renders or draws meshes to screen, updates scree etc..

class Renderer : public Broadcaster
{
private:
	GLuint modelFrameID, perspectiveFrameID, viewFrameID, shaderID, shadowShaderID;
	glm::mat4 viewMatrix, perspectiveMatrix, modelMatrix;
	int contextWidth, contextHeight;
	std::map<std::string, Object*> objectList;
	std::map<std::string, Broadcaster*> broadcasters;
	ShadowMap *shadowMap;
public:
	Renderer(GLuint shader, GLuint shadowShader);
	void init(Window::Window *w, Camera *c);
	
	void registerBroadcaster(Broadcaster *b, std::string identifier);
	
	virtual void broadcast(void);
	void update(Window *w);
	void clear(void) const;
	
	void bind(Object *obj,GLenum DRAW_TYPE, std::string identifier);
	void bindSquare(void);
	void bindCube(void);
	void bindAxis(void);
	void bindTexture(std::string key, Texture *tex);
	Object findObject(std::string identifier);
	
	void draw(GLuint shaderID);
	void drawArrays(GLuint vao, GLenum DRAW_TYPE, int shapeCount);
	void drawElements(GLuint vao, GLenum DRAW_TYPE, int indexCount);
	void render(void);
	void updateBias(float value);
	
	void transformViewMatrix(glm::mat4 transform);
	void transformModelMatrix(glm::mat4 transform);
	void transformProjectionMatrix(glm::mat4 transform);
	
private:
	void clearContext(void);
	void setContextSize(Window::Window *w);
	void setDepthTesting(void);
	void genShadowMap(void);
	std::vector<glm::vec3> frustrumPoints(void);
	
};

#endif /* renderer_h */
