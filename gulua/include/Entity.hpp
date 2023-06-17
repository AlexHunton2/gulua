#ifndef ENTITY
#define ENTITY

// factory 
class Entity {
public:
	virtual void init(); // called once
	virtual void draw(); // called every frame
protected:
	bool m_initalized = false;
};

#endif