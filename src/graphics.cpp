#include "graphics.h"

#include "SDL.h"

#include "GL/glew.h"

#include "logger.h"

using namespace graphics;

GraphicsBase::GraphicsBase(const core::Config & config)
{
	// Create window with these attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4); 
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetSwapInterval(config.GetVerticalSync());

	window_ = SDL_CreateWindow(config.GetWindowTitle().c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		config.GetWindowWidth(),
		config.GetWindowHeight(),
		SDL_WINDOW_OPENGL);

	if (!window_)
	{
		core::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
	}

	// Create GL context

	context_ = SDL_GL_CreateContext(window_);

	if (!context_)
	{
		SDL_DestroyWindow(window_);

		core::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
	}

	// Make the GL context current to load extensions

	if (SDL_GL_MakeCurrent(window_, context_))
	{
		SDL_GL_DeleteContext(context_);
		SDL_DestroyWindow(window_);

		core::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
	}

	// Get rid of "no context set as current" error

	SDL_ClearError();

	// Load GL extensions

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_GL_DeleteContext(context_);
		SDL_DestroyWindow(window_);

		core::Log(SDL_LOG_PRIORITY_CRITICAL, SDL_LOG_CATEGORY_VIDEO, "Could not load GL extensions.");
	}

	window_width_ = config.GetWindowWidth();
	window_height_ = config.GetWindowHeight();

	camera_ = std::make_unique<OrthographicCamera>("Orthographic",
		glm::vec3(1.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}  
 
GraphicsBase::~GraphicsBase()
{
	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window_);
}

glm::vec2 GraphicsBase::PixelsToScaleAspect(const glm::uvec2 &pixels) const
{
	return glm::vec2(float(pixels.x) / window_width_,
		GetAspectRatio() * float(pixels.y) / window_height_);
}

glm::vec2 GraphicsBase::PixelsToScale(const glm::uvec2 &pixels) const
{
	return glm::vec2(float(pixels.x) / window_width_, float(pixels.y) / window_height_);
}