#ifndef INIT_AIS_H
#define INIT_AIS_H
#include "../../basic/BasicDef.h"
#include "../EntityControl.h"
#include "Entity1.h"
#include "Entity10.h"
#include "Entity11.h"
#include "Entity2.h"
#include "Entity3.h"
#include "Entity4.h"
#include "Entity5.h"
#include "Entity6.h"
#include "Entity8.h"
#include "EntityCzy.h"
#include "EntityPCF.h"
void initAIs(EntityControl::Player&a,int x)
{
	switch(x)
	{
		case 0:break;
		case 1:Entity1::entity_input(a);break;
		case 2:Entity10::entity_input(a);break;
		case 3:Entity11::entity_input(a);break;
		case 4:Entity2::entity_input(a);break;
		case 5:Entity3::entity_input(a);break;
		case 6:Entity4::entity_input(a);break;
		case 7:Entity5::entity_input(a);break;
		case 8:Entity6::entity_input(a);break;
		case 9:Entity8::entity_input(a);break;
		case 10:EntityCzy::entity_input(a);break;
		case 11:EntityPCF::entity_input(a);break;
		default:assert(0);
	}
}
#endif
