#include "FinishLine.h"

FinishLine::FinishLine()
{
}

FinishLine::~FinishLine()
{
}

void FinishLine::setCanPass()
{
	m_canPass = true;
}

void FinishLine::turnOffCanPass()
{
	m_canPass = false;
}
