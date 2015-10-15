#include "alucontrol.hpp"
#include "env.hpp"
using namespace Env;

namespace MIPS {
void ALUControl::onChange()
{
	if(in[aluOp] == 0)
	{
		setOutput(aluCtr, B("0010"));
		return;
	}
	else if(in[aluOp] == 1)
	{
		setOutput(aluCtr, B("0110"));
		return;
	}
	else if (in[aluOp] == 2)
	{
		if ((in[funct] & 0xF) == 0)
		{
			setOutput(aluCtr,B("0010"));
			return;
		}
		else if ((in[funct] & 0xF) == 2)
		{
			setOutput(aluCtr,B("0110"));
			return;
		}
		else if ((in[funct] & 0xF) == 4)
		{
			setOutput(aluCtr,B("0000"));
			return;
		}
		else if ((in[funct] & 0xF) == 5)
		{
			setOutput(aluCtr,B("0001"));
			return;
		}
		else if ((in[funct] & 0xF) == 10)
		{
			setOutput(aluCtr,B("0111"));
			return;
		}
		else if ((in[funct] & 0xF) == 12)
		{
			setOutput(aluCtr,B("1010"));
			return;
		}
	}

}
}
