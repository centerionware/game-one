
For client updating to be reliable, we may wish to statically link libraries into the release versions we distribute.
Or include the "dynamic link libraries" with the updates, if the versions have changed from what the client already has.



The server map loads the map.
The clients get the map info from the server.



The client first screen should have configuration, login, and new account buttons only.
Login should save every used user name on that system only, and display them nicely as avatars

The basic packet definition from client to server and server to client is
BYTE[4] packetsize;
BYTE[4] code;

Depending on the code the remainder of the packet will be treated differently.
The BYTE[4] is used to standardize different architectures. We will always use 32-bit int's, which are always 4 bytes long.

The different code numbers are:
0 = logout
1 = login
2 = register
3 = movement
4 = option change // set run on/off, set crouch on/off
5 = emotenimation // activate a sequence and animation for your charactor (like wave hi, wave by, smile, dance, whatever the designers put in for that model), also may initiate 'attack' sequences 
6 = map update // The server will only ever send this to clients
7 = admin login // The server has detected the user logged in is an admin and sends this packet to the client, to indicate this user is an admin, and adopt theinterface accordingly.
8 = admin command // If the server has not sent admin login to the client, ban any client that sends this. They are trying to cheat.
9 = client info update // Update information about the client. Store on server linked to their user account.
10 = client purchase gold request // Client purchased non-regular gold (For real money) to buy elite items
11 = buy_item
12 = sell_item
13 = pickup_item
14 = refresh_stats
15 = list_inventory
code 0 (logout):
	nothing should follow this command. client can send to server, server can send to client.
	if the server sends to the client, the client should quit, saying an admin has kicked you off
	Unless
code 1 (login):
	initiate from client to server, always followed by username and encrypted password.
	BYTE[24] username;
	BYTE[24] password;
	BYTE[4] client_ver;

	server tests encrypted password against it's copy, if match, send back to client with
	a single byte following 
	BYTE[1] login_state;
	if login_state = 0, login is successful, server will quickly initiate map update for this client. client should wait for mapupdate to finish.
	if login_state = 1, bad password, try again
	if login_state = 2, bad username, try again and or add option on client to go to register
	
code 2 (register):
	BYTE[24] username;
	BYTE[24] password;
	BYTE[4] client_ver;

	Verify password length & email address on client side quickly, possibly with a regex for email.
	Bad email address will occurr if the email address submitted does not exist. (Is it easy to verify?)
	We could use systems like bb registration with activation links?
	Should we require users to 

	almost exactly like login, except includes
	BYTE[24] email_address
	
	server returns 
	BYTE[1] register_state;
	server returns 0 on success and will initiate mapupdate for this client
	1 on username exists
	2 on email already registered
	3 Bad email address
	4 on password to short
code 3 (movement):
	BYTE[4] x
	BYTE[4] y
	if sent by server, include
		BYTE[8] object_id // users will have a unique object_id, and so will everything that can move. Use 64-bit int
	if sent by client server will replicate to other nearby and inbetween clients including the unique object_id for the player
	If recieved by server on client, begin to move object_id to x,y.

code 4 (option change):
	byte[4] option_id
	Most options will have:
	byte[4] option_value
	But some may be longer. Use the size of sizeof(code)+sizeof(packetsize)+sizeof(option_id) - packetsize to determine option_value's length. 
	sent by client to change optional values.
	packetsize should have a maximum for every type of option_id
	some options like "self description" can be long
	some options like "player kill" or "hardcore mode" should only ever be 1 or 0
	The server must ensure boundries for option types are not broken, and can assume it's under attack if they are.
code 5 (emotenimation):
	byte[4] emoteid
	byte[8] target_object_id
	if sent by server follows with
	byte[8] initaiator_object_id
	client sends to server, server replicates to nearby clients appending the initial clients object_id
	server does not duplicate back to initial client
	if recieved by server, .. orient initiator id twoard target id, and  play animation emoteid on initiator
code 6 (map update):
	if client_ver is not the newest, initiate a binary download, and download the newest version.	
	This will update a LOT of details, and is not suitable for small updates in real time to the game.

code 7 (admin login):
	sent by server to client only. contains no arguments.
	Changes the client screen to an admin interface
code 8 (admin command):
	there will be a lot of admin commands, like, ban, place, rezone, spawn, spawnarea
	There should be a fairly simple interface, and the commands and their options will basically be controlled by their interface.
	Let's try to keep it all backward compatible, but we won't really need to.
code 9 (client info update):
	extremely similar to option change, in fact, maybe option change should be used and this not at all. 
code 10 (client purchase gold request):
	// Don't know how this should be done. Website with ecommerce? 
	// If website, we could integrate QT and create a window to launch the proper page and set the proper information
	// QT? Hrmf. Maybe just build http request using info from client, and do manual http response parsing. not all that hard.
	// Use ecommerce software at the backend, to ease implimentation. share database with game.
code 11 (buy item):
	// buy an item from a nearby shop
	// if sent by the server, the objectis taken from the client, then the server sends 'pickup item' 'gold' 'amount' (for example)
	// the server might initiate this for 'quest rewards'.
	// if sent by the server, the client will send back 'sell item'.
	// the item_id in the case of being sent by the server is the global id number for the item in question ('created' by the database)
	byte[8] shop_object_id
	byte[4] item_id // the number of the item in the list at the shop 
code 12 (sell item):
	// sell an item to the shop
	// initiated by client always. The server will make the sale, remove the item from the players inventory server side (client is responsible client side)
	// Then add the item to the inventory of the shop server side.
	byte[8] shop_object_id
	byte[4] item_id // the inventory index number the item is in.

code 13 (pickup item)
code 14 (refresh stats)
code 15 (list inventory)
	client to server:
	byte[8] shop_object_id
	server response to client:
	byte[4] list_size
	byte[ list_size ][2] list;
		at [x][0] the global item id number
		at [x][1] the number of items of that type at the shop
	
