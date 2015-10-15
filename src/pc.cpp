#include "pc.hpp"
#include "env.hpp"
#include <iostream>
using namespace Env;
namespace MIPS {
void PC::onClock()
{
	if(in[branch] == 1 && in[zero] == 1) m_pc += 4+4*in[immData];
	else if(in[jump]==1) m_pc = in[immData]*4;
	else if(in[jump]==2) m_pc = in[readData1];
	else m_pc += 4;
	setOutput(newPC,m_pc);
}
}