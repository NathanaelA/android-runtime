#ifndef METADATAREADER_H_
#define METADATAREADER_H_

#include "MetadataEntry.h"
#include <map>

namespace tns
{
	typedef std::vector<std::string> (*GetTypeMetadataCallback)(const std::string& classname, int index);

	class MetadataReader
	{
	public:
		MetadataReader();

		MetadataReader(uint32_t nodesLength, uint8_t *nodeData, uint8_t *nameData, uint8_t *valueData, GetTypeMetadataCallback getTypeMetadataCallack);

		MetadataEntry ReadInstanceMethodEntry(uint8_t*& data);

		MetadataEntry ReadStaticMethodEntry(uint8_t*& data);

		MetadataEntry ReadInstanceFieldEntry(uint8_t*& data);

		MetadataEntry ReadStaticFieldEntry(uint8_t*& data);

		std::string ReadTypeName(uint16_t nodeId);

		std::string ReadTypeName(MetadataTreeNode *treeNode);

		std::string ReadName(uint8_t *names, uint32_t offset);

		std::string ReadInterfaceImplementationTypeName(MetadataTreeNode *treeNode, bool& isPrefix);

		uint8_t* GetValueData() const;

		uint8_t GetNodeType(MetadataTreeNode *treeNode);

		uint16_t GetNodeId(MetadataTreeNode *treeNode);

		MetadataTreeNode* GetRoot() const;

		MetadataTreeNode* GetOrCreateTreeNodeByName(const std::string& className);

		MetadataTreeNode* GetBaseClassNode(MetadataTreeNode *treeNode);

		bool IsPrimitive(uint8_t type);

		bool IsNodeTypeArray(uint8_t type);

		bool IsNodeTypeStatic(uint8_t type);

		bool IsNodeTypeClass(uint8_t type);

		bool IsNodeTypeInterface(uint8_t type);

		bool IsNodeTypePackage(uint8_t type);

		static const uint32_t ARRAY_OFFSET = 1000000000;

	private:
		MetadataTreeNode* BuildTree();

		std::string ReadTypeNameInternal(MetadataTreeNode *treeNode);

		MetadataTreeNode *m_root;
		uint32_t m_nodesLength;
		uint8_t *m_nodeData;
		uint8_t *m_nameData;
		uint8_t *m_valueData;
		std::vector<MetadataTreeNode*> m_v;
		GetTypeMetadataCallback m_getTypeMetadataCallback;

		std::map<MetadataTreeNode*, std::string> m_typeNameCache;
	};
}


#endif /* METADATAREADER_H_ */