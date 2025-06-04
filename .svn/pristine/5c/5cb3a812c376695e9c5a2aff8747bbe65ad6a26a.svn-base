void inet_player::TryRegistration(std::vector<std::string>&in) {
	size_t emailsize, unamesize, pwordsize;
	memcpy(&emailsize, in[0].c_str(), sOfT);
	memcpy(&unamesize, in[0].substr(sOfT, sOfT).c_str(), sOfT);
	memcpy(&pwordsize, in[0].substr(sOfT*2, sOfT).c_str(), sOfT);
	if(emailsize < 7 || emailsize > 30) { // a@a.com = 7 charactors.
		std::string update;
		update += to_value(Register);
		update += to_value(InvalidEmail);
		send_text(update, socket);
		deleteMe = true;
		return;
	}
	if(unamesize < 5 || unamesize > 30) {
		std::string update;
		update += to_value(Register);
		update += to_value(InvalidUsername);
		send_text(update, socket);
		deleteMe = true;
		return;
	}
	if(pwordsize < 5 || pwordsize > 30) {
		std::string update;
		update += to_value(Register);
		update += to_value(InvalidPassword);
		send_text(update, socket);
		deleteMe = true;
		return;
	}
	char *e = new char[emailsize];
	char *n = new char[unamesize];
	char *p = new char[pwordsize];
	memcpy(e, in[0].substr( (sOfT*3), emailsize).c_str(), emailsize);
	memcpy(n, in[0].substr( (sOfT*3)+emailsize, unamesize).c_str(), unamesize);
	memcpy(p, in[0].substr( (sOfT*3)+emailsize+unamesize, pwordsize).c_str(), pwordsize);
	std::cout << "Read email as: " << e << " with size of " << emailsize << std::endl;
	char *eenc = new char[emailsize*2+1];
	char *nenc = new char[unamesize*2+1];
	char *penc = new char[pwordsize*2+1];
	unsigned long eencsize = mysql_real_escape_string(&(database_connection.getConn()),eenc, e, emailsize); 
	unsigned long nencsize = mysql_real_escape_string(&(database_connection.getConn()),nenc, n, unamesize); 
	unsigned long pencsize = mysql_real_escape_string(&(database_connection.getConn()),penc, p, pwordsize);
	// Check if username exists
	std::string query;
	query.append("select id from users where name = \"");
	query.append(nenc,nencsize);
	query.append("\"");
	database_connection.runQuery(query);
	if(database_connection.numrows >= 1) {
		std::string update;
		update += to_value(Register);
		update += to_value(InvalidUsername);
		send_text(update, socket);
		deleteMe = true;
		delete[] e;
		delete[] n;
		delete[] p;
		delete[] eenc;
		delete[] nenc;
		delete[] penc;
		return;
	}
	// Check if email exists
	query = "";
	query.append("select id from users where email = \"");
	query.append(eenc,eencsize);
	query.append("\"");
	database_connection.runQuery(query);
	if(database_connection.numrows >= 1) {
		std::string update;
		update += to_value(Register);
		update += to_value(InvalidEmail);
		send_text(update, socket);
		deleteMe = true;
		delete[] e;
		delete[] n;
		delete[] p;
		delete[] eenc;
		delete[] nenc;
		delete[] penc;
		return;
	}
	//Check usernames against filter list (To Be Added)
	
	//Good login
	query = "";
	query.append("insert into users (name, password, email) values ('");
	query.append(nenc,nencsize);
	query.append("','");
	query.append(penc,pencsize);
	query.append("','");
	query.append(eenc,eencsize);
	query.append("')");
	database_connection.runQuery(query);
	//if(database_connection.numrows >= 1) {
	std::string update;
	update += to_value(Register);
	update += to_value(GoodRegister);
	send_text(update, socket);
	deleteMe = true;
	delete[] e;
	delete[] n;
	delete[] p;
	delete[] eenc;
	delete[] nenc;
	delete[] penc;
	return;
}