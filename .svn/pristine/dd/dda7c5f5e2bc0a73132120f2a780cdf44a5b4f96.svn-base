#define IS_A_SERVER
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "inet.h"
#include "database_utilities.h"
// The server and client file are virtually the same but seperated so it will be easier to expand on seperatly.
#include "CState_MainMenu_Login.h"
#include "server-map.h"
#include "command.h"
/*
namespace heightmap_globals {
extern boost::mutex mut_c;
}
struct mut_c_locker {
  bool locked;
  mut_c_locker() { heightmap_globals::mut_c.lock(); locked = true; }
  ~mut_c_locker() { if(locked) heightmap_globals::mut_c.unlock(); }
  void unlock() { heightmap_globals::mut_c.unlock(); locked = false;}
  void lock() { if(!locked) heightmap_globals::mut_c.lock(); locked = true; }
};
*/
bool is_server = true;
#include "inet-server_chunk_quick_cache.hpp"
#include "inet-server_globals.hpp"
#include "inet-server_network_callbacks.hpp"
#include "inet-server_create_commands.hpp"



#include "inet-server_core_stuff.hpp"
#include "inet-server_changeHeadText.hpp"
#include "inet-server_changePosition.hpp"
#include "inet-server_send_updates.hpp"
#include "inet-server_broadcastNearby.hpp"



#include "inet-server_PlayerFollowing.hpp"
#include "inet-server_check_close_player_chunks.hpp"
#include "inet-server_run_player_server_movements.hpp"
#include "inet-server_getName.hpp"
#include "inet-server_db_retrieve_chunk.hpp"
#include "inet-server_getChunk.hpp"
#include "inet-server_tick_server.hpp"
#include "inet-server_add_in_range.hpp"
#include "inet-server_ensure_not_in_range.hpp"
#include "inet-server_login_queue.hpp"

#include "inet-server_preAuthenticate.hpp"
#include "inet-server_TryRegistration.hpp"
#include "inet-server_clientChunkPush.hpp"

#include "inet-server_loginAuthenticate.hpp"
#include "inet-server_login_queue_receive.hpp"
void Chunk::render_chunk() {

}

int spawn_server_and_pass_control(int MAX_PLAYERS, int PORT, server_functor_base &on_accept, server_functor_base &on_close, server_functor_base &on_recv,server_functor_base &on_full){
	NewHeightmapLoader::hm_instance = new NewHeightmapLoader();// &HM_INSTANCE;
	/* master file descriptor list */
	fd_set master;
	/* temp file descriptor list for select() */
	fd_set read_fds;
	/* server address */
	struct sockaddr_in serveraddr;
	/* client address */
	struct sockaddr_in clientaddr;
	/* maximum file descriptor number */
	int fdmax;
	/* listening socket descriptor */
	int listener;
	/* newly accept()ed socket descriptor */
	int newfd;
	/* buffer for client data */
	char buf[1024];
	int nbytes;
	/* for setsockopt() SO_REUSEADDR, below */
	int yes = 1;
	socklen_t addrlen;
	int i;//, j;
	struct timeval timeout;
	/* clear the master and temp sets */
	FD_ZERO(&master);
	FD_ZERO(&read_fds);
	database_connection.setup("localhost","gameone","gameonedbpassword","GameOne");
	/* get the listener */
	if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Server-socket() error lol!");
		/*just exit lol!*/
		exit(1);
	}
	printf("Server-socket() is OK...\n");
	/*"address already in use" error message */
	if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		perror("Server-setsockopt() error lol!");
		exit(1);
	}
	if( fcntl(listener, F_SETFD, FD_CLOEXEC)  == -1) {
		perror("fnctl close on exec failed\n");
		exit(1);
	}
	printf("Server-setsockopt() is OK...\n");
	 /*************************************************************/
	/* Set socket to be non-blocking.  All of the sockets for    */
	/* the incoming connections will also be non-blocking since  */
	/* they will inherit that state from the listening socket.   */
	/*************************************************************/
	int on = 1;
	on = ioctl(listener, FIONBIO, (char *)&on);
	if (on < 0)
	{
		perror("set socket as nonblocking ioctl() failed");
		close(listener);
		exit(-1);
	}
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;
	/* bind */
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(PORT);
	memset(&(serveraddr.sin_zero), '\0', 8);
	
	if(bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
	{
	    perror("Server-bind() error lol!");
	    exit(1);
	}
	printf("Server-bind() is OK...\n");
	
	/* listen */
	if(listen(listener, 10) == -1)
	{
	    perror("Server-listen() error lol!");
	    exit(1);
	}
	printf("Server-listen() is OK...\n");
	
	/* add the listener to the master set */
	FD_SET(listener, &master);
	/* keep track of the biggest file descriptor */
	fdmax = listener; /* so far, it's this one*/
	Ogre::Timer time_of_ticks;
	Ogre::Timer sql_keepalive_timer;
	sql_keepalive_timer.reset();
	unsigned long last_frame_time = 0;
	Ogre::Timer clear_terrain_timer;
	clear_terrain_timer.reset();
	/* loop */
	for(;;)
	{
		/* copy it */
		read_fds = master;
		
		if(select(fdmax+1, &read_fds, NULL, NULL, &timeout) == -1)
		{
			
			
			perror("Server-select() error lol!");
			exit(1);
		}
		timeout.tv_usec=100000;
		timeout.tv_sec=0;
		run_player_server_movements();
		if(clear_terrain_timer.getMilliseconds() > 25000){ 
			  clear_terrain_not_close_to_players();
			  clear_terrain_timer.reset();
		}
		unsigned long int ttime = time_of_ticks.getMilliseconds();
		tick_server(last_frame_time, ttime);
		last_frame_time = ttime;
		tick_login_queue(master);
		if(sql_keepalive_timer.getMilliseconds() > 27000000) { // 7.5 hours
			sql_keepalive_timer.reset();
			database_connection.query("show databases");
		}
	//	printf("Server-select() is OK...\n");
		
		/*run through the existing connections looking for data to be read*/
		for(i = 0; i <= fdmax; ++i)
		{
			if(FD_ISSET(i, &read_fds))
			{ /* we got one... */
				if(i == listener)
				{
					/* handle new connections */
					addrlen = sizeof(clientaddr);
					if((newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
					{
						perror("Server-accept() error lol!");
					}
					else
					{
						if( fcntl(newfd, F_SETFD, FD_CLOEXEC)  == -1) {
						    perror("fnctl close on exec failed\n");
						  //exit(1);
						}
						if(MAX_PLAYERS==0 || player_count() < MAX_PLAYERS) {
							FD_SET(newfd, &master); /* add to master set */
							if(newfd > fdmax)
							{ /* keep track of the maximum */
							    fdmax = newfd;
							}
							on_accept.Call(newfd);
							printf(": New connection from %s on socket %d\n",  inet_ntoa(clientaddr.sin_addr), newfd); 
						} else {
							on_full.Call(newfd);
							close(newfd);
						}
					}
				}
				else
				{
					/* handle data from a client */
					if((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
					{
						/* got error or connection closed by client */
						if(nbytes == 0)
						/* connection closed */
							printf(": socket %d hung up\n", i);
						
						else
							perror("recv() error lol!");
						
						/* close it... */
						on_close.Call(i);
						close(i);
						/* remove from master set */
						FD_CLR(i, &master);
					} 
					else
					{
						std::string b;
						b.append(buf, nbytes);
						on_recv.Call(i,b,master);
						//std::cout << "Nbytes recieved: " << nbytes << std::endl;
						
					}
				}
			}
		}
		
	}
}