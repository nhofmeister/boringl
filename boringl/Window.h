//
//  Window.h
//  boringl
//
//  Created by Nils Hofmeister on 06/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#ifndef __boringl__Window__
#define __boringl__Window__

class Window
{
public:
    Window();
    virtual ~Window();
    int getWindow() const { return m_windowID; }
    
private:
    void init();
    int m_windowID;
};

#endif /* defined(__boringl__Window__) */
