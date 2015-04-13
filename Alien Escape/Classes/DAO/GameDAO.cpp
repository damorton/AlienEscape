/*
GameDAO.cpp

Data Access Object for read and writing to XML file

@author	David Morton K00179391, James Daly L.I.T
@date	13.4.15
*/
#include "GameDAO.h"

void GameDAO::create()
{
	//Create the XML file using the XMLDOC filename
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("Config");
	doc.InsertEndChild(node);
	doc.SaveFile(XMLDOC);
}

std::shared_ptr<std::vector<Record>> GameDAO::read()
{
	//Create a vector of records and populate with information from the XML file
	std::shared_ptr<std::vector<Record>> recordToReturn = std::shared_ptr<std::vector<Record>>(new std::vector<Record>());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{		
		//Read the XML file and add resources to the vector of records
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			Record tempRecord;
			tempRecord.setName(child->FirstChildElement()->GetText());
			for(tinyxml2::XMLElement* resourceElement = child->FirstChildElement(); resourceElement != NULL; resourceElement = resourceElement->NextSiblingElement())
			{
				tempRecord.addResource(resourceElement->Name(), resourceElement->GetText());
			}
			recordToReturn->push_back(tempRecord);
		}

		//Return the vector of records and resources
		return recordToReturn;
	}
	return NULL;
}

void GameDAO::update(std::shared_ptr<std::vector<Record>> resources)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	//Load the XML file and begin reading from the root element
	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		doc.Parse(XMLDOC);
		tinyxml2::XMLElement* root = doc.NewElement("Config");
		
		//Write each resource stored in each record from the vector parameter
		int i = 0;
		int j = 0;
		for(i = 0; i<resources->size(); i++)
		{
			tinyxml2::XMLElement* storyElement = doc.NewElement(resources->at(i).getName().c_str());
						
			root->InsertEndChild(storyElement);							
			for(j = 0; j<resources->at(i).getResources()->size(); j++)
			{
				tinyxml2::XMLElement* resourceElement = doc.NewElement(resources->at(i).getResources()->at(j).getName().c_str());
				tinyxml2::XMLText* resourceText = doc.NewText(resources->at(i).getResources()->at(j).getValue().c_str());
				storyElement->InsertEndChild(resourceElement);
				resourceElement->InsertEndChild(resourceText);				
			}
			doc.InsertEndChild(root);
		}		

		// Save updated file to XMLDOC
		doc.SaveFile(XMLDOC);
	}
}

void GameDAO::del()
{
	// Not used
}