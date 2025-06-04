#include <string>
#include <stdio.h>

#include <OgreResourceGroupManager.h>
#include <OgreTextureManager.h>
#include <OgreImage.h>
#include <OgreDataStream.h>
#include <fstream>
// Ogre image loader.. needs to be renamed.
class internal_image {
public:
	size_t height;
	size_t width;
	Ogre::Image img;
	std::string f_name;
	unsigned char byteCount;
	
	internal_image(std::string &filename) { load_image(filename); f_name = filename; }
	internal_image() { }
	internal_image(const internal_image &other) { f_name=other.f_name; load_image(f_name); }
	~internal_image() { }

	bool load_image(std::string &filename, std::string texture_name = "heightmap")
	{
	  
	  
	  bool image_loaded = false; 
	  std::ifstream ifs(filename.c_str(), std::ios::binary|std::ios::in); 
	  if (ifs.is_open()) { 
	      Ogre::String tex_ext;
	      Ogre::String::size_type index_of_extension = filename.find_last_of('.'); 
	      if (index_of_extension != Ogre::String::npos) { 
		  tex_ext = filename.substr(index_of_extension+1); 
		  Ogre::DataStreamPtr data_stream(new Ogre::FileStreamDataStream(filename, &ifs, false));
		  img.load(data_stream, tex_ext); 
		  this->width = img.getWidth();
		  this->height = img.getHeight();
//		  this->data = img.getData();
		   Ogre::TextureManager::getSingleton().loadImage(texture_name,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, img, Ogre::TEX_TYPE_2D, 0, 1.0f); 
		  image_loaded = true; 
		
	      } ifs.close(); 
	    
	  } else {
		std::string out;
		out = "Could not load image file ";
		out += filename;
		throw out.c_str();
	  } 
	  return image_loaded;
	}

};
