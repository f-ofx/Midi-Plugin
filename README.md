# Midi-Plugin
Midi delay/harmoniser plugin

How to use these files. 

Download JUCE: https://juce.com/get-juce/download

Start the projucer, and select basic>plugin. Name and create folder, "TimeStamp". Replace generated files with the files here. 

AmountOfNotes.h does nothing, but is added to show basic idea of the harmoniser. This is probably the better way to create a harmoniser/delay, set events in the future, in add events function. In main process block just check whether it's time to play note, and keep track of own sample counter. (Casues it's own issues) Rather than trying to use PPQ positions from host, which leads to mind numbing spaghetti code.  
