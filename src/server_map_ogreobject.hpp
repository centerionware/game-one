
	OgreObjectWrapper::OgreObjectWrapper(const char *name, const char *group) : need_resize(true),curIntCnt(0) {
		msh = Ogre::MeshManager::getSingleton().createManual(name, group);
		std::stringstream sm_name;
		sm_name << name << "_sm";
		sub = msh->createSubMesh(sm_name.str().c_str());
		sub->setMaterialName("VoxelTexture");
		
		sub->operationType = Ogre::RenderOperation::OT_POINT_LIST;
		rs = Ogre::Root::getSingleton().getRenderSystem();
		msh->sharedVertexData = new Ogre::VertexData();
		node = NULL;
		entity = NULL;
		_name = name;
		_group = group;
		entity_loaded = false;
		
	}
#include "CState_Testing.h"
namespace OgreUtil {
	void destroyAllAttachedMovableObjects( Ogre::SceneNode* node )
	{
	   if(!node) return;

	   // Destroy all the attached objects
	   Ogre::SceneNode::ObjectIterator itObject = node->getAttachedObjectIterator();

	   while ( itObject.hasMoreElements() )
		  node->getCreator()->destroyMovableObject(itObject.getNext());

	   // Recurse to child SceneNodes
	   Ogre::SceneNode::ChildNodeIterator itChild = node->getChildIterator();

	   while ( itChild.hasMoreElements() )
	   {
		  Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
		  destroyAllAttachedMovableObjects( pChildNode );
	   }
	}

	void destroySceneNode( Ogre::SceneNode* node )
	{
	   if(!node) return;
		destroyAllAttachedMovableObjects(node);
	   node->removeAndDestroyAllChildren();
	   node->getCreator()->destroySceneNode(node);
	}
}
	OgreObjectWrapper::~OgreObjectWrapper() {
		//Ogre::HardwareBufferManager::getSingleton()._notifyIndexBufferDestroyed(ibuf.get());
		Ogre::HardwareBufferManager::getSingleton()._notifyVertexBufferDestroyed(vibuf.get());
		Ogre::HardwareBufferManager::getSingleton()._notifyVertexBufferDestroyed(vbuf.get());
		Ogre::SceneManager * ptr =  CState_Testing::ReturnInstance()->mSceneManager;
		//node->getCreator()->destroyManualObject((Ogre::ManualObject*)(*msh));
		if(entity != NULL) {
			node->detachObject(entity);
			OgreUtil::destroySceneNode(node);
			ptr->destroyEntity(entity);
		}
	//	std::stringstream sm_name;
	//	sm_name << _name << "_sm";
	//	delete msh->sharedVertexData;
	//	msh->destroySubMesh(sm_name.str().c_str());
		Ogre::MeshManager::getSingleton().remove( msh.get()->getHandle());
	}

	void OgreObjectWrapper::create_ogre_object(GOREAL*vertices,size_t nVertices,Ogre::AxisAlignedBox &_bbox,Ogre::RGBA *colors,float*mcWeights, bool _export){
		if(nVertices >= curIntCnt) {
			curIntCnt = nVertices*6;
			need_resize = true;
		} else if(nVertices >3 && nVertices >= curIntCnt/3) {
			curIntCnt = nVertices*6;
			need_resize = true;
		} else {need_resize = false; }


		msh->sharedVertexData->vertexCount = nVertices;
		decl = msh->sharedVertexData->vertexDeclaration;
		size_t offset = 0;
		decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		if(need_resize) 
			vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(offset, curIntCnt, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		vbuf->writeData(0, sizeof(GOREAL)*(nVertices*3), vertices, true);
		
		bind = msh->sharedVertexData->vertexBufferBinding;
		bind->setBinding(0, vbuf);
		offset = 0;
		
		decl->addElement(1, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
		
		if(need_resize)
			vibuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(offset, nVertices*2, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		vibuf->writeData(0, sizeof(Ogre::RGBA)*(nVertices), colors, true);
		bind->setBinding(1, vibuf);

		offset = 0;
		
		decl->addElement(2, offset, Ogre::VET_FLOAT3, Ogre::VES_TEXTURE_COORDINATES);
		offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		
		if(need_resize)
			mcbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(offset, nVertices*6, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		mcbuf->writeData(0, sizeof(float)*(nVertices*3), mcWeights, true);
		bind->setBinding(2, mcbuf);

		msh->_setBounds(_bbox);
		msh->load();
	}
  

//OgreObjectWrapper *OgreObjectWrapper::_stinstance = NULL;