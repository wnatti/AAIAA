#pragma once

#include <lodepng.h>
#include <vector>
#include <map>

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
	int height, width;
};


/**
	All assets are loaded through ResourceManager.
	Keeps track of loaded assets.
*/

//TODO: Singleton
class core::ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	
	/**
		Loads png image with given filename. 
		Uses lodepng and android assetmanager for decoding.
		Returns image struct.
	*/
	Image loadImage(std::string filename);
	//TODO:
	//loadSound()
	//loadTextFile()
	//loadFont()  

	
private:
	std::map<std::string, Image> _loadedImages;
	//TODO: container for other file types

};

