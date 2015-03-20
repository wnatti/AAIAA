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
	class Graphics :  public GraphicsContext, public ShaderManager, public BufferManager
	{
		friend class core::Siika2D;
		
	public:
	

	private:
		
		/**
			Create Graphics context, buffer- and shadermanagers
		*/
		Graphics(android_app* application, core::ResourceManager* resourceManager);
		~Graphics();
	};
}
