#ifndef _VOXEL_H_
#define _VOXEL_H_

enum VoxelType { EMPTY, BLOCK };

struct Voxel {
	VoxelType m_type;
	glm::vec3 m_position;


	Voxel() {}

	Voxel(VoxelType voxType) {
		m_type = voxType;
	}

	Voxel(const Voxel &voxel) {
		m_type = voxel.m_type;
	}
};

#endif