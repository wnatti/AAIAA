#include "ResourceManager.h"

namespace core
{
	ResourceManager::ResourceManager(AAssetManager* aAssetManager)
	{
		_androidAssetManager = aAssetManager;
	}

	ResourceManager::~ResourceManager()
	{

	}

	Image ResourceManager::loadImage(std::string filename)
	{
		Image loadedImage;

		std::vector<unsigned char> assetData = loadAsset(filename);

		unsigned error = lodepng::decode(loadedImage.data, loadedImage.width, loadedImage.height, assetData);

		s2d_assert(error, __FILE__, __LINE__);

		_loadedImages.insert(std::make_pair(filename, loadedImage));

		return loadedImage;
	}

	std::string ResourceManager::loadTextFile(std::string filename)
	{
		std::vector<unsigned char> assetData = loadAsset(filename);

		std::string loadedText(assetData.begin(), assetData.end());

		_loadedTextFiles.insert(std::make_pair(filename, loadedText));

		return loadedText;
	}

	std::vector<unsigned char> ResourceManager::loadAsset(std::string filename)
	{
		std::vector<unsigned char> assetData;

		AAsset* asset = nullptr;
		asset = AAssetManager_open(_androidAssetManager, filename.c_str(), 0);

		s2d_assert((asset == nullptr), __FILE__, __LINE__);

		unsigned int assetLength = AAsset_getLength(asset);
		AAsset_read(asset, assetData.data(), assetLength);

		AAsset_close(asset);

		return assetData;
	}
}