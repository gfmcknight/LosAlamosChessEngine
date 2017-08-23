//
// Created by Graham McKnight on 7/4/2017.
//

#include <string.h>

#include "chessEngine.h"

static const char * properties[] = {
        "Self_Placeholder",
        "Self_Pawn_Value",
        "Self_Super_Pawn_Value",
        "Self_Knight_Value",
        "Self_Bishop_Value",
        "Self_Rook_Value",
        "Self_Arch_Bishop_Value",
        "Self_Queen_Value",
        "Self_Super_Queen_Value",
        "Self_King_Value",
        "Opponent_Placeholder",
        "Opp_Pawn_Value",
        "Opp_Super_Pawn_Value",
        "Opp_Knight_Value",
        "Opp_Bishop_Value",
        "Opp_Rook_Value",
        "Opp_Arch_Bishop_Value",
        "Opp_Queen_Value",
        "Opp_Super_Queen_Value",
        "Opp_King_Value",
        "King_Safety_Value",
        "King_Centrality_Value",
        "Mobility_Value",
        "Pawn_Push_Value",
        "King_Center_Cutoff",
        "Depth",
        "Q_Depth"
};

/*
 * Function Name: getEvalPropertyIndex()
 * Function Prototype: int getEvalPropertyIndex(const char * str);
 * Description: Returns the index at which the named property appears in the
 *              array for the evalProfile.
 * Parameters:
 *      const char * str -- The name of the property.
 * Side Effects: None.
 * Return Value: The index for the given property.
 */

int getEvalPropertyIndex(const char * str)
{
    for (int i = 0; i < NUM_PROPERTIES; i++)
    {
        if (strcmp(properties[i], str) == 0)
        {
            return i;
        }
    }
    return -1;
}