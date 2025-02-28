#include "cbase.h"

bool CheckValveSignature(const void *data, uint32 nDataSize, const void *signature, uint32 nSignatureSize)
{
	return true;
}

bool TF_CheckSignature(const char* fileName, const char *pathID, CUtlBuffer& bufRawData)
{
	printf("------------------- FILENAME %s, PATHID %s ---------------------", fileName, pathID);
	//quake_rl | 513
	//if (fileName == "items_game" || fileName == "items_game.txt")
	//	return false;

	return true;
}