//
//  shadowMap.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-21.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef shadowMap_h
#define shadowMap_h

#include "texture.h"

class ShadowMap : public Texture
{
	int width, height;
	public:
		ShadowMap(GLenum DIMS, GLenum COLORS, int w, int h);
		virtual void init(GLuint dfbo);
	
};


#endif /* shadowMap_h */
