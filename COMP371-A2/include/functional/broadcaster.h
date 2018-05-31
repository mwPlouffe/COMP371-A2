//
//  broadcaster.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-21.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef broadcaster_h
#define broadcaster_h

//pure virtual class
//allows any child to be interated over so that shader uniform data can be broadcast

class Broadcaster
{
	public:
		virtual void broadcast(void)=0;
		Broadcaster(void){};
};

#endif /* broadcaster_h */

