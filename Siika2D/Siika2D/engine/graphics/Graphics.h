#pragma once
#include "../core/ResourceManager.h"
#include "GraphicsContext.h"
#include "BufferManager.h"
#include "ShaderManager.h"

namespace core
{
	class Siika2D;
}

namespace graphics
{
	class Graphics
	{
		friend class core::Siika2D;
		
	public:
		void swap();
		void clear();

	private:
		Graphics();
		~Graphics();
		void initializeGraphics(core::ResourceManager *resourceManager);
		void wipeContext();
		graphics::ShaderManager *_shaderManager;
		graphics::GraphicsContext _graphicsContext;
		graphics::BufferManager _buffManager;
	};
}
