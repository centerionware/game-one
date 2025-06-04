All that'd be left to do is add to the enum list the to_value GetExampleList to the OLC enum in the OLC_Enum.hpp file, 
then add the proper .hpp's in this dir to the 4 .hpp's in the parent dir at the end (Just like is done for the player editor)
Then finally, the final step, is to open inet-client&&server_create_commands.hpp and add the callback(s) to the command processors for the client and server. It's one small line per callback, all macro'd to be super short. 

The only thing to be really cautious of is naming. Since all the functions in all the modules (Except the GUI portion of the module, it's completely seperate) will get added to inet_player.h, in the order they're defined in, naming collissions could happen. 

A good,clear naming scheme is important.

