#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	using tile_type = int;

private:

	sf::VertexArray vertices;
	sf::Texture *tileset;
	std::vector<tile_type> tiles;

	unsigned int width, height;
	unsigned int tilewidth, tileheight;


	sf::Vertex *getTileVertex(unsigned int x, unsigned int y);
	void setQuadTexCoords(sf::Vertex *v, unsigned int x, unsigned int y);
	void setQuadPosition(sf::Vertex *v, unsigned int x, unsigned int y);

	void initTiles();

public:

	void load(std::vector<tile_type> tiles, sf::Texture *texture, int width, int height, int tilesize);

	void setSize(unsigned int mapwidth, unsigned int mapheight);
	void setTileSize(unsigned int tilesize);
	void setTileSize(unsigned int tilewidth, unsigned int tileheight);

	void setTiles(std::vector<tile_type> tiles);
	void setTileset(sf::Texture *t);
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif
