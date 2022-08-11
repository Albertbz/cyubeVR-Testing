#include "GameAPI.h"


/************************************************************
	Custom variables
*************************************************************/

// Whether the currently active world is the "TestingWorld" world.
bool isTestingWorld = false;
// Keeps track of how many times the block has been destroyed.
int numTracker = 0;
// The handle of the hint text showing the number of times the block has been destroyed.
void* currentHandle = nullptr;

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/

UniqueID ThisModUniqueIDs[] = { 0 }; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 10;							 // Set how many times per second Event_Tick() is called. 0 means the Event_Tick() function is never called.

/************************************************************* 
//	Functions (Run automatically by the game, you can put any code you want into them)
*************************************************************/

// Run every time a block is placed
void Event_BlockPlaced(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	
}




// Run every time a block is destroyed
void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{

}


/*
*	Run every time a block is hit by a tool
*	All the exact possible ToolName are: T_Stick, T_Arrow, T_Pickaxe_Stone, T_Axe_Stone, T_Shovel_Stone, T_Pickaxe_Copper, T_Axe_Copper, T_Shovel_Copper, T_Sledgehammer_Copper, T_Pickaxe_Iron, T_Axe_Iron, T_Shovel_Iron, T_Sledgehammer_Iron
*/ 
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{

	if (ToolName == L"T_Stick") {

	}
	else if (ToolName == L"T_Pickaxe_Stone") {

	}
	else if (ToolName == L"T_Arrow") {

	}
	else {

	}
}


// Run X times per second, as specified in the TickRate variable at the top
void Event_Tick()
{
	// This makes the block at (0, 0, 200) not register hits properly all the time. Feels like the stick makes it worse somehow.
	if (isTestingWorld) {
		if (GetBlock(CoordinateInBlocks(0, 1, 200)).Type == EBlockType::Air) {
			SetBlock(CoordinateInBlocks(0, 1, 200), EBlockType::Stone);
		}
	}
}



// Run once when the world is loaded
void Event_OnLoad(bool CreatedNewWorld)
{
	// This is simply so that the mod only runs when in the world called "TestingWorld".
	if (GetWorldName() == L"TestingWorld") {
		isTestingWorld = true;


		if (GetBlock(CoordinateInBlocks(0, 0, 200)).Type == EBlockType::Air) {
			SetBlock(CoordinateInBlocks(0, 0, 200), EBlockType::Stone);
		}
	}
}

// Run once when the world is exited
void Event_OnExit()
{
	
}

/*******************************************************

	Advanced functions

*******************************************************/


// Run every time any block is placed by the player
void Event_AnyBlockPlaced(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{

}

// Run every time any block is destroyed by the player
void Event_AnyBlockDestroyed(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{
	// Here, SetBlock is only run once when destroying the Stone block with two pickaxes at the same time. The event, however, is run twice (numTracker is incremented twice, etc.).
	if (isTestingWorld) {
		if (At == CoordinateInBlocks(0, 0, 200)) {
			if (Type.Type == EBlockType::Stone) {
				numTracker++;
				DestroyHintText(currentHandle);
				currentHandle = SpawnHintTextAdvanced(CoordinateInBlocks(0, 0, 201), std::to_wstring(numTracker), 5, 0.3F, 2.0F, 10);
				SetBlock(At, EBlockType::Stone);
			}
		}
	}

}

/*
*	Run every time any block is hit by a tool
*	All the exact possible ToolName are: T_Stick, T_Arrow, T_Pickaxe_Stone, T_Axe_Stone, T_Shovel_Stone, T_Pickaxe_Copper, T_Axe_Copper, T_Shovel_Copper, T_Sledgehammer_Copper, T_Pickaxe_Iron, T_Axe_Iron, T_Shovel_Iron, T_Sledgehammer_Iron
*/
void Event_AnyBlockHitByTool(CoordinateInBlocks At, BlockInfo Type, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{

}


/*******************************************************

	For all the available game functions you can call, look at the GameAPI.h file

*******************************************************/