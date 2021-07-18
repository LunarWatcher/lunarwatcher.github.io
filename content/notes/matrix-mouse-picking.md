---
title: Matrix mouse picking
tags: ["c++", "mouse picking", "opengl"]
date: 2021-07-18T11:42:36+02:00
category: "Note"
---

`glm::unProject` is a fucking lifesaver.

For it to work properly, `GL_DEPTH_TEST` has to be enabled. This allows `glGetPixels()` to return a value != 1 for `GL_DEPTH_COMPONENT`, which is necessary to unproject the correct coordinates.

The documentation for `unProject` is trash. It claims the second parameter is a model-view matrix (`model * view`, or as I like to call it, `transMatrix * camMatrix`), or just a model matrix. Obligatory reminder that the model matrix is primarily used to transform the position of an _object_, which doesn't really matter.

Secondly, common pitfall (thank you compsci - how many coord systems do you possibly need for computer graphics?), this OpenGL call takes the window coordinates, which are relative to the bottom-left corner. Not the top-right, not [-1, 1] relative to the center of the window. The Z is also critical, which is why `GL_DEPTH_TEST` is needed. This also requires clearing `GL_DEPTH_BUFFER_BIT`, or shit breaks.

The coordinate system being weird means that the dimensions of the window need to be known. This can be found with `glViewport`, but storing what the window is created with is a better and more optimized idea. The dimensions are required for `glm::unProject` anyway.

Overly documented code (MIT-licensed; see the Genesis repo for the license):

```cpp
// This method can be called directly from the mouse event listener.
glm::vec2 Camera::convertToWorld(double mouseX, double mouseY) {
    // Pre-declaration of the variable used for glReadPixels
    GLfloat z;

    // these might be useless. Could probably get away with mouseY = 576 - mouseY
    // 576 is the height of the window
    GLfloat x = mouseX,
          y = 576 - mouseY;

    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

    return glm::vec2{
        glm::unProject(
            glm::vec3{
                x, // The x position. Again, in screen coordinates relative to the bottom-left, not OpenGL coords
                y, // The y position. Same as the x position
                z // The z-position, as received from glReadPixels.
            },
            this->matrix, // Horribly named, but this is the camera matrix. It's created with glm::lookAt
                          // in my project, but this is a many ways to rome-situation.
                          // As long as it's the matrix used to represent the translation and rotation of
                          // the camera, that's all you need.
                          // Like I mentioned earlier, no need for a model matrix - only a camera
                          // matrix.
            this->perspectiveMatrix, // The perspective matrix. May also be an ortho matrix or another form
                                     // of perspective matrix.
            glm::vec4{0, 0, // I have no idea what these two numbers mean.
                1024.0, // width
                576.0} // height
        )
    };
}
```

As a side-note, I imagine this is only useful if there isn't a 1:1 world matrix. In Genesis, I use an ortho matrix for text rendering, and it (should) use the same dimensions as the screen. If the UI uses coords that match the window size, there's no need to unproject to do collision testing.

Adding UI handling is potentially done without converting to world coordinates. I'll have to revisit this at a later time.

The live and updated version is available in the repo for [Genesis](https://github.com/LunarWatcher/Genesis/blob/master/src/genesis/rendering/view/Camera.cpp) (`Camera.cpp`, `convertToWorld(double mouseX, double mouseY)`)
