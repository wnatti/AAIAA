#include "ResourceManager.h"

namespace core
{
	ResourceManager::ResourceManager(AAssetManager* aAssetManager)
	{
		_errorHandler = ErrorHandler::getInstance();
		_androidAssetManager = aAssetManager;
	}

	ResourceManager::~ResourceManager()
	{

	}

	Image ResourceManager::loadImage(std::string filename)
	{
		Image loadedImage;

		AAsset* asset = nullptr;
		asset = AAssetManager_open(_androidAssetManager, filename.c_str(), 0);

		_errorHandler->checkForError(asset == nullptr, __LINE__, __FILE__, "Failed to android load asset");

		unsigned int assetLength = AAsset_getLength(asset);
		std::vector<unsigned char> assetData;
		AAsset_read(asset, assetData.data(), assetLength);

		AAsset_close(asset);

		unsigned error = lodepng::decode(loadedImage.data, loadedImage.width, loadedImage.height, assetData);

		_errorHandler->checkForError(error, __LINE__, __FILE__, "lodepng failed to decode image");

		return loadedImage;
	}

	std::string ResourceManager::loadTextFile(std::string filename)
	{
		AAsset* asset = nullptr;
		asset = AAssetManager_open(_androidAssetManager, filename.c_str(), 0);

		unsigned int assetLength = AAsset_getLength(asset);

		std::vector<unsigned char> assetData;

		AAsset_read(asset, assetData.data(), assetLength);

		return std::string(assetData.begin(), assetData.end());
	}
}