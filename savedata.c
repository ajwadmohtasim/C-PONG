#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pong.h"

//Save gamedata
//------------------------------------------------------------
bool Save(unsigned int position, int value)
{
    
    bool ok = false;
    int dataSize = 0; // store size of the savefle
    unsigned int newDataSize = 0; // store size of the new savefile if reallocation is needed
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize); //Load exisitng data from savefile
    unsigned char *newFileData = NULL; // Pointer for new savefile after reallocation


    // Check if savefile successfully loaded
    if (fileData != NULL)
    {

        // Check if current file size is less than required position, if yes, re-allocaiton is required
        if (dataSize <= (position * sizeof(int)))
        {

            newDataSize = (position + 1) * sizeof(int); //Calculate new data size.
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize); //Reallocate memory for new savefile

            // Check if it reallocation is successful
            if (newFileData != NULL)
            {
                // RL_REALLOC succeded - store data into new savefile
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value; 
            }
            else
            {
                // RL_REALLOC failed
                TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", STORAGE_DATA_FILE, dataSize, position * sizeof(int));
                // We store the old size of the file
                newFileData = fileData;
                newDataSize = dataSize;
            }
        }
        // Reallocation is not required
        else
        {   
            // We store the old size of the file
            newFileData = fileData;
            newDataSize = dataSize;

            // Replace value on selected position
            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }

        ok = SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize); // save data back to the savefile
        RL_FREE(newFileData); // Free allocated memory
        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }
    // New savefile required
    else
    {
        TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);
        dataSize = (position + 1) * sizeof(int);

        fileData = (unsigned char *)RL_MALLOC(dataSize); //reallocate new file 
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;
        ok = SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
        UnloadFileData(fileData); // unload the datafile form memory
        TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }
    return ok;
}

//Load gamedata
//------------------------------------------------------------
int Load(unsigned int position)
{
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < (position * 4)) // Check if our required position is out of bounds.
            TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        UnloadFileData(fileData); //unload the file data from memory
        TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}

//Check if Save File exist
//------------------------------------------------------------
bool file_exists(const char *filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return true;
    }
    return false;
}
