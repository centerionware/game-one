
void inet_player::getExampleSearch(std::vector<std::string>&in){
  if(!admin) {
   std::cout << "Non admin user: " << name << " on socket " << socket << " requested player search list!\n";
   return;
  }
  std::string output;
  output += to_value(OLC);
  output += to_value(GetExampleSearch);
  // now lookup in the database...
  //{
  std::string safe_query = in[0];
  
  if(safe_query.size() == 0) return;
  MySQL_Helper::Query stmt(database_connection);
  std::string dbq;
  bool like = false;
  
  if(safe_query.substr(0,1).compare("?") == 0) {
    like = true;
    safe_query = safe_query.substr(1,safe_query.size()-1);
  }
  if(safe_query.size() == 1 && safe_query.compare("*") == 0){
	  dbq = "select name from users";
	  stmt.prepare(dbq);
  }else if(!like){
	  dbq = "select name from users where name='?'";
	  stmt.prepare(dbq,safe_query);
  }else {
	  dbq = "select name from users where name like '?'";
	  stmt.prepare(dbq,safe_query);
  }
  stmt.run();
  auto  result_rows = stmt.numrows;

  for(auto i=0;i<result_rows;++i) {
      MYSQL_ROW& lmrow = stmt.row();
      unsigned long *lengths = mysql_fetch_lengths(stmt.result()); // Need to try to delete[] this..     
      std::string name;
      name.append(lmrow[0],lengths[0]);
      output.append(string_serialize(name));
  }
  
  send_text(output,socket);
}
//--- End of example left is rest in for reference on select vs insert||update||delete
void inet_player::modifyPlayer(std::vector<std::string>&in){
  std::string &b = in[0];
  if(!admin) {
	  std::cout << "Non admin " << name << " tried to modify a player! " <<std::endl;
	  return;
  } else std::cout << "Admin is modifying a player.\n";
  #define discern(X) std::string X = non_safe_string_deserialize(b);

  discern(id)
  discern(name)
  discern(email)
  discern(LastPosX)
  discern(LastPosY)
  discern(LastPosZ)
  discern(AdminLevel)
  std::cout << id << " " << name << " " << email << " " << AdminLevel << "\n";
  
  {std::string qry = "update users set name='?', email='?', LastPosX='?', LastPosY='?', LastPosZ='?'  where id='?'";
    MySQL_Helper::Query mstmt(database_connection);
    mstmt.prepare(qry, name, email, LastPosX, LastPosY, LastPosZ, id);
    mstmt.run();}

  std::string qry2;
  unsigned int admnlvl = fromstring<unsigned int>(AdminLevel);
  MySQL_Helper::Query stmt(database_connection);
  if(admnlvl == 0) {
   qry2 = "delete from Admin where user_id='?'"; 
   stmt.prepare(qry2,id);
   stmt.run();
  } else {
      {
	qry2 = "select Level from Admin where user_id='?'";
	MySQL_Helper::Query substmt(database_connection);
	substmt.prepare(qry2, id);
	substmt.run();
	
	if(substmt.numrows==0) {
	  qry2 = "insert into Admin (user_id,Level) values('?','?')";
	  stmt.prepare(qry2,id,AdminLevel);
	} else {
	  qry2 = "update Admin set Level='?' where user_id='?'";
	  stmt.prepare(qry2,AdminLevel,id);
	}
      }
      stmt.run();
  }
}
void inet_player::deletePlayer(std::vector<std::string>&in){
std::string &b = in[0];
  #define discern(X) std::string X = non_safe_string_deserialize(b);

  discern(id)
  if(!admin) {
	  std::cout << "Non admin " << name << " tried to delete player("<<id<<")! " <<std::endl;
	  return;
  } else std::cout << "Admin is deleting a player("<<id<<").\n";
  std::string qry = "delete from users where id='?'";
  MySQL_Helper::Query stmt(database_connection);
  stmt.prepare(qry, id);
  stmt.run();
  
}
void inet_player::lockPlayer(std::vector<std::string>&in){
  std::string &b = in[0];
    #define discern(X) std::string X = non_safe_string_deserialize(b);

  discern(id)
  if(!admin) {
	  std::cout << "Non admin " << name << " tried to lock player("<<id<<")! " <<std::endl;
	  return;
  } else std::cout << "Admin is locking a player("<<id<<").\n";
  std::string qry = "update users set AccountLocked = 1-AccountLocked where id='?'";
  MySQL_Helper::Query stmt(database_connection);
  stmt.prepare(qry, id);
  stmt.run();
}
void inet_player::getPlayerDetails(std::vector<std::string>&in){
  if(!admin) {
    std::cout << "Non admin user: " << name << " on socket " << socket << " requested player search list!\n";
    return;
  }
  std::string output;
  output += to_value(OLC);
  output += to_value(GetPlayerDetails);
  
  std::string qry =  "select id,name,email,LastPosX,LastPosY,LastPosZ,AccountLocked from users where name='?'";
  MySQL_Helper::Query stmt(database_connection);
  stmt.prepare(qry, in[0]);
  stmt.run();
  //std::string ffsfufufu = dbq.str();
  database_connection.query(dbq.str());

  if(stmt.numrows != 1) {
    std::cout << "Search for player name " << safe_query << " found no result_rows!\n";
    return; 
  }
#define streq(X,Y) std::string X; X.append(lmrow[Y],lengths[Y]); output.append(string_serialize(X)); 
  {
    MYSQL_ROW& lmrow = stmt.row();
    unsigned long *lengths = stmt.lengths();
    streq(id,0)
    streq(name,1)
    streq(email,2)
    streq(LastPosX,3)
    streq(LastPosY,4)
    streq(LastPosZ,5)
    streq(Locked, 6)
   
    
   stmt.prepare(qry, id);
    
  }
  stmt.run();
  if(stmt.numrows == 1) {
    MYSQL_ROW& lmrow = stmt.row();
    unsigned long* lengths = stmt.lengths();
    streq(Level, 0);
  } else {
    std::string Level;
    Level.append(tostring<unsigned int>(0));
    output.append(string_serialize(Level));
  }
  send_text(output,socket);
}