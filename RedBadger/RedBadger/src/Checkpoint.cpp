#include "Checkpoint.h"

Checkpoint::Checkpoint()
{
}

Checkpoint::~Checkpoint()
{
}

void Checkpoint::setCanPass()
{
	m_canPass = true;
}

void Checkpoint::turnOffCanPass()
{
	m_canPass = false;
}
