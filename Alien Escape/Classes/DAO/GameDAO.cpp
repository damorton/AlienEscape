#include "GameDAO.h"

//create
void GameDAO::create()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("Config");
	doc.InsertEndChild(node);
	doc.SaveFile(XMLDOC);
}

//read
std::shared_ptr<std::vector<StoryPoint>> GameDAO::read()
{

	//construct a story point vector to pass back
	std::shared_ptr<std::vector<StoryPoint>> storyPointToReturn = std::shared_ptr<std::vector<StoryPoint>>(new std::vector<StoryPoint>());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		//doc.Parse(XMLDOC);

		//get the first story element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			StoryPoint tempStoryPoint;
			tempStoryPoint.setName(child->FirstChildElement()->GetText());
			for(tinyxml2::XMLElement* storyChoiceElement = child->FirstChildElement(); storyChoiceElement != NULL; storyChoiceElement = storyChoiceElement->NextSiblingElement())
			{
				tempStoryPoint.addFilePath(storyChoiceElement->Name(), storyChoiceElement->GetText());
			}

			storyPointToReturn->push_back(tempStoryPoint);
		}
		return storyPointToReturn;

	}
	return NULL;
}
//update
void GameDAO::update(std::shared_ptr<std::vector<StoryPoint>> resources)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		doc.Parse(XMLDOC);
		tinyxml2::XMLElement* root = doc.NewElement("Config");
		
		int i = 0;
		int j = 0;
		for(i = 0; i<resources->size(); i++)
		{
			tinyxml2::XMLElement* storyElement = doc.NewElement(resources->at(i).getName().c_str());
			//doc.InsertEndChild(storyElement);
						
			root->InsertEndChild(storyElement);
						
			//write the story choices
			for(j = 0; j<resources->at(i).getStoryChoices()->size(); j++)
			{
				tinyxml2::XMLElement* storyChoiceElement = doc.NewElement(resources->at(i).getStoryChoices()->at(j).getName().c_str());
				//tinyxml2::XMLAttribute* storyTextElement = storyChoiceElement->
				tinyxml2::XMLText* storyChoiceText = doc.NewText(resources->at(i).getStoryChoices()->at(j).getValue().c_str());
				storyElement->InsertEndChild(storyChoiceElement);
				storyChoiceElement->InsertEndChild(storyChoiceText);
				
			}

			doc.InsertEndChild(root);

		}
		//doc.Print();
		doc.SaveFile(XMLDOC);
	}
}

//delete
void GameDAO::del()
{

}