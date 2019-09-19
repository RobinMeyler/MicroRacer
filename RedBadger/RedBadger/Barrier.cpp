#include "Barrier.h"





Barrier::Barrier(ResourceManager & t_gameAssets) :
	m_barrierBox(t_gameAssets.m_gameTextures["Bridge Wall"])
{
}

Barrier::~Barrier()
{
}
