#include "ctr.hpp"
#include "env.hpp"
#include <iostream>
using namespace Env;

namespace MIPS {
void Ctr::onChange()
{
	if(in[opCode] == B("000000"))
	{
		if(in[funct] != B("001000"))
		{
			setOutput(regDst,1);
			setOutput(ALUSrc,0);
			setOutput(memToReg,0);
			setOutput(regWrite,1);
			setOutput(memRead,0);
			setOutput(memWrite,0);
			setOutput(branch,0);
			setOutput(aluOp,2);

			setOutput(jump,0);
		}
		else
		{
			setOutput(regDst,0);
			setOutput(ALUSrc,0);
			setOutput(memToReg,0);
			setOutput(regWrite,0);
			setOutput(memRead,0);
			setOutput(memWrite,0);
			setOutput(branch,0);
			setOutput(aluOp,0);
			setOutput(jump,2);

		}
	}
	else if(in[opCode] == B("100011"))
	{
		setOutput(regDst,0);
		setOutput(ALUSrc,1);
		setOutput(memToReg,1);
		setOutput(regWrite,1);
		setOutput(memRead,1);
		setOutput(memWrite,0);
		setOutput(branch,0);
		setOutput(aluOp,0);
		setOutput(jump,0);
	}	
	else if(in[opCode] == B("101011"))
	{
		setOutput(regDst,0);
		setOutput(ALUSrc,1);
		setOutput(memToReg,0);
		setOutput(regWrite,0);
		setOutput(memRead,0);
		setOutput(memWrite,1);
		setOutput(branch,0);
		setOutput(aluOp,0);
		setOutput(jump,0);
	}	
	else if(in[opCode] == B("000100"))
	{
		setOutput(regDst,0);
		setOutput(ALUSrc,0);
		setOutput(memToReg,0);
		setOutput(regWrite,0);
		setOutput(memRead,0);
		setOutput(memWrite,0);
		setOutput(branch,1);
		setOutput(aluOp,1);
		setOutput(jump,0);
	}	
	else if(in[opCode] == B("000010"))
	{
		setOutput(regDst,0);
		setOutput(ALUSrc,0);
		setOutput(memToReg,0);
		setOutput(regWrite,0);
		setOutput(memRead,0);
		setOutput(memWrite,0);
		setOutput(branch,0);
		setOutput(aluOp,0);
		setOutput(jump,1);
	}
	else if(in[opCode] == B("000011"))
	{
		setOutput(regDst,0);
		setOutput(ALUSrc,0);
		setOutput(memToReg,0);
		setOutput(regWrite,2);
		setOutput(memRead,0);
		setOutput(memWrite,0);
		setOutput(branch,0);
		setOutput(aluOp,0);
		setOutput(jump,1);
	}
	else if(in[opCode] == B("001000"))
	{
		setOutput(regDst,0);
		setOutput(ALUSrc,1);
		setOutput(memToReg,0);
		setOutput(regWrite,1);
		setOutput(memRead,0);
		setOutput(memWrite,0);
		setOutput(branch,0);
		setOutput(aluOp,0);
		setOutput(jump,0);			
	}

}
}
