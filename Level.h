#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <Graphics.hpp>
#include <iostream>
#include "TinyXML/tinyxml.h"

using namespace std;

struct Object
{
	int GetPropertyInt(string name);//����� �������� ������� � ����� ������
	float GetPropertyFloat(string name);
	string GetPropertyString(std::string name);

	std::string name;//�������� ���������� name ���� string
	std::string type;//� ����� ���������� type ���� string
	sf::Rect<float> rect;//��� Rect � �������� ����������
	map<std::string, std::string> properties;//������ ������������ ������. ���� - ��������� ���, �������� - ���������

	sf::Sprite sprite;//�������� ������
};

struct Layer//����
{
	int opacity;//�������������� ����
	vector<sf::Sprite> tiles;//���������� � ������ �����
};

class Level//������� ����� - �������
{
public:
	bool LoadFromFile(string filename);//���������� false ���� �� ���������� ���������
	Object GetObject(string name);
	vector<Object> GetObjects(string name);//������ ������ � ��� �������
	vector<Object> GetAllObjects();//������ ��� ������� � ��� �������
	void Draw(sf::RenderWindow &window);//������ � ����
	sf::Vector2i GetTileSize();//�������� ������ �����

private:
	int width, height, tileWidth, tileHeight;//� tmx ����� width height � ������,����� ������ �����
	int firstTileID;//�������� ���� ������� �����
	sf::Rect<float> drawingBounds;//������ ����� ����� ������� ������
	sf::Texture tilesetImage;//�������� �����
	vector<Object> objects;//������ ���� �������, ������� �� �������
	vector<Layer> layers;
};

///////////////////////////////////////


int Object::GetPropertyInt(string name)//���������� ����� �������� � ����� ������
{
	return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(string name)
{
	return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(string name)//�������� ��� � ���� ������.����� �������
{
	return properties[name];
}

bool Level::LoadFromFile(string filename)//���������-��������� � ������� ������ ��� ������ 
{
	TiXmlDocument levelFile(filename.c_str());//��������� ���� � TiXmlDocument
											  // ��������� XML-�����
	if (!levelFile.LoadFile())//���� �� ������� ��������� �����
	{
		cout << "Loading level \"" << filename << "\" failed." << endl;//������ ������
		return false;
	}

	// �������� � ����������� map
	TiXmlElement *map;
	map = levelFile.FirstChildElement("map");

	// ������ �����: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//��������� �� ����� ����� �� ��������
	height = atoi(map->Attribute("height"));//�� ��������, ������� �������� ��� ������ � 
	tileWidth = atoi(map->Attribute("tilewidth"));//������� ���������
	tileHeight = atoi(map->Attribute("tileheight"));

	// ����� �������� �������� � ������������� ������� �����
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - ���� �� �������� � ���������� image
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	string imagepath = image->Attribute("source");

	// �������� ��������� �������
	sf::Image img;


	if (!img.loadFromFile(imagepath))
	{
		cout << "Failed to load tile sheet." << endl;//���� �� ������� ��������� �������-������� ������ � �������
		return false;
	}


	img.createMaskFromColor(sf::Color(255, 255, 255));//��� ����� �����.������ ��� �����
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//�����������

								  // �������� ���������� �������� � ����� ��������
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;


	// ������ �� ��������������� ����������� (TextureRect)
	vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	// ������ �� ������
	TiXmlElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;

		// ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		//  ��������� <data> 
		TiXmlElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");
		
		if (layerDataElement == NULL)
		{
			cout << "Bad map. No layer information found." << endl;
		}
		
		//  ��������� <tile> - �������� ������ ������� ����
		TiXmlElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			cout << "Bad map. No tile information found." << endl;
			return false;
		}
		
		int x = 0;
		int y = 0;

		while (tileElement)
		{
			
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			// ������������� TextureRect ������� �����
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);//���������� � ���� ������� ������
			}
			
			tileElement = tileElement->NextSiblingElement("tile");
			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}
		

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
		
	}

	// ������ � ���������
	TiXmlElement *objectGroupElement;

	// ���� ���� ���� ��������
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			//  ��������� <object>
			TiXmlElement *objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{
				// �������� ��� ������ - ���, ���, �������, � ��
				string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}

				// ��������� �������
				Object object;
				object.name = objectName;
				object.type = objectType;
				object.sprite = sprite;

				sf::Rect <float> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
				object.rect = objectRect;

				// "����������" �������
				TiXmlElement *properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement *prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							string propertyName = prop->Attribute("name");
							string propertyValue = prop->Attribute("value");

							object.properties[propertyName] = propertyValue;

							prop = prop->NextSiblingElement("property");
						}
					}
				}


				objects.push_back(object);

				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		cout << "No object layers found..." << endl;
	}

	return true;
}

Object Level::GetObject(string name)
{
	// ������ ������ ������ � �������� ������
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

vector<Object> Level::GetObjects(string name)
{
	// ��� ������� � �������� ������
	vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}


vector<Object> Level::GetAllObjects()
{
	return objects;
};


sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
	// ������ ��� ����� (������� �� ������!)
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);
}

#endif