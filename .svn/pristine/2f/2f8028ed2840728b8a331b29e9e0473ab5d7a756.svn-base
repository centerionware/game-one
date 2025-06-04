void inet_player::loginAuthenticate(std::vector<std::string>&in) {
	// database helper run query select username from users where password = password, if rows == 1, true, else false.
	// if true, run login, else send logout, to prompt going back to login_menu state.
	
	size_t unamesize, pwordsize;
	memcpy(&unamesize, in[0].c_str(), sOfT);
	memcpy(&pwordsize, in[0].substr(sOfT, sOfT).c_str(), sOfT);
	
	if(unamesize > 30 || pwordsize > 30) {
		std::string update;
		update += to_value(LoginCommand);
		update += to_value(BadLogin);
		send_text(update, socket);
		deleteMe = true;
		return;
		  
	}
	char *n = new char[unamesize];
	char *p = new char[pwordsize];
	memcpy(n, in[0].substr( (sOfT*2), unamesize).c_str(), unamesize);
	memcpy(p, in[0].substr( (sOfT*2)+unamesize, pwordsize).c_str(), pwordsize);
	
	std::string uname,pword;
	uname.append(n, unamesize);
	pword.append(p, pwordsize);
	
	char *nenc = new char[unamesize*2+1];
	char *penc = new char[pwordsize*2+1];
	unsigned long nencsize = mysql_real_escape_string(&(database_connection.getConn()),nenc, uname.c_str(), uname.size()); 
	unsigned long pencsize = mysql_real_escape_string(&(database_connection.getConn()),penc, pword.c_str(), pword.size());
	std::string query,idquery;
	query.append("select id, LastPosX, LastPosY, LastPosZ,AccountLocked from users where name = \"");
	query.append(nenc,nencsize);
	query.append("\" and password=\"");
	query.append(penc, pencsize);
	query.append("\"");
	
	idquery.append("select id from users where name = \"");
	idquery.append(nenc,nencsize);
	idquery.append("\" and password=\"");
	idquery.append(penc, pencsize);
	idquery.append("\"");
	
	database_connection.runQuery(query);
	admin = false;
	if(database_connection.numrows == 1) {
		MYSQL_ROW& lmrow = database_connection.row();
		unsigned long *lengths = mysql_fetch_lengths(database_connection.result());
		size_t user_id = fromstring<int>(lmrow[0],lengths[0]);
		int last_posx =  fromstring<int>(lmrow[1],lengths[1]);
		int last_posy =  fromstring<int>(lmrow[2],lengths[2]);
		int last_posz =  fromstring<int>(lmrow[3],lengths[3]);
		int account_locked = fromstring<int>(lmrow[4],lengths[4]);
		if(account_locked != 1) {
			std::cout << "lmrow1-3 {" << lmrow[1] << "} {" << lmrow[2] << "} {" << lmrow[3] << std::endl; 
			position.x = last_posx;
			position.y = last_posy;
			position.z = last_posz;
			vec3 npos(last_posx,last_posy,last_posz);
			actual_target_position = npos;
			targetposition = npos;
			std::cout <<npos.print("last_posXYZ") << vec3(position).print("Initial Position") << std::endl;
			user_ids[(inet_player*)(this)] = user_id;
	//		std::string update;
	//		update += to_value(LoginCommand);
	//		update += to_value(GoodLogin);
	//		send_text(update, socket);
			logged_in = true;
			headtext = uname;
			headtext.append(" is a Good Ninja.");	
			name = uname;
			std::cout << "Logged in properly!" << std::endl;
			{
			  std::string update;
			  update += to_value(LoginCommand);
			  update += to_value(GoodLogin);
			  send_text(update, socket); 
			}
			{
				std::string update;
				update += to_value(NetCommand);
				update += to_value(Teleport);
				static int float_size = sizeof(float);
				char sArr[sizeof(unsigned int)];//size_tsize];
				unsigned int s_out = 0;
				memcpy(sArr, &s_out, sizeof(unsigned int));
				update.append(sArr,sizeof(unsigned int));
				char oneArr[float_size];
				memcpy(oneArr, &position.x, float_size);
				update.append(oneArr,float_size);
				memcpy(oneArr, &position.y, float_size);
				update.append(oneArr,float_size);
				memcpy(oneArr, &position.z, float_size);
				update.append(oneArr,float_size);
				update.append(headtext);
				send_text(update, socket); 
			}
			// Check if they are admin now
			std::string adminquery = "select level from Admin where user_id=(";
			adminquery.append(idquery);
			adminquery.append(")");
			database_connection.runQuery(adminquery);
			if(database_connection.numrows == 1) {
				std::string update;
				update += to_value(NetCommand);
				update += to_value(AdminAuth);
				std::string adminlevel;
				MYSQL_ROW& tr = database_connection.row();
				unsigned long *lt = mysql_fetch_lengths(database_connection.result());
				adminlevel.append(tr[0],lt[0]);
				//unsigned int intadminlevel = fromstring<unsigned int>(adminlevel);
				
				update += string_serialize(adminlevel);
				send_text(update, socket);
				admin_level = fromstring<unsigned int>(adminlevel);
				admin = true;
			}
		} else {
			std::cout << "Login failure! Account Locked! (" << uname << ") (" << pword << ")\n" ;
			std::string update;
			update += to_value(LoginCommand);
			update += to_value(BadLogin);
			send_text(update, socket);
			deleteMe = true;
		}
	} else {
		std::cout << "Login failure! (" << uname << ") (" << pword << ")\n" ;
		std::string update;
		update += to_value(LoginCommand);
		update += to_value(BadLogin);
		send_text(update, socket);
		deleteMe = true;
	}
	delete[] nenc;
	delete[] penc;
	delete[] n;
	delete[] p;
}