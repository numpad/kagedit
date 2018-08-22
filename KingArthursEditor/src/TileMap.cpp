#include "TileMap.hpp"

sf::Vertex *TileMap::getTileVertex(unsigned int x, unsigned int y) {
	return &this->vertices[(x + y * this->width) * 4];
}

void TileMap::setQuadTexCoords(sf::Vertex *v, unsigned int tx, unsigned int ty) {
	v[0].texCoords = sf::Vector2f((tx    ) * tilewidth, (ty    ) * tileheight);
	v[1].texCoords = sf::Vector2f((tx + 1) * tilewidth, (ty    ) * tileheight);
	v[2].texCoords = sf::Vector2f((tx + 1) * tilewidth, (ty + 1) * tileheight);
	v[3].texCoords = sf::Vector2f((tx    ) * tilewidth, (ty + 1) * tileheight);
}

void TileMap::setQuadPosition(sf::Vertex *v, unsigned int x, unsigned int y) {
	v[0].position = sf::Vector2f((x    ) * tilewidth, (y    ) * tileheight);
	v[1].position = sf::Vector2f((x + 1) * tilewidth, (y    ) * tileheight);
	v[2].position = sf::Vector2f((x + 1) * tilewidth, (y + 1) * tileheight);
	v[3].position = sf::Vector2f((x    ) * tilewidth, (y + 1) * tileheight);
}

void TileMap::initTiles() {
	const int tiles_width = (this->tileset->getSize().x / this->tilewidth);
	for (unsigned int y = 0; y < this->height; ++y) {
		for (unsigned int x = 0; x < this->width; ++x) {
			/* value of tile */
			TileMap::tile_type tile_val = this->tiles[x + y * width];
			sf::Vertex *quad = this->getTileVertex(x, y);

			/* texcoords */
			int tu = tile_val % tiles_width;
			int tv = tile_val / tiles_width;
			/* init */
			this->setQuadPosition(quad, x, y);
			this->setQuadTexCoords(quad, tu, tv);
		}
	}
}

void TileMap::load(std::vector<tile_type> tiles, sf::Texture *texture, int width, int height, int tilesize) {
	this->setSize(width, height);
	this->setTileSize(tilesize);
	this->setTiles(tiles);
	this->setTileset(texture);

	this->vertices.setPrimitiveType(sf::PrimitiveType::Quads);
	this->vertices.resize(width * height * 4);

	this->initTiles();
}

void TileMap::setSize(unsigned int mapwidth, unsigned int mapheight) {
	this->width = mapwidth;
	this->height = mapheight;
}

void TileMap::setTileSize(unsigned int tilesize) {
	this->setTileSize(tilesize, tilesize);
}

void TileMap::setTileSize(unsigned int tilewidth, unsigned int tileheight) {
	this->tilewidth = tilewidth;
	this->tileheight = tileheight;
}

void TileMap::setTiles(std::vector<TileMap::tile_type> tiles) {
	this->tiles = tiles;
}

void TileMap::setTileset(sf::Texture *t) {
	this->tileset = t;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= this->getTransform();
	states.texture = this->tileset;
	target.draw(vertices, states);
}
