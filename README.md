# schafkopf-base-engine

The goal of this project is to provide an engine for playing Schafkopf. The main purpose of this engine is to build a basis for experiments by providing a TCP interface. This interface can be used by components implementing a player participating in the game, e.g. an interactive UI or some instance of artificial intelligence.
Currently, the engine is only able to connect with players on port 8080 and provides a single game type (Sauspiel). The interface consists of three core events that are propagated to the client, which are identified by the first four bytes of the message:
- "VOTE":
  - provided data: hand cards (16 bytes), open cards (8 bytes, all set to 0xff), index of start player (1 byte), index of Spieler (1 byte, referring to the player having announced a Spiel), currently announced Spiel (2 bytes, 0x0000 in case of none announced)
  - expected response: ignored
- "PLAY":
  - provided data: hand cards (16 bytes, empty slots represented by oxff), open cards (8 bytes), index of the player having placed the first card in total (1 byte), index of Spieler (1 byte, referring to the player having announced a Spiel), the Spiel being played (2 bytes, currently only Sauspiel), cards that may be played (16 bytes, 0xff for empty slots)
  - expected response: index of the card to be played in the possible cards list
- "RSLT":
  - provided data: same as "PLAY" but first byte is added with the number of points achieved by the player's team in the last Stich
  - expected response: 1 arbitrary byte

The project is provided as an Eclipse CDT project and has only been tested on Linux.
