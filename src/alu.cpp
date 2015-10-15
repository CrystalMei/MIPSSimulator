#include "alu.hpp"
#include "env.hpp"
#include <iostream>
using namespace Env;

namespace MIPS {
void ALU::onChange()
{
	switch (in[aluCtr]) 
	{ 
		case 0: setOutput(aluRes, in[input1] & in[input2]); break; 
		case 1: setOutput(aluRes, in[input1] | in[input2]); break; 
		case 2: setOutput(aluRes, in[input1] + in[input2]); break; 
		case 6: setOutput(aluRes, in[input1] - in[input2]); break; 
		case 7: if (in[input1] < in[input2]) setOutput(aluRes, 1); else setOutput(aluRes, 0); break; 
		case 12: setOutput(aluRes, ~(in[input1] | in[input2])); break; 
	} 
	if (out[aluRes] == 0) setOutput(zero, 1); 
	else setOutput(zero, 0); 
}
}