#include "BaseVolume.h"

BaseVolume::~BaseVolume() {
	m_data.clear();
}

bool BaseVolume::IsSolid(glm::vec3 position) {
	return !(m_data.find(position) == m_data.end());
}

bool BaseVolume::IsFull() {
	return m_data.size() == m_capacity * m_capacity * m_capacity;
}

bool BaseVolume::IsEmpty() {
	return m_data.begin() == m_data.end();
}

void BaseVolume::Empty() {
	m_data.clear();
}

void BaseVolume::Fill() {
	for (int i = 0; i < m_capacity; ++i) {
		for (int j = 0; j < m_capacity; ++j) {
			for (int k = 0; k < m_capacity; ++k) {
				Set(glm::vec3(i, j, k), 1);
			}
		}
	}
}

uint8_t BaseVolume::Get(glm::vec3 position) {
	if (IsSolid(position))
		return m_data[position].type;

	else
		return 0;
}

void BaseVolume::Set(glm::vec3 position, uint8_t type) {
	glm::vec3 key = glm::clamp(position, glm::vec3(0), glm::vec3(m_capacity));

	Block element;

	if (type > 0) {
		if (m_data[key].type != type) {
			element.type = type;
			m_data[key] = element;
			m_modified = true;
		}
	}

	else if (IsSolid(key)) {
		m_data.erase(key);
		m_modified = true;
	}
}

void BaseVolume::Updated() {
	if (m_modified) m_modified = false;
}

///////////////////
// Visibility check
///////////////////

bool BaseVolume::TopVisible(glm::vec3 pos) {
	return IsSolid(glm::vec3(pos.x, pos.y + 1, pos.z));
}

bool BaseVolume::BottomVisible(glm::vec3 pos) {
	return IsSolid(glm::vec3(pos.x, pos.y - 1, pos.z));
}

bool BaseVolume::LeftVisible(glm::vec3 pos) {
	return IsSolid(glm::vec3(pos.x - 1, pos.y, pos.z));
}


bool BaseVolume::RightVisible(glm::vec3 pos) {
	return IsSolid(glm::vec3(pos.x + 1, pos.y, pos.z));
}


bool BaseVolume::FrontVisible(glm::vec3 pos) {
	return IsSolid(glm::vec3(pos.x, pos.y, pos.z + 1));
}


bool BaseVolume::BackVisible(glm::vec3 pos) {
	return IsSolid(glm::vec3(pos.x, pos.y, pos.z - 1));
}


/////////////////////
// Mesh merging check
/////////////////////

bool BaseVolume::IsTopFaceFull() {
	int y = m_capacity - 1;

	for (int x = 0; x < m_capacity; ++x) {
		for (int z = 0; z < m_capacity; ++z) {
			if (!IsSolid(glm::vec3(x, y, z)))
				return false;
		}
	}

	return true;
}

bool BaseVolume::IsBottomFaceFull() {
	int y = 0;

	for (int x = 0; x < m_capacity; ++x) {
		for (int z = 0; z < m_capacity; ++z) {
			if (!IsSolid(glm::vec3(x, y, z)))
				return false;
		}
	}

	return true;
}

bool BaseVolume::IsLeftFaceFull() {
	int x = 0;

	for (int y = 0; y < m_capacity; ++y) {
		for (int z = 0; z < m_capacity; ++z) {
			if (!IsSolid(glm::vec3(x, y, z)))
				return false;
		}
	}

	return true;
}

bool BaseVolume::IsRightFaceFull() {
	int x = m_capacity - 1;

	for (int y = 0; y < m_capacity; ++y) {
		for (int z = 0; z < m_capacity; ++z) {
			if (!IsSolid(glm::vec3(x, y, z)))
				return false;
		}
	}

	return true;
}

bool BaseVolume::IsFrontFaceFull() {
	int z = m_capacity - 1;

	for (int x = 0; x < m_capacity; ++x) {
		for (int y = 0; y < m_capacity; ++y) {
			if (!IsSolid(glm::vec3(x, y, z)))
				return false;
		}
	}

	return true;
}

bool BaseVolume::IsBackFaceFull() {
	int z = 0;

	for (int x = 0; x < m_capacity; ++x) {
		for (int y = 0; y < m_capacity; ++y) {
			if (!IsSolid(glm::vec3(x, y, z)))
				return false;
		}
	}

	return true;
}