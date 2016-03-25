# Rifle Mod 
Rifle Mod is a server side mod for Alien Swarm. It's initial purpose was to force players to use only rifles. Now it contains a big number of features and modifiers which can change gameplay drastically. Including player reviving, much smarter bots(AI marines), modifiers for alien speed and health, weapon restrictions and much more. See details at https://sites.google.com/site/swarmaddons/server-mods/rifle-mod
The mod works by building a new server.dll file and replacing this file on your Alien Swarm dedicated server or your game. 

# Building
To build server.dll you need to copy libraries from your Alien Swarm SDK to the downloaded source code folder. 
From
C:\Program Files (x86)\Steam\SteamApps\common\alien swarm\sdk_src\lib
to 
C:\Work\riflemod\src\lib
Then you can use Visual Studio 2005 or 2013 to build the project. VS versions between 2005 and 2013 should work too. Note that VS 2015 will not work and give you a bunch of errors. 

# License
All files belong to Valve Corp. It's not clear under which license is Alien Swarm SDK distributed but it's most likely similar to SOURCE 1 SDK LICENSE https://github.com/ValveSoftware/source-sdk-2013/blob/master/LICENSE
