#ifndef _VOLUME_H_
#define _BASE_VOLUME_H_


#include "glm\glm.hpp"
#include <unordered_map>


struct Block {
	uint8_t type;
};

typedef std::unordered_map<glm::vec3, Block> VolumeData;
typedef std::unordered_map<glm::vec3, Block>::iterator VolumeIterator;

class BaseVolume {
public:
	BaseVolume(int capacity) {
		m_capacity = capacity;
	}
	~BaseVolume();

	bool IsSolid(glm::vec3 position);
	bool IsEmpty();
	bool IsFull();

	// Methods for checking face visibility
	bool TopVisible(glm::vec3 pos);
	bool BottomVisible(glm::vec3 pos);
	bool LeftVisible(glm::vec3 pos);
	bool RightVisible(glm::vec3 pos);
	bool FrontVisible(glm::vec3 pos);
	bool BackVisible(glm::vec3 pos);

	// Helper methods for mesh merging
	bool IsTopFaceFull();
	bool IsBottomFaceFull();
	bool IsLeftFaceFull();
	bool IsRightFaceFull();
	bool IsFrontFaceFull();
	bool IsBackFaceFull();

	void Empty();
	void Fill();

	uint8_t Get(glm::vec3 position);
	void Set(glm::vec3 position, uint8_t type);

	void Updated();

	VolumeIterator begin() { return m_data.begin(); }
	VolumeIterator end() { return m_data.end(); }

protected:

	int m_capacity;
	bool m_modified;

	VolumeData m_data;
};



#endif
