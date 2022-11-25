/*
  ==============================================================================

    NoteHarmony.h
    Created: 25 Nov 2022 4:02:52pm
    Author:  Mouldy Soul

  ==============================================================================
*/

#pragma once

int returnHarmonyAddition(int interNote, bool majorOn, int intervalSpacing)
{
    int intervalAddition;
    
    switch(intervalSpacing)
    {
        case 3:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 4;
                        break;
                    case 1:
                        intervalAddition = 3;
                        break;
                    case 2:
                        intervalAddition = 3;
                        break;
                    case 3:
                        intervalAddition = 3;
                        break;
                    case 4:
                        intervalAddition = 3;
                        break;
                    case 5:
                        intervalAddition = 4;
                    case 6:
                        intervalAddition = 4;
                        break;
                    case 7:
                        intervalAddition = 4; // or 2?
                        break;
                    case 8:
                        intervalAddition = 4; // or 2?
                        break;
                    case 9:
                        intervalAddition = 3;
                        break;
                    case 10:
                        intervalAddition = 3;
                        break;
                    case 11:
                        intervalAddition = 3;
                        break;
                }
            }
            
            if (!majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 3;
                        break;
                    case 1:
                        intervalAddition = 3;
                        break;
                    case 2:
                        intervalAddition = 3;
                        break;
                    case 3:
                        intervalAddition = 4;
                        break;
                    case 4:
                        intervalAddition = 4;
                        break;
                    case 5:
                        intervalAddition = 3;
                        break;
                    case 6:
                        intervalAddition = 4;
                        break;
                    case 7:
                        intervalAddition = 3; // or 2?
                        break;
                    case 8:
                        intervalAddition = 4; // or 2?
                        break;
                    case 9:
                        intervalAddition = 3;
                        break;
                    case 10:
                        intervalAddition = 4;
                        break;
                    case 11:
                        intervalAddition = 3;
                        break;
                }
            }
            break;
        case 4:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 7;
                        break;
                    case 1:
                        intervalAddition = 7;
                        break;
                    case 2:
                        intervalAddition = 7;
                        break;
                    case 3:
                        intervalAddition = 7;
                        break;
                    case 4:
                        intervalAddition = 7;
                        break;
                    case 5:
                        intervalAddition = 7;
                        break;
                    case 6:
                        intervalAddition = 7;
                        break;
                    case 7:
                        intervalAddition = 7; // or 2?
                        break;
                    case 8:
                        intervalAddition = 7;
                        break;
                    case 9:
                        intervalAddition = 7;
                        break;
                    case 10:
                        intervalAddition = 7;
                        break;
                    case 11:
                        intervalAddition = 6;
                        break;
                }
            }
            
            if (!majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 7;
                        break;
                    case 1:
                        intervalAddition = 7;
                        break;
                    case 2:
                        intervalAddition = 6;
                        break;
                    case 3:
                        intervalAddition = 7;
                        break;
                    case 4:
                        intervalAddition = 7;
                        break;
                    case 5:
                        intervalAddition = 7;
                        break;
                    case 6:
                        intervalAddition = 7;
                        break;
                    case 7:
                        intervalAddition = 7; // or 2?
                        break;
                    case 8:
                        intervalAddition = 7; // or 2?
                        break;
                    case 9:
                        intervalAddition = 6;
                        break;
                    case 10:
                        intervalAddition = 7;
                        break;
                    case 11:
                        intervalAddition = 6;
                        break;
                }
            }
            break;
        case 2:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -3;
                        break;
                    case 1:
                        intervalAddition = -3;
                        break;
                    case 2:
                        intervalAddition = -3;
                        break;
                    case 3:
                        intervalAddition = -3;
                        break;
                    case 4:
                        intervalAddition = -4;
                        break;
                    case 5:
                        intervalAddition = -3;
                        break;
                    case 6:
                        intervalAddition = -3;
                        break;
                    case 7:
                        intervalAddition = -3; // or 2?
                        break;
                    case 8:
                        intervalAddition = -3; // or 2?
                        break;
                    case 9:
                        intervalAddition = -4;
                        break;
                    case 10:
                        intervalAddition = -3;
                        break;
                    case 11:
                        intervalAddition = -4;
                        break;
                }
            }
            
            if (!majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -4;
                        break;
                    case 1:
                        intervalAddition = -3;
                        break;
                    case 2:
                        intervalAddition = -4;
                        break;
                    case 3:
                        intervalAddition = -3;
                        break;
                    case 4:
                        intervalAddition = -3;
                        break;
                    case 5:
                        intervalAddition = -3;
                        break;
                    case 6:
                        intervalAddition = -3;
                        break;
                    case 7:
                        intervalAddition = -4; // or 2?
                        break;
                    case 8:
                        intervalAddition = -3; // or 2?
                        break;
                    case 9:
                        intervalAddition = -3;
                        break;
                    case 10:
                        intervalAddition = -3;
                        break;
                    case 11:
                        intervalAddition = -3;
                        break;
                }
            }
            break;
        case 1:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -7;
                        break;
                    case 1:
                        intervalAddition = -7;
                        break;
                    case 2:
                        intervalAddition = -7;
                        break;
                    case 3:
                        intervalAddition = -7;
                        break;
                    case 4:
                        intervalAddition = -7;
                        break;
                    case 5:
                        intervalAddition = -6;
                        break;
                    case 6:
                        intervalAddition = -7;
                        break;
                    case 7:
                        intervalAddition = -7; // or 2?
                        break;
                    case 8:
                        intervalAddition = -7; // or 2?
                        break;
                    case 9:
                        intervalAddition = -7;
                        break;
                    case 10:
                        intervalAddition = -7;
                        break;
                    case 11:
                        intervalAddition = -7;
                        break;
                }
            }
            
            if (!majorOn)
            {
                
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -7;
                        break;
                    case 1:
                        intervalAddition = -7;
                        break;
                    case 2:
                        intervalAddition = -7;
                        break;
                    case 3:
                        intervalAddition = -7;
                        break;
                    case 4:
                        intervalAddition = -7;
                        break;
                    case 5:
                        intervalAddition = -7;
                        break;
                    case 6:
                        intervalAddition = -7;
                        break;
                    case 7:
                        intervalAddition = -7; // or 2?
                        break;
                    case 8:
                        intervalAddition = -6; // or 2?
                        break;
                    case 9:
                        intervalAddition = -7;
                        break;
                    case 10:
                        intervalAddition = -7;
                        break;
                    case 11:
                        intervalAddition = -6;
                        break;
                }
            }
            break;
    }
    
    
    
    return intervalAddition;
}

