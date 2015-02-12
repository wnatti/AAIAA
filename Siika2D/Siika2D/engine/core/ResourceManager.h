#pragma once

#include <lodepng.h>
#include <vector>
#include <map>
#include <android/asset_manager.h>

#include "ErrorHandler.h"

namespace core
{
	class ResourceManager;
	struct Image;
}

/**
	Struct for storing image data, height and width.
*/
struct core::Image
{
	std::vector<unsigned char> data;
	unsigned int height, width;
};


/**
	All assets are loaded through ResourceManager.
	Keeps track of loaded assets.
*/

//TODO: Singleton
class core::ResourceManager
{
public:
	ResourceManager(AAssetManager* aAssetManager);
	~ResourceManager();
	
	/**
		Loads png image with given filename. 
		Uses lodepng and android assetmanager for decoding.
		Returns image struct.
	*/
	Image loadImage(std::string filename);

	/**
		Loads text file with given filename.
		Uses android assetmanager.
		Returns text from file as a std::string
	*/
	std::string loadTextFile(std::string filename);
	//TODO:
	//loadSound()
	//loadFont()  

	
private:
	std::map<std::string, Image> _loadedImages;
	ErrorHandler* _errorHandler;
	AAssetManager* _androidAssetManager;
	//TODO: container for other file types

};
