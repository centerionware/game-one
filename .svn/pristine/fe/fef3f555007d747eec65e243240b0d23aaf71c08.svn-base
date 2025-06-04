/* This is mostly so I don't forget. Hopefully you may find it useful too. */
----------------quickstart--------------
How it works:
--super short version--
inet_player.h -> Inside of inet_player class, #include "OLC/base_inet.h"
inet.h -> include "OLC/OLC_Enum.hpp"
inet-server_network_callsbacks.hpp -> include "OLC/base_network_server.hpp"
inet-client_network_callbacks.hpp -> include "OLC/base_network_client.hpp"
CState_Testing_createGui.hpp -> include "OLC/base_gui.hpp"

Finish by adding base_inet.h stuff to client & server command processors (../inet-(client|server)_create_commands.hpp)

The meat of the code is put into a subdir. See Example/* for a short example. */
--Remember--
Each new 'module' right now does require each of the 4 hpp's in OLC/ to be edited to include them
and edits of 2 files in the main src/ dir.

--Longer version--
base_gui includes whatever gui modules you define. The entire gui module can be seperated from the main source code.
base_inet is included inside the inet_player structure definition,  #include "yourfolder/yourfile.hpp", and declare functions which will end up on the inet_player structure. Do not define them here, declare them only.
base_network_client&&server both define the functions declared by whatever you included into base_inet.

There are two places in the main tree that must still be edited for all of this to work, 
"src/inet-client_create_commands.hpp" and "src/inet-server_create_commands.hpp" - where the commands get encapsulated into function pointer objects so they can be called easily by the command processor. 
anytime after defining stuff, add the new commands to the create_commands files to get turn on the faucet and watch it (hopefully not) crash everything horribly. 

--------------More Details--------------

base_gui.hpp contains the gui_module struct. All gui elements are wise to inherit from it.
All gui elements require an initialize() function (Ensured to exist via it being pure virtual in the base),
deinitialize() is optional.
Initialize is where they can setup whatever gui elements, and set the event bindings.
All gui elements have access to the local player object, the window manager object, and the window object.

To add a new full gui sheet, first create a subdirectory to contain the pieces. It should contain at least 4 files.
for the GUI, 
for the function names of the functions that handle client & server network message execution
for the server network message execution,
for the client network message execution.

------Example Layout for new element----
Example files:
gui_creation_and_eventcallbacks, server-callbacks, client-callbacks, client-server-callback-function-names

The gui creation and eventcallbacks filename should be self explanitory, as should the others, but just in case:


Gui creation and event callbacks go in gui_creation_and_eventcallbacks.hpp (Typically initiates sending "forms" to server)
Any server side callbacks should go in the server-callbacks.hpp (Database lookups, et al.)
Any client side callbacks should go in the client-callbacks.hpp (Responses from server.)

The fourth file defines function names in a specific format (The format of network function names.)

--------------More Info-------------
To add new network message types, one can either open ../inet.h and add a new entry to the command_type (Around line 90) enum, then add a new enum{} for it (Which can be placed in ./OLC_Enum.hpp)