int returnVoiceAddition(int interNote, bool majorOn, int intervalSpacing)
{
    int intervalAddition;
    
    switch(intervalSpacing)
    {
        case 3:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 4;
                        break;
                    case 1:
                        intervalAddition = 3;
                        break;
                    case 2:
                        intervalAddition = 2;
                        break;
                    case 3:
                        intervalAddition = 2;
                        break;
                    case 4:
                        intervalAddition = 3;
                        break;
                    case 5:
                        intervalAddition = 2;
                    case 6:
                        intervalAddition = 4;
                        break;
                    case 7:
                        intervalAddition = 5; // or 2?
                        break;
                    case 8:
                        intervalAddition = 4; // or 2?
                        break;
                    case 9:
                        intervalAddition = 3;
                        break;
                    case 10:
                        intervalAddition = 2;
                        break;
                    case 11:
                        intervalAddition = 1;
                        break;
                }
            }
            
            if (!majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 4;
                        break;
                    case 1:
                        intervalAddition = 3;
                        break;
                    case 2:
                        intervalAddition = 2;
                        break;
                    case 3:
                        intervalAddition = 1;
                        break;
                    case 4:
                        intervalAddition = 5;
                        break;
                    case 5:
                        intervalAddition = 4;
                        break;
                    case 6:
                        intervalAddition = 3;
                        break;
                    case 7:
                        intervalAddition = 2; // or 2?
                        break;
                    case 8:
                        intervalAddition = 1; // or 2?
                        break;
                    case 9:
                        intervalAddition = 3;
                        break;
                    case 10:
                        intervalAddition = 2;
                        break;
                    case 11:
                        intervalAddition = 1;
                        break;
                }
            }
            break;
        case 4:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 7;
                        break;
                    case 1:
                        intervalAddition = 6;
                        break;
                    case 2:
                        intervalAddition = 5;
                        break;
                    case 3:
                        intervalAddition = 9;
                        break;
                    case 4:
                        intervalAddition = 8;
                        break;
                    case 5:
                        intervalAddition = 7;
                        break;
                    case 7:
                        intervalAddition = 9; // or 2?
                        break;
                    case 9:
                        intervalAddition = 7;
                        break;
                    case 11:
                        intervalAddition = 5;
                        break;
                }
            }
            
            if (!majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = 9;
                        break;
                    case 1:
                        intervalAddition = 8;
                        break;
                    case 2:
                        intervalAddition = 7;
                        break;
                    case 3:
                        intervalAddition = 6;
                        break;
                    case 4:
                        intervalAddition = 8;
                        break;
                    case 5:
                        intervalAddition = 7;
                        break;
                    case 6:
                        intervalAddition = 6;
                        break;
                    case 7:
                        intervalAddition = 5; // or 2?
                        break;
                    case 8:
                        intervalAddition = 4; // or 2?
                        break;
                    case 9:
                        intervalAddition = 7;
                        break;
                    case 10:
                        intervalAddition = 6;
                        break;
                    case 11:
                        intervalAddition = 5;
                        break;
                }
            }
            break;
        case 2:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -5;
                        break;
                    case 1:
                        intervalAddition = -6;
                        break;
                    case 2:
                        intervalAddition = -2;
                        break;
                    case 3:
                        intervalAddition = -3;
                        break;
                    case 4:
                        intervalAddition = -4;
                        break;
                    case 5:
                        intervalAddition = -1;
                        break;
                    case 7:
                        intervalAddition = -3; // or 2?
                        break;
                    case 9:
                        intervalAddition = -2;
                        break;
                    case 11:
                        intervalAddition = -4;
                        break;
                }
            }
            
            if (!majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -3;
                        break;
                    case 1:
                        intervalAddition = -1;
                        break;
                    case 2:
                        intervalAddition = -2;
                        break;
                    case 3:
                        intervalAddition = -3;
                        break;
                    case 4:
                        intervalAddition = -4;
                        break;
                    case 5:
                        intervalAddition = -1;
                        break;
                    case 6:
                        intervalAddition = -2;
                        break;
                    case 7:
                        intervalAddition = -3; // or 2?
                        break;
                    case 8:
                        intervalAddition = -4; // or 2?
                        break;
                    case 9:
                        intervalAddition = -5;
                        break;
                    case 10:
                        intervalAddition = -1;
                        break;
                    case 11:
                        intervalAddition = -2;
                        break;
                }
            }
            break;
        case 1:
            if (majorOn)
            {
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -8;
                        break;
                    case 1:
                        intervalAddition = -8;
                        break;
                    case 2:
                        intervalAddition = -7;
                        break;
                    case 3:
                        intervalAddition = -8;
                        break;
                    case 4:
                        intervalAddition = -9;
                        break;
                    case 5:
                        intervalAddition = -5;
                        break;
                    case 7:
                        intervalAddition = -7; // or 2?
                        break;
                    case 9:
                        intervalAddition = -5;
                        break;
                    case 11:
                        intervalAddition = -7;
                        break;
                }
            }
            
            if (!majorOn)
            {
                
                switch(interNote)
                {
                    case 0:
                        intervalAddition = -8;
                        break;
                    case 1:
                        intervalAddition = -4;
                        break;
                    case 2:
                        intervalAddition = -5;
                        break;
                    case 3:
                        intervalAddition = -6;
                        break;
                    case 4:
                        intervalAddition = -7;
                        break;
                    case 5:
                        intervalAddition = -5;
                        break;
                    case 6:
                        intervalAddition = -6;
                        break;
                    case 7:
                        intervalAddition = -7; // or 2?
                        break;
                    case 8:
                        intervalAddition = -8; // or 2?
                        break;
                    case 9:
                        intervalAddition = -9;
                        break;
                    case 10:
                        intervalAddition = -6;
                        break;
                    case 11:
                        intervalAddition = -7;
                        break;
                }
            }
            break;
    }
    
    
    
    return intervalAddition;
    }
