# LibraPatch For Elden Ring: Nightreign
Increases the cap on clones which can be spawned by Everdark Libra, currently to 10 sets (10 in singleplayer, 20 in multiplayer, 30 if you actually use `entityId3`).

This mod does nothing on its own. You will need to also edit the game's scripts, maps, and models to correctly set everything up for spawning.

## Dependencies
[MinHook](https://github.com/Umgak/minhook) (fork of [MinHook](https://github.com/TsudaKageyu/minhook) for personal use)

[Pattern16](github.com/Dasaav-dsv/Pattern16)

## Building
```
git clone https://github.com/Umgak/LibraPatch.git --recurse-submodules
cd LibraPatch
msbuild .\LibraPatch.slnx /p:Configuration=Release
````