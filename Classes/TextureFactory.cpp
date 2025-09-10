#include "TextureFactory.h"
Texture2D* TextureFactory::Create(std::string filepath)
{

	Image* image = new Image;//이미지를 만듬
	image->initWithImageFile(filepath);

	Texture2D* texture =new Texture2D;//이미지로 Texture2D를 만듬
	texture->initWithImage(image);

	return texture;

}
