/* Copyright 2019 Google LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef THIRD_PARTY_PY_TENSORFLOW_GRAPHICS_RENDERING_OPENGL_EGL_OFFSCREEN_CONTEXT_H_
#define THIRD_PARTY_PY_TENSORFLOW_GRAPHICS_RENDERING_OPENGL_EGL_OFFSCREEN_CONTEXT_H_

#include <EGL/egl.h>

#include <memory>

static const EGLint kDefaultConfigurationAttributes[] = {
    EGL_SURFACE_TYPE,
    EGL_PBUFFER_BIT,
    EGL_RENDERABLE_TYPE,
    EGL_OPENGL_ES2_BIT,
    EGL_BLUE_SIZE,
    8,
    EGL_GREEN_SIZE,
    8,
    EGL_RED_SIZE,
    8,
    EGL_DEPTH_SIZE,
    24,
    EGL_NONE  // The array must be terminated with that value.
};

static const EGLint kDefaultContextAttributes[] = {
    EGL_CONTEXT_CLIENT_VERSION,
    2,
    EGL_NONE,
};

// EGL is an interface between OpenGL ES and the windowing system of the native
// platform. The following class provides functionality to manage an EGL
// off-screen contexts.
class EGLOffscreenContext {
 public:
  ~EGLOffscreenContext();

  // Creates an EGL display, pixel buffer surface, and context that can be used
  // for rendering.
  //
  // Arguments:
  // * pixel_buffer_width: width of the pixel buffer surface.
  // * pixel_buffer_height: height of the pixel buffer surface.
  // * context: if the method succeeds, this variable returns an object storing
  //   a valid display, context, and pixel buffer surface.
  // * configuration_attributes: attributes used to build frame buffer
  // * configurations.
  // * context_attributes: attributes used to create the EGL context.
  // * rendering_api: defines the rendering API for the current thread. The
  //     available APIs are EGL_OPENGL_API, EGL_OPENGL_ES_API, and
  //     EGL_OPENVG_API.
  //
  // Returns:
  //   A boolean set to false if any error occured during the process, and set
  //   to true otherwise.
  static bool Create(
      const int pixel_buffer_width, const int pixel_buffer_height,
      std::unique_ptr<EGLOffscreenContext>* egl_offscreen_context,
      const EGLenum rendering_api = EGL_OPENGL_API,
      const EGLint* configuration_attributes = kDefaultConfigurationAttributes,
      const EGLint* context_attributes = kDefaultContextAttributes);

  // Binds the EGL context to the current rendering thread and to the pixel
  // buffer surface. Note that this context must not be current in any other
  // thread.
  //
  // Returns:
  //   A boolean set to false if any error occured during the process, and set
  //   to true otherwise.
  bool MakeCurrent() const;

  // Un-binds the current EGL rendering context from the current rendering
  // thread and from the pixel buffer surface.
  //
  // Returns:
  //   A boolean set to false if any error occured during the process, and set
  //   to true otherwise.
  bool Release();

 private:
  EGLOffscreenContext() = delete;
  EGLOffscreenContext(EGLContext context, EGLDisplay display,
                      EGLSurface pixel_buffer_surface);
  EGLOffscreenContext(const EGLOffscreenContext&) = delete;
  EGLOffscreenContext(EGLOffscreenContext&&) = delete;
  EGLOffscreenContext& operator=(const EGLOffscreenContext&) = delete;
  EGLOffscreenContext& operator=(EGLOffscreenContext&&) = delete;

  EGLContext context_;
  EGLDisplay display_;
  EGLSurface pixel_buffer_surface_;
};

#endif  // THIRD_PARTY_PY_TENSORFLOW_GRAPHICS_RENDERING_OPENGL_EGL_OFFSCREEN_CONTEXT_H_
