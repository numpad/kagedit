#ifndef ENTITY_HPP
#define ENTITY_HPP

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SFML/Graphics.hpp>

class Entity {
private:
	glm::vec2 view_dir = glm::vec2(1.0f, 0.0f);

protected:
	glm::vec2 pos = glm::vec2(0.0f),
	          vel = glm::vec2(0.0f);

	sf::Sprite sprite;

	/* util */
	void setTexture(const sf::Texture &texture, glm::vec2 origin = glm::vec2(0.5f));
	void updatePhysics(float dt_seconds);

	Entity();

public:
	virtual ~Entity();

	/* util */
	float distanceTo(Entity &other);

	/* position */
	glm::vec2 getPos();
	void setPos(glm::vec2 pos);

	/* velocity */
	glm::vec2 getVel();
	void setVel(glm::vec2 vel);

	/* view direction */
	glm::vec2 getViewDirection();
	float getViewAngle(glm::vec2 base_dir = glm::vec2(1.0f, 0.0f));
	void setViewTarget(glm::vec2 target_pos);
	void setViewDirection(glm::vec2 target_dir);


	/* items */
	//virtual void onCollect(Item &item);
	
	/* update/render */
	virtual void update(float dt);
	virtual void draw(sf::RenderTarget &);
};

#endif
